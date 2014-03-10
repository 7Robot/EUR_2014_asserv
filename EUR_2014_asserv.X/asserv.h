/* 
 * File:   asserv.h
 * Author: matthieu
 *
 * Created on March 10, 2014, 7:26 PM
 */

#ifndef ASSERV_H
#define	ASSERV_H

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
// 26kHz et 1.2kHz pour respecter la datasheet du pont en H
#define P1TPER_MIN 1500
#define P1TPER_MAX 32000

// initialise les PWM
void Init_PWM(void);
// initialise le QEI (compteur pour encodeur)
void Init_QEI(void);
// Applique un PWM en ne réglant que les Duty-Cycle (compris entre -100 et 100)
// la fréquence du PWM est automatiquement réglée à 26.667 kHz (P1TPER=1500)
void PWM_Moteurs(float DC_gauche, float DC_droit);
// Applique un PWM en réglant la fréquence (1kHz-26.66kHz) et les Duty-Cycle (-100->+100)
void PWM_Moteurs_Detail(float frequence, float DC_gauche, float DC_droit);

#endif	/* ASSERV_H */
