/*
 * Template dsPIC33F
 * Compiler : Microchip xC16
 * µC : 33FJ128MC804
 * Mars 2014
 *    ______ _____      _           _
 *   |___  /| ___ \    | |         | |
 *      / / | |_/ /___ | |__   ___ | |_
 *     / /  |    // _ \| '_ \ / _ \| __|
 *    / /   | |\ \ (_) | |_) | (_) | |_
 *   /_/    |_| \_\___/|____/ \___/'\__|
 *			      7robot.fr
 */

/* Device header file */
#if defined(__XC16__)
    #include <xc.h>
#elif defined(__C30__)
    #if defined(__dsPIC33E__)
    	#include <p33Exxxx.h>
    #elif defined(__dsPIC33F__)
    	#include <p33Fxxxx.h>
    #endif
#endif


#include <stdint.h>        /* Includes uint16_t definition                    */
#include <stdbool.h>       /* Includes true/false definition                  */

#include "user.h"          /* User funct/params, such as InitApp              */
#include "asserv.h"
#include "qei.h"           /* QEI definitions for easier use                  */
#include <libpic30.h>
#include "tests.h"
#include <uart.h>
#include "ax12.h"

/******************************************************************************/
/* Global Variable Declaration                                                */
/******************************************************************************/

/* i.e. uint16_t <variable_name>; */

/******************************************************************************/
/* Configuration                                                              */
/******************************************************************************/
// Select Oscillator and switching.
_FOSCSEL(FNOSC_FRCPLL & IESO_OFF);
// Select clock.
_FOSC(POSCMD_NONE & OSCIOFNC_OFF & IOL1WAY_OFF & FCKSM_CSDCMD);
// Watchdog Timer.
_FWDT(FWDTEN_OFF);
// Select debug channel.
_FICD(ICS_PGD1 & JTAGEN_OFF);

/* TODO Add clock switching code if appropriate.  An example stub is below.   */
void ConfigureOscillator(void)
{
    // Configure PLL prescaler, PLL postscaler, PLL divisor
    PLLFBDbits.PLLDIV = 41;        // M=152
    CLKDIVbits.PLLPRE  = 0;         // N1=7
    CLKDIVbits.PLLPOST = 0;         // N2=2
    /* Fosc = M/(N1.N2)*Fin
     * Fin : 7.37MHz (quartz interne)
     * Fosc à 80 MHZ (ne doit pas dépasser 80 MHZ)
     * la solution la plus proche est 152*7.37/(7*2) = 80.017
     * attention, cela entraine donc une FCY et une FPériphériques à 40 MHZ
     */
    while (!OSCCONbits.LOCK);       // attente que la PLL soit lockée sur se nouvelle configuration.
}


/******************************************************************************/
/* Main Program                                                               */
/******************************************************************************/

int16_t main(void)
{
    /* variables */
    long int qei_total = 0;
    float erreur_old = 0;
    float integral = 0;
    int qei = 0;

    
    /* Configure the oscillator for the device */
    ConfigureOscillator();

    /* Initialize IO ports and peripherals */
    InitApp();
    Init_PWM();
    Init_QEI();

    //pour les AX12
    responseReadyAX = 0;
    ODCBbits.ODCB5 = 1; //open drain

    /* TODO <INSERT USER APPLICATION CODE HERE> */
    __delay_ms(10);
    PutAX(AX_BROADCAST, AX_MOVING_SPEED, 250);
    __delay_ms(10);
    PutAX(AX_BROADCAST, AX_MAX_TORQUE, 1100);
    __delay_ms(10);
   // PutAX(AX_BROADCAST, AX_BAUD_RATE, 34); //57600

    while (1){
        //test_Asserv_droit(&qei_total, &qei, &erreur_old, &integral);
       // __delay_ms(1000);
        __delay_ms(1000);
        PutAX(18, AX_GOAL_POSITION, 100);
        __delay_ms(1000);
        PutAX(18, AX_GOAL_POSITION, 0);
        //led = !led;
        //test_frequence_fixe_moteurs(10000);
        //test_frequence_fixe_moteurs(20000);
    }
}
