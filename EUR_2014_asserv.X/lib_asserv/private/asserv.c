#include "asserv.h"
#include "odo.h"


/******************************    Variables    *******************************/
volatile int asserv_mode;

volatile Asserv asserv_pos_g;
volatile Asserv asserv_pos_d;
volatile Asserv asserv_speed_g;
volatile Asserv asserv_speed_d;

volatile Position pos_order;
volatile Speed speed_order;



/******************************    Fonctions    *******************************/

// assigner un PID et des contraintes à un asservissement
void set_asserv_pid(Asserv *asserv, Pid pid){ asserv->pid = pid; }
void set_asserv_constraint(Asserv *asserv, MotionConstraint *constraint){ asserv->constraint = constraint; }

// choisir le mode d'asservissement (désactivé, en position, en vitesse)
void set_asserv_off(){asserv_mode = ASSERV_MODE_OFF;}
void set_asserv_pos_mode(){asserv_mode = ASSERV_MODE_POS;}
void set_asserv_speed_mode(){asserv_mode = ASSERV_MODE_SPEED;}


// effectue un pas d'asservissement
void asserv_step(Odo *odo, float *commande_g, float *commande_d){
    // variables intermédiaires permettant de passer des vitesses du robot aux vitesses roue gauche et droite
    float delta_v = odo->coefs.spacing * 0.5 * odo->state->speed.vt;
    float delta_v_order = odo->coefs.spacing * 0.5 * speed_order.vt;
    float v_g, v_d, v_g_order, v_d_order;
    // choix en fonction du mode d'asservissement (off, position ou vitesse)
    switch (asserv_mode){
        // si on est en roue libre
        case ASSERV_MODE_OFF :
            *commande_g = 0;
            *commande_d = 0;
            break;
        // si on est en asservissement en position
        case ASSERV_MODE_POS :
            break;
        // si on est en asservissement en vitesse
        case ASSERV_MODE_SPEED :
            // vitesses gauche et droite
            v_g = odo->state->speed.v - delta_v;
            v_d = odo->state->speed.v + delta_v;
            // consignes des vitesses gauche et droite
            v_g_order = speed_order.v - delta_v_order;
            v_d_order = speed_order.v + delta_v_order;
            // calcul des PID
            pid_set_order(&(asserv_speed_g.pid), v_g_order);
            pid_set_order(&(asserv_speed_d.pid), v_d_order);
            pid_maj(&(asserv_speed_g.pid), v_g);
            pid_maj(&(asserv_speed_d.pid), v_d);
            *commande_g = pid_process(&(asserv_speed_g.pid));
            *commande_d = pid_process(&(asserv_speed_d.pid));
            break;
    }
}