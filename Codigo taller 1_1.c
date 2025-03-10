/*
 * File:   newmain.c
 * Author: Nicolas Jr
 *
 * Created on 24 de febrero de 2025, 09:03 AM
 */



// CONFIG1H
#pragma config FOSC = XT        // Oscillator Selection bits (XT oscillator)
#pragma config PLLCFG = OFF     // 4X PLL Enable (Oscillator used directly)
#pragma config PRICLKEN = ON    // Primary clock enable bit (Primary clock is always enabled)
#pragma config FCMEN = OFF      // Fail-Safe Clock Monitor Enable bit (Fail-Safe Clock Monitor disabled)
#pragma config IESO = OFF       // Internal/External Oscillator Switchover bit (Oscillator Switchover mode disabled)

// CONFIG2L
#pragma config PWRTEN = ON      // Power-up Timer Enable bit (Power up timer enabled)
#pragma config BOREN = OFF      // Brown-out Reset Enable bits (Brown-out Reset disabled in hardware and software)
#pragma config BORV = 190       // Brown Out Reset Voltage bits (VBOR set to 1.90 V nominal)

// CONFIG2H
#pragma config WDTEN = OFF      // Watchdog Timer Enable bits (Watch dog timer is always disabled. SWDTEN has no effect.)
#pragma config WDTPS = 32768    // Watchdog Timer Postscale Select bits (1:32768)

// CONFIG3H
#pragma config CCP2MX = PORTC1  // CCP2 MUX bit (CCP2 input/output is multiplexed with RC1)
#pragma config PBADEN = OFF     // PORTB A/D Enable bit (PORTB<5:0> pins are configured as digital I/O on Reset)
#pragma config CCP3MX = PORTB5  // P3A/CCP3 Mux bit (P3A/CCP3 input/output is multiplexed with RB5)
#pragma config HFOFST = ON      // HFINTOSC Fast Start-up (HFINTOSC output and ready status are not delayed by the oscillator stable status)
#pragma config T3CMX = PORTC0   // Timer3 Clock input mux bit (T3CKI is on RC0)
#pragma config P2BMX = PORTD2   // ECCP2 B output mux bit (P2B is on RD2)
#pragma config MCLRE = EXTMCLR  // MCLR Pin Enable bit (MCLR pin enabled, RE3 input pin disabled)

// CONFIG4L
#pragma config STVREN = ON      // Stack Full/Underflow Reset Enable bit (Stack full/underflow will cause Reset)
#pragma config LVP = OFF        // Single-Supply ICSP Enable bit (Single-Supply ICSP disabled)
#pragma config XINST = OFF      // Extended Instruction Set Enable bit (Instruction set extension and Indexed Addressing mode disabled (Legacy mode))

// CONFIG5L
#pragma config CP0 = OFF        // Code Protection Block 0 (Block 0 (000800-001FFFh) not code-protected)
#pragma config CP1 = OFF        // Code Protection Block 1 (Block 1 (002000-003FFFh) not code-protected)
#pragma config CP2 = OFF        // Code Protection Block 2 (Block 2 (004000-005FFFh) not code-protected)
#pragma config CP3 = OFF        // Code Protection Block 3 (Block 3 (006000-007FFFh) not code-protected)

// CONFIG5H
#pragma config CPB = OFF        // Boot Block Code Protection bit (Boot block (000000-0007FFh) not code-protected)
#pragma config CPD = OFF        // Data EEPROM Code Protection bit (Data EEPROM not code-protected)

// CONFIG6L
#pragma config WRT0 = OFF       // Write Protection Block 0 (Block 0 (000800-001FFFh) not write-protected)
#pragma config WRT1 = OFF       // Write Protection Block 1 (Block 1 (002000-003FFFh) not write-protected)
#pragma config WRT2 = OFF       // Write Protection Block 2 (Block 2 (004000-005FFFh) not write-protected)
#pragma config WRT3 = OFF       // Write Protection Block 3 (Block 3 (006000-007FFFh) not write-protected)

// CONFIG6H
#pragma config WRTC = OFF       // Configuration Register Write Protection bit (Configuration registers (300000-3000FFh) not write-protected)
#pragma config WRTB = OFF       // Boot Block Write Protection bit (Boot Block (000000-0007FFh) not write-protected)
#pragma config WRTD = OFF       // Data EEPROM Write Protection bit (Data EEPROM not write-protected)

// CONFIG7L
#pragma config EBTR0 = OFF      // Table Read Protection Block 0 (Block 0 (000800-001FFFh) not protected from table reads executed in other blocks)
#pragma config EBTR1 = OFF      // Table Read Protection Block 1 (Block 1 (002000-003FFFh) not protected from table reads executed in other blocks)
#pragma config EBTR2 = OFF      // Table Read Protection Block 2 (Block 2 (004000-005FFFh) not protected from table reads executed in other blocks)
#pragma config EBTR3 = OFF      // Table Read Protection Block 3 (Block 3 (006000-007FFFh) not protected from table reads executed in other blocks)

