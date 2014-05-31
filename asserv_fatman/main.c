/*
 * Template dsPIC33F
 * Compiler : Microchip xC16
 * µC : 33FJ128MC804
 * Avril 2014
 *    ______ _____      _           _
 *   |___  /| ___ \    | |         | |
 *      / / | |_/ /___ | |__   ___ | |_
 *     / /  |    // _ \| '_ \ / _ \| __|
 *    / /   | |\ \ (_) | |_) | (_) | |_
 *   /_/    |_| \_\___/|____/ \___/'\__|
 *			      7robot.fr
 */

/* Device header file */
#include <xc.h>

#include <stdint.h>        /* Includes uint16_t definition                    */
#include <stdbool.h>       /* Includes true/false definition                  */
#include <uart.h>

#include "user.h"          /* User funct/params, such as InitApp              */
#include "qei.h"           /* QEI definitions for easier use                  */
#include <libpic30.h>
#include "globals.h"
#include "tests.h"
#include "ax12.h"
#include "actions_ax12.h"
#include "lib_asserv/lib_asserv_default.h"
#include "lib_asserv/lib_asserv.h"
#include "motor.h"

/******************************************************************************/
/* Global Variable Declaration                                                */
/******************************************************************************/

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

/******************************************************************************/
/* Main Program                                                               */

/******************************************************************************/

int16_t main(void) {
    /* Configure the oscillator for the device */
    //int toto = 0;
    ConfigureOscillator();
/*    Init_PWM();
    while (1)
    {
        while (toto < 3000)
        {
            PWM_Moteurs(20,20);
            __delay_ms(1);
            toto ++;
        }
        while (toto < 4500)
        {
            PWM_Moteurs(-10,-10);
            __delay_ms(1);
            toto ++;
        }
        toto = 0;
    }
    __delay_ms(1000);

    PWM_Moteurs(50, 50);
    __delay_ms(1000);
    __delay_ms(10000);
    PWM_Moteurs(0,0);
    __delay_ms(2000);
 */
    Init_All();
    /*while (toto < 3000)
    {
        PWM_Moteurs(30,30);
        __delay_ms(1);
        toto ++;
    }*/
    while(1);
    return 1;
}