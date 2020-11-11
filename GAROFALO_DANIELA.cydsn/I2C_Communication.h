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
    
    #include <project.h> /* Library that contains all the functions related to the
    components associated to this project */
    #include <cytypes.h>
    #include <stdio.h> /* Library that contains all the functions used in the standard
    input/output communication */
    #include <ErrorCodes.h> // File in which the ErrorCode variables are defined
    
    /* Definition of the values related to the connection or to the disconnection of the device
    during the communication protocol */
    #define DEVICE_CONNECTED 1
    #define DEVICE_UNCONNECTED 0
    
    // Definition of the number of bytes used to represent the sampled data
    #define BYTES_NUMBER 2

    // Definition of the header and of the tail in the communication protocol
    #define HEADER 0xA0
    #define TAIL 0xC0

    #define BUFFER_SIZE BYTES_NUMBER * 3 // 2 bytes for each of the 3 channels
    #define BYTES_TO_SEND 1 + BUFFER_SIZE + 1

    // Definition of the address of the device
    #define LIS3DH_DEVICE_ADDRESS 0x18

    // Definition of the address of the identification register of the device
    #define LIS3DH_WHO_AM_I_REG_ADDRESS 0x0F

    // Definition of the address of the status register of the device
    #define LIS3DH_STATUS_REG_ADDRESS 0x27

    // Definition of the bits that must be controlled in the status register
    #define LIS3DH_STATUS_REG_AVAILABLEDATA 0x08 // ZYXDA bit = 1
    #define LIS3DH_STATUS_REG_AVAILABLE_X 0x01 // XDA bit = 1
    #define LIS3DH_STATUS_REG_AVAILABLE_Y 0x02 // YDA bit = 1
    #define LIS3DH_STATUS_REG_AVAILABLE_Z 0x04 // ZDA bit = 1

    // Definition of the address of the control register 1 of the device
    #define LIS3DH_CTRL_REG1_ADDRESS 0x20

    // Definition of the bits that must be set in the control register 1
    #define LIS3DH_CTRL_REG1_SETTINGS 0x07 // LPen = 0, Zen = 1, Yen = 1 and Xen = 1 

    // Definition of the address of the control register 4 of the device
    #define LIS3DH_CTRL_REG4_ADDRESS 0x23

    // Definition of the bits that must be set in the control register 4
    #define LIS3DH_CTRL_REG4_SETTINGS 0x08 // HR bit = 1

    // Definition of the address of the registers that contain the accelerometer outputs
    // Channel X
    #define LIS3DH_OUT_X_L 0x28
    #define LIS3DH_OUT_X_H 0x29
    
    // Channel Y
    #define LIS3DH_OUT_Y_L 0x2A
    #define LIS3DH_OUT_Y_H 0x2B
    
    // Channel Z
    #define LIS3DH_OUT_Z_L 0x2C
    #define LIS3DH_OUT_Z_H 0x2D
    
    /* Definition of the coefficients necessary to the conversion of the accelerometer data
    from digit to [m/s^2] in order to plot them correctly */
    #define M_COEFFICIENT_G_TO_ACC -9.81
    #define Q_COEFFICIENT_G_TO_ACC 0

    // Declaration of the string used to print out the message on the UART Debug
    char message[50];
        
    // Declaration of the variables that represents the registers 
    uint8_t who_am_i_register;
    uint8_t status_register;
    uint8_t ctrl_register_1;
    uint8_t ctrl_register_4;

    // Declaration of the variables that will contain the values coming from the accelerator
    uint8_t X_data[BYTES_NUMBER];
    uint8_t Y_data[BYTES_NUMBER];
    uint8_t Z_data[BYTES_NUMBER];

    /* Declaration of the output variable that will be contain the whole information coming
    from the accelerometer */
    int16 Output_X;
    int16 Output_Y;
    int16 Output_Z;
    
    uint8_t Output_Array[BYTES_TO_SEND];
    
    /******  Declaration of all the functions contained in the source file  ******/
    void I2C_CommunicationStart(); // Function that starts the communication
    
    void I2C_CommunicationStop(); // Function that stops the communication
    
    ErrorCode I2C_CommunicationReadRegister(uint8_t device_address, 
                                            uint8_t register_address,
                                            uint8_t* data);
    // Function that reads the values contained in the register 
    
    ErrorCode I2C_CommunicationWriteRegister(uint8_t device_address,
                                             uint8_t register_address,
                                             uint8_t data);
    // Function that modifies the values contained in the register
    
    uint8_t I2C_Communication_IsDeviceConnected(uint8_t device_address); /* Function that identifies
    if the device is still connected or not */
    
    void I2C_CommunicationSetRegisters(); /* Function that manages the settings of the registers
    according to the requirements and the constraints of the project */
    
    void I2C_CommunicationAvailableData(); /* Function that manages the presence of some new data
    available to be sent through the I2C communication protocol */
    
    int16 I2C_CommunicationConversion(uint8_t *data);/* Function aimed in the conversion of the 
    sampled data in the correct measurement unit in order to plot them after the communication */
    
    void I2C_CommunicationTransmission(); // Function aimed in the transmission of the data
    
#endif

/* [] END OF FILE */
