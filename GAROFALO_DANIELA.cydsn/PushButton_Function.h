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
    File PushButton_Function.h
    Function aimed to the inclusion and the declaration of all the variables and functions
    in order to change the ODR infomation according to the pressure of the PushButton component
    Author: Daniela Garofalo
*/
    
#ifndef __PUSHBUTTON_FUNCTION_H__
    #define __PUSHBUTTON_FUNCTION_H__
    
    // Definition of the address in the EEPROM where the ODR information is saved
    #define EEPROM_ODR_ADRESS 0x0000
    
    #include <project.h> /* Library that contains all the functions related to the components
    added in the project, included the PushButton functions */
    #include <I2C_Communication.h>
    
    uint8 read_ODR;
    
    // Declaration of the function aimed to manage the pressing of the PushButton component
    void PushButton_IsPressed();
    
#endif

/* [] END OF FILE */
