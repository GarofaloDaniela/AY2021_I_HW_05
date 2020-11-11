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
    File I2C_Communication.c
    Functions that assures the proper operation of the I2C communication protocol
    Author: Daniela Garofalo
*/
    
#include <I2C_Communication.h>

void I2C_CommunicationStart()
{
    // Start the component
    I2C_Start(); 
}

void I2C_CommunicationStop()
{
    // Stop the component
    I2C_Stop();
}

ErrorCode I2C_CommunicationReadRegister(uint8_t device_address, 
                                        uint8_t register_address,
                                        uint8_t *data)
{
    /* Send start condition: WRITE command in order to communicate the device and the
    register addresses to the slave peripheral */
    uint8_t error = I2C_MasterSendStart(device_address, I2C_WRITE_XFER_MODE);
    if (error == I2C_MSTR_NO_ERROR)
    {
        // Write address of register to be read 
        error = I2C_MasterWriteByte(register_address);
        if (error == I2C_MSTR_NO_ERROR)
        {
            /* Send restart condition: READ command in order to communicate to the device
            the necessity to upload the asked data on the bus */
            error = I2C_MasterSendRestart(device_address, I2C_READ_XFER_MODE);
            if (error == I2C_MSTR_NO_ERROR)
            {
                /* Read data and sending the NACK signal in order to report the ending of the
                data trasmission */
                *data = I2C_MasterReadByte(I2C_NAK_DATA);
            }
        }
    }
    
    // Send stop condition
    I2C_MasterSendStop();
        
    // Return error code
    return error ? ERROR : NO_ERROR;
}

ErrorCode I2C_CommunicationWriteRegister(uint8_t device_address,
                                         uint8_t register_address,
                                         uint8_t data)
{
    /* Send start condition: WRITE command in order to communicate the device and the
    register addresses to the slave peripheral */
    uint8_t error = I2C_MasterSendStart(device_address, I2C_WRITE_XFER_MODE);
    if (error == I2C_MSTR_NO_ERROR)
    {
        // Write register address
        error = I2C_MasterWriteByte(register_address);
        if (error == I2C_MSTR_NO_ERROR)
        {
            // Write byte of interest
            error = I2C_MasterWriteByte(data);
        }
    }
    
    // Send stop condition
    I2C_MasterSendStop();
    
    // Return error code
    return error ? ERROR : NO_ERROR;
}

uint8_t I2C_Communication_IsDeviceConnected(uint8_t device_address)
{
    // Send a start condition followed by a stop condition
    uint8_t error = I2C_MasterSendStart(device_address, I2C_WRITE_XFER_MODE);
    I2C_MasterSendStop();
    /* If no error is generated during the sending of the conditions, this means that
    the device is connected */
    if (error == I2C_MSTR_NO_ERROR)
    {
        return DEVICE_CONNECTED;
    } else {
        return DEVICE_UNCONNECTED;
    }
}

