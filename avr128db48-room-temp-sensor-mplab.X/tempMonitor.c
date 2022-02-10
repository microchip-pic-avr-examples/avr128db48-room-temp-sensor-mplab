#include "tempMonitor.h"
#include "MLX90632.h"

#include <stdbool.h>
#include <stdint.h>
#include <stdio.h>

#include "GPIO.h"
#include "EEPROM_Locations.h"
#include "printUtility.h"
#include "RTC.h"

#include <avr/io.h>
#include <avr/eeprom.h>

//State Machine for the main program
typedef enum  {
    TEMP_START = 0, TEMP_WAIT, TEMP_RESULTS, TEMP_ERROR_WAIT, TEMP_ERROR
} TemperatureMeasState;

//Temperature Measurement State Machine
static TemperatureMeasState tempState = TEMP_START;

//Set if results are ready to be printed
static bool temperatureResultsReady = false;

//If set to 'F', results will be printed in Fahrenheit
//Threshold inputs will be considered as numbers in Fahrenheit
static char tempUnit = DEFAULT_TEMP_UNIT;

//Init the Temp Monitor
void tempMonitor_init(bool safeStart)
{
    bool success;
    
    USB_sendString("Initializing MLX90632 Temperature Sensor...");
    if (safeStart)
    {
        //Button is Held - Safe Mode
        success = MLX90632_initDevice(true);
    }
    else
    {
        //Normal Init Sequence
        success = MLX90632_initDevice(false);
    }
            
    //EEPROM was successfully loaded
    if (MLX90632_cacheOK())
    {
        //Load EEPROM Value for RTC Period
        USB_sendString("\r\nLoaded cached constants and settings...");
        
        //Update RTC Timer
        RTC_setPeriod(eeprom_read_word((uint16_t*) TEMP_UPDATE_PERIOD));
    }
    else
    {
        //Write the default RTC Period to EEPROM
        USB_sendString("\r\nLoaded constants from sensor and reset to defaults...");
        
        //Write Default Sample Rate Value
        eeprom_write_word((uint16_t*) TEMP_UPDATE_PERIOD, RTC_getPeriod());        
    }
    
    //Print Result
    if (success)
    {
        USB_sendString("OK\r\n");
    }
    else
    {
        USB_sendString("FAILED\r\n");
        tempState = TEMP_ERROR;
    }
}

//Run the Temp Monitor's Finite State Machine
void tempMonitor_FSM(void)
{
    bool success;
    
    //MLX90632 Temperature Sensor State Machine
    switch (tempState)
    {
        case TEMP_START:
        {            
            //Start a temperature measurement
            success = MLX90632_startSingleConversion();

            //Move to the next state
            if (!success)
            {               
                USB_sendString("[ERR] Failed to start temp conversion in TEMP_START\r\n");
                tempState = TEMP_ERROR;
            }
            else
            {
                tempState = TEMP_WAIT;
            }

            break;
        }
        case TEMP_WAIT:
        {
            if (MLX90632_isDataReady())
            {
                //Get Results
                success = MLX90632_getResults();

                //Move to the next state
                if (!success)
                {
                    USB_sendString("[ERR] Failed to get temp data from MLX90632_getResults()\r\n");
                    tempState = TEMP_ERROR;
                }
                else
                {
                    tempState = TEMP_RESULTS;
                }
            }
            break;
        }
        case TEMP_RESULTS:
        {
            LED0_Toggle();

            //Compute Temperature
            success = MLX90632_computeTemperature();

            //Update State
            if (success)
            {
                temperatureResultsReady = true;
                tempState = TEMP_START;
            }
            else
            {
                USB_sendString("[ERR] Failed to compute temp from MLX90632_computeTemperature()\r\n");
                tempState = TEMP_ERROR;
            }
            
            break;
        }
        case TEMP_ERROR_WAIT:
        {
            //Wait...
            break;
        }
        case TEMP_ERROR:
        default:
        {
            tempState = TEMP_ERROR_WAIT;
        }
    }
}

//Returns true if results are ready
bool tempMonitor_getResultStatus(void)
{
    return temperatureResultsReady;
}

void tempMonitor_printResults(void)
{
    //Clear Flag
    temperatureResultsReady = false;
    
    //Get temp (in Celsius)
    float sensorTemp, objTemp;
    sensorTemp = MLX90632_getSensorTemp();
    objTemp = MLX90632_getObjectTemp();
    
    if (tempUnit == 'F')
    {
        //Convert to Fahrenheit
        sensorTemp = (sensorTemp * 1.8) + 32;
        objTemp = (objTemp * 1.8) + 32;
    }
    else if (tempUnit == 'K')
    {
        //Convert to Kelvin
        sensorTemp += 273.15;
        objTemp += 273.15;
    }
    else if (tempUnit != 'C')
    {
        //Invalid Units
        
        //Print Constant String
        USB_sendString("[WARN] Invalid Unit Specifier for Temperature: ");
        
        //Then call sprintf to print the value
        sprintf(USB_getCharBuffer(), "%c\r\n", tempUnit);
        USB_sendBufferedString();
    }
    
    //Queue Data to Send
    sprintf(USB_getCharBuffer(), "Sensor Temperature: %2.1f%c\r\nRoom Temperature: %2.1f%c\r\n\r\n",
        sensorTemp, tempUnit, objTemp, tempUnit);
    
    //Print String
    USB_sendBufferedString();
}