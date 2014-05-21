#ifndef _LIB_ASSERV_H_
#define _LIB_ASSERV_H_

#include "private/motion.h"
#include "private/extern_globals_asserv.h"

/*##############################   MOTION   ##################################*/

// initialiser la lib d'asservissement
void motion_init(void(*_done)(void));

// consignes de déplacements du robot
void motion_free(); // passer en roue libre
void motion_pos(Position pos); // aller à cette position
void motion_speed(Speed speed); // avancer à cette vitesse
void motion_angle(float abs_angle); // tourner pour être à un angle (absolu) alpha

// checker si le déplacement est terminé
int motion_done();

// renvoie les commandes des roues gauche et droite (appelé par l'interruption toutes les 10 ms)
void motion_step(int tics_g, int tics_d, float *commande_g, float *commande_d);

/*############################   MOTION STATE   ##############################*/

// connaître l'état du robot
Position get_position();
Speed get_speed();
Acceleration get_acceleration();


#endif // _LIB_ASSERV_H_