// CONFIG7H
#pragma config EBTRB = OFF      // Boot Block Table Read Protection bit (Boot Block (000000-0007FFh) not protected from table reads executed in other blocks)

// #pragma config statements should precede project file includes.
// Use project enums instead of #define for ON and OFF.


#include <xc.h>
#define _XTAL_FREQ 4000000 

void CONF_PUERTOS(void);
void BORRAR_BASURA(void);
void RUTINA (void);
void LEER_OPERANDO_1(void);
void LEER_OPERANDO_2(void);
void LEER_OPERACION(void);
void FUNCION_ENTER(void);
void F_S(void);
void F_R(void);
void F_A(void);
void F_O(void);
void F_M(void);
void F_D(void);
void MOSTRAR_RESULTADO(void);
void ESTA_VIVO(void);

unsigned char OPERANDO_1;
unsigned char OPERANDO_2;
unsigned char selector;
unsigned char RESULTADO;

void main(void) 
{
    CONF_PUERTOS();
    BORRAR_BASURA();
    ESTA_VIVO();
    RUTINA();    
}

void CONF_PUERTOS(void)
{
    //76543210    
    TRISB = 0b00011111; // RB0-RB3 como entradas, RB4 como botón.
    TRISC = 0b00000000; // Puerto C como salida
    TRISD = 0b00000000; // Puerto D como salida
    ANSELB = 0b00000000; // Desactivar funciones analógicas en RB.
}

void BORRAR_BASURA(void)
{
    LATC = LATD = 0; 
    OPERANDO_1 = OPERANDO_2 = selector = RESULTADO = 0;
}

void RUTINA(void)
{
    FUNCION_ENTER();  
    LEER_OPERANDO_1();
    FUNCION_ENTER();
    LEER_OPERACION();
    FUNCION_ENTER();
    LEER_OPERANDO_2();  

    while(1)
    {
        MOSTRAR_RESULTADO();
    }    
}

void LEER_OPERANDO_1(void)
{
    OPERANDO_1 = PORTB & 0b00001111; // Leer bits bajos del puerto B.
}

void LEER_OPERACION(void)
{
    selector = PORTB & 0b00001111; // Leer bits bajos para la operación.
    switch(selector)
    {
        case 0: F_S(); break; // Suma
        case 1: F_R(); break; // Resta
        case 2: F_A(); break; // AND lógico
        case 3: F_O(); break; // OR lógico
        case 4: F_M(); break; // Multiplicación
        case 5: F_D(); break; // División
        default: 
            RESULTADO = 0; // Código de error.
            break;    
    }        
}

void LEER_OPERANDO_2(void)
{
    OPERANDO_2 = PORTB & 0b00001111; // Leer bits bajos del puerto B.
}

void FUNCION_ENTER(void)
{
    while(PORTBbits.RB4 == 1) {} // Esperar a que se presione el botón.
    __delay_ms(50); // Retardo para evitar rebotes.
    while(PORTBbits.RB4 == 0) {} // Esperar a que se suelte el botón.
    __delay_ms(50); // Retardo para evitar rebotes.
}

void F_S(void)
{
    RESULTADO = OPERANDO_1 + OPERANDO_2;      
}
void F_R(void)
{
    RESULTADO = OPERANDO_1 - OPERANDO_2;      
}
void F_A(void)
{
    RESULTADO = OPERANDO_1 & OPERANDO_2;      
}
void F_O(void)
{
    RESULTADO = OPERANDO_1 | OPERANDO_2;        
}
void F_M(void)
{
    RESULTADO = OPERANDO_1 * OPERANDO_2;      
}
void F_D(void)
{
    if (OPERANDO_2 == 0)
    {
        RESULTADO = 0; // Manejo de división por cero.
    }
    else
    {
        RESULTADO = OPERANDO_1 / OPERANDO_2;      
    }
}

void MOSTRAR_RESULTADO(void)
{
    LATC = selector; // Mostrar el selector.
    LATD = 0;
    __delay_ms(250);

    LATD = OPERANDO_1; // Mostrar OPERANDO_1.
    __delay_ms(1000); // Mostrar por 1 segundo.

    LATD = 0;
    __delay_ms(250);

    LATD = OPERANDO_2; // Mostrar OPERANDO_2.
    __delay_ms(1000);

    LATD = 0;
    __delay_ms(250);

    LATD = RESULTADO; // Mostrar el resultado.
    __delay_ms(1000);

    LATD = 0;
    __delay_ms(250);
}

void ESTA_VIVO(void)
{
    int i;
    for(i = 0; i < 8; i++)
    {    
        LATD = LATC = 0b11111111; // LEDs encendidos.
        __delay_ms(500);
        LATD = LATC = 0; // LEDs apagados.
        __delay_ms(500);
    }
}