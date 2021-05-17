#include <xc.h>
#include <stdint.h>

#pragma config FOSC = HS        // Oscillator Selection bits (XT oscillator)
#pragma config WDTE = OFF       // Watchdog Timer Enable bit (WDT disabled)
#pragma config PWRTE = ON       // Power-up Timer Enable bit (PWRT enabled)
#pragma config BOREN = ON       // Brown-out Reset Enable bit (BOR enabled)
#pragma config LVP = OFF        // Low-Voltage (Single-Supply) In-Circuit Serial Programming Enable bit (RB3 is digital I/O, HV on MCLR must be used for programming)
#pragma config CPD = OFF        // Data EEPROM Memory Code Protection bit (Data EEPROM code protection off)
#pragma config WRT = OFF        // Flash Program Memory Write Enable bits (Write protection off; all program memory may be written to by EECON control)
#pragma config CP = OFF         // Flash Program M

#define _XTAL_FREQ 20000000

uint16_t activity = 0;

void main(void) {
    TRISD = 0x00;               // Set direction of port D as Output
    TRISB = 0xFF;               // Set direction of port B as Input
    PORTD = 0xFF;               // Set value of port D as 0xFF
    TRISC2 = 0;
    
    INTEDG = 1;                 // Interrupt edge config bit (HIGH value means interrupt occurs every rising edge)
    INTE = 1;                   // IRQ (Interrupt request pin RB0) Interrupt Enable bit
    GIE = 1;                    // Global Interrupt Enable bit
    
    while(1){
        if(activity == 0){
	        RC2 = 0;
	    }
		else
		{
			RC2 = 1;
		}
    }
}

void __interrupt() ISR(void){
    if(INTF == 1){               // Check the flag bit 
    	activity++;
        if(activity > 1){
			activity = 0;
		}
        INTF = 0;
    }                   
} 
