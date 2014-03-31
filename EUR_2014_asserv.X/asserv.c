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
#include "robot.h"

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
    // module QEI1 = Moteur Gauche
    QEI1CONbits.QEISIDL = 1;    // module toujours actif, meme en etat de pause du pic
    QEI1CONbits.QEIM = 6;       // module en mode x4 : regarde tous les fronts, reset sur index, désactivé en dessous
    QEI1CONbits.POSRES = 0;     // desactive l'index => pas de reset du compteur;
    QEI1CONbits.TQCS = 0;       // use PIC clock

    // configuration des pins A et B du module
    // ce sont des pins dites remapable,
    // ce qui veut dire que l'on peut choisir presque toutes les IO du PIC
    RPINR14bits.QEA1R = 22; // 25 = pin RP25
    RPINR14bits.QEB1R = 25;


    // module QEI2 identique = Moteur Droit
    QEI2CONbits.QEISIDL = 1;    // module toujours actif, meme en etat de pause du pic
    QEI2CONbits.QEIM = 6;       // module en mode x4 : regarde tous les fronts, reset sur index, désactivé en dessous
    QEI2CONbits.POSRES = 0;     // desactive l'index => pas de reset du compteur;
    QEI2CONbits.TQCS = 0;       // use PIC clock

    // configuration des pins A et B du module
    RPINR16bits.QEA2R = 23; // 23 = pin RP23
    RPINR16bits.QEB2R = 24;
}


