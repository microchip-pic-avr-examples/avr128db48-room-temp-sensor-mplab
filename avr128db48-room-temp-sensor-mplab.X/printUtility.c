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

//Prints a specially formatted packet for MPLAB Data Visualizer
//Byte 0 - 3 = room temperature, 4 - 7 = sensor temperature
void USB_sendResults(uint32_t roomTemp, uint32_t sensTemp)
{
    //10 bytes to send
    uint8_t packet[10];
    
    //Header Start
    packet[0] = 0xAA;
    
    packet[1] = (((0xFF << 0) & roomTemp) >> 0) & 0xFF;
    packet[2] = (((0xFF00) & roomTemp) >> 8) & 0xFF;
    packet[3] = (((0xFF0000) & roomTemp) >> 16) & 0xFF;
    packet[4] = (((0xFF000000) & roomTemp) >> 24) & 0xFF;
    
    packet[5] = (((0xFF) & sensTemp) >> 0) & 0xFF;
    packet[6] = (((0xFF00) & sensTemp) >> 8) & 0xFF;
    packet[7] = (((0xFF0000) & sensTemp) >> 16) & 0xFF;
    packet[8] = (((0xFF000000) & sensTemp) >> 24) & 0xFF;
    
    //Head End
    packet[9] = 0x55;
    
    uint8_t index = 0;
    
    //Clear USART Done Flag
    USART3.STATUS |= USART_TXCIF_bm;
    
    //Send data
    while (index < 10)
    {
        while (!USART3_canTransmit());
        
        USART3_sendByte(packet[index]);
        index++;
    }
    
    //Wait for completion of UART
    while (!USART3_canTransmit());
    while (USART3_isBusy());

}
