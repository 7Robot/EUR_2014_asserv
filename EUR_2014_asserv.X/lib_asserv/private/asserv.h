#ifndef _ASSERV_H_
#define _ASSERV_H_

#include "motion.h"
#include "pid.h"
#include "odo.h"

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

// Un asservissement en position connait les asserv en vitesse des roues gauche et droite
typedef struct {
    Position pos_order;
    Asserv *asserv_speed_g;
    Asserv *asserv_speed_d;
    MotionState *state;
    int done;
} PositionAsserv;

// Un asservissement en vitesse connait les asserv en vitesse des roues gauche et droite
typedef struct {
    Speed speed_order;
    Asserv *asserv_speed_g;
    Asserv *asserv_speed_d;
    MotionState *state;
    int done;
} SpeedAsserv;


/******************************    Fonctions    *******************************/

// initialiser le mode et les différents asservissement
void asserv_init();

// assigner un PID et des contraintes à un asservissement
void set_asserv_pid(Asserv *asserv, Pid pid);
void set_asserv_constraint(Asserv *asserv, MotionConstraint *constraint);

// choisir le mode d'asservissement (désactivé, en position, en vitesse)
void set_asserv_off();
void set_asserv_pos_mode();
void set_asserv_speed_mode();

// obtenir les consignes vitesse roue gauche et droite
float get_cons_vg();
float get_cons_vd();

// effectue un pas d'asservissement
void asserv_step(Odo *odo, float *commande_g, float *commande_d);
void speed_asserv_step(Odo *odo, float *commande_g, float *commande_d);

// indique si l'asservissement en cours a terminé
int asserv_done();


#endif // _ASSERV_H_