/*
 * Copyright (c) 2006-2018, RT-Thread Development Team
 *
 * SPDX-License-Identifier: Apache-2.0
 *
 * Change Logs:
 * Date           Author       Notes
 * 2018-08-16     armink       first implementation
 */

#include <rtthread.h>
#include <rtdevice.h>
#include <board.h>
#include "infrared.h"

#define DBG_SECTION_NAME "main"
#define DBG_LEVEL DBG_LOG
#include <rtdbg.h>

#include "pwm.h"
#include "mymotor.h"

#include <drv_lcd.h>
#include <rttlogo.h>

rt_uint16_t repeated_times = 0;

rt_int16_t key_scan(void)
{
    if (rt_pin_read(PIN_KEY0) == PIN_LOW)
    {
        rt_thread_mdelay(50);
        if (rt_pin_read(PIN_KEY0) == PIN_LOW)
        {
            return PIN_KEY0;
        }
    }
    return -RT_ERROR;
}

void motor_init(void)
{
    /* 设置电机 dir 引脚为输出模式 */
    rt_pin_mode(MOTORA_DIR, PIN_MODE_OUTPUT);
    rt_pin_mode(MOTORB_DIR, PIN_MODE_OUTPUT);
    rt_pin_mode(MOTORC_DIR, PIN_MODE_OUTPUT);
    rt_pin_mode(MOTORD_DIR, PIN_MODE_OUTPUT);
    
    rt_pin_write(MOTORA_DIR, PIN_LOW);
    rt_pin_write(MOTORB_DIR, PIN_LOW);
    rt_pin_write(MOTORC_DIR, PIN_LOW);
    rt_pin_write(MOTORD_DIR, PIN_HIGH);
    
    /* 设置电机 pwm 引脚为输出 tim4 (ch0-ch3) pwm 输出模式 */
    PWM_Init(1000 - 1, 80 - 1);	//TIM4时钟频率 80M/80=1M   计数频率1M/1000=1KHZ     默认占空比为50%
    function_up(0);
}

void lcd_dis(void)
{
     /* 清屏 */
    lcd_clear(WHITE);
    /* 显示 RT-Thread logo */
    lcd_show_image(0, 0, 240, 69, image_rttlogo);
    
    /* 设置背景色和前景色 */
    lcd_set_color(WHITE, BLACK);

    /* 在 LCD 上显示字符 */
    lcd_show_string(10, 69, 16, "Hello, RT-Thread!");
    lcd_show_string(10, 69+16, 24, "RT-Thread");
    lcd_set_color(WHITE, BRED);
    lcd_show_string(10, 69+16+24, 32, "RT-Thread");
    
    /* 在 LCD 上画线 */
    lcd_set_color(WHITE, BLUE);
    lcd_draw_line(0, 69+16+24+32, 240, 69+16+24+32);
    
    /* 在 LCD 上画一个同心圆 */
    lcd_draw_point(120, 194);
    for (int i = 0; i < 46; i += 4)
    {
        lcd_draw_circle(120, 194, i);
    }
}

/*定时器检查红外接收 按键是否松开*/


/*红外接收线程 */

void infrared_thread_entry(void* parameter)
{ 
    int speed = 500;
    rt_int16_t key,infrared_key;
    struct infrared_decoder_data infrared_data;

    
    /* 选择 NEC 解码器 */
    ir_select_decoder("nec");

    /* 设置按键引脚为输入模式 */
    rt_pin_mode(PIN_KEY0, PIN_MODE_INPUT);

    /* 设置 RGB 引脚为输出模式*/
    rt_pin_mode(PIN_LED_R, PIN_MODE_OUTPUT);
    rt_pin_mode(PIN_LED_B, PIN_MODE_OUTPUT);

    rt_pin_write(PIN_LED_R, PIN_HIGH);
    rt_pin_write(PIN_LED_B, PIN_HIGH);
    
    /*电机初始化*/
    motor_init();

    while (1)
    {
        /* 按键扫描 */
        key = key_scan();
        if(key == PIN_KEY0)
        {
            /* 有按键按下，蓝灯亮起 */
            rt_pin_write(PIN_LED_B, PIN_LOW);
            infrared_data.data.nec.repeat = 0;
            /* 发送红外数据 */
            infrared_write("nec",&infrared_data);
            rt_thread_mdelay(200);
            LOG_I("SEND    OK: addr:0x%02X key:0x%02X repeat:%d",
                infrared_data.data.nec.addr, infrared_data.data.nec.key, infrared_data.data.nec.repeat);
        }
        else if(infrared_read("nec",&infrared_data) == RT_EOK)  
        {
            /* 读取到红外数据，红灯亮起 */
            rt_pin_write(PIN_LED_R, PIN_LOW);
            LOG_I("RECEIVE OK: addr:0x%02X key:0x%02X repeat:%d",
                infrared_data.data.nec.addr, infrared_data.data.nec.key, infrared_data.data.nec.repeat);
            repeated_times++;
            if (infrared_key != infrared_data.data.nec.key)
            {
              //repeated_times = infrared_data.data.nec.repeat;
              infrared_key = infrared_data.data.nec.key;
              switch (infrared_key)
              {
              case  up:
                function_up(speed);
                lcd_show_string(10, 69+16+24, 32, "up             ");
                break;
              case  left:
                function_left(speed);
                lcd_show_string(10, 69+16+24, 32, "left           ");
                break;
              case  down:
                function_down(speed);
                lcd_show_string(10, 69+16+24, 32, "down           ");
                break;
              case  right:
                function_right(speed);
                lcd_show_string(10, 69+16+24, 32, "right          ");
                break;
                
              case  left_up:
                function_left_up(speed);
                lcd_show_string(10, 69+16+24, 32, "left_up         ");
                break;
              case  right_up:
                function_right_up(speed);
                lcd_show_string(10, 69+16+24, 32, "right_up        ");
                break;
              case  left_down:
                function_left_down(speed);
                lcd_show_string(10, 69+16+24, 32, "left_down        ");
                break;              
              case  right_down:
                function_right_down(speed);
                lcd_show_string(10, 69+16+24, 32, "right_down        ");
                break;
                
              case  turn_left_up:
                function_turn_left_up(speed);
                lcd_show_string(10, 69+16+24, 32, "turn_left_up      ");
                break;
              case  turn_left_mid:
                function_turn_left_mid(speed);
                lcd_show_string(10, 69+16+24, 32, "turn_left_mid     ");
                break;
              case  turn_left_down:
                function_turn_left_down(speed);
                lcd_show_string(10, 69+16+24, 32, "turn_left_down    ");
                break;
              case  turn_left:
                function_turn_left(speed);
                lcd_show_string(10, 69+16+24, 32, "turn_left          ");
                break;
                
              case  turn_right_up:
                function_turn_right_up(speed);
                lcd_show_string(10, 69+16+24, 32, "turn_right_up     ");
                break;
              case  turn_right_mid:
                function_turn_right_mid(speed);
                lcd_show_string(10, 69+16+24, 32, "turn_right_mid     ");
                break;
              case  turn_right_down:
                function_turn_right_down(speed);
                lcd_show_string(10, 69+16+24, 32, "turn_right_down    ");
                break;
              case  turn_right:
                function_turn_right(speed);
                lcd_show_string(10, 69+16+24, 32, "turn_right         ");
                break;
              case  stop1:
              case  stop2:
              case  stop3:
              case  stop4:
                function_stop1();
                lcd_show_string(10, 69+16+24, 32, "stop               ");
                break;
              default:
                break;              
              }
            }
        }
        
        rt_thread_mdelay(1);

        /* 熄灭蓝灯 */
        rt_pin_write(PIN_LED_B, PIN_HIGH);
        /* 熄灭红灯 */
        rt_pin_write(PIN_LED_R, PIN_HIGH);
    }    
}

