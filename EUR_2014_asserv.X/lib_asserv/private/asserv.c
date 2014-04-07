#include "asserv.h"
#include "odo.h"
#include "../lib_asserv_default.h"


/******************************    Variables    *******************************/
volatile int asserv_mode;

volatile Asserv asserv_pos_g;
volatile Asserv asserv_pos_d;
volatile Asserv asserv_speed_g;
volatile Asserv asserv_speed_d;

volatile Position pos_order;
volatile Speed speed_order;



/******************************    Fonctions    *******************************/

// initialiser le mode et les différents asservissement
void asserv_init(){
    asserv_mode = DEFAULT_ASSERV_MODE;
    pos_order = (Position) {0,0,0};
    speed_order = (Speed) {0,0};

    // PID pour l'asserv en position gauche
    Pid pid_pg;
    PidCoefs coefs_pg = DEFAULT_PID_COEFS_PG;
    PidState state_pg = {0,0,0,DEFAULT_PID_MAX_INT_POS};
    PidEps eps_pg = DEFAULT_PID_EPS_POS;
    pid_set_coefs(&pid_pg,coefs_pg);
    pid_set_state(&pid_pg, state_pg);
    pid_set_eps(&pid_pg, eps_pg);
    pid_set_order(&pid_pg, 0);

    // PID pour l'asserv en position droite
    Pid pid_pd;
    PidCoefs coefs_pd = DEFAULT_PID_COEFS_PD;
    PidState state_pd = {0,0,0,DEFAULT_PID_MAX_INT_POS};
    PidEps eps_pd = DEFAULT_PID_EPS_POS;
    pid_set_coefs(&pid_pd,coefs_pd);
    pid_set_state(&pid_pd, state_pd);
    pid_set_eps(&pid_pd, eps_pd);
    pid_set_order(&pid_pd, 0);

    // PID pour l'asserv en vitesse gauche
    Pid pid_vg;
    PidCoefs coefs_vg = DEFAULT_PID_COEFS_VG;
    PidState state_vg = {0,0,0,DEFAULT_PID_MAX_INT_SPEED};
    PidEps eps_vg = DEFAULT_PID_EPS_SPEED;
    pid_set_coefs(&pid_vg,coefs_vg);
    pid_set_state(&pid_vg, state_vg);
    pid_set_eps(&pid_vg, eps_vg);
    pid_set_order(&pid_vg, 0);

    // PID pour l'asserv en vitesse droite
    Pid pid_vd;
    PidCoefs coefs_vd = DEFAULT_PID_COEFS_VD;
    PidState state_vd = {0,0,0,DEFAULT_PID_MAX_INT_SPEED};
    PidEps eps_vd = DEFAULT_PID_EPS_SPEED;
    pid_set_coefs(&pid_vd,coefs_vd);
    pid_set_state(&pid_vd, state_vd);
    pid_set_eps(&pid_vd, eps_vd);
    pid_set_order(&pid_vd, 0);

    // initialisation des 4 asserv (position et vitesse gauche et droite)
    set_asserv_pid(&asserv_pos_g,pid_pg);
    set_asserv_constraint(&asserv_pos_g,&motionConstraint);
    set_asserv_pid(&asserv_pos_d,pid_pd);
    set_asserv_constraint(&asserv_pos_d,&motionConstraint);
    set_asserv_pid(&asserv_speed_g,pid_vg);
    set_asserv_constraint(&asserv_speed_g,&motionConstraint);
    set_asserv_pid(&asserv_speed_d,pid_vd);
    set_asserv_constraint(&asserv_speed_d,&motionConstraint);
}

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