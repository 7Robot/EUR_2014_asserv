/*
* Lance
* Compiler : Microchip xC16
* �C : 33FJ64MC804
* Mai 2014
*    ____________      _           _
*   |___  /| ___ \    | |         | |
*      / / | |_/ /___ | |__   ___ | |_
*     / /  |    // _ \| '_ \ / _ \| __|
*    / /   | |\ \ (_) | |_) | (_) | |_
*   /_/    |_| \_\___/|____/ \___/'\__|
*			      7robot.fr
*/

/******************************************************************************/
/* Files to Include                                                           */
/******************************************************************************/

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

#include "atp-asserv.h"
#include "user.h"
#include "Lance.h"

#include <timer.h>         /* Include timer fonctions                         */
#include <outcompare.h>

#include <libpic30.h>

/******************************************************************************/
/* Global Variable Declaration                                                */
/******************************************************************************/

char RemainingBalls = 6;
volatile char FirePermission = 0;
volatile char actionBalls = 0;
volatile char actionLance = 0;

/******************************************************************************/
/* User Functions                                                             */
/******************************************************************************/

void InitLance(void)
{
    //Relais
    _TRISC4 = 0;    // Motor Pin as Output
    MOTOR_LANCE = 0;

    //Configuration du Timer 2, p�riode 20ms pour l'OC1
    OpenTimer3(T3_ON & T3_GATE_OFF & T3_PS_1_256 & T3_SOURCE_INT, 3000);
    //ConfigIntTimer3(T3_INT_ON & T2_INT_PRIOR_4);

    //Configuration du Output Compare 1 en mode PWM
    OpenOC1(OC_IDLE_CON & OC_TIMER3_SRC & OC_PWM_FAULT_PIN_DISABLE, LOAD, 0);   //1.5ms
    _TRISC5 = 0;        //RC5 en sortie
    _ODCC5 = 1;         //Open Drain
    __builtin_write_OSCCONL(OSCCON & 0xBF); // Unlock RP
    _RP21R = 18;        //OC1(18) sur RP21;
    __builtin_write_OSCCONL(OSCCON | 0x40); // Lock RP

    // Configuration SPI Interrupt
    IFS2bits.SPI2IF = 0; // Flag SPI2 Event Interrupt Priority
    IPC8bits.SPI2IP = 2; // Priority SPI2 Event Interrupt Priority
    IEC2bits.SPI2IE = 1; // Enable SPI2 Event Interrupt Priority
}

void LaunchBalls(int BallsAfterShoot)
{
    int BallsToShoot, i;

    FirePermission = 1;
    BallsToShoot = RemainingBalls - BallsAfterShoot;

    if(BallsToShoot <= 0)
    {
        SendDoneLaunch();
    }
    else
    {
        MOTOR_LANCE = 1;         // Turn On the motor
        __delay_ms(1000);   // Wait for the moteur to be full speed

        for(i = 0; i< BallsToShoot; i++)
        {
            if(FirePermission == 1)
            {
                FireBall();         // Fire one ball
                //SendDoneBall();
                RemainingBalls--;
                __delay_ms(500);   // Wait for the robot to move
            }
            else
            {
                FirePermission = 0;
                MOTOR_LANCE = 0; // Turn off the motor
                return;
            }
        }
        FirePermission = 0;
        MOTOR_LANCE = 0; // Turn off the motor
    }
    SendDoneLaunch();
}

void FireBall(void)
{
    OC1RS = FIRE;        // Launch the Ball
    __delay_ms(500);   // Wait for the ball to go
    OC1RS = LOAD;        // Recharges
}

void AbortLaunch(void)
{
    FirePermission = 0;
}

void OnStopLaunch()
{
    AbortLaunch();
}

void OnLaunchBalls(unsigned int amount_left)
{
    actionLance |= LANCE_LAUNCH;
    actionBalls = amount_left;
    IFS2bits.SPI2IF = 1;
}

void OnSetBalls(unsigned int amount)
{
    RemainingBalls = amount;
}

/*************************************************
 *         Lance SPI Interrupt
 *
 *************************************************/

void __attribute__((interrupt, no_auto_psv)) _SPI2Interrupt(void)
{
    IFS2bits.SPI2IF = 0;
    if ((actionLance & LANCE_LAUNCH) == LANCE_LAUNCH) {
        LaunchBalls(actionBalls);  // TODO Mettre variable Global pour le param
        actionLance &= ~LANCE_LAUNCH;
    }
}
