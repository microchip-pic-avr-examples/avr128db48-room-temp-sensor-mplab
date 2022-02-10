#ifndef TEMPMONITOR_H
#define	TEMPMONITOR_H

#ifdef	__cplusplus
extern "C" {
#endif
    
#include <stdbool.h>
#include <stdint.h>
        
//Default Temperature Unit for Printing
#define DEFAULT_TEMP_UNIT 'F'

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

