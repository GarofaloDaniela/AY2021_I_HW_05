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

void I2C_CommunicationInit()
{
    
}

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

/* [] END OF FILE */
