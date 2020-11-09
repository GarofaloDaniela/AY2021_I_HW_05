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
        while(PushButton_Read() == 0); /* Wait until the end of the pushing in order to
        change the ODR information only when the button is released */
        read_ODR++;
        if (read_ODR > 0x06) /* The ODR value can range from 0x01 to 0x06 and then the
        cycling is restarted again at the pushing of the PushButton component */
        {
            read_ODR = 0x01;
        }
        EEPROM_WriteByte(read_ODR, EEPROM_ODR_ADRESS); /* Saving the current information
        related to the ODR data in order to use them in the successive startup of the 
        device */
    }
}

/* [] END OF FILE */
