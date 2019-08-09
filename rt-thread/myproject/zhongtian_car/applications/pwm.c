#include "pwm.h"

TIM_HandleTypeDef TIM4_Handler;         //定时器4PWM句柄
TIM_OC_InitTypeDef TIM4_CHnHandler;	    //定时器4句柄


/**
 * @brief	TIM4 PWM输出初始化函数
 *
 * @param   arr		自动重装值
 * @param   psc		时钟预分频数
 *
 * @return  void
 */
void PWM_Init(u16 arr, u16 psc)
{
    TIM4_Handler.Instance = TIM4;          				//定时器4
    TIM4_Handler.Init.Prescaler = psc;     				//定时器分频
    TIM4_Handler.Init.CounterMode = TIM_COUNTERMODE_UP; //向上计数模式
    TIM4_Handler.Init.Period = arr;        				//自动重装载值
    TIM4_Handler.Init.ClockDivision = TIM_CLOCKDIVISION_DIV1;
    HAL_TIM_PWM_Init(&TIM4_Handler);       				//初始化PWM

    TIM4_CHnHandler.OCMode = TIM_OCMODE_PWM1; 			//模式选择PWM1
    TIM4_CHnHandler.Pulse = arr / 2;       				//设置比较值,此值用来确定占空比，默认比较值为自动重装载值的一半,即占空比为50%
    TIM4_CHnHandler.OCPolarity = TIM_OCPOLARITY_HIGH; 	//输出比较极性为低

    HAL_TIM_PWM_ConfigChannel(&TIM4_Handler, &TIM4_CHnHandler, TIM_CHANNEL_1); //配置TIM4通道1
    HAL_TIM_PWM_Start(&TIM4_Handler, TIM_CHANNEL_1); 	//开启PWM通道1

    HAL_TIM_PWM_ConfigChannel(&TIM4_Handler, &TIM4_CHnHandler, TIM_CHANNEL_2); //配置TIM4通道2
    HAL_TIM_PWM_Start(&TIM4_Handler, TIM_CHANNEL_2); 	//开启PWM通道2

    HAL_TIM_PWM_ConfigChannel(&TIM4_Handler, &TIM4_CHnHandler, TIM_CHANNEL_3); //配置TIM4通道3
    HAL_TIM_PWM_Start(&TIM4_Handler, TIM_CHANNEL_3); 	//开启PWM通道3

    HAL_TIM_PWM_ConfigChannel(&TIM4_Handler, &TIM4_CHnHandler, TIM_CHANNEL_4); //配置TIM4通道4
    HAL_TIM_PWM_Start(&TIM4_Handler, TIM_CHANNEL_4); 	//开启PWM通道4
}


/**
 * @brief	定时器底层驱动，时钟使能，引脚配置，此函数会被HAL_TIM_PWM_Init()调用
 *
 * @param   htim		定时器句柄
 *
 * @return  void
 */
void HAL_TIM_PWM_MspInit(TIM_HandleTypeDef *htim)
{
    GPIO_InitTypeDef GPIO_Initure;
    __HAL_RCC_TIM4_CLK_ENABLE();				//使能定时器4
    __HAL_RCC_GPIOD_CLK_ENABLE();				//开启GPIOD时钟

    GPIO_Initure.Pin = GPIO_PIN_12 | GPIO_PIN_13| GPIO_PIN_14| GPIO_PIN_15; //PD12 D13 D14 D15
    GPIO_Initure.Mode = GPIO_MODE_AF_PP;  		//复用推挽输出
    GPIO_Initure.Pull = GPIO_PULLUP;        	//上拉
    GPIO_Initure.Speed = GPIO_SPEED_HIGH;   	//高速
    GPIO_Initure.Alternate = GPIO_AF2_TIM4;		//PD12-15 复用为TIM4_CH1.CH2
    HAL_GPIO_Init(GPIOD, &GPIO_Initure);
}


/**
 * @brief	设置TIM4通道1的占空比
 *
 * @param   compare		比较值
 *
 * @return  void
 */
void TIM_SetTIM4Compare1(u32 compare)
{
    TIM4->CCR1 = compare;
}

/**
 * @brief	设置TIM4通道2的占空比
 *
 * @param   compare		比较值
 *
 * @return  void
 */
void TIM_SetTIM4Compare2(u32 compare)
{
    TIM4->CCR2 = compare;
}

void TIM_SetTIM4Compare3(u32 compare)
{
    TIM4->CCR3 = compare;
}
void TIM_SetTIM4Compare4(u32 compare)
{
    TIM4->CCR4 = compare;
}

