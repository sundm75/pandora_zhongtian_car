#include <rtthread.h>
#include <rtdevice.h>
#include <board.h>

#include "drv_gpio.h"
#include "motor.h"
#include "pwm.h"


static void motor_dir(int a, int b, int c, int d)
{
    rt_pin_write(MOTORA_DIR, !a);
    rt_pin_write(MOTORB_DIR, !b);
    rt_pin_write(MOTORC_DIR, !c);
    rt_pin_write(MOTORD_DIR, d);
  
}

void motor_control(int pwma, int pwmb, int pwmc, int pwmd)
{
  int a,b,c,d;
  a =  pwma>0 ? 1 : 0;
  b =  pwmb>0 ? 1 : 0;
  c =  pwmc>0 ? 1 : 0;
  d =  pwmd>0 ? 1 : 0;
  motor_dir(a, b, c, d);
  
  a =  pwma>0 ? pwma : (-1 * pwma);
  b =  pwmb>0 ? pwmb : (-1 * pwmb);
  c =  pwmc>0 ? pwmc : (-1 * pwmc);
  d =  pwmd>0 ? pwmd : (-1 * pwmd);  
  TIM_SetTIM4Compare1(a);
  TIM_SetTIM4Compare2(b);
  TIM_SetTIM4Compare3(c);
  TIM_SetTIM4Compare4(d);
}

void function_up             (int speed)
{
  motor_control(speed, speed, speed, speed);
}

void function_left           (int speed)
{
  motor_control(-speed, speed, speed, -speed);
}

void function_down           (int speed)
{
  motor_control(-speed, -speed, -speed, -speed);
}

void function_right          (int speed)
{
  motor_control(speed, -speed, -speed, speed);
}

void function_left_up        (int speed)
{
  motor_control(0, speed, speed, 0);
}

void function_right_up       (int speed)
{
  motor_control(speed, 0, 0, speed);
}

void function_left_down      (int speed)
{
  motor_control( -speed, 0, 0,-speed);
}

void function_right_down     (int speed)
{
  motor_control(0, -speed, -speed, 0);
}


void function_stop1          (void)
{
  motor_control(0, 0, 0, 0);
}

void function_stop2          (void)
{
  motor_control(0, 0, 0, 0);
}

void function_stop3          (void)
{
  motor_control(0, 0, 0, 0);
}

void function_stop4          (void)
{
  motor_control(0, 0, 0, 0);
}

void function_turn_left_up   (int speed)
{
  motor_control(0, 0, -speed, speed);
}

void function_turn_left_mid  (int speed)
{
  motor_control(-speed, speed, -speed, speed);
}

void function_turn_left_down (int speed)
{
  motor_control(0, speed, 0, speed);
}

void function_turn_left      (int speed)
{
  motor_control(-speed, speed, 0, 0);
}

void function_turn_right_up  (int speed)
{
  motor_control(0, 0, speed, -speed);
}

void function_turn_right_mid (int speed)
{
  motor_control(speed, -speed, speed, -speed);
}

void function_turn_right_down(int speed)
{
  motor_control(speed, 0, speed, 0);
}

void function_turn_right     (int speed)
{
  motor_control(speed, -speed, 0, 0);
}

