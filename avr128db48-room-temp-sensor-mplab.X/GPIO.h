/*
© 2022 Microchip Technology Inc. and its subsidiaries

Subject to your compliance with these terms, you may use Microchip software and any derivatives exclusively with Microchip products. You are responsible for complying with 3rd party license terms applicable to your use of 3rd party software (including open source software) that may accompany Microchip software. SOFTWARE IS “AS IS.” NO WARRANTIES, WHETHER EXPRESS, IMPLIED OR STATUTORY, APPLY TO THIS SOFTWARE, INCLUDING ANY IMPLIED WARRANTIES OF NON-INFRINGEMENT, MERCHANTABILITY, OR FITNESS FOR A PARTICULAR PURPOSE. IN NO EVENT WILL MICROCHIP BE LIABLE FOR ANY INDIRECT, SPECIAL, PUNITIVE, INCIDENTAL OR CONSEQUENTIAL LOSS, DAMAGE, COST OR EXPENSE OF ANY KIND WHATSOEVER RELATED TO THE SOFTWARE, HOWEVER CAUSED, EVEN IF MICROCHIP HAS BEEN ADVISED OF THE POSSIBILITY OR THE DAMAGES ARE FORESEEABLE. TO THE FULLEST EXTENT ALLOWED BY LAW, MICROCHIP’S TOTAL LIABILITY ON ALL CLAIMS RELATED TO THE SOFTWARE WILL NOT EXCEED AMOUNT OF FEES, IF ANY, YOU PAID DIRECTLY TO MICROCHIP FOR THIS SOFTWARE
*/

#ifndef GPIO_H
#define	GPIO_H

#ifdef	__cplusplus
extern "C" {
#endif

#include <avr/io.h>

#define SW0_GetValue() (VPORTB.IN & PIN2_bm)

#define LED0_SetHigh() do { PORTB.OUTSET = PIN3_bm; } while(0)
#define LED0_SetLow() do { PORTB.OUTCLR = PIN3_bm; } while(0)
#define LED0_Toggle() do { PORTB.OUTTGL = PIN3_bm; } while(0)

#define RN4870_MODE_SetHigh() do { PORTD.OUTSET = PIN0_bm; } while(0)
#define RN4870_MODE_SetLow() do { PORTD.OUTCLR = PIN0_bm; } while(0)
#define RN4870_MODE_Toggle() do { PORTD.OUTTGL = PIN0_bm; } while(0)

#define DBG_OUT_SetHigh() do { PORTD.OUTSET = PIN2_bm; } while(0)
#define DBG_OUT_SetLow() do { PORTD.OUTCLR = PIN2_bm; } while(0)
#define DBG_OUT_Toggle() do { PORTD.OUTTGL = PIN2_bm; } while(0)


    //Inits. General Purpose I/O
    void GPIO_init(void);


#ifdef	__cplusplus
}
#endif

#endif	/* GPIO_H */
