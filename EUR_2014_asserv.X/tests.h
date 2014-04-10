#ifndef TESTS_H
#define	TESTS_H

// Asserve en vitesse + vitesse angulaire
void test_Asserv_vitesse(float cons_v,float cons_vt);
void test_Asserv_vitesse_reglage();

/******************************************************************************/
/*                      Tests avec les interruptions                          */
/******************************************************************************/

// allumer la led à une fréquence de 1Hz
void test_interrupt_led(int periode);
void basculer_led();

#endif	/* TESTS_H */