void I2C_CommunicationSetRegisters()
{
    /********  Reading the WHO AM I REGISTER  ******/
    ErrorCode error = I2C_CommunicationReadRegister(LIS3DH_DEVICE_ADDRESS,
                                                    LIS3DH_WHO_AM_I_REG_ADDRESS, 
                                                    &who_am_i_register);
    if (error == NO_ERROR)
    {
        sprintf(message, "WHO AM I REGISTER (expected: 0x33): 0x%02X\r\n", who_am_i_register);
        UART_Debug_PutString(message);
    }
    else
    {
        UART_Debug_PutString("Error occurred during I2C communication with WHO AM I REGISTER");
    }
    
    /******  Reading the STATUS REGISTER  ******/
    error = I2C_CommunicationReadRegister(LIS3DH_DEVICE_ADDRESS,
                                          LIS3DH_STATUS_REG_ADDRESS,
                                          &status_register);
    if (error == NO_ERROR)
    {
        sprintf(message, "STATUS REGISTER: 0x%02X\r\n", status_register);
        UART_Debug_PutString(message);
    }
    else
    {
        UART_Debug_PutString("Error occurred during I2C communication with STATUS REGISTER");
    }
    
    /******  Reading the CONTROL REGISTER 1  ******/
    error = I2C_CommunicationReadRegister(LIS3DH_DEVICE_ADDRESS,
                                          LIS3DH_CTRL_REG1_ADDRESS, 
                                          &ctrl_register_1);
    if (error == NO_ERROR)
    {
        sprintf(message, "CONTROL REGISTER 1: 0x%02X\r\n", ctrl_register_1);
        UART_Debug_PutString(message);
    }
    else
    {
        UART_Debug_PutString("Error occurred during I2C communication with CONTROL REGISTER 1");
    }
    
    /******  Reading the CONTROL REGISTER 4  ******/
    error = I2C_CommunicationReadRegister(LIS3DH_DEVICE_ADDRESS,
                                          LIS3DH_CTRL_REG4_ADDRESS, 
                                          &ctrl_register_4);
    if (error == NO_ERROR)
    {
        sprintf(message, "CONTROL REGISTER 4: 0x%02X\r\n", ctrl_register_4);
        UART_Debug_PutString(message);
    }
    else
    {
        UART_Debug_PutString("Error occurred during I2C communication the CONTROL REGISTER 4");
    }
    
    // Setting the registers according to the requirements and the contraints of the project
    
    /******  Setting the configurations for the CONTROL REGISTER 1  ******/
    ctrl_register_1 |= LIS3DH_CTRL_REG1_SETTINGS; /* Modify only the bits relative to the enabling
    of the three axes without modifying the ODR bits */
    error = I2C_CommunicationWriteRegister(LIS3DH_DEVICE_ADDRESS,
                                           LIS3DH_CTRL_REG1_ADDRESS,
                                           ctrl_register_1);
    if (error == NO_ERROR)
    {
        sprintf(message, "CONTROL REGISTER 1 is setted equal to: 0x%02X\r\n", ctrl_register_1);
        UART_Debug_PutString(message);
    }
    else
    {
        UART_Debug_PutString("Error occurred during I2C communication with CONTROL REGISTER 1");
    }
    
    /******  Setting the configurations for the CONTROL REGISTER 4  ******/
    if (ctrl_register_4 != LIS3DH_CTRL_REG4_SETTINGS)
    {
        ctrl_register_4 = LIS3DH_CTRL_REG4_SETTINGS;
    }
    error = I2C_CommunicationWriteRegister(LIS3DH_DEVICE_ADDRESS,
                                           LIS3DH_CTRL_REG4_ADDRESS,
                                           ctrl_register_4);
    if (error == NO_ERROR)
    {
        sprintf(message, "CONTROL REGISTER 4 is setted equal to (expected: 0x08): 0x%02X\r\n", ctrl_register_4);
        UART_Debug_PutString(message);
    }
    else
    {
        UART_Debug_PutString("Error occurred during I2C communication with CONTROL REGISTER 4");
    }
 }

