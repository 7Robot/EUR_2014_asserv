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

    Init_All();
  //  init_arm(1);
   // init_arm(2);



    // PutAX(CONV, AX_CW_ANGLE_LIMIT, 0); // on met le servo en "roue libre"
     //PutAX(CONV, AX_CCW_ANGLE_LIMIT, 0);




    while (1) {

    PutAX(CONV, AX_MOVING_SPEED, 0b11111111111); // le bit de poids fort gère le sens, les autres la vitesse
    __delay_ms(1000); // temps de déroulage du tapis

    // PutAX(CONV, AX_MOVING_SPEED, 0b01111111111); // le bit de poids fort gère le sens, les autres la vitesse
  //  __delay_ms(1000); // temps de déroulage du tapis


    }
    return 1;
}
