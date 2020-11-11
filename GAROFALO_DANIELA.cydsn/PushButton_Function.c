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
    File PushButton_Function.c
    Functions that assures the proper operation of the PushButton component
    Author: Daniela Garofalo
*/
    
#include <PushButton_Function.h>
    
void PushButton_IsPressed()
{
    if (PushButton_Read() == 0) // The button is pressed so the input is low logic level
    {
        /* Wait until the end of the pushing in order to change the ODR information only 
        when the button is released */
        while(PushButton_Read() == 0); 
        
        // Changing the value of the ODR information
        read_ODR++;
        if (read_ODR > 0x06) /* The ODR value can range from 0x01 to 0x06 and then the
        cycling is restarted again at the pushing of the PushButton component */
        {
            read_ODR = 0x01;
        }
        
        /* Saving the current information related to the ODR data in order to use them in 
        the successive power-up of the device */
        EEPROM_WriteByte(read_ODR, EEPROM_ODR_ADRESS); 
        
        // Sending the information to the register in order to update the data rate of the device
        ctrl_register_1 = (read_ODR << 4) + 0x07; /* Setting the first 4 bits of the register using
        the ODR information and the remaining ones according to the requirements of the project
        (LPen = 0, Zen = 1, Yen = 1 and Xen = 1) */
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
    }
}

/* [] END OF FILE */