void I2C_CommunicationAvailableData()
{
    if (status_register & LIS3DH_STATUS_REG_AVAILABLEDATA)
    // ZYXDA bit = 1 and at least one among ZDA, YDA and XDA bits are equal to 1
    {
        /*Definition of the variable error in order to store the outputs of the functions
        related to the I2C communication protocol */
        ErrorCode error;
        
        // Channel X
        if (status_register & LIS3DH_STATUS_REG_AVAILABLE_X) 
        // XDA bit = 1
        {
            // Reading of the least significant bits of the value
            error = I2C_CommunicationReadRegister(LIS3DH_DEVICE_ADDRESS,
                                                  LIS3DH_OUT_X_L,
                                                  &X_data[0]);
            if (error == NO_ERROR)
            {
                error = I2C_CommunicationReadRegister(LIS3DH_DEVICE_ADDRESS,
                                                      LIS3DH_OUT_X_H,
                                                      &X_data[1]);
                if (error == NO_ERROR)
                {
                    // Conversion of the data
                    Output_X = I2C_CommunicationConversion(X_data);
                }
                else
                {
                    UART_Debug_PutString("Error occurred during I2C communication to read the channel X");
                }
            }
            else
            {
                UART_Debug_PutString("Error occurred during I2C communication to read the channel X");
            }
        }
        
        // Channel Y
        if (status_register & LIS3DH_STATUS_REG_AVAILABLE_Y)
        // YDA bit = 1
        {
            // Reading of the least significant bits of the value
            error = I2C_CommunicationReadRegister(LIS3DH_DEVICE_ADDRESS,
                                                  LIS3DH_OUT_Y_L,
                                                  &Y_data[0]);
            if (error == NO_ERROR)
            {
                error = I2C_CommunicationReadRegister(LIS3DH_DEVICE_ADDRESS,
                                                      LIS3DH_OUT_Y_H,
                                                      &Y_data[1]);
                if (error == NO_ERROR)
                {
                    // Conversion of the data
                    Output_Y = I2C_CommunicationConversion(Y_data);
                }
                else
                {
                    UART_Debug_PutString("Error occurred during I2C communication to read the channel Y");
                }
            }
            else
            {
                UART_Debug_PutString("Error occurred during I2C communication to read the channel Y");
            }
        }
        
        // Channel Z
        if (status_register & LIS3DH_STATUS_REG_AVAILABLE_Z) 
        // ZDA bit = 1
        {
            // Reading of the least significant bits of the value
            error = I2C_CommunicationReadRegister(LIS3DH_DEVICE_ADDRESS,
                                                  LIS3DH_OUT_Z_L,
                                                  &Z_data[0]);
            if (error == NO_ERROR)
            {
                error = I2C_CommunicationReadRegister(LIS3DH_DEVICE_ADDRESS,
                                                      LIS3DH_OUT_Z_H,
                                                      &Z_data[1]);
                if (error == NO_ERROR)
                {
                    // Conversion of the data
                    Output_Z = I2C_CommunicationConversion(Z_data);
                }
                else
                {
                    UART_Debug_PutString("Error occurred during I2C communication to read the channel Z");
                }
            }
            else
            {
                UART_Debug_PutString("Error occurred during I2C communication to read the channel Z");
            }
        }
        
        // Transmission of the data through the I2C communication protocol
        I2C_CommunicationTransmission();
    }
}

int16 I2C_CommunicationConversion(uint8_t *data)
{
    // Output value expressed in digit stored a single variable
    int16 output_data = (int16)(data[0] | data[1] << 8) >> 4; /* The values coming from
    the data registers are left aligned, so they are shifted by 4 in order to place the least
    significant bit in correspondence of the first bit in the 16 bits variable */
    
    /* Considering that the sensibility of the device is 10^-3 in the high resolution mode and
    with a full scale range that is between -2g and +2g, and also considering that the digits
    are symmetrically distributed around the origin of the axes in the function that converts
    from [digits] to [g] so the intercept is equal to zero, the coefficients nullify themselves 
    because it is necessary to multiply the value obtained after the conversion for 10^3 in order
    to "store" 3 decimals to be sent through the UART communication protocol in order to plot 
    correctly the values sampled from the accelerometer --> the only conversion that remains to be 
    done is the one that associates the data expressed in [g] to values of accelerations expressed
    in [m/s^2] */
    
    // Conversion from g to accelerations expressed in [m/s^2]
    float converted_data = M_COEFFICIENT_G_TO_ACC * output_data + Q_COEFFICIENT_G_TO_ACC;
    
    // Return the converted value
    return converted_data;
}

void I2C_CommunicationTransmission()
{
    // Channel X
    Output_Array[1] = (uint8_t)(Output_X & 0xFF); // Least significant bits
    Output_Array[2] = (uint8_t)((Output_X >> 8) & 0xFF); // Most significant bits
    
    // Channel Y
    Output_Array[3] = (uint8_t)(Output_Y & 0xFF); // Least significant bits
    Output_Array[4] = (uint8_t)((Output_Y >> 8) & 0xFF); // Most significant bits
    
    // Channel Z
    Output_Array[5] = (uint8_t)(Output_Z & 0xFF); // Least significant bits
    Output_Array[6] = (uint8_t)((Output_Z >> 8) & 0xFF); // Most significant bits
    
    // Transmission
    UART_Debug_PutArray(Output_Array, BYTES_TO_SEND);
}
/* [] END OF FILE */
