#include "system.h"

#include <avr/io.h>

#include "GPIO.h"
#include "TWI0_host.h"
#include "usart3.h"
#include "RTC.h"

FUSES = 
{
  .BODCFG = ACTIVE_DISABLE_gc | LVL_BODLEVEL0_gc | SAMPFREQ_128Hz_gc | SLEEP_DISABLE_gc,
  .BOOTSIZE = 0x0,
  .CODESIZE = 0x0,
  .OSCCFG = CLKSEL_OSCHF_gc,
  .SYSCFG0 = CRCSEL_CRC16_gc | CRCSRC_NOCRC_gc | RSTPINCFG_GPIO_gc,
  .SYSCFG1 = MVSYSCFG_DUAL_gc | SUT_16MS_gc,
  .WDTCFG = PERIOD_OFF_gc | WINDOW_OFF_gc,
};

//Inits CLKCTRL, EVSYS, WDT, and SLPCTRL
void System_initDevice(void)
{
    //Init CLKCTRL
    //Default is 4MHz, which is desired
    
    //Init SLPCTRL
    
    //Power Level = STANDBY, SLEEP ENABLED
    SLPCTRL.CTRLA = SLPCTRL_SMODE_STDBY_gc | SLPCTRL_SEN_bm;
}

//Inits peripherals
void System_initPeripherals(void)
{
    //Init GPIO
    GPIO_init();
                
    //Configure TWI0 for Thermometer
    TWI0_initHost();
    TWI0_initPins();
        
    //Configure USART 3 for USB
    USART3_init();
    USART3_initIO();
        
    //Enable USART for USB (TX Only)
    USART3_enableTX();
    
    //Init RTC
    RTC_init();
}