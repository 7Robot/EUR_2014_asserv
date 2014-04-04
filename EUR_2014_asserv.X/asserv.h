/* 
 * File:   asserv.h
 * Author: matthieu
 *
 * Created on March 10, 2014, 7:26 PM
 */

#ifndef _ASSERV_ASSERV_H
#define	_ASSERV_ASSERV_H

// Mode des pins de sens des moteurs
#define MOTOR_1A_TRIS TRISBbits.TRISB9
#define MOTOR_1B_TRIS TRISBbits.TRISB11
#define MOTOR_2A_TRIS TRISBbits.TRISB13
#define MOTOR_2B_TRIS TRISBbits.TRISB14
// Valeur des pin de sens des moteurs (output)
#define MOTOR_1A_O LATBbits.LATB9
#define MOTOR_1B_O LATBbits.LATB11
#define MOTOR_2A_O LATBbits.LATB13
#define MOTOR_2B_O LATBbits.LATB14

// min et max de P1TPER (periode du PWM en nb de cycles)
// ici min et max permettent de rester dans des fréquences comprises entre
// 26Hz et 1.2kHz pour respecter la datasheet du pont en H
#define P1TPER_MIN 1500UL
#define P1TPER_MAX 32000UL
// Duty-Cycle max (au cas ou on veut limiter la puissance moteur)
#define DC_MAX 100
// Entraxe entre les 2 roues du robot

// nombre de tics de l'encodeur pour faire 1 mètre
#define TICS_BY_METERD 13969
#define METER_BY_TICD (1.0/TICS_BY_METERD)
#define METER_BY_TICG METER_BY_TICD
#define LARGEUR_ROBOT 0.219 //distance entre axes

#define CONSIGNE_MAX 800 //TODO :
#define CONSIGNE_MIN 120 //
#define CONSIGNE_NULLE 30 //valeurs a checker

#endif