/* 定时器的控制块 */
static rt_timer_t timer1;

/* 定时器1超时函数 */
static void timeout1(void* parameter)
{
  static rt_uint16_t this_times,stop_times=0;
  if  (this_times < repeated_times)
  {
    this_times = repeated_times;
    stop_times = 0;
  }
  else
  {
    if(stop_times==0)
    {
      LOG_I("stoped \n");
      repeated_times = 0;
      this_times = 0;
      function_stop1();
      stop_times = 1;
    }
  }
}


extern uint8_t Flag_Qian;
extern uint8_t Flag_Hou;
extern uint8_t Flag_Left;
extern uint8_t Flag_Right;
extern uint8_t Flag_sudu; //2为低速挡（默认值）1为高速档
extern struct rt_mailbox mb;

void motor_control_entry(void* parameter)
{
  int speed = 500;
  rt_uint32_t data;
  while(1)
  {
    if(Flag_sudu==1)     speed = 600;  //高速档 
    else if(Flag_sudu==2) speed = 300; //低速挡（默认值）
    
    /* 从邮箱中收取邮件 */
    if (rt_mb_recv(&mb, (rt_ubase_t*)&data, 1000)
            == RT_EOK)
    {
        /* 显示邮箱内容 */
        rt_kprintf((char const*)&data);
        /*控制车辆*/
        switch (data)
        {
        case 'A':function_up(speed);
          break;
        case 'B':function_right_up(speed); 
          break;
        case 'C':function_right(speed); 
          break;
        case 'D':function_right_down(speed);
          break;
        case 'E':function_down(speed); 
          break;
        case 'F':function_left_down(speed);
          break;
        case 'G': function_left(speed);
          break;
        case 'H':function_left_up(speed);   
          break;
        case 'Z':function_stop1();   
          break;
        default:
          break;
        }
    }
    
  }
  
  
}

#define THREAD_PRIORITY         25
#define THREAD_STACK_SIZE       512
#define THREAD_TIMESLICE        5

static rt_thread_t tid1 = RT_NULL;

int main(void)
{
    extern int wifi_init(void);
    //wifi_init();
    
    extern void telnet_server(void);
    //telnet_server();
        
    lcd_dis();
    /*红外接收线程*/
    tid1 = rt_thread_create("thread1",
            infrared_thread_entry, 
            RT_NULL,
            THREAD_STACK_SIZE, THREAD_PRIORITY, THREAD_TIMESLICE); 
    if (tid1 != RT_NULL)
            rt_thread_startup(tid1);
        
      /* 创建定时器1 检测红外接收中的停止*/
      timer1 = rt_timer_create("timer1",  /* 定时器名字是 timer1 */
                                              timeout1, /* 超时时回调的处理函数 */
                                              RT_NULL,  /* 超时函数的入口参数 */
                                              RT_TICK_PER_SECOND/4,       /* 定时长度  */
                                              RT_TIMER_FLAG_PERIODIC); /* 周期性定时器 */
    /* 启动定时器 */
    if (timer1 != RT_NULL) rt_timer_start(timer1); 
    
    /*接收串口数据控制车线程*/    
    extern int test_rtt_uartse(void);    
    test_rtt_uartse();    
    /*串口接收数据控制线程*/
    tid1 = rt_thread_create("thread1",
            motor_control_entry, 
            RT_NULL,
            THREAD_STACK_SIZE, THREAD_PRIORITY, THREAD_TIMESLICE); 
    if (tid1 != RT_NULL)
            rt_thread_startup(tid1);        
    return 0;
}