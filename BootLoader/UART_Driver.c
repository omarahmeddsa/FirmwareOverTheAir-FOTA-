/* Module Name : UART_Driver.c
 *  Desc : Init UART and Recive and transmit
 *  Created on: May 15, 2024
 *      Author: omar
 ****************************************/

#include "UART_Driver.h"


void UART0_Init (void ){

    // Enable UART0 and GPIO port A
    SysCtlPeripheralEnable(SYSCTL_PERIPH_UART0);
    SysCtlPeripheralEnable(SYSCTL_PERIPH_GPIOA);

    // Configure GPIO pins for UART0
    GPIOPinConfigure(GPIO_PA0_U0RX);
    GPIOPinConfigure(GPIO_PA1_U0TX);
    GPIOPinTypeUART(GPIO_PORTA_BASE, GPIO_PIN_0 | GPIO_PIN_1);

    // Configure UART0 with a baud rate of 115200, 8 data bits, 1 stop bit, no parity
    UARTConfigSetExpClk(UART0_BASE, SysCtlClockGet(), UART0_BaudRate,
                        (UART_CONFIG_WLEN_8 | UART_CONFIG_STOP_ONE |
                                UART_CONFIG_PAR_NONE));

    // Enable UART0
    UARTEnable(UART0_BASE);

}

void UART_Send_Str (uint8_t * Str, uint32_t Copy_UARTBase){

    uint32_t Index = 0 ;

    while (Str [Index] != '\0'){

        UARTCharPut(Copy_UARTBase, Str [Index]);
        Index++;
    }
}
void UART_Rec_Str (uint8_t * Str, uint32_t Copy_UARTBase){

    uint32_t Index = 0 ;
    Str [Index] = UARTCharGet(Copy_UARTBase);
    while (Str [Index] != '#'){
        Index++;
        Str [Index] =  UARTCharGet(Copy_UARTBase);

    }

    Str [Index] = '\0';
}

void UART_Rec_Sring_Size (uint8_t * Str, uint32_t Copy_UARTBase ){
    uint32_t Index = 0 ;

    // Recive the Data length in the first Element of the array
    Str [Index] = UARTCharGet(Copy_UARTBase);

    // loop till the data length
    while (Index < Str [Index]){
        Index++ ;
        Str [Index] = UARTCharGet(Copy_UARTBase);
    }

}
