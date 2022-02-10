#include "RTC.h"

#include <avr/io.h>
#include <avr/interrupt.h>

#include <stdint.h>
#include <stdbool.h>

void (*RTC_OVF_handler)(void);

static volatile bool RTCtriggered = false;

void RTC_init(void)
{
    //Clear Callbacks
    RTC_OVF_handler = 0;
    
    //Enable run in debug for the RTC
    RTC.DBGCTRL = RTC_DBGRUN_bm;
    
    //Enable Interrupt on Overflow
    RTC.INTCTRL = RTC_OVF_bm;
    
    //Run from 32.768kHz Internal Oscillator
    RTC.CLKSEL = RTC_CLKSEL_OSC32K_gc;
    
    //Wait for sync before modifying...
    while (RTC.STATUS & RTC_PERBUSY_bm);
    
    //Set Period to 0.5s 
    //0x0F0 = 128
    RTC.PER = 0xF0;
    
    //Wait for sync before modifying...
    while (RTC.STATUS & RTC_CTRLABUSY_bm);
    
    //Run the RTC in Standby, Prescaler is 128, Enable RTC
    RTC.CTRLA = RTC_RUNSTDBY_bm | RTC_PRESCALER_DIV128_gc | RTC_RTCEN_bm;
}

//Set the OVF Callback Function
void RTC_setOVFCallback(void (*func)(void))
{
    RTC_OVF_handler = func;
}

uint16_t RTC_getPeriod(void)
{
    return RTC.PER;
}

void RTC_setPeriod(uint16_t period)
{
    while (RTC.STATUS & RTC_CTRLABUSY_bm);
    
    //Turn off the RTC
    RTC.CTRLA &= ~(RTC_RTCEN_bm);
    
    while (RTC.STATUS & RTC_CNTBUSY_bm);
    
    //Clear Counter
    RTC.CNT = 0x0000;
    
    while (RTC.STATUS & RTC_PERBUSY_bm);
    
    //Write Value
    RTC.PER = period;
 
    while (RTC.STATUS & RTC_CTRLABUSY_bm);
    
    //Reset the RTC
    RTC.CTRLA |= RTC_RTCEN_bm;
}

//Returns true if RTC was triggered
bool RTC_isRTCTriggered(void)
{
    return RTCtriggered;
}

//Clears RTC Triggered Flag
void RTC_clearRTCTrigger(void)
{
    RTCtriggered = false;
}

ISR(RTC_CNT_vect)
{
    
//    if (RTC.INTFLAGS | RTC_OVF_bm)
//    {
        //Overflow Flag
    
        //Set RTC Trigger Flag
        RTCtriggered = true;

        
        //If callback is set...
        if (RTC_OVF_handler)
        {
            RTC_OVF_handler();
        }
//    }
    
    //Clear OVF Flag
    RTC.INTFLAGS |= RTC_OVF_bm;
}