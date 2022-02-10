#include <stdint.h>

#ifndef PRINTUTILITY_H
#define	PRINTUTILITY_H

#ifdef	__cplusplus
extern "C" {
#endif
        
#define PRINT_BUFFER_SIZE 255
    
    //Returns the Address of the character buffer
    char* USB_getCharBuffer(void);
    
    //Returns the size of the char buffer
    uint8_t USB_getCharBufferSize(void);
    
    //Prints the string on the UART
    void USB_sendBufferedString(void);
    
    //Prints a constant string to the UART
    void USB_sendString(const char* text);
    
    //Prints a specially formatted packet for MPLAB Data Visualizer
    //Inputs are the binary representation of the floating point values
    //Byte 0 - 3 = room temperature, 4 - 7 = sensor temperature
    void USB_sendResults(uint32_t roomTemp, uint32_t sensTemp);
    
#ifdef	__cplusplus
}
#endif

#endif	/* PRINTUTILITY_H */

