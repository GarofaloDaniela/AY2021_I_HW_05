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
    
    // Definition of the number of bytes used to represent the sampled data
    #define BYTES_NUMBER 2
    
    // Definition of the header and of the tail in the communication protocol
    #define HEADER 0xA0
    #define TAIL 0xC0
    #define BUFFER_SIZE BYTES_NUMBER*3 // 2 bytes for each of the 3 channels
    #define BYTES_TO_SEND 1 + BUFFER_SIZE + 1
    
    /* Definition of the values related to the connection or to the disconnection of the device
    during the communication protocol */
    #define DEVICE_CONNECTED 1
    #define DEVICE_UNCONNECTED 0
    
    // Definition of the address of the device
    #define LIS3DH_DEVICE_ADDRESS 0x18

    // Definition of the address of the identification register of the device
    #define LIS3DH_WHO_AM_I_REG_ADDRESS 0x0F

    // Definition of the address of the status register of the device
    #define LIS3DH_STATUS_REG_ADDRESS 0x27
    
    // Definition of the bits that must be controlled in the status register
    #define LIS3DH_STATUS_REG_AVAILABLEDATA 0x08
    #define LIS3DH_STATUS_REG_AVAILABLEZ 0x04
    #define LIS3DH_STATUS_REG_AVAILABLEY 0x02
    #define LIS3DH_STATUS_REG_AVAILABLEX 0x01

    // Definition of the address of the control register 1 of the device
    #define LIS3DH_CTRL_REG1_ADDRESS 0x20

    // Definition of the bits that must be set in the control register 1
    #define LIS3DH_CTRL_REG1_SETTINGS 0x0F

    // Definition of the address of the control register 4 of the device
    #define LIS3DH_CTRL_REG4_ADDRESS 0x23

    // Definition of the bits that must be set in the control register 4
    #define LIS3DH_CTRL_REG4_SETTINGS 0x88
    
    // Definitio of the address of the registers that contain the accelerometer outputs
    #define LIS3DH_OUT_X_L 0x28
    #define LIS3DH_OUT_Y_L 0x2A
    #define LIS3DH_OUT_Z_L 0x2C
    
    /* Definition of the coefficients for the conversion of the values sampled by the
    accelerometer is values that are expressed in [m/s^2] */
    #define M_COEFFICIENT_DIGIT_TO_G (2^12 - 1)/(2 - (-2)) /* All the possible values obtained
    with 12 bits are remapped on the full scale (FS) range, that is set ranging from -2g to
    + 2g */
    #define Q_COEFFICIENT_DIGIT_TO_G -2 // Intercept with the vertical axis
    #define M_COEFFICIENT_G_TO_ACC 9.81 // Coefficient of conversion from [g] to [m/s^2]
    #define Q_COEFFICIENT_G_TO_ACC 0
    
    #include <project.h> /* Library that contains all the functions related to the
    components associated to this project */
    #include <cytypes.h>
    #include <stdio.h> /* Library that contains all the functions used in the standard
    input/output communication */
    #include <ErrorCodes.h> // File in which the ErrorCode variables are defined

    // Declaration of the string used to print out the message on the UART Debug
    char message[50] = {'\0'};
    
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
    
    // Declaration of all the functions contained in the source file
    void I2C_CommunicationStart(); // Function that starts the communication
    void I2C_CommunicationStop(); // Function that stops the communication
    ErrorCode I2C_CommunicationReadRegister(uint8_t device_address, 
                                            uint8_t register_address,
                                            uint8_t register_count,
                                            uint8_t* data);
    // Function that reads the values contained in the register 
    ErrorCode I2C_CommunicationWriteRegister(uint8_t device_address,
                                             uint8_t register_address,
                                             uint8_t data);
    // Function that modifies the values contained in the register
    uint8_t I2C_Communication_IsDeviceConnected(uint8_t device_address); /* Function that identifies
    if the device is still connected or not */
    void I2C_CommunicationInitRegister(); /* Function that initialises the addresses of the 
    registers */
    void I2C_CommunicationSetRegister(); // Function that sets the configurations of the registers
    void I2C_CommunicationAvailableData(); /* Function that manages the presence of some new data
    available to be sent through the I2C communication protocol */
    int16 I2C_CommunicationConversion(uint8_t *data);/* Function aimed in the conversion of the 
    sampled data in the correct measurement unit in order to plot them after the communication */
    void I2C_CommunicationTransmission(); // Function aimed in the transmission of the data
    
#endif

/* [] END OF FILE */
