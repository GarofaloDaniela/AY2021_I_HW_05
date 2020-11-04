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
    File I2C_Communication.h
    Function aimed to the inclusion and the declaration of all the variables and functions
    in order to allow the communication following the I2C protocol
    Author: Daniela Garofalo
*/
    
#ifndef __I2C_COMMUNICATION_H__
    #define __I2C_COMMUNICATION_H__
    
    #define DEVICE_CONNECTED 1
    #define DEVICE_UNCONNECTED 0
    
    #include <project.h> /* Library that contains all the functions related to the
    components associated to this project */
    #include <cytypes.h>
    #include <ErrorCodes.h>

    void I2C_CommunicationStart();
    void I2C_CommunicationStop();
    ErrorCode I2C_CommunicationReadRegister(uint8_t device_address, 
                                            uint8_t register_address,
                                            uint8_t* data);
    ErrorCode I2C_CommunicationWriteRegister(uint8_t device_address,
                                             uint8_t register_address,
                                             uint8_t data);
    uint8_t I2C_Communication_IsDeviceConnected(uint8_t device_address);
    
#endif

/* [] END OF FILE */
