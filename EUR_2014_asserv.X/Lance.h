/*
* Lance
* Compiler : Microchip xC16
* µC : 33FJ64MC804
* Mai 2014
*    ____________      _           _
*   |___  /| ___ \    | |         | |
*      / / | |_/ /___ | |__   ___ | |_
*     / /  |    // _ \| '_ \ / _ \| __|
*    / /   | |\ \ (_) | |_) | (_) | |_
*   /_/    |_| \_\___/|____/ \___/'\__|
*			      7robot.fr
*/

#ifndef LANCE_H
#define	LANCE_H

/******************************************************************************/
/* User Level #define Macros                                                  */
/******************************************************************************/

#define MOTOR_LANCE _LATC4

#define FIRE 260
#define LOAD 158

#define LANCE_LAUNCH (1 << 1)
#define LANCE_ABORT  (1 << 2)

/******************************************************************************/
/* Function Prototypes                                                        */
/******************************************************************************/

void InitLance(void);
void LaunchBalls(int RemainingBalls);
void FireBall(void);
void AbortLaunch(void);

// ATP func
void OnStopLaunch();
void OnLaunchBalls(unsigned int amount_left);
void OnSetBalls(unsigned int amount);

#endif	/* LANCE_H */

