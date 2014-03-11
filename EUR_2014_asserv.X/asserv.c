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
#include <math.h>

#include "system.h"
#include "user.h"
#include "asserv.h"

void Init_PWM(void)
{
    // P1TCON
    P1TCONbits.PTEN = 1;        // enable module PWM
    P1TCONbits.PTCKPS = 0;      // Clk input of the PWM module is TCY (no prescale)
    P1TCONbits.PTMOD = 0;       // free-runnig mode

    /*
     * la période des PWM (temps entre 2 fronts montants)
     * est fixée à 1500 cycles de 40MHz
     * ça donne une periode de sortie de 37.5 µs soit 26.66 kHz
     * RMQ : les registres de rapport cycliques ayant une précision double
     * leur valeur max sera 3000
     */
    P1TPER = 1500;

    //PWM1CON1
    PWM1CON1bits.PMOD2 = 1;     // sorties indépendantes
    PWM1CON1bits.PMOD3 = 1;
    // desactivation de toutes les sorties
    // à réactiver une fois le pinout trouvé ;)

    // sorties High du pwm
    PWM1CON1bits.PEN1H = 0;
    PWM1CON1bits.PEN2H = 1;
    PWM1CON1bits.PEN3H = 1;

    // sorties Low (opposé du High, on ne l'utilise pas)
    PWM1CON1bits.PEN1L = 0;
    PWM1CON1bits.PEN2L = 0;
    PWM1CON1bits.PEN3L = 0;

    // réglage des rapports cycliques, pour l'instant on mets 0 lors de l'initialisation
    P1DC2 = 0;
    P1DC3 = 0;

    // Activation en sortie des pin de sens du PONT en H
    MOTOR_1A_TRIS = 0;
    MOTOR_1B_TRIS = 0;
    MOTOR_2A_TRIS = 0;
    MOTOR_2B_TRIS = 0;

    // pins de sens des moteurs
    MOTOR_1A_O = 0;
    MOTOR_1B_O = 0;
    MOTOR_2A_O = 0;
    MOTOR_2B_O = 0;
}

void Init_QEI(void)
{
    // module QEI1 = Moteur Droit
    QEI1CONbits.QEISIDL = 1;    // module toujours actif, meme en etat de pause du pic
    QEI1CONbits.QEIM = 6;       // module en mode x4 : regarde tous les fronts, reset sur index, désactivé en dessous
    QEI1CONbits.POSRES = 0;     // desactive l'index => pas de reset du compteur;
    QEI1CONbits.TQCS = 0;       // use PIC clock

    // configuration des pins A et B du module
    // ce sont des pins dites remapable,
    // ce qui veut dire que l'on peut choisir presque toutes les IO du PIC
    RPINR14bits.QEA1R = 0;
    RPINR14bits.QEB1R = 0;


    // module QEI2 identique = Moteur Gauche
    QEI2CONbits.QEISIDL = 1;    // module toujours actif, meme en etat de pause du pic
    QEI2CONbits.QEIM = 6;       // module en mode x4 : regarde tous les fronts, reset sur index, désactivé en dessous
    QEI2CONbits.POSRES = 0;     // desactive l'index => pas de reset du compteur;
    QEI2CONbits.TQCS = 0;       // use PIC clock

    // configuration des pins A et B du module
    RPINR16bits.QEA2R = 0;
    RPINR16bits.QEB2R = 0;
}


// Applique un PWM en ne réglant que les Duty-Cycle (compris entre -100 et 100)
// la fréquence du PWM est automatiquement réglée à 26.667 kHz (P1TPER=1500)
void PWM_Moteurs(float DC_gauche, float DC_droit)
{
    PWM_Moteurs_Detail(26667,DC_gauche,DC_droit);
}

// Applique un PWM en réglant la fréquence (1kHz-26.66kHz) et les Duty-Cycle (-100->+100)
void PWM_Moteurs_Detail(float frequence, float DC_gauche, float DC_droit)
{
    // variable temporaire servant a connaitre le signe des Duty-Cycle
    int DC_positif;

    // pins de sens du moteur gauche
    DC_positif = DC_gauche >= 0;
    MOTOR_1A_O = !DC_positif;
    MOTOR_1B_O = DC_positif;

    // pins de sens du moteur droit
    DC_positif = DC_droit >= 0;
    MOTOR_2A_O = !DC_positif;
    MOTOR_2B_O = DC_positif;

    // calcul du nombre de cycles pour avoir la bonne fréquence (FCY/frequence)
    P1TPER = (int) limit_int((long int)(FCY/frequence),P1TPER_MIN,P1TPER_MAX);

    // limitation des Duty-Cycle
    DC_gauche = limit_float(DC_gauche,-100,100);
    DC_droit = limit_float(DC_droit,-100,100);

    DC_gauche = 2*P1TPER*fabs(DC_gauche)/100.0;
    DC_droit = 2*P1TPER*fabs(DC_droit)/100.0;

    // calcul des temps High des moteurs (cf datasheet)
    // RMQ : ici la précision est 2 fois plus grande que pour P1TPER
    P1DC2 = (int) limit_int((long int)(DC_gauche), 0, (long int)(2*P1TPER_MAX));
    P1DC3 = (int) limit_int((long int)(DC_droit), 0,  (long int)(2*P1TPER_MAX));
}
