#include <stdint.h>
#include <stdbool.h>
#include "inc/hw_memmap.h"
#include "inc/hw_types.h"
#include "driverlib/sysctl.h"
#include "driverlib/gpio.h"
#include "driverlib/pin_map.h"
#include "driverlib/uart.h"
#include "UART_Driver.h"
int main(void)
{

    UART0_Init();

    uint32_t Str [] = {0};

    UART_Rec_Str(Str, UART0_BASE);
    UART_Send_Str(Str, UART0_BASE);
    while (1)
    {




    }
}
