#include <avr/io.h>
#include <stdint.h>

#include "printUtility.h"

#include "usart3.h"

static char bufferUSB[PRINT_BUFFER_SIZE];

//Returns the Address of the character buffer
char* USB_getCharBuffer(void)
{
    return &bufferUSB[0];
}

//Returns the size of the char buffer
uint8_t USB_getCharBufferSize(void)
{
    return PRINT_BUFFER_SIZE;
}

//Prints the string on the UART
void USB_sendBufferedString(void)
{   
    if (bufferUSB[0] == '\0')
        return;
    
    uint8_t index = 0;
    
    //Clear USART Done Flag
    USART3.STATUS |= USART_TXCIF_bm;
    
    while ((bufferUSB[index] != '\0') && (index < PRINT_BUFFER_SIZE))
    {
        while (!USART3_canTransmit());
        
        USART3_sendByte(bufferUSB[index]);
        index++;
    }
    
    //Wait for completion of UART
    while (!USART3_canTransmit());
    while (USART3_isBusy());
}

//Prints a constant string to the UART
void USB_sendString(const char* text)
{
#ifdef DISABLE_STRING_MESSAGES
    return;
#else    
    if (text[0] == '\0')
        return;
    
    uint8_t index = 0;
    
    //Clear USART Done Flag
    USART3.STATUS |= USART_TXCIF_bm;
    
    while ((text[index] != '\0') && (index < 255))
    {
        while (!USART3_canTransmit());
        
        USART3_sendByte(text[index]);
        index++;
    }
    
    //Wait for completion of UART
    while (!USART3_canTransmit());
    while (USART3_isBusy());
#endif
}