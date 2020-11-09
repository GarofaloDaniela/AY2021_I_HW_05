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
                                        uint8_t register_count,
                                        uint8_t* data)
{
    /* Send start condition: WRITE command in order to communicate the device and the
    register addresses to the slave peripheral */
    uint8_t error = I2C_MasterSendStart(device_address, I2C_WRITE_XFER_MODE);
    if (error == I2C_MSTR_NO_ERROR)
    {
        // Write address of register to be read with the MSB equal to 1
        register_address |= 0x80; // Datasheet indication for multi read -- autoincrement
        error = I2C_MasterWriteByte(register_address);
        if (error == I2C_MSTR_NO_ERROR)
        {
            /* Send restart condition: READ command in order to communicate to the device
            the necessity to upload the asked data on the bus */
            error = I2C_MasterSendRestart(device_address, I2C_READ_XFER_MODE);
            if (error == I2C_MSTR_NO_ERROR)
            {
                // Continue reading until we have register to read
                uint8_t counter = register_count;
                while(counter > 1)
                {
                    // Sending an ACK to continue the trasmission
                    data[register_count - counter] = I2C_MasterReadByte(I2C_ACK_DATA);
                    // Decreasing the counter 
                    counter--;
                }
                
                // Sending a NACK to end the transmission
                data[register_count-1] = I2C_MasterReadByte(I2C_NAK_DATA);
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

void I2C_CommunicationInitRegister()
{
    /********  Reading the WHO AM I REGISTER  ******/
    ErrorCode error = I2C_CommunicationReadRegister(LIS3DH_DEVICE_ADDRESS,
                                                    LIS3DH_WHO_AM_I_REG_ADDRESS,
                                                    1, 
                                                    &who_am_i_register);
    if (error == NO_ERROR)
    {
        sprintf(message, "WHO AM I REGISTER address: 0x%02X\r\n", who_am_i_register);
        UART_Debug_PutString(message);
    }
    else
    {
        UART_Debug_PutString("Error occurred during I2C communication with WHO AM I REGISTER");
    }
    
    /******  Reading the STATUS REGISTER  ******/
    error = I2C_CommunicationReadRegister(LIS3DH_DEVICE_ADDRESS,
                                          LIS3DH_STATUS_REG_ADDRESS,
                                          1, 
                                          &status_register);
    if (error == NO_ERROR)
    {
        sprintf(message, "STATUS REGISTER address: 0x%02X\r\n", status_register);
        UART_Debug_PutString(message);
    }
    else
    {
        UART_Debug_PutString("Error occurred during I2C communication with STATUS REGISTER");
    }
    
    /******  Reading the CONTROL REGISTER 1  ******/
    error = I2C_CommunicationReadRegister(LIS3DH_DEVICE_ADDRESS,
                                          LIS3DH_CTRL_REG1_ADDRESS,
                                          1, 
                                          &ctrl_register_1);
    if (error == NO_ERROR)
    {
        sprintf(message, "CONTROL REGISTER 1 address: 0x%02X\r\n", ctrl_register_1);
        UART_Debug_PutString(message);
    }
    else
    {
        UART_Debug_PutString("Error occurred during I2C communication with CONTROL REGISTER 1");
    }
    
    /******  Reading the CONTROL REGISTER 4  ******/
    error = I2C_CommunicationReadRegister(LIS3DH_DEVICE_ADDRESS,
                                          LIS3DH_CTRL_REG4_ADDRESS,
                                          1, 
                                          &ctrl_register_4);
    if (error == NO_ERROR)
    {
        sprintf(message, "CONTROL REGISTER 4 address: 0x%02X\r\n", ctrl_register_4);
        UART_Debug_PutString(message);
    }
    else
    {
        UART_Debug_PutString("Error occurred during I2C communication the CONTROL REGISTER 4");
    }
}

void I2C_CommunicationSetRegister()
{
    /******  Setting the configurations for the CONTROL REGISTER 1  ******/
    if (ctrl_register_1 != LIS3DH_CTRL_REG1_SETTINGS)
    {
        ctrl_register_1 = LIS3DH_CTRL_REG1_SETTINGS;
    }
    ErrorCode error = I2C_CommunicationWriteRegister(LIS3DH_DEVICE_ADDRESS,
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
        sprintf(message, "CONTROL REGISTER 4 is setted equal to: 0x%02X\r\n", ctrl_register_4);
        UART_Debug_PutString(message);
    }
    else
    {
        UART_Debug_PutString("Error occurred during I2C communication with CONTROL REGISTER 4");
    }
}

void I2C_CommunicationAvaiableData()
{
    if (status_register == LIS3DH_STATUS_REG_AVAILABLEDATA)
    {
        switch (status_register << 5) /* Considering only the 3 least significat bits associated
        to the presence of available data for each signle channel of the accelerometer */
        {
            case LIS3DH_STATUS_REG_AVAILABLEX:
            {
                // Read the data register in order to save the available data
                ErrorCode error = I2C_CommunicationReadRegister(LIS3DH_DEVICE_ADDRESS,
                                                                LIS3DH_OUT_X_L,
                                                                2,
                                                                X_data);
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
            case LIS3DH_STATUS_REG_AVAILABLEY:
            {
                // Read the data register in order to save the available data
                ErrorCode error = I2C_CommunicationReadRegister(LIS3DH_DEVICE_ADDRESS,
                                                                LIS3DH_OUT_Y_L,
                                                                2,
                                                                Y_data);
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
            case LIS3DH_STATUS_REG_AVAILABLEZ:
            {
                // Read the data register in order to save the available data
                ErrorCode error = I2C_CommunicationReadRegister(LIS3DH_DEVICE_ADDRESS,
                                                                LIS3DH_OUT_Z_L,
                                                                2,
                                                                Z_data);
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
        }
        // Transmission of the data through the I2C communication protocol
        I2C_CommunicationTransmission();
    }
}

int16 I2C_CommunicationConversion(uint8_t *data)
{
    // Output value expressed in digit
    int16 output_data = (int16)((data[0] | data[1] << 8) >> 4);
    
    // Conversion from digit to g
    output_data = M_COEFFICIENT_DIGIT_TO_G * output_data + Q_COEFFICIENT_DIGIT_TO_G;
    
    // Conversion from g to accelerations expressed in [m/s^2]
    output_data = M_COEFFICIENT_G_TO_ACC * output_data + Q_COEFFICIENT_G_TO_ACC;
    
    /* Conversion from a float number to an unsigned integer in order to transfer
    correctly the data through the I2C communication protocol */
    output_data = output_data * 1000;
    
    // Return the converted value
    return output_data;
}

void I2C_CommunicationTransmission()
{
    // Channel X
    Output_Array[1] = (uint8_t)(Output_X & 0xFF); // Least significant bits
    Output_Array[2] = (uint8_t)(Output_X >> 8); // Most significant bits
    
    // Channel Y
    Output_Array[3] = (uint8_t)(Output_Y & 0xFF); // Least significant bits
    Output_Array[4] = (uint8_t)(Output_Y >> 8); // Most significant bits
    
    // Channel Z
    Output_Array[5] = (uint8_t)(Output_Z & 0xFF); // Least significant bits
    Output_Array[6] = (uint8_t)(Output_Z >> 8); // Most significant bits
    
    // Transmission
    UART_Debug_PutArray(Output_Array, BYTES_TO_SEND);
}
/* [] END OF FILE */
