#ifndef _ASSERV_H_
#define _ASSERV_H_

#include "motion.h"
#include "pid.h"

// mode de l'asservissement
#define ASSERV_MODE_OFF 0
#define ASSERV_MODE_POS 1
#define ASSERV_MODE_SPEED 2


/*****************************    Structures    *******************************/

// Une asserve possède un PID et connaît les contraintes de déplacement du robot
typedef struct {
    Pid pid;
    MotionConstraint *constraint;
} Asserv;


/******************************    Fonctions    *******************************/

// assigner un PID et des contraintes à un asservissement
void set_asserv_pid(Asserv *asserv, Pid pid);
void set_asserv_constraint(Asserv *asserv, MotionConstraint *constraint);

// choisir le mode d'asservissement (désactivé, en position, en vitesse)
void set_asserv_off();
void set_asserv_pos_mode();
void set_asserv_speed_mode();

// effectue un pas d'asservissement
void asserv_step(Odo *odo, float *commande_g, float *commande_d);


#endif // _ASSERV_H_