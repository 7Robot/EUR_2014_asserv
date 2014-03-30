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
#define P1TPER_MIN 1500UL
#define P1TPER_MAX 32000UL
// Duty-Cycle max (au cas ou on veut limiter la puissance moteur)
#define DC_MAX 100

// nombre de tics de l'encodeur pour faire 1 mètre
#define TICPARMETRE 54340
// durée entre 2 asserv
#define TEMPSASSERV 0.01

// initialise les PWM
void Init_PWM(void);
// initialise le QEI (compteur pour encodeur)
void Init_QEI(void);
// Applique un PWM en ne réglant que les Duty-Cycle (compris entre -100 et 100)
// la fréquence du PWM est automatiquement réglée à 26.667 kHz (P1TPER=1500)
void PWM_Moteurs(float DC_gauche, float DC_droit);
// Applique un PWM en réglant la fréquence (1kHz-26.66kHz) et les Duty-Cycle (-100->+100)
void PWM_Moteurs_Detail(float frequence, float DC_gauche, float DC_droit);

void PWM_Moteurs_gauche(float DC);
void PWM_Moteurs_droit(float DC);

// asservissement proportionnel
void Asserv_gauche(float consigne, float valeur, float *erreur_old, float *integral);
void Asserv_droit(float consigne, float valeur, float *erreur_old, float *integral);

// asservissement en position
void Asserv_position(float x,float y,float v,float theta,float vtheta,float cons_x,float cons_y);

// maj des variables d'état du robot
void Maj_reperage(float *x,float *y,float *v,float *theta,float *vtheta,
        int qei_g_old, int qei_d_old,int qei_g_new,int qei_d_new);

// teste si le robot est arrivé à destination
int is_arrived(float erreur, float derivee);

#endif	/* ASSERV_H */
