#ifndef __UART_H
#define	__UART_H

#include "stm32f10x.h"


void usart1_init(void);
void usart_send(USART_TypeDef* USARTx, char *Buffer);


#endif /* __UART_H */
