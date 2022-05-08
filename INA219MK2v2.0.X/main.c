#define FCY 16000000UL 
#include <assert.h>
#include <stdbool.h>
#include "mcc_generated_files/system.h"
#include <stdio.h>
#include <stdlib.h>
#include <libpic30.h>
#include <xc.h>
#include <string.h>
#include "mcc_generated_files/i2c1.h"
#include "ina219.h"

#if defined(__dsPIC33E__)
	#include <p33exxxx.h>
#elif defined(__dsPIC33F__)
	#include <p33fxxxx.h>
#elif defined(__dsPIC30F__)
	#include <p30fxxxx.h>
#elif defined(__PIC24E__)
	#include <p24exxxx.h>
#elif defined(__PIC24H__)
	#include <p24hxxxx.h>
#elif defined(__PIC24F__) || defined(__PIC24FK__)
	#include <p24fxxxx.h>
#endif

float   shunt_mV;                                   // definiert "shunt_mV"
float   bus_voltage;                                // definiert "bus_voltage"
float   power_mW;                                   // definiert "power_mW"
float   current_mA;                                 // definiert "current_mA"
    
/*
                         Main application
 */
int main(void){                                         // "main"
    SYSTEM_Initialize();                                // ruft "SYSTEM_Initialize" auf
    __delay_ms(500);                                    // warte 500ms
    INA219_Initialize();                                // ruft "INA219_Initialize" auf
    INA219_setCalibration_32V_2A();                     // ruft "INA219_setCalibration_32V_2A" auf
    //INA219_setCalibration_32V_1A();                     // ruft "INA219_setCalibration_32V_1A" auf
    //INA219_setCalibration_16V_400mA();                  // ruft "INA219_setCalibration_16V_400mA" auf
    //INA219_setCalibration_16V_32A();                    // ruft "INA219_setCalibration_16V_32A" auf
    
    while (1){                                          // Endloschleife
        shunt_mV = INA219_getShuntVoltage_mV();         // schreibt ergebnis von "INA219_getShuntVoltage_mV" in "Shunt_Voltage"
        bus_voltage = INA219_getBusVoltage_V();         // schreibt ergebnis von "INA219_getBusVoltage_V" in "Bus_Voltage"
        power_mW = INA219_getPower_mW();                // schreibt ergebnis von "INA219_getPower_mW" in "Power"
        current_mA = INA219_getCurrent_mA();            // schreibt ergebnis von "INA219_getCurrent_mA" in "Current"
        current_mA = current_mA / 10;                   // current_mA geteilt durch 10

        printf("Shunt-Spannung: %.2fmV \r\n",shunt_mV);     // schreibt "Shunt-Spannung: %fV \r\n" an UART  
        printf("BUS-Spannung:   %.2fV \r\n",bus_voltage);   // schreibt "BUS-Spannung: %fV \r\n" an UART  
        printf("Leistung:       %.2fmW \r\n",power_mW);     // schreibt "Leistung: %fmW \r\n" an UART  
        printf("Strom:          %.2fmA \r\n",current_mA);   // schreibt "Strom: %fmA \r\n" an UART  
        
        __delay_ms(500);                                // warte 500ms
    }                                                   // 
}                                                       // 
    
