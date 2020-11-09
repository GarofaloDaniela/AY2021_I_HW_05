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
#include <Device_Initialisation.h>
#include <PushButton_Function.h>

// Declaration of the variable in which is saved the ODR information from the EEPROm
extern uint8 read_ODR;

/* Declaration of the variables in which are saved the converted information coming from the
accelerator that must be send throuhg the I2C communication protocol */
extern uint8_t Output_Array[BYTES_TO_SEND];

int main(void)
{
    CyGlobalIntEnable; /* Enable global interrupts. */

    /* Place your initialization/startup code here (e.g. MyInst_Start()) */
    
    // Initialisation of the device
    Device_Init();
    
    // Initialisation of the registers needed in the I2C communication protocol
    I2C_CommunicationInitRegister();
    
    // Setting the registers according to the requirements and the contraints of the project
    I2C_CommunicationSetRegister();
    
    for(;;)
    {
        /* Place your application code here. */
        
        // Function that controls if the PushButton is pressed in order to update the ODR data
        PushButton_IsPressed();
        
        
    }
}

/* [] END OF FILE */
