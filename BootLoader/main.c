#include <stdint.h>
#include <stdbool.h>
#include "inc/hw_memmap.h"
#include "inc/hw_types.h"
#include "driverlib/sysctl.h"
#include "driverlib/gpio.h"
#include "driverlib/pin_map.h"
#include "driverlib/uart.h"
#include "UART_Driver.h"
#include "Bootloader.h"


void Clock_Init (void){
    SysCtlClockSet(SYSCTL_SYSDIV_2_5 | SYSCTL_USE_PLL | SYSCTL_OSC_MAIN | SYSCTL_XTAL_16MHZ);
}


int main(void)
{
    Clock_Init ();
    BL_Debbuging_Init();
    BL_Fetch_Init();


    //    uint32_t Str [] = {0};
    //
    //    UART_Rec_Str(Str, UART0_BASE);
    //    UART_Send_Str(Str, UART0_BASE);


    while (1)
    {
        BL_Fetch_Command();



    }
}
