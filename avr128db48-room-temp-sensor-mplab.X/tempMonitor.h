/*
© 2022 Microchip Technology Inc. and its subsidiaries

Subject to your compliance with these terms, you may use Microchip software and any derivatives exclusively with Microchip products. You are responsible for complying with 3rd party license terms applicable to your use of 3rd party software (including open source software) that may accompany Microchip software. SOFTWARE IS “AS IS.” NO WARRANTIES, WHETHER EXPRESS, IMPLIED OR STATUTORY, APPLY TO THIS SOFTWARE, INCLUDING ANY IMPLIED WARRANTIES OF NON-INFRINGEMENT, MERCHANTABILITY, OR FITNESS FOR A PARTICULAR PURPOSE. IN NO EVENT WILL MICROCHIP BE LIABLE FOR ANY INDIRECT, SPECIAL, PUNITIVE, INCIDENTAL OR CONSEQUENTIAL LOSS, DAMAGE, COST OR EXPENSE OF ANY KIND WHATSOEVER RELATED TO THE SOFTWARE, HOWEVER CAUSED, EVEN IF MICROCHIP HAS BEEN ADVISED OF THE POSSIBILITY OR THE DAMAGES ARE FORESEEABLE. TO THE FULLEST EXTENT ALLOWED BY LAW, MICROCHIP’S TOTAL LIABILITY ON ALL CLAIMS RELATED TO THE SOFTWARE WILL NOT EXCEED AMOUNT OF FEES, IF ANY, YOU PAID DIRECTLY TO MICROCHIP FOR THIS SOFTWARE
*/

#ifndef TEMPMONITOR_H
#define	TEMPMONITOR_H

#ifdef	__cplusplus
extern "C" {
#endif

#include <stdbool.h>
#include <stdint.h>

//Default Temperature Unit for Printing
#define DEFAULT_TEMP_UNIT 'F'

//If set, the output of this is formatted for the Data Visualizer's Variable Streamer
//If NOT set, the output is in plaintext
#define DV_FLOAT_OUT

    //Init the Temp Monitor
    void tempMonitor_init(bool safeStart);

    //Run the Temp Monitor's Finite State Machine
    void tempMonitor_FSM(void);

    //Returns true if results are ready
    bool tempMonitor_getResultStatus(void);

    //Call this function to print the temp results to the Bluetooth UART Interface
    void tempMonitor_printResults(void);

#ifdef	__cplusplus
}
#endif

#endif	/* TEMPMONITOR_H */
