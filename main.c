#include <msp430.h>
#include "lcd_I2C.h"

void main(void)
{
    int adcValue = 0; // Declare an integer to store the ADC result

    // Stop the watchdog timer
    WDTCTL = WDTPW | WDTHOLD;

    // Clear P2OUT register
    P2OUT = 0;

    // Set all P2 pins as output
    P2DIR = 0xFF;

    // Select P1.2 for secondary function (e.g., Timer or Analog)
    P1SEL0 |= BIT2;
    P1SEL1 |= BIT2;

    // Unlock I/O pin configuration
    PM5CTL0 &= ~LOCKLPM5;

    // ADC setup
    ADCCTL0 = 0x0210; // Sample and hold time, ADC on
    //ADCCTL0 = ADCSHT_12 | ADCON;
    ADCCTL1 = 0x0220; // Source signal and clock selection
    ADCCTL2 = 0x0020; // ADC resolution and data format
    ADCMCTL0 = 0x0002; // Input channel selection

    I2C_Init(0x27);
    LCD_Setup();
    LCD_SetCursor(0, 0);

    while (1)
    {
        LCD_ClearDisplay();
        LCD_SetCursor(0, 0);
        //LCD_Write("DutyCycle=");
        LCD_WriteNum(adcValue);
        //LCD_SetCursor(0, 1);
        //LCD_Write("Input: ");
        //LCD_WriteNum(InputValue);

        // Start conversion
        ADCCTL0 |= 0x0213;

        // Wait for conversion to complete
        while (!(ADCIFG & BIT0));

        // Store result in the adcValue variable
        adcValue = ADCMEM0/40.95;

        // Store result in P2OUT
        P2OUT = adcValue;

        // No operation (can be used for debugging breakpoint)
        __no_operation();
        //__delay_cycles(100000);
    }
}
