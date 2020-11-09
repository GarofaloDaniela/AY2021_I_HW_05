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
    
    // Inclusion of all the functions related to the components added to the project
    #include <project.h> 
    #include <I2C_Communication.h> 
    
    // Declaration of the variable that will contain the information related to the ODR data
    uint8 read_ODR;
    
    /* Declaration of the function that is aimed to the initialisation of all the components
    needed for the proper operation of the device */
    void Device_Init();
    
#endif

/* [] END OF FILE */
