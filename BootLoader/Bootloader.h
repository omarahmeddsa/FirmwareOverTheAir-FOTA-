/*
 * Bootloader.h
 *
 *  Created on: May 15, 2024
 *      Author: omar
 */

#ifndef BOOTLOADER_H_
#define BOOTLOADER_H_
#include <stdbool.h>
#include <stdint.h>
#include <stdbool.h>
#include "inc/hw_memmap.h"
#include "inc/hw_types.h"
#include "driverlib/sysctl.h"
#include "driverlib/gpio.h"
#include "driverlib/pin_map.h"
#include "driverlib/uart.h"
#include "UART_Driver.h"
#include "driverlib/crc.h"
#include "driverlib/flash.h"
/*************************************
 * Enums
 ************************************/
typedef enum {
    BL_Ok,
    BL_Nok

}BL_ACK;


typedef enum {
    Data_Len,
    DataBytes,
    GET_VER,
    GET_HELP,
    GET_CID,
    GET_RDP_STATUS,
    GO_TO_ADDR,
    FLASH_ERASE,
    MEM_WRITE,
    ED_W_PROTECT,
    MEM_READ,
    READ_SECTOR_STATUS,
    CHANGE_ROP_Level
}BL_Index;

typedef struct
{
    volatile uint32_t CPUID;               // CPUID Base Register
    volatile uint32_t ICSR;                // Interrupt Control and State Register
    volatile uint32_t VTOR;                // Vector Table Offset Register
    volatile uint32_t AIRCR;               // Application Interrupt and Reset Control Register
    volatile uint32_t SCR;                 // System Control Register
    volatile uint32_t CCR;                 // Configuration and Control Register
    volatile uint8_t  SHP[12];             // System Handlers Priority Registers
    volatile uint32_t SHCSR;               // System Handler Control and State Register
    volatile uint32_t CFSR;                // Configurable Fault Status Register
    volatile uint32_t HFSR;                // HardFault Status Register
    volatile uint32_t DFSR;                // Debug Fault Status Register
    volatile uint32_t MMFAR;               // MemManage Fault Address Register
    volatile uint32_t BFAR;                // BusFault Address Register
    volatile uint32_t AFSR;                // Auxiliary Fault Status Register
    volatile uint32_t PFR[2];              // Processor Feature Register
    volatile uint32_t DFR;                 // Debug Feature Register
    volatile uint32_t ADR;                 // Auxiliary Feature Register
    volatile uint32_t MMFR[4];             // Memory Model Feature Register
    volatile uint32_t ISAR[5];             // Instruction Set Attributes Register
    volatile uint32_t RESERVED0[5];        // Reserved
    volatile uint32_t CPACR;               // Coprocessor Access Control Register
} SCB_Type;

#define SCB_BASE            (0xE000ED00UL)                            // System Control Block Base Address
#define SCB                 ((SCB_Type *) SCB_BASE)

#define Enable_Exceptions()    __asm(" CPSIE I ")
/* Disable Exceptions ... This Macro disable IRQ interrupts, Programmable Systems Exceptions and Faults by setting the I-bit in the PRIMASK. */
#define Disable_Exceptions()   __asm(" CPSID I ")

#define Load_Start_Address()  __asm(" movw r0 , #0x00001000")

#define Load_MSP()           __asm(" ldr sp , [r0]")

#define Load_VTable()       __asm(" ldr r0 , [r0, #4]")

#define Branching()             __asm (" bx r0 ")
/************************************
 * Macros
 ***********************************/
#define Programmed_Bytes    4
#define NULL             (void *) (0)
#define Debugging_UART   UART0_BASE
#define BL_Fetch_UART          UART0_BASE

#define CBL_GET_VER_CMD              0x10
#define CBL_GET_HELP_CMD             0x11
#define CBL_GET_CID_CMD              0x12
/* Get Read Protection Status */
#define CBL_GET_RDP_STATUS_CMD       0x13
#define CBL_GO_TO_ADDR_CMD           0x14
#define CBL_FLASH_ERASE_CMD          0x15
#define CBL_MEM_WRITE_CMD            0x16
/* Enable/Disable Write Protection */
#define CBL_ED_W_PROTECT_CMD         0x17
#define CBL_MEM_READ_CMD             0x18
/* Get Sector Read/Write Protection Status */
#define CBL_READ_SECTOR_STATUS_CMD   0x19
#define CBL_OTP_READ_CMD             0x20
/* Change Read Out Protection Level */
#define CBL_CHANGE_ROP_Level_CMD     0x21
#define BootloadorJmp                0x22

/***Version ****/
#define BL_Vendor_ID        100
#define BL_Version_Major    1
#define BL_Version_Minor    0
#define BL_Version_Patch    0

#define BL_SendACK          0xAB
#define BL_SendNACK         0xCD
#define App_Add             0x00001000
#define Total_Num_Sectors   255
/***********************************
 * prototypes
 **********************************/

void BL_Debbuging_Init (void);
void BL_Fetch_Init (void);
void BL_Fetch_Command (void);

/*********************
 * BootLoader Services
**********************/
void BL_Get_Version (void  );
void BL_Send_ACK (uint8_t   );
void BL_Send_NACK ( void );
void BL_Get_Help ();
void UART_Rec_Sring_Size (uint8_t * , uint32_t  );
static void Bootloador_Jmp (void);
void Bootloador_Flash_Erase (void);
void Bootloador_Write (uint32_t * PTR_Program );
#endif /* BOOTLOADER_H_ */
