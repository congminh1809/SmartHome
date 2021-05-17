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

#define _XTAL_FREQ 20000000      // PIC frequency (Hz)
#define Fpwm 200000              // PWM frequency (Hz)
#define ps 1                    // Prescaler = 1:1

void ADC_Init();
uint16_t ADC_Read(uint8_t ADC_channel);
void init_PWM();
void setPWM_DutyCycle(uint16_t DC);

void main(void) 
{
	// Init ADC module
    ADC_Init();
    
    // Init PWM mode for CCP1 module
    init_PWM();
    
    while(1){
        setPWM_DutyCycle(ADC_Read(0));
    }
    return;
}

void ADC_Init(){
    //------[There are 2 registers to configure ADCON0 and ADCON1]---------
    // ADCON0 = 0x41
    // Select clock option Fosc/8
    ADCS0 = 1;
    ADCS1 = 0;
    // Turn ADC on
    ADON = 1;
    
    //ADCON1 = 0x80
    // Result mode: Right justified
    ADFM = 1;
    // Select clock option Fosc/8
    ADCS2 = 0;
    // Configure all 8 channels are analog 
    PCFG0 = 0;
    PCFG1 = 1;
    PCFG2 = 0;
    PCFG3 = 0;
}

uint16_t ADC_Read(uint8_t ADC_channel){
    // Check channel number
    if(ADC_channel < 0 || ADC_channel > 7)
        return 0;
    
    // Write ADC__channel into register ADCON0
    CHS0 = (ADC_channel & 1) >> 0;
    CHS1 = (ADC_channel & 2) >> 1;
    CHS2 = (ADC_channel & 4) >> 2;
    
    // Wait the Acquisition time 
    __delay_us(25);
    
    // Start A/D conversion
    GO_DONE = 1;
    
    // (Polling) Wait for the conversion to complete
    while(GO_DONE);
    
    // Read the ADC result ("right justified" mode)
    uint16_t result = ((ADRESH << 8) + ADRESL);
    return result;
}

void init_PWM(){
    // Configure the CCP1 module for PWM operation
    CCP1M2 = 1;
    CCP1M3 = 1;
    
    // Set CCP1 pin as output
    TRISC2 = 0; //RC2 pin as output
    
    // Set the Timer2 prescaler value and enable Timer2
    switch(ps){
        case 1: {T2CKPS0 = 0;   T2CKPS1 = 0;    break;}
        case 4: {T2CKPS0 = 1;   T2CKPS1 = 0;    break;}
        case 16: T2CKPS1 = 0;   
    }
    
    TMR2ON = 1;
    
    // Set the PWM period 
    PR2 = ((float)(_XTAL_FREQ/Fpwm))/(4*ps)-1;
    // --------[Warning: Check if PR2 value fits in 8-bit register (0-255)]---------]
}

void setPWM_DutyCycle(uint16_t DC){
    // DC means % (Ex: DC = 50 means Duty Cycle = 50%)
    // uint16_t val = ((float)_XTAL_FREQ/(float)Fpwm)*((float)DC/(float)100)/ps;
    // Write to CCP1CON<5:4>
    CCP1Y = DC & (1<<0);
    CCP1X = DC & (1<<1);
    // Write to CCPR1L register
    CCPR1L = DC >> 2;
}
