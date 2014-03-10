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

#endif	/* TESTS_H */

