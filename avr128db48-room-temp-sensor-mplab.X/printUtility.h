/*
© 2022 Microchip Technology Inc. and its subsidiaries

Subject to your compliance with these terms, you may use Microchip software and any derivatives exclusively with Microchip products. You are responsible for complying with 3rd party license terms applicable to your use of 3rd party software (including open source software) that may accompany Microchip software. SOFTWARE IS “AS IS.” NO WARRANTIES, WHETHER EXPRESS, IMPLIED OR STATUTORY, APPLY TO THIS SOFTWARE, INCLUDING ANY IMPLIED WARRANTIES OF NON-INFRINGEMENT, MERCHANTABILITY, OR FITNESS FOR A PARTICULAR PURPOSE. IN NO EVENT WILL MICROCHIP BE LIABLE FOR ANY INDIRECT, SPECIAL, PUNITIVE, INCIDENTAL OR CONSEQUENTIAL LOSS, DAMAGE, COST OR EXPENSE OF ANY KIND WHATSOEVER RELATED TO THE SOFTWARE, HOWEVER CAUSED, EVEN IF MICROCHIP HAS BEEN ADVISED OF THE POSSIBILITY OR THE DAMAGES ARE FORESEEABLE. TO THE FULLEST EXTENT ALLOWED BY LAW, MICROCHIP’S TOTAL LIABILITY ON ALL CLAIMS RELATED TO THE SOFTWARE WILL NOT EXCEED AMOUNT OF FEES, IF ANY, YOU PAID DIRECTLY TO MICROCHIP FOR THIS SOFTWARE
*/

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
