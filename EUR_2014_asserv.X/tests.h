/* 
 * File:   tests.h
 * Author: matthieu
 *
 * Created on March 10, 2014, 11:05 PM
 */

#ifndef TESTS_H
#define	TESTS_H

// teste si la fréquence du PWM est bien la bonne
void test_frequence_fixe_moteurs(float frequence);

// teste si la fréquence a une influence importante sur les perfs
// la fréquence va varier de f_min a f_max en temps secondes
void test_frequence_variable_moteurs(float f_min,float f_max, float temps);

// teste si le Duty-Cycle est bien respecté à la fréquence f
void test_DC_variable_moteurs(float DC_min,float DC_max, float temps, float frequence);

// test asserv
void test_Asserv_gauche(long int *qei_total, int *qei_old, float *erreur_old, float *integral);
void test_Asserv_droit(long int *qei_total, int *qei_old, float *erreur_old, float *integral);

// trouver une approximation de la relation v = f(Duty-Cycle) pour chaque moteur
void test_Asserv_vitesse_1();

// etalonage
void etalonner_qei();
void test_Reperage();

#endif	/* TESTS_H */

