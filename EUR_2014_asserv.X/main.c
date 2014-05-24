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

//includes pic libs

#include <uart.h>
#include <math.h>
#include <adc.h>

//includes atp
#include "atp.h"
#include "atp-asserv.h"

//includes projet
#include "user.h"          /* User funct/params, such as InitApp              */
#include "../asserv/asserv/libasserv.h"
#include "ax12.h"

#include <libpic30.h>
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
    while (!OSCCONbits.LOCK); // attente que la PLL soit lockée sur se nouvelle configuration.
}


/******************************************************************************/
/* Main Program                                                               */
/******************************************************************************/

int odoBroadcast = 0;
unsigned long int odoBroadcastDelay = 1000; // en ms

int16_t main(void)
{
    /* Configure the oscillator for the device */
    ConfigureOscillator();

    /* Initialize IO ports and peripherals */
    InitApp();
    Init_PWM();
    Init_QEI();

    AtpInit();
    motion_init(SendDone);
    SendBoardId();
    // Petit blink kikou au d�marrage
    int i;
    for (i = 0 ; i < 14 ; i++) {
        __delay_ms(50);
        led = led ^ 1;
    }
    SendBoardId();

    //pour les AX12
    responseReadyAX = 0;

    //Set_Vitesse_MoteurG(400, 0);

    while (1){
        if (odoBroadcast) {
            OnGetPos();
        }
        __delay_ms(odoBroadcastDelay);
    }
}
