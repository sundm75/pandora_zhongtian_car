#ifndef  __MOTOR_H
#define  __MOTOR_H

//定义按键值


//car
#define   MOTORA_DIR    GET_PIN(B, 10)     // PB10 :  A方向输出
#define   MOTORB_DIR    GET_PIN(B, 11)     // PB11 :  A方向输出
#define   MOTORC_DIR    GET_PIN(B, 12)     // PB12 :  A方向输出
#define   MOTORD_DIR    GET_PIN(C, 4)      // PC4  :  A方向输出



#define up              0x62
#define left            0x22
#define down            0xA8
#define right           0xC2
#define left_up         0xA2
#define right_up        0xE2
#define left_down       0xE0
#define right_down      0x90

#define stop1           0x02
#define stop2           0x98
#define stop3           0x18
#define stop4           0x38

#define turn_left_up    0x68
#define turn_left_mid   0x30
#define turn_left_down  0x10
#define turn_left       0x42

#define turn_right_up   0xB0
#define turn_right_mid  0x7A
#define turn_right_down 0x5A
#define turn_right      0x52

void motor_control(int pwma, int pwmb, int pwmc, int pwmd);

void function_up             (int speed);
void function_left           (int speed);
void function_down           (int speed);
void function_right          (int speed);
void function_left_up        (int speed);
void function_right_up       (int speed);
void function_left_down      (int speed);
void function_right_down     (int speed);
                   
void function_stop1          (void);
void function_stop2          (void);
void function_stop3          (void);
void function_stop4          (void);
                    
void function_turn_left_up   (int speed);
void function_turn_left_mid  (int speed);
void function_turn_left_down (int speed);
void function_turn_left      (int speed);
                    
void function_turn_right_up  (int speed);
void function_turn_right_mid (int speed);
void function_turn_right_down(int speed);
void function_turn_right     (int speed);

#endif