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
    File ErrorCodes.h
    Functions that defines the error codes that are the outputs of the I2C functions
    Author: Daniela Garofalo
*/
    
#ifndef __ERRORCODES_H__
    #define __ERRORCODES_H__
    
    /* Definition of a new variable type whose values that econde for the occurrence or not 
    of an error during the communication */
    typedef enum
    {
        NO_ERROR, // NO errors: the communication is successful
        ERROR     // Occurrence of an error: segnalation to the user with the UART_Debug
    } ErrorCode;
#endif
    
/* [] END OF FILE */
