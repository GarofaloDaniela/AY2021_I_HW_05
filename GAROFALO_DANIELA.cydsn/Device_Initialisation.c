/* ========================================
 *
 * Copyright YOUR COMPANY, THE YEAR
 * All Rights Reserved
 * UNPUBLISHED, LICENSED SOFTWARE.
 *
 * CONFIDENTIAL AND PROPRIETARY INFORMATION
 * WHICH IS THE PROPERTY OF your company.
 *
 * ========================================
*/

/*
    File Device_Initialisation.c
    Functions that assures the proper operation of the device initialisation at the power-up
    Author: Daniela Garofalo
*/
    
#include <Device_Initialisation.h>
#include <I2C_Communication.h>

void Device_Init()
{
    // Initialisation of the UART component
    UART_Debug_Start();
    
    // Initialisation of the I2C component
    I2C_CommunicationStart();
    
    // Initialisation of the EEPROM component
    EEPROM_Start();
    
    read_ODR = EEPROM_ReadByte(EEPROM_ODR_ADRESS);
    if (read_ODR < 0x01 || read_ODR > 0x06) /* If the value saved in correspondence of the memory 
    address is not one of the allowable values for the ODR information, this value is set
    equal to the minimum frequency (which is 1 Hz) corresponding to the minimum number for 
    the read_ODR variable */
    {
        read_ODR = 0x01;
    }
    
    /* Initialisation of the header and of the tail in the array to be send throught the I2C
    communication protocol */
    Output_Array[0] = HEADER;
    Output_Array[BYTES_TO_SEND - 1] = TAIL;
}

/* [] END OF FILE */
