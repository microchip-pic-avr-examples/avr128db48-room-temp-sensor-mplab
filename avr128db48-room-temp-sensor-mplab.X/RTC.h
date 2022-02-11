/*
© 2022 Microchip Technology Inc. and its subsidiaries

Subject to your compliance with these terms, you may use Microchip software and any derivatives exclusively with Microchip products. You are responsible for complying with 3rd party license terms applicable to your use of 3rd party software (including open source software) that may accompany Microchip software. SOFTWARE IS “AS IS.” NO WARRANTIES, WHETHER EXPRESS, IMPLIED OR STATUTORY, APPLY TO THIS SOFTWARE, INCLUDING ANY IMPLIED WARRANTIES OF NON-INFRINGEMENT, MERCHANTABILITY, OR FITNESS FOR A PARTICULAR PURPOSE. IN NO EVENT WILL MICROCHIP BE LIABLE FOR ANY INDIRECT, SPECIAL, PUNITIVE, INCIDENTAL OR CONSEQUENTIAL LOSS, DAMAGE, COST OR EXPENSE OF ANY KIND WHATSOEVER RELATED TO THE SOFTWARE, HOWEVER CAUSED, EVEN IF MICROCHIP HAS BEEN ADVISED OF THE POSSIBILITY OR THE DAMAGES ARE FORESEEABLE. TO THE FULLEST EXTENT ALLOWED BY LAW, MICROCHIP’S TOTAL LIABILITY ON ALL CLAIMS RELATED TO THE SOFTWARE WILL NOT EXCEED AMOUNT OF FEES, IF ANY, YOU PAID DIRECTLY TO MICROCHIP FOR THIS SOFTWARE
*/

#ifndef RTC_H
#define	RTC_H

#ifdef	__cplusplus
extern "C" {
#endif

#include <stdint.h>
#include <stdbool.h>

    //Configures the RTC and PIT
    void RTC_init(void);

    //Set the OVF Callback Function
    void RTC_setOVFCallback(void (*func)(void));

    //Set the PIT Callback Function
    void RTC_setPITCallback(void (*func)(void));

    //Returns the period of the RTC
    uint16_t RTC_getPeriod(void);

    //Sets the period of the RTC
    void RTC_setPeriod(uint16_t period);

    //Returns true if RTC was triggered
    bool RTC_isRTCTriggered(void);

    //Clears RTC Triggered Flag
    void RTC_clearRTCTrigger(void);

#ifdef	__cplusplus
}
#endif

#endif	/* RTC_H */
