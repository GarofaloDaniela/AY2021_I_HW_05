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

void Device_Init()
{
    // Initialisation of the UART component
    UART_Debug_Start();
    
    // Initialisation of the I2C component
    I2C_CommunicationStart();
    
    // Initialisation of the EEPROM component
    EEPROM_Start();
    
    // Initialisation of the ODR information in the control register 1
    read_ODR = EEPROM_ReadByte(EEPROM_ODR_ADRESS);
    if (read_ODR < 0x01 || read_ODR > 0x06) /* If the value saved in correspondence of the memory 
    address is not one of the allowable values for the ODR information, this value is set
    equal to the minimum frequency (which is 1 Hz) corresponding to the minimum number for 
    the read_ODR variable */
    {
        read_ODR = 0x01;
    }
    // Sending the information to the register in order to set the data rate of the device
    ctrl_register_1 = (read_ODR << 4) + 0x07; /* Setting the first 4 bits of the register using
    the ODR information and the remaining ones are equal to set according to the requirements
    of the project: LPen = 0, Xen = 1, Yen = 1 and Zen = 1 */
    ErrorCode error = I2C_CommunicationWriteRegister(LIS3DH_DEVICE_ADDRESS,
                                                     LIS3DH_CTRL_REG1_ADDRESS,
                                                     ctrl_register_1);
    if (error == NO_ERROR)
    {
        sprintf(message, "CONTROL REGISTER 1 is set equal to: 0x%02X\r\n", ctrl_register_1);
        UART_Debug_PutString(message);
    }
    else
    {
        UART_Debug_PutString("Error occurred during I2C communication with CONTROL REGISTER 1");
    }
    
    /* Initialisation of the header and of the tail in the array to be send throught the I2C
    communication protocol */
    Output_Array[0] = HEADER;
    Output_Array[BYTES_TO_SEND - 1] = TAIL;
}

/* [] END OF FILE */