// Applique un PWM en ne réglant que les Duty-Cycle (compris entre -100 et 100)
// la fréquence du PWM est automatiquement réglée à 26.667 kHz (P1TPER=1500)
void PWM_Moteurs(float DC_gauche, float DC_droit)
{
    // variable temporaire servant a connaitre le signe des Duty-Cycle
    int DC_positif;

    // pins de sens du moteur gauche
    DC_positif = (DC_gauche >= 0);
    MOTOR_1A_O = !DC_positif;
    MOTOR_1B_O = DC_positif;

    // pins de sens du moteur droit
    DC_positif = (DC_droit >= 0);
    MOTOR_2A_O = !DC_positif;
    MOTOR_2B_O = DC_positif;

    P1TPER = 1500;

    // limitation des Duty-Cycle
    DC_gauche = limit_float(DC_gauche,-DC_MAX,DC_MAX);
    DC_droit = limit_float(DC_droit,-DC_MAX,DC_MAX);

    // calcul des temps High des moteurs (cf datasheet)
    // RMQ : ici la précision est 2 fois plus grande que pour P1TPER
    P1DC2 =  (int) (30*fabs(DC_gauche));
    P1DC3 =  (int) (30*fabs(DC_droit));
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

void PWM_Moteurs_gauche(float DC)
{
    // variable temporaire servant a connaitre le signe des Duty-Cycle
    int DC_positif;

    // pins de sens du moteur gauche
    DC_positif = (DC >= 0);
    MOTOR_2A_O = !DC_positif;
    MOTOR_2B_O = DC_positif;

    P1TPER = 1500;

    // limitation des Duty-Cycle
    DC = limit_float(DC,-DC_MAX,DC_MAX);

    // calcul des temps High des moteurs (cf datasheet)
    // RMQ : ici la précision est 2 fois plus grande que pour P1TPER
    P1DC2 =  (int) (30*fabs(DC));
}

void PWM_Moteurs_droit(float DC)
{
    // variable temporaire servant a connaitre le signe des Duty-Cycle
    int DC_positif;

    // pins de sens du moteur droit
    DC_positif = (DC >= 0);
    MOTOR_1A_O = !DC_positif;
    MOTOR_1B_O = DC_positif;

    P1TPER = 1500;

    // limitation des Duty-Cycle
    DC = limit_float(DC,-DC_MAX,DC_MAX);

    // calcul des temps High des moteurs (cf datasheet)
    // RMQ : ici la précision est 2 fois plus grande que pour P1TPER
    P1DC3 =  (int) (30*fabs(DC));
}

void Asserv_gauche(float consigne, float valeur, float *erreur_old, float *integral)
{
    float K_p = 0.22; // (0.22) choisit pour arriver un peu en dessous sans oscillation
    float K_i = 0.08; // (0.08) choisit pour être à la limite de redémarrage possible depuis l'arrêt
    float K_d = 22.0; // (22.0) choisit pour arriver la première fois sans oscillation proche de la consigne
    static float erreur = 0;
    static float derivee = 0;
    float commande = 0;

    erreur = 0.2*erreur + 0.8*(consigne-valeur); // erreur moyennée
    derivee = 0.2*derivee + 0.8*(erreur-(*erreur_old)); // derivee moyennée
    *erreur_old = erreur;

    // Si on considère être arrivé, on annule l'integrale (a activer après avoir choisit K_p,K_i et K_d)
    if (is_arrived(erreur,derivee))
        *integral = 0.0;
    else
        *integral = limit_float((*integral)+erreur*(1+0.1*derivee), -130.0, 130.0);

    commande = K_p*erreur + K_i*(*integral) + K_d*derivee;

    PWM_Moteurs_gauche(commande);
}

void Asserv_droit(float consigne, float valeur, float *erreur_old, float *integral)
{
    float K_p = 0.22; // (0.22) choisit pour arriver un peu en dessous sans oscillation
    float K_i = 0.08; // (0.08) choisit pour être à la limite de redémarrage possible depuis l'arrêt
    float K_d = 22.0; // (22.0) choisit pour arriver la première fois sans oscillation proche de la consigne
    static float erreur = 0;
    static float derivee = 0;
    float commande = 0;

    erreur = 0.2*erreur + 0.8*(consigne-valeur); // erreur moyennée
    derivee = 0.2*derivee + 0.8*(erreur-(*erreur_old)); // derivee moyennée
    *erreur_old = erreur;

    // Si on considère être arrivé, on annule l'integrale (a activer après avoir choisit K_p,K_i et K_d)
    if (is_arrived(erreur,derivee))
        *integral = 0.0;
    else
        *integral = limit_float((*integral)+erreur*(1+0.1*derivee), -130.0, 130.0);

    commande = K_p*erreur + K_i*(*integral) + K_d*derivee;

    PWM_Moteurs_droit(commande);
}

//asservissement en vitesse
/* Principe original : 4 termes au lieu de 3 :
 * terme 1 : cf courbe d'étalonage en vitesse
 * terme 2 : proportionnel à l'erreur
 * terme 3 : proportionnel à la dérivée de l'erreur
 * terme 4 : proportionnel à l'intégrale
 */
void Asserv_vitesse(float v,float cons_v, float *commande_old){
    // coefficients
    float Kp = 0;
    float Ki = 0;
    float Kd = 0;
    // autres variables
    static float erreur = 0;
    static float erreur_old = 0;
    static float derivee = 0;
    static float integral = 0;
    static float commande = 0;
    // commandes aux moteurs
    static float DC_g = 0;
    static float DC_d = 0;
    float alpha = 0.7; // coef de moyennage

    erreur = (1-alpha)*erreur_old + alpha*(cons_v-v); // erreur moyennée
    derivee = (1-alpha)*derivee + alpha*(erreur-erreur_old); // derivee moyennée
    erreur_old = erreur;

    // Si on considère être arrivé, on annule l'integrale (a activer après avoir choisit K_p,K_i et K_d)
    if (vitesse_ok(erreur,derivee))
        integral = 0.0;
    else
        integral = limit_float((integral)+erreur*(1+0.1*derivee), -130.0, 130.0);

    // application de la commande
    commande = limit_float(*commande_old + Kp*erreur + Ki*integral + Kd*derivee, -100.0, 100.0);
    *commande_old = commande;
    DC_g = commande;
    DC_d = commande;
    PWM_Moteurs(DC_g, DC_d);
}


// asservissement en position
void Asserv_position(float x,float y,float v,float theta,float vtheta,float cons_x,float cons_y)
{/*
    // variables
    float DC_g = 0; // Duty-cycle du moteur gauche
    float DC_d = 0; // Duty-cycle du moteur droit
    // coefficients
    float Kp = 0;
    float Ki = 0;
    float Kd = 0;

    // a coder
    */
}

// maj des variables d'état du robot
void Maj_reperage(float *x,float *y,float *v,float *theta,float *vtheta,
        int qei_g_old, int qei_d_old,int qei_g_new,int qei_d_new)
{
    // calculs intermédiaires roues gauches et droites
    float dg = (float)(qei_g_new-qei_g_old)/TICPARMETRE;
    float dd = (float)(qei_d_new-qei_d_old)/TICPARMETRE;
    float d = (dd+dg)/2;
    float dtheta = (dd-dg)/(ENTRAXE);

    // maj des vitesses
    *v = d/TEMPSASSERV;
    *vtheta = dtheta/TEMPSASSERV;

    // maj des positions
    *x += d*cos(*theta+dtheta/2); // ou *theta+dtheta/2 est l'angle moyen pendant le déplacement
    *y += d*sin(*theta+dtheta/2);
    *theta += dtheta;
}

// mise a jour des vitesses droite et gauche du robot
void Maj_vitesse(float *vg,float *vd,
        int qei_g_old, int qei_d_old,int qei_g_new,int qei_d_new)
{
    // calculs intermédiaires roues gauches et droites
    float dg = (float)(qei_g_new-qei_g_old)/TICPARMETRE;
    float dd = (float)(qei_d_new-qei_d_old)/TICPARMETRE;

    // maj des vitesses
    *vg = dg/TEMPSASSERV;
    *vd = dd/TEMPSASSERV;
}


int is_arrived(float erreur, float derivee)
{
    return (fabs(erreur)<1 && fabs(derivee)<0.1);
}

int vitesse_ok(float erreur, float derivee)
{
    return (fabs(erreur)<0.1 && fabs(derivee)<0.01);
}
