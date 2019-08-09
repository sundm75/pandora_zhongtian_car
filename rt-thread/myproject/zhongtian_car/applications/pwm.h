#ifndef __PWM_H
#define __PWM_H
#include "stm32l4xx.h"
#include "sys.h"

void PWM_Init(u16 arr, u16 psc);
void TIM_SetTIM4Compare1(u32 compare);
void TIM_SetTIM4Compare2(u32 compare);
void TIM_SetTIM4Compare3(u32 compare);
void TIM_SetTIM4Compare4(u32 compare);

#endif

