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

#include "system.h"        /* System funct/params, like osc/peripheral config */
#include "user.h"          /* User funct/params, such as InitApp              */
#include "asserv.h"
#include "qei.h"           /* QEI definitions for easier use                  */
#include <libpic30.h>
#include "tests.h"


/*############################################################################*/
/*                Tests pour faire fonctionner les moteurs                    */
/*############################################################################*/

// teste si la fréquence du PWM est bien la bonne
void test_frequence_fixe_moteurs(float frequence)
{
    while (1)
    {
        PWM_Moteurs_Detail(frequence, 50, 50);
        __delay_ms(10);
    }
}

// teste si la fréquence a une influence importante sur les perfs
// la fréquence va varier de f_min a f_max en temps secondes
void test_frequence_variable_moteurs(float f_min,float f_max, float temps)
{
    float f;
    float pas = (f_max-f_min)/(100*temps);

    for (f=f_min; f<f_max; f+=pas)
    {
        PWM_Moteurs_Detail(f, 25, 25);
        __delay_ms(10);
    }
}

// teste si le Duty-Cycle est bien respecté à la fréquence f
void test_DC_variable_moteurs(float DC_min,float DC_max, float temps, float frequence)
{
    float DC;
    float pas = (DC_max-DC_min)/(100*temps);

    // dans le cas ou DC_min et DC_max sont inversés
    if (DC_min>DC_max)
    {
        for (DC=DC_min; DC>DC_max; DC+=pas)
        {
            PWM_Moteurs_Detail(frequence, DC, DC);
            __delay_ms(10);
        }
    }
    // dans le cas normal
    else
    {
        for (DC=DC_min; DC<DC_max; DC+=pas)
        {
            PWM_Moteurs_Detail(frequence, DC, DC);
            __delay_ms(10);
        }
    }
}


/*############################################################################*/
/*                   Tests d'asservissement du robot                          */
/*############################################################################*/

// test d'asserv
void test_Asserv_gauche(long int *qei_total, int *qei_old, float *erreur_old, float *integral)
{
    float valeur;
    float consigne = 100;
    int qei_new = (int)POS1CNT;

    *qei_total += (qei_new-(*qei_old));
    *qei_old = qei_new;

    // conversion de QEI à mètre
    valeur = 0.01*(float)(*qei_total);

    Asserv_gauche(consigne, valeur, erreur_old, integral);
}

// test d'asserv
void test_Asserv_droit(long int *qei_total, int *qei_old, float *erreur_old, float *integral)
{
    float valeur;
    float consigne = 100;
    int qei_new = (int)POS2CNT;

    *qei_total += (qei_new-(*qei_old));
    *qei_old = qei_new;

    // conversion de QEI à mètre
    valeur = 0.01*(float)(*qei_total);

    Asserv_droit(consigne, valeur, erreur_old, integral);
}

// trouver une approximation de la relation v = f(Duty-Cycle) pour chaque moteur
void test_Asserv_vitesse_1()
{
    // variables QEI
    int qei_g_old = 0;
    int qei_d_old = 0;
    int qei_g_new = 0;
    int qei_d_new = 0;

    // vitesses gauche et droite
    float vg = 0;
    float vd = 0;
    // vitesses moyennées
    float vg_m = 0;
    float vd_m = 0;

    // variable de temps
    int t = 0;

    /* Configure the oscillator for the device */
    ConfigureOscillator();

    /* Initialize IO ports and peripherals */
    InitApp();
    Init_PWM();
    Init_QEI();

    // test d'une durée de 5 secondes
    for (t=0; t<1000; t++)
    {
        // récupération des données des compteurs qei gauche et droit
        qei_g_new = (int)POS1CNT;
        qei_d_new = (int)POS2CNT;
        // mise a jour des vitesses droite et gauche du robot
        Maj_vitesse(&vg,&vd,qei_g_old,qei_d_old,qei_g_new,qei_d_new);
        // vitesses moyennes
        vg_m = 0.95*vg_m + 0.05*vg;
        vd_m = 0.95*vd_m + 0.05*vd;
        // application d'un DC
        PWM_Moteurs(100, 100);
        // sauvegarde des valeurs des compteurs
        qei_g_old = qei_g_new;
        qei_d_old = qei_d_new;
        __delay_ms(10);
    }

    // un delay pour mettre un point d'arrêt (en mode debug)
    __delay_ms(1000);
}

