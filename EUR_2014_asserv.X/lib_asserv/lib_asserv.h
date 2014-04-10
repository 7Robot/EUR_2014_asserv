#ifndef _LIB_ASSERV_H_
#define _LIB_ASSERV_H_

#include "private/motion.h"
#include "private/extern_globals.h"

/******************************** Fonctions ***********************************/

// consignes de déplacements du robot
void motion_free(); // passer en roue libre
void motion_pos(Position pos); // aller à cette position
void motion_speed(Speed speed); // avancer à cette vitesse

// renvoie les commandes des roues gauche et droite (appelé par l'interruption toutes les 10 ms)
void motion_step(int tics_g, int tics_d, float *commande_g, float *commande_d);


#endif // _LIB_ASSERV_H_