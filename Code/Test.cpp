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

uint8_t counter0 = 0;


#define MAX_VALUE 200
	
uint8_t pulse_max = 0;
uint8_t pulse_top = 0;
uint8_t top_value = 185;


void main(void) 
{
    TRISD = 0x00;
    PORTD = 0xFF;
    TRISC = 0x00; //set all pins as Output
    PORTC = 0x00; //turn off portC
    
    // Config Interrupt cho Timer1
    TMR1IE = 1;                 // Timer1 Interrupt enable bit
    TMR1IF = 0;                 // Clear the Interrupt flag bit for timer1        
    PEIE = 1;                   // Peripherals Interrupts enable bit 
    GIE = 1;                    // Global Interrupt Enable bit
    
    // Config Timer1
    // Clear the Timer1 register to start counting from 65286
    TMR1 = 65286;                  
    // Clear the Timer1 clock select bit to choose local clock source
    TMR1CS = 0;                 
    // Prescaler ratio 1:1
    T1CKPS0 = 0;
    T1CKPS1 = 0;
    
    // Switch ON Timer1
    TMR1ON = 1;
	
	 
    while(1)
	{
    	
    }
}

void __interrupt() ISR(void)
{
    if(TMR1IE) // TIMER0 Interrupt Flag
	{	            
	    pulse_max++;            // Pulse Max Increment
	    pulse_top++;            // Pulse Top Increment
	
	 	/* top_value = MAX_VALUE - n, n=10: 10 x 0.02ms = 1.0ms, n=20: 20 x 0.1ms = 2.0ms */
	    /* 2ms -> CCW Rotation, 1ms -> CW Rotation */
	    if (pulse_top == top_value) 
		{
	      RC2 = 1;                // Turn On RC2
	    }
	    
	    /* MAX_VALUE = 1000 turn off the pulse */
	    if (pulse_max >= MAX_VALUE)
		{
	      pulse_max = 0;
	      pulse_top = 0;
	      RC2 = 0;                // Turn off RC2
	    }
	
	    TMR1 = 65286;             // Initial Value for 0.1ms Interrupt
	    TMR1IE = 0;		    // Clear TIMER0 interrupt flag
  	}
} 
