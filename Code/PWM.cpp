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
#define PWM_max 500

void setPWM_DutyCycle(uint16_t DC);

void main(void) {
    // -------------[Configuration part]----------------
    // Configure the CCP1 module for PWM operation
    CCP1M2 = 1;
    CCP1M3 = 1;
    
    // Set CCP1 pin as output of PWM
    TRISC2 = 0; //RC2 pin as output
    
    // Set the PWM period 
    PR2 = 124;
    
    // Set the Timer2 prescaler value and enable Timer2
    T2CKPS0 = 1;
    T2CKPS1 = 0;
    
    TMR2ON = 1;
    
    
    // -------------[Operation part]----------------
    uint16_t DC = 0;
    while(1){
        while(DC < PWM_max){
            setPWM_DutyCycle(DC);
            DC++;
            __delay_ms(2);
        }
        __delay_ms(100);
        
        while(DC>0){
            setPWM_DutyCycle(DC);
            DC--;
            __delay_ms(2);
        }
        __delay_ms(100);
    }
    return;
}

void setPWM_DutyCycle(uint16_t DC){
    // Write to CCP1CON<5:4>
    CCP1Y = DC & (1<<0);
    CCP1X = DC & (1<<1);
    // Write to CCPR1L register
    CCPR1L = DC >> 2;
}
