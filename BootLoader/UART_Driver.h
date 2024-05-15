/***************************************
 * Module Name : UART_Driver.h
 *  Desc : Macros and prototypes for
 *  Created on: May 15, 2024
 *      Author: omar
 ****************************************/

#ifndef UART_DRIVER_H_
#define UART_DRIVER_H_
/*******************************************
 * Macros
 ******************************************/
#define UART0_BaudRate 9600
/*******************************************
 * Global Functions
 *******************************************/

void UART0_Init (void);
void UART_Send_Str (uint8_t * , uint32_t );
void UART_Rec_Str (uint8_t * , uint32_t );
#endif /* UART_DRIVER_H_ */
