/*
 * Bootloader.c
 *
 *  Created on: May 15, 2024
 *      Author: omar
 */
/**********************************
 * Includes
 **********************************/
#include "Bootloader.h"
/**********************************
 * Global Variables
 *********************************/
uint8_t Message_Buffer [100] = {0};
BL_ACK  Status_Buffer  [100] = {BL_Ok};

static uint8_t BL_Get_Command [12] = {CBL_GET_VER_CMD,CBL_GET_HELP_CMD,CBL_GET_CID_CMD,CBL_GET_RDP_STATUS_CMD,
                                      CBL_GO_TO_ADDR_CMD,CBL_FLASH_ERASE_CMD,CBL_MEM_WRITE_CMD,CBL_ED_W_PROTECT_CMD,
                                      CBL_MEM_READ_CMD,CBL_READ_SECTOR_STATUS_CMD,CBL_OTP_READ_CMD,CBL_CHANGE_ROP_Level_CMD};
/**********************************/
void BL_Debbuging_Init (void){
    /*Init UART 0 */
    UART0_Init();
}

void BL_Fetch_Init (void){
    /*Init UART 0 */
    UART0_Init();
}
void BL_Fetch_Command (void){

    /*The First Byte of the Command is the Length of the Buffer*/
    uint8_t Message_Buffer [100] = {0};

    uint8_t Data_Length = 0 ;  /*The Length of the data that the user will send */

    UART_Rec_Sring_Size(Message_Buffer, BL_Fetch_UART);

    Data_Length = Message_Buffer [Data_Len];

    if ((void *)Data_Length == NULL){
        Status_Buffer [Data_Len] = BL_Nok;
    }
    else {
        Status_Buffer [Data_Len] = BL_Ok;
        Message_Buffer [Data_Len] = Data_Length;
    }

    if ((void *)Message_Buffer[DataBytes] == NULL){
        Status_Buffer [DataBytes] = BL_Nok;

    }
    else {
        Status_Buffer [DataBytes] = BL_Ok;

    }

    switch ( Message_Buffer[DataBytes]){

    case CBL_GET_VER_CMD:

        UART_Send_Str("GET VER", Debugging_UART);
        /***Sending the Version using UART****/
        BL_Get_Version();

        break;

    case CBL_GET_HELP_CMD:

        UART_Send_Str("GET_HELP", Debugging_UART);
        /**Sending Commands**/
        BL_Get_Help();
        break;
    case CBL_GET_CID_CMD:

        UART_Send_Str("GET_CID", Debugging_UART);
        Status_Buffer [GET_CID] = BL_Ok;

        break;
    case CBL_GET_RDP_STATUS_CMD:
        UART_Send_Str("GET_RDP_STATUS", Debugging_UART);
        Status_Buffer [GET_RDP_STATUS] = BL_Ok;

        break;
    case CBL_GO_TO_ADDR_CMD:
        UART_Send_Str("GO_TO_ADDR", Debugging_UART);
        Status_Buffer [GO_TO_ADDR] = BL_Ok;

        break;

    case CBL_FLASH_ERASE_CMD:
        UART_Send_Str("FLASH_ERASE", Debugging_UART);
        Status_Buffer [GO_TO_ADDR] = BL_Ok;

        break;

    case CBL_MEM_WRITE_CMD:
        UART_Send_Str("FLASH_Write", Debugging_UART);
        break;

    case BootloadorJmp :

        UART_Send_Str("Jump to the application", Debugging_UART);
        Bootloador_Jmp();
        break;

    }





}

/**************************************************
 * Services
 **************************************************/
// Getting the version of the Bootloader
void BL_Get_Version (void  ){
    // status var
    BL_ACK Status = BL_Ok ;

    //Buffer that has vendor ID , etc....
    uint8_t BL_Get_Version_Buffer [4] = {BL_Vendor_ID,BL_Version_Major,BL_Version_Minor,BL_Version_Patch};
    // Sending These Data using UART
    if (Status == BL_Ok){
        /**Send ACK**/
        BL_Send_ACK(4);
        UART_Send_Str(BL_Get_Version_Buffer, BL_Fetch_UART);

    }
    else if (Status == BL_Nok){
        /**Send NACK**/
        BL_Send_NACK();

    }

}
// Get Help Command
void BL_Get_Help (void  ){
    // status var
    BL_ACK Status = BL_Ok ;

    //Buffer that has vendor ID , etc....

    // Sending These Data using UART
    if (Status == BL_Ok){
        /**Send ACK**/
        BL_Send_ACK(12);
        UART_Send_Str(BL_Get_Command, BL_Fetch_UART);

    }
    else if (Status == BL_Nok){
        /**Send NACK**/
        BL_Send_NACK();

    }

}

//Send ACK / NACK
void BL_Send_ACK (uint8_t Message_Length  ){


    uint8_t ACK_Array [2 ] = {0} ;
    ACK_Array [0] = BL_SendACK ;
    ACK_Array [1] = Message_Length ;
    UART_Send_Str(ACK_Array, BL_Fetch_UART);

}
void BL_Send_NACK (  ){

    uint8_t NACK_MS = BL_SendNACK;
    UART_Send_Str(&NACK_MS, BL_Fetch_UART);
}
// Bootloador


static void Bootloador_Jmp (void){

    Load_Start_Address();// Load Start Address of the application on r0
    SCB->VTOR = App_Add;
    Load_MSP();
    Load_VTable();
    Branching();


}

BL_ACK Bootloador_Flash_Erase (uint16_t Copy_Sector_Number, uint32_t Copy_NumberofSector){
    uint16_t Index;
    BL_ACK Flash_Status = BL_Ok;
    uint32_t Addresse = 0;


    // User Can not Erase the first  4 Sectors, because these are the sectors of the Bootloador
    // User can not exceed the limit of the sectors (256)
    if ((Copy_NumberofSector > (Total_Num_Sectors - Copy_Sector_Number )) || (Copy_Sector_Number > Total_Num_Sectors) || Copy_Sector_Number <= 4  ) {
        // Return Error
        Flash_Status = BL_Nok;

    }

    else {

        for ( Index = 0 ; Index < Copy_NumberofSector ; Index++ ){

            Addresse =  Copy_Sector_Number * 1024;

            FlashErase(Addresse);

        }
    }

    return Flash_Status;
}

void Bootloador_ProgramHandle (void ){




}
void Bootloador_Write (uint32_t * PTR_Program , uint32_t Number_Sector ){

    BL_ACK Status = BL_Ok;
    uint32_t NumberofBytes = 0 ;
    uint32_t SectorAddresse = 0 ;
    uint32_t Index  ;
    uint32_t PayLoad_Counter  = 0;
    // Calc The Sector addresse
    SectorAddresse = Number_Sector * 1024;

    for (Index = 0 ; Index <  PayLoad_Counter ; Index ++ ){


        FlashProgram((PTR_Program + Index) , SectorAddresse, Programmed_Bytes);

    }





}