// Asserve en vitesse indépendante pour chaque moteur
void test_Asserv_vitesse_2()
{
    // variables QEI
    int qei_g_old = 0;
    int qei_d_old = 0;
    int qei_g_new = 0;
    int qei_d_new = 0;
    // vitesses gauche et droite
    float vg = 0;
    float vd = 0;
    // vitesses moyennées
    float vg_m = 0;
    float vd_m = 0;
    // consignes de vitesse
    float cons_vg = 0.50;
    float cons_vd = 0.50;

    // variable de temps
    int t = 0;

    /* Configure the oscillator for the device */
    ConfigureOscillator();

    /* Initialize IO ports and peripherals */
    InitApp();
    Init_PWM();
    Init_QEI();

    // test d'une durée de 2.5 secondes
    for (t=0; t<250; t++)
    {
        // récupération des données des compteurs qei gauche et droit
        qei_g_new = (int)POS1CNT;
        qei_d_new = (int)POS2CNT;
        // mise a jour des vitesses droite et gauche du robot
        Maj_vitesse(&vg,&vd,qei_g_old,qei_d_old,qei_g_new,qei_d_new);
        // vitesses moyennes
        vg_m = 0.95*vg_m + 0.05*vg;
        vd_m = 0.95*vd_m + 0.05*vd;
        // asservissement en vitesse des moteurs
        //PWM_Moteurs(15, 15);
        Asserv_vitesse_gauche(vg,cons_vg);
        Asserv_vitesse_droite(vd,cons_vd);
        // sauvegarde des valeurs des compteurs
        qei_g_old = qei_g_new;
        qei_d_old = qei_d_new;
        __delay_ms(10);
    }

    // un delay pour mettre un point d'arrêt (en mode debug)
    __delay_ms(1000);
}


// Asserve en vitesse + vitesse angulaire
void test_Asserv_vitesse_3()
{
    // variables QEI
    int qei_g_old = 0;
    int qei_d_old = 0;
    int qei_g_new = 0;
    int qei_d_new = 0;

    // variables repérage
    float x = 0;
    float y = 0;
    float v = 0;
    float theta = 0;
    float vtheta = 0;

    // consignes de vitesse et vitesse angulaire
    float cons_v = 0.4;
    float cons_vtheta = 0;

    // vitesses moyennées (pour debuggage)
    float v_m = 0;
    float vtheta_m = 0;

    // variable de temps
    int duration = 500;

    /* Configure the oscillator for the device */
    ConfigureOscillator();

    /* Initialize IO ports and peripherals */
    InitApp();
    Init_PWM();
    Init_QEI();

    segment_vitesse(300, 0.4, 0,
            &qei_g_new, &qei_d_new, &qei_g_old, &qei_d_old,
            &x, &y, &v, &theta, &vtheta,
            &v_m, &vtheta_m);
    segment_vitesse(130, 0.4, -0.5,
            &qei_g_new, &qei_d_new, &qei_g_old, &qei_d_old,
            &x, &y, &v, &theta, &vtheta,
            &v_m, &vtheta_m);
    segment_vitesse(200, 0.4, 0.7,
            &qei_g_new, &qei_d_new, &qei_g_old, &qei_d_old,
            &x, &y, &v, &theta, &vtheta,
            &v_m, &vtheta_m);
    segment_vitesse(120, 0.4, -0.7,
            &qei_g_new, &qei_d_new, &qei_g_old, &qei_d_old,
            &x, &y, &v, &theta, &vtheta,
            &v_m, &vtheta_m);
    segment_vitesse(320, 0, 1,
            &qei_g_new, &qei_d_new, &qei_g_old, &qei_d_old,
            &x, &y, &v, &theta, &vtheta,
            &v_m, &vtheta_m);


    // un delay pour mettre un point d'arrêt (en mode debug)
  //  __delay_ms(1000);
    while(1);
}

