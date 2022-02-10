/*
 * MAIN Generated Driver File
 * 
 * @file main.c
 * 
 * @defgroup main MAIN
 * 
 * @brief This is the generated driver implementation file for the MAIN driver.
 *
 * @version MAIN Driver Version 1.0.0
*/

/*
© [2022] Microchip Technology Inc. and its subsidiaries.

    Subject to your compliance with these terms, you may use Microchip 
    software and any derivatives exclusively with Microchip products. 
    You are responsible for complying with 3rd party license terms  
    applicable to your use of 3rd party software (including open source  
    software) that may accompany Microchip software. SOFTWARE IS ?AS IS.? 
    NO WARRANTIES, WHETHER EXPRESS, IMPLIED OR STATUTORY, APPLY TO THIS 
    SOFTWARE, INCLUDING ANY IMPLIED WARRANTIES OF NON-INFRINGEMENT,  
    MERCHANTABILITY, OR FITNESS FOR A PARTICULAR PURPOSE. IN NO EVENT 
    WILL MICROCHIP BE LIABLE FOR ANY INDIRECT, SPECIAL, PUNITIVE, 
    INCIDENTAL OR CONSEQUENTIAL LOSS, DAMAGE, COST OR EXPENSE OF ANY 
    KIND WHATSOEVER RELATED TO THE SOFTWARE, HOWEVER CAUSED, EVEN IF 
    MICROCHIP HAS BEEN ADVISED OF THE POSSIBILITY OR THE DAMAGES ARE 
    FORESEEABLE. TO THE FULLEST EXTENT ALLOWED BY LAW, MICROCHIP?S 
    TOTAL LIABILITY ON ALL CLAIMS RELATED TO THE SOFTWARE WILL NOT 
    EXCEED AMOUNT OF FEES, IF ANY, YOU PAID DIRECTLY TO MICROCHIP FOR 
    THIS SOFTWARE.
*/

#include <avr/io.h>
#include <avr/interrupt.h>

#include <stdint.h>
#include <stdbool.h>

#include "GPIO.h"

#include "tempMonitor.h"

#include "usart3.h"

#include "TWI0_host.h"

#include "system.h"
#include "TCB0_oneShot.h"
#include "RTC.h"
#include "printUtility.h"

int main(void)
{
    //Init System / Core Peripherals
    System_initDevice();
    
    //Init Peripherals and IO
    System_initPeripherals();
                
    //This boolean is used to determine if reset to defaults is required
    bool safeStart = SW0_GetValue();
            
    //Init State Machines
    tempMonitor_init(safeStart);
        
    //Start Interrupts
    sei();
        
    while(1)
    {                                                
        //Run the thermometer state machine
        tempMonitor_FSM();
        
        //If ready to print results...
        if (tempMonitor_getResultStatus())
        {
            tempMonitor_printResults();
        }
        
        //Return to Sleep
        asm("SLEEP");
        
    }    
}