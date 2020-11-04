// USART1_TX -> PB6, USART1_RX -> PB7
// USART2_TX -> PA2, USART2_RX -> PA3

#include "usart.h"
#include "utils.h"
#include <stdarg.h>
#include <stdio.h>
#include "stm32f10x_usart.h"


volatile char StringLoop[10];


// USART1_TX -> Pa9, USART1_RX -> Pa10
// interrupt disabled
void usart1_init(void)
{
	GPIO_InitTypeDef  GPIO_InitStructure;
	USART_InitTypeDef USART_InitStructure;
	NVIC_InitTypeDef NVIC_InitStrue;

	RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOA, ENABLE);
	RCC_APB2PeriphClockCmd(RCC_APB2Periph_USART1, ENABLE );
	
	/*	
	GPIO_PinRemapConfig(GPIO_Remap_USART1,ENABLE);
	|RCC_APB2Periph_AFIO

	//tx
	GPIO_InitStructure.GPIO_Pin = GPIO_Pin_6;
	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_AF_PP;
	GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
	GPIO_Init(GPIOB, &GPIO_InitStructure); 
//rx
	GPIO_InitStructure.GPIO_Pin = GPIO_Pin_7;
	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_IN_FLOATING;
	GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
	GPIO_Init(GPIOB, &GPIO_InitStructure);  
		*/

	

//tx
	GPIO_InitStructure.GPIO_Pin = GPIO_Pin_9;
	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_AF_PP;
	GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
	GPIO_Init(GPIOA, &GPIO_InitStructure); 
//rx
	GPIO_InitStructure.GPIO_Pin = GPIO_Pin_10;
	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_IN_FLOATING;
	GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
	GPIO_Init(GPIOA, &GPIO_InitStructure);  
	
		// ??? ?????
  NVIC_PriorityGroupConfig(NVIC_PriorityGroup_0);
	NVIC_InitStrue.NVIC_IRQChannel=USART1_IRQn;
  NVIC_InitStrue.NVIC_IRQChannelCmd=ENABLE;
	NVIC_InitStrue.NVIC_IRQChannelPreemptionPriority=0;
	NVIC_InitStrue.NVIC_IRQChannelSubPriority=1;
	NVIC_Init(&NVIC_InitStrue);

	
	USART_InitStructure.USART_BaudRate = 115200;  // baud rate
	USART_InitStructure.USART_WordLength = USART_WordLength_8b;  // data bits
	USART_InitStructure.USART_StopBits = USART_StopBits_1;  // stop bit
	USART_InitStructure.USART_Parity = USART_Parity_No;  // no parity check
	USART_InitStructure.USART_HardwareFlowControl = USART_HardwareFlowControl_None;  // no flow control
	USART_InitStructure.USART_Mode = USART_Mode_Rx | USART_Mode_Tx;  // rx and tx
	USART_Init(USART1, &USART_InitStructure);

	
	
	
	USART_ITConfig(USART1,USART_IT_RXNE,ENABLE);//??????
	

	USART_Cmd(USART1, ENABLE);  // enable
	
}

// USART2_TX -> PA2, USART2_RX -> PA3
// interrupt enabled


void usart_send(USART_TypeDef* USARTx, char *Buffer)
{
	uint8_t i = 0;

	while (Buffer[i] != '\0') {   
		// Send one byte
		USART_SendData(USARTx, Buffer[i]);
		// Loop until USART1 DR register is empty
		while(USART_GetFlagStatus(USARTx, USART_FLAG_TXE) == RESET) {}
		i++;
	}
}


void USART1_IRQHandler(void)
{
		static int rx_index;
    uint16_t ch;
    
    if(USART_GetITStatus(USART1, USART_IT_RXNE) != RESET)
    {     
			
			ch = USART_ReceiveData(USART1); 
       //  StringLoop[rx_index++] = USART_ReceiveData(USART1);  
   
  //  if (rx_index >= (sizeof(StringLoop) - 1))  
    //  rx_index = 0; 
		
		 //USART_SendData(USART1,ch);   // ??2 ??
			//while(USART_GetFlagStatus(USART1, USART_FLAG_TXE) == RESET) {}
		 //USART_SendData(USART1,'g');   // ??2 ??
	//	USART_ClearFlag(USART1,USART_IT_RXNE);   // ??2 ??
		//USART_ClearITPendingBit(USART1,USART_IT_RXNE); 
  }


}


