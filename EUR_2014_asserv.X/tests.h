#ifndef TESTS_H
#define	TESTS_H

// Asserve en vitesse + vitesse angulaire
void test_Asserv_vitesse_reglage();

// asserve en position
void test_Asserv_pos();

/******************************************************************************/
/*                      Tests avec les interruptions                          */
/******************************************************************************/

// allumer la led à une fréquence de 1Hz
void test_interrupt_led(int periode);
void basculer_led();

#endif	/* TESTS_H */