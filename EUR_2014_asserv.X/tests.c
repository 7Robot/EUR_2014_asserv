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