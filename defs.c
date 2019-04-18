#include <xc.h>
#include <pic.h>
#include "Functions_Globals.h"



void Lab2_WriteDAQ(short WriteValue){
    
    char c = WriteValue & 0xff;
    DAC5REFL = c;
    
    char d = WriteValue >> 8;
    DAC5REFH = d;
    DAC5LD = 1;
    
}

void Lab2_ConfigureTimer2(char TimerPeriod_us)
{
    // Set the system clock speed to 32MHz.
    OSCCON = 0xF4;
    
    //Wait for the oscillator to switch to its new speed.
    while(OSCSTATbits.HFIOFR == 0);
    
    // T2PR: TMR2 PERIOD REGISTER (Page 287)
    // The timer runs at 1MHz, so it increments every 1us.
    T2PR = TimerPeriod_us;
    
    // T2CLKCON: TIMER2 CLOCK SELECTION REGISTER (Page 306))
    // Bits 8:4 = 0b00000   These bits are not implemented
    // Bits 3:0 = 0b0010    Clock source is the system clock
    T2CLKCON = 0x02;

    // T2CON: TIMERx CONTROL REGISTER (Page 307)
    // Bit  7   = 0b1       Timer is on.
    // Bits 6:4 = 0b101     Prescaler is 1:32 (Timer increments every 32 cycles)
    // Bits 3:0 = 0b0000    Postscaler is 1:1 
    T2CON = 0xD0;
            
    // TMR2IF is an interrupt flag, and is set whenever Timer2 expires.
    // We are not using interrupts, but it can still be checked manually.
    // It is cleared here as we start the timer.
    PIR1bits.TMR2IF = 0;
    
    return;
}

char buttonPress(void) {

    static char buttonValue = 255;

    //Remember the previous state
    char previousButtonValue = buttonValue;
    
    //Reset buttonValue, then check for a new button press
    buttonValue = 255;
    PORTAbits.RA7 = 1;
            
    if(PORTAbits.RA3 == 1)
        buttonValue = 1;
    if (PORTAbits.RA2 ==1)
        buttonValue = 2;
    if (PORTAbits.RA1 ==1)
        buttonValue = 3;
    if (PORTAbits.RA0 ==1)
        buttonValue = 'A'; //A
    
    PORTAbits.RA7 = 0;
    PORTAbits.RA6 = 1;
    
    if (PORTAbits.RA3 ==1)
        buttonValue = 4;
    if (PORTAbits.RA2 ==1)
        buttonValue = 5;
    if (PORTAbits.RA1 ==1)
        buttonValue = 6;
    if (PORTAbits.RA0 ==1)
        buttonValue = 'B'; //B
    
    PORTAbits.RA6 = 0;
    PORTAbits.RA5 = 1;
    
    if(PORTAbits.RA3 ==1)
        buttonValue = 7;
    if (PORTAbits.RA2 ==1)
        buttonValue = 8;
    if (PORTAbits.RA1 ==1)
        buttonValue = 9;
    if (PORTAbits.RA0 ==1)
        buttonValue = 'C'; //C
    
    PORTAbits.RA5 = 0; 
    PORTAbits.RA4 = 1;
    
    if (PORTAbits.RA3 ==1)
        buttonValue = 35; //*
    if (PORTAbits.RA2 ==1)
        buttonValue = 0;
    if (PORTAbits.RA1 ==1)
        buttonValue = 42; //#
    if (PORTAbits.RA0 ==1)
        buttonValue = 'D'; //D
     
        PORTAbits.RA4 = 0;

    
    //If the previous state was "nothing pressed"
    //return the current button state
    if (previousButtonValue == 255) return buttonValue;
    
    //If the previous button state is "something pressed"
    //Don't return a duplicate value until the button is released
    else return 255;
    
}
