#define USE_STM3210B_EVAL

#include "stm32f10x.h"
#include "stmTemp.h"
#include "usart.h"
#include "stdio.h"

#define uint32 unsigned int



volatile uint32 pulse_width = 0;
volatile uint32	direction = 0;
 
void delay_ms(uint16_t ms)
{
	uint32_t i, j;
	j = ms * 19200; // j = ms / 1000.0 * 48000000 / 2.5;  
	for (i=0; i<j; i++) {
	}
} 


void ledinit()
{
	GPIO_InitTypeDef GPIO_InitStructure;
	RCC_APB2PeriphClockCmd( RCC_APB2Periph_GPIOB , ENABLE); 						 					 
	GPIO_InitStructure.GPIO_Pin =  GPIO_Pin_12;
	GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_Out_PP; 
	GPIO_Init(GPIOB, &GPIO_InitStructure);
	GPIO_SetBits(GPIOB , GPIO_Pin_12);
	
}



int main()                                                                          
{   
 

    short temp;
	  unsigned char a[4];
	  unsigned char b[10];
    uint8_t data[2];
	
    usart1_init();
    
    User_Adc_Init();
    while(1)
    {
        temp = Get_Temprate();    //得到温度值
			  data[0] = temp/100;
        data[1] = temp%100;
			
			  DecToChar(data,a,2);

				sprintf(b,"%c%c.%c%cC\n",a[0],a[1],a[2],a[3]);
			
        usart_send(USART1,b);
			

			
        delay_ms(550);
    }
		
		
		

}

