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
    File main.c
    Function aimed to assure the correct functioning of the device in order to 
    fulfill the requests of the project
    Author: Daniela Garofalo
*/

// Including the necessary header files
#include "project.h"
#include <I2C_Communication.h>
#include <stdio.h>
#include <EEPROM.h>

// Definition of the address of the device
#define LIS3DH_DEVICE_ADDRESS 0x18

// Definition of the address of the identification register of the device
#define LIS3DH_WHO_AM_I_REG_ADDR 0x0F

// Definition of the address of the status register of the device
#define LIS3DH_STATUS_REG 0x27

// Definition of the address of the control register 1 of the device
#define LIS3DH_CTRL_REG1 0x20

// Definition of the address of the control register 4 of the device
#define LIS3DH_CTRL_REG4 0x23

// Definition of the bits that must be set in the control register 4
#define LIS3DH_CTRL_REG4_BDU_ACTIVE 0x80
#define LIS3DH_CTRL_REG4_FS_2g ~(0x30) // Set the values equal to 0 with an AND operator 
#define LIS3DH_CTRL_REG_HR_ACTIVE 0x08

// Definition of the operational mode in the control register 1 of the device
#define LIS3DH_NORMAL_MODE_CTRL_REG1 0x47

// Definition of the address in the EEPROM where the ODR information is saved
#define EEPROM_ODR_ADRESS 0x0000

#define LIS3DH_OUT_ADC_3L 0x0C

#define LIS3DH_OUT_ADC_3H 0x0D

uint8 read_ODR;

int main(void)
{
    CyGlobalIntEnable; /* Enable global interrupts. */

    /* Place your initialization/startup code here (e.g. MyInst_Start()) */
    
    // Initialisation of the UART component
    UART_Debug_Start();
    
    // Initialisation of the I2C component
    I2C_CommunicationStart();
    
    // Initialisation of the EEPROM component
    EEPROM_Start();
    
    read_ODR = EEPROM_ReadByte(EEPROM_ODR_ADRESS);
    if (read_ODR < 0x01 || read_ODR > 0x06) /* The value saved in correspondence of the memory 
    address is not one of the allowable values for the ODR information, this value is set
    equal to the minimum frequency (which is 1 Hz) corresponding to the minimum number */
    {
        read_ODR = 0x01;
    }

    for(;;)
    {
        /* Place your application code here. */
        if (PushButton_Read() == 0) // The button is pressed so the input is low logic level
        {
            while(PushButton_Read() == 0); /* Wait until the end of the pushing in order to
            change the ODR information only when the button is released */
            read_ODR = read_ODR + 0x01;
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
}

/* [] END OF FILE */
