#include "motion.h"
#include "asserv.h"
#include "odo.h"

/******************************    Variables    *******************************/
volatile MotionState motionState;
volatile MotionConstraint motionConstraint;
static void(*done)(void); // callback


/******************************    Fonctions    *******************************/

// initialiser la lib d'asservissement
void motion_init(void(*_done)(void)) {
    done = _done;
    odo_init();
    asserv_init();
}

// assigner des valeurs à la position (x, y et theta)
void set_position(MotionState *state, Position pos){state->pos = pos;}
void set_position_x(MotionState *state, float x){state->pos.x = x;}
void set_position_y(MotionState *state, float y){state->pos.y = y;}
void set_position_t(MotionState *state, float t){state->pos.t = t;}

// assigner des valeurs à la vitesse (vitesse et vitesse angulaire)
void set_speed(MotionState *state, Speed speed){state->speed = speed;}
void set_speed_v(MotionState *state, float v){state->speed.v = v;}
void set_speed_vt(MotionState *state, float vt){state->speed.vt = vt;}

// assigner des valeurs à l'accélération
void set_acceleration(MotionState *state, Acceleration acc){state->acc = acc;}
void set_acceleration_a(MotionState *state, float a){state->acc.a = a;}
void set_acceleration_at(MotionState *state, float at){state->acc.at = at;}
void set_acceleration_v_vt(MotionState *state, float v_vt){state->acc.v_vt = v_vt;}

// consignes de déplacements du robot
void motion_free(){set_asserv_off();}
void motion_pos(Position pos){
    pos_asserv.done = 0;
    pos_asserv.pos_order = pos;
    set_asserv_pos_mode();
}
void motion_speed(Speed speed){
    speed_asserv.done = 0;
    speed_asserv.speed_order = speed;
    set_asserv_speed_mode();
}


// renvoie les commandes des roues gauche et droite (appelé par l'interruption toutes les 10 ms)
void motion_step(int tics_g, int tics_d, float *commande_g, float *commande_d){
    // maj de l'odométrie
    odo_step(&odo, tics_g, tics_d);
    // on appelle la bonne fonction d'asservissement
    asserv_step(&odo, commande_g, commande_d);
    // indique si on est arrivé
    if (asserv_done()) done();
}