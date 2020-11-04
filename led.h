// LED1 PB12
// LED2 PB13

#ifndef __LED_H
#define	__LED_H

#include "stm32f10x.h"

#define LED1_PIN		GPIO_Pin_12
#define LED1_PORT		GPIOB
#define LED1_RCC		RCC_APB2Periph_GPIOB

void led_init(void);
void led1_on(void);
void led1_off(void);



#endif
