#ifndef TESTS_H
#define	TESTS_H

// Asserve en vitesse + vitesse angulaire
void test_Asserv_vitesse();

// asserve en position
void test_Asserv_pos();

// asserve en angle
void test_Asserv_angle();

// test des ax12 integrés à l'asserve
void test_ax12();

// teste les commande atp
void test_atp();

// test de décélération
void test_deceleration();

// test de sequence de positions
void test_sequence();

/******************************************************************************/
/*                      Tests avec les interruptions                          */
/******************************************************************************/

// allumer la led à une fréquence de 1Hz
void test_interrupt_led(int periode);
void basculer_led();

#endif	/* TESTS_H */