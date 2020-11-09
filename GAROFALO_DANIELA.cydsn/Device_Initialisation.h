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
    File Device_Initialisation.h
    Function aimed to the inclusion and the declaration of all the variables and functions
    in order to allow initialisation of the device at the startup
    Author: Daniela Garofalo
*/
    
#ifndef __DEVICE_INITIALISATION_H__
    #define __DEVICE_INITIALISATION_H__
    
    // Definition of the address in the EEPROM where the ODR information is saved
    #define EEPROM_ODR_ADRESS 0x0000
    
    // Definition of the number of bytes used to represent the sampled data
    #define BYTES_NUMBER 2
    
    // Definition of the header and of the tail in the communication protocol
    #define HEADER 0xA0
    #define TAIL 0xC0
    #define BUFFER_SIZE BYTES_NUMBER*3 // 2 bytes for each of the 3 channels
    #define BYTES_TO_SEND 1 + BUFFER_SIZE + 1
    
    // Inclusion of all the functions related to the components added to the project
    #include <project.h>
    
    // Declaration of the variable that will contain the information related to the ODR data
    uint8 read_ODR;
    
    /* Declaration of the variables in which are saved the converted information coming from the
    accelerator that must be send throuhg the I2C communication protocol */
    extern uint8_t Output_Array[BYTES_TO_SEND];
    
    /* Declaration of the function that is aimed to the initialisation of all the components
    needed for the proper operation of the device */
    void Device_Init();
#endif

/* [] END OF FILE */