// applique un asservissement en vitesse pour une duree donnée
    void segment_vitesse(int duration, float cons_v, float cons_vtheta,
            int *qei_g_new, int *qei_d_new, int *qei_g_old, int *qei_d_old,
            float *x, float *y, float *v, float *theta, float *vtheta,
            float *v_m, float *vtheta_m){
    int t = 0;
    for (t=0; t<duration; t++)
    {
        // récupération des données des compteurs qei gauche et droit
        *qei_g_new = (int)POS1CNT;
        *qei_d_new = (int)POS2CNT;
        // mise a jour des variables d'état du robot (position, vitesse)
        Maj_reperage(x,y,v,theta,vtheta,*qei_g_old,*qei_d_old,*qei_g_new,*qei_d_new);
        // vitesses moyennes
        *v_m = 0.95*(*v_m) + 0.05*(*v);
        *vtheta_m = 0.95*(*vtheta_m) + 0.05*(*vtheta);
        // asservissement en vitesse et vitesse angulaire
        Asserv_vitesse(*v,*vtheta,cons_v,cons_vtheta);
        // sauvegarde des valeurs des compteurs
        *qei_g_old = *qei_g_new;
        *qei_d_old = *qei_d_new;
        __delay_ms(10);
    }
}




/******************************************************************************/
/*                      Tests avec les interruptions                          */
/******************************************************************************/

// allumer la led à une fréquence de 1Hz
void test_interrupt_led(int periode){
    static int compteur = 0;
    compteur++;
    if (compteur==periode) {
        led = !led;
        compteur = 0;
    }
}





/******************************************************************************/
/*                      Fonctions bien pratiques                              */
/******************************************************************************/


/********************************* Test d'étalonage ***************************/
void test_Reperage()
{
    // variables QEI
    int qei_g_old = 0;
    int qei_d_old = 0;
    int qei_g_new = 0;
    int qei_d_new = 0;

    // variables repérage
    float x = 0;
    float y = 0;
    float v = 0;
    float theta = 0;
    float vtheta = 0;

    /* Configure the oscillator for the device */
    ConfigureOscillator();

    /* Initialize IO ports and peripherals */
    InitApp();
    Init_PWM();
    Init_QEI();

    while (1)
    {
        // récupération des données des compteurs qei gauche et droit
        qei_g_new = (int)POS1CNT;
        qei_d_new = (int)POS2CNT;
        // mise a jour des variables d'état du robot (position, vitesse)
        Maj_reperage(&x,&y,&v,&theta,&vtheta,qei_g_old,qei_d_old,qei_g_new,qei_d_new);
        // sauvegarde des valeurs des compteurs
        qei_g_old = qei_g_new;
        qei_d_old = qei_d_new;
        __delay_ms(10);
    }

}



// étalonner les QEI
void etalonner_qei()
{
    /* variables */
    long long int qei_g = 0;
    long long int qei_d = 0;
    int qei_g_old = 0;
    int qei_d_old = 0;
    int qei_g_new = 0;
    int qei_d_new = 0;

    /* Configure the oscillator for the device */
    ConfigureOscillator();

    /* Initialize IO ports and peripherals */
    InitApp();
    Init_PWM();
    Init_QEI();

    while (1)
    {
        qei_g_new = (int)POS1CNT;
        qei_d_new = (int)POS2CNT;
        qei_g += (qei_g_new-(qei_g_old));
        qei_d += (qei_d_new-(qei_d_old));
        qei_g_old = qei_g_new;
        qei_d_old = qei_d_new;
        __delay_ms(10);
    }
}