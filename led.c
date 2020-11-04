#include "stm32f10x.h"
#include "led.h"

void led_init(void)
{
	GPIO_InitTypeDef GPIO_InitStruct;
	
	RCC_APB2PeriphClockCmd(LED1_RCC, ENABLE);
  GPIO_InitStruct.GPIO_Pin = LED1_PIN;
  GPIO_InitStruct.GPIO_Mode = GPIO_Mode_Out_PP;
  GPIO_InitStruct.GPIO_Speed = GPIO_Speed_50MHz;
  GPIO_Init(LED1_PORT, &GPIO_InitStruct);
	GPIO_SetBits(LED1_PORT, LED1_PIN);

	
	
	
}

void led1_on(void)
{
	GPIO_SetBits(LED1_PORT, LED1_PIN);
}

void led1_off(void)
{
	GPIO_ResetBits(LED1_PORT, LED1_PIN);
}


