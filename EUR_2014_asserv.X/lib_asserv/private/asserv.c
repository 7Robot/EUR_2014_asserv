#include "extern_globals.h"
#include "asserv.h"
#include "odo.h"
#include "pid.h"
#include "../lib_asserv_default.h"
#include "tools.h"
#include <math.h>


/******************************    Variables    *******************************/
volatile int asserv_mode;

volatile Asserv asserv_pos_g;
volatile Asserv asserv_pos_d;
volatile Asserv asserv_speed_g;
volatile Asserv asserv_speed_d;

volatile PositionAsserv pos_asserv;
volatile SpeedAsserv speed_asserv;



/******************************    Fonctions    *******************************/

// initialiser le mode et les différents asservissement
void asserv_init(){
    asserv_mode = DEFAULT_ASSERV_MODE;

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

    // initialisation des 4 asserv des roues (position et vitesse gauche et droite)
    set_asserv_pid(&asserv_pos_g,pid_pg);
    set_asserv_constraint(&asserv_pos_g,&motionConstraint);
    set_asserv_pid(&asserv_pos_d,pid_pd);
    set_asserv_constraint(&asserv_pos_d,&motionConstraint);
    set_asserv_pid(&asserv_speed_g,pid_vg);
    set_asserv_constraint(&asserv_speed_g,&motionConstraint);
    set_asserv_pid(&asserv_speed_d,pid_vd);
    set_asserv_constraint(&asserv_speed_d,&motionConstraint);

    // initialisation de l'asservissement en position
    pos_asserv.pos_order = (Position){0,0,0};
    // respect des contraintes d'accélération max avec ce coef
    pos_asserv.kp = 3*motionConstraint.a_max.a; // ! motionConstraint doit être initialisé
    pos_asserv.state = &motionState;
    pos_asserv.asserv_speed_g = &asserv_speed_g;
    pos_asserv.asserv_speed_d = &asserv_speed_d;
    pos_asserv.done = 0;
    // initialisation de l'asservissement en vitesse
    speed_asserv.speed_order = (Speed){0,0};
    speed_asserv.speed_order_constrained = (Speed){0,0};
    speed_asserv.state = &motionState;
    speed_asserv.asserv_speed_g = &asserv_speed_g;
    speed_asserv.asserv_speed_d = &asserv_speed_d;
    speed_asserv.done = 0;
}

// assigner un PID et des contraintes à un asservissement
void set_asserv_pid(Asserv *asserv, Pid pid){ asserv->pid = pid; }
void set_asserv_constraint(Asserv *asserv, MotionConstraint *constraint){ asserv->constraint = constraint; }

// choisir le mode d'asservissement (désactivé, en position, en vitesse)
void set_asserv_off(){asserv_mode = ASSERV_MODE_OFF;}
void set_asserv_pos_mode(){asserv_mode = ASSERV_MODE_POS;}
void set_asserv_speed_mode(){asserv_mode = ASSERV_MODE_SPEED;}

// obtenir les consignes vitesse roue gauche et droite
float get_cons_vg(){return asserv_speed_g.pid.order;}
float get_cons_vd(){return asserv_speed_d.pid.order;}
// obtenir les consignes en vitesse et vitesse angulaire
float get_cons_v(){return speed_asserv.speed_order_constrained.v;}
float get_cons_vt(){return speed_asserv.speed_order_constrained.vt;}

// observer les contraintes aux vitesse et vitesse angulaire
void constrain_speed(float v, float vt, float *v_constrained, float *vt_constrained){
    // contraintes
    float v_max = motionConstraint.v_max.v;
    float vt_max = motionConstraint.v_max.vt;
    float a_max = motionConstraint.a_max.a;
    float at_max = motionConstraint.a_max.at;
    float v_vt_max = motionConstraint.a_max.v_vt;
    float v_c_old = *v_constrained;

    // calcul des contraintes
    float period = DEFAULT_PERIOD;
    *v_constrained = limit_float(v,  *v_constrained-a_max*period,  *v_constrained+a_max*period);
    *v_constrained = limit_float(*v_constrained,-v_max,v_max);
    *vt_constrained = limit_float(vt,   *vt_constrained-at_max*period,   *vt_constrained+at_max*period);
    *vt_constrained = limit_float(*vt_constrained,-vt_max,vt_max);

    if (fabs((*v_constrained)*(*vt_constrained)) > v_vt_max){
        if (*v_constrained>0){
            *v_constrained = limit_float(
                    v_vt_max/fabs(*vt_constrained),
                    v_c_old-a_max*period,
                    v_c_old+a_max*period);
        }
        else {
            *v_constrained = limit_float(
                    -v_vt_max/fabs(*vt_constrained),
                    v_c_old-a_max*period,
                    v_c_old+a_max*period);
        }
    }
}

// contraindre les vitesses et accélérations autorisées
void constrain_speed_order(){
    
    // vitesse consigne(o comme order) et consigne contrainte(oc)
    float v_o = speed_asserv.speed_order.v;
    float vt_o = speed_asserv.speed_order.vt;
    float v_oc = speed_asserv.speed_order_constrained.v;
    float vt_oc = speed_asserv.speed_order_constrained.vt;

    constrain_speed(v_o, vt_o, &v_oc, &vt_oc);
    speed_asserv.speed_order_constrained.v = v_oc;
    speed_asserv.speed_order_constrained.vt = vt_oc;
}

// effectue un pas d'asservissement
void asserv_step(Odo *odo, float *commande_g, float *commande_d){
    // choix en fonction du mode d'asservissement (off, position ou vitesse)
    switch (asserv_mode){
        // si on est en roue libre
        case ASSERV_MODE_OFF :
            *commande_g = 0;
            *commande_d = 0;
            break;
        // si on est en asservissement en position
        case ASSERV_MODE_POS :
            pos_asserv_step(odo, commande_g, commande_d);
            break;
        // si on est en asservissement en vitesse
        case ASSERV_MODE_SPEED :
            speed_asserv_step(odo, commande_g, commande_d);
            break;
    }
}

void speed_asserv_step(Odo *odo, float *commande_g, float *commande_d){
    // on commence par vérifier les contraintes de vitesses et accélération
    constrain_speed_order();
    // variables intermédiaires permettant de passer des vitesses du robot aux vitesses roue gauche et droite
    float delta_v = odo->coefs.spacing * 0.5 * odo->state->speed.vt;
    float delta_v_order = odo->coefs.spacing * 0.5 * speed_asserv.speed_order_constrained.vt;
    float v_g, v_d, v_g_order, v_d_order;
    // vitesses gauche et droite
    v_g = odo->state->speed.v - delta_v;
    v_d = odo->state->speed.v + delta_v;
    // consignes des vitesses gauche et droite
    v_g_order = speed_asserv.speed_order_constrained.v - delta_v_order;
    v_d_order = speed_asserv.speed_order_constrained.v + delta_v_order;
    // calcul des PID
    pid_set_order(&(asserv_speed_g.pid), v_g_order);
    pid_set_order(&(asserv_speed_d.pid), v_d_order);
    pid_maj(&(asserv_speed_g.pid), v_g);
    pid_maj(&(asserv_speed_d.pid), v_d);
    *commande_g = pid_process(&(asserv_speed_g.pid));
    *commande_d = pid_process(&(asserv_speed_d.pid));

    // vérification si on est arrivé à la bonne consigne
    if (pid_done(asserv_speed_g.pid) && pid_done(asserv_speed_d.pid)){
        speed_asserv.done = 1;
    }
}


void pos_asserv_step(Odo *odo, float *commande_g, float *commande_d){
    /*
     * On calcule les consignes de vitesse et vitesse angulaire
     * en fonction de la position actuelle et de la consigne de position.
     *
     * Idées :
     * La priorité à la rotation
     * on doit avoir une décroissance des consignes de vitesse plus lente que
     * celles autorisées par l'accélération max
     */
    // distance et angle restants à parcourir
    float x_c = pos_asserv.pos_order.x; // consigne en x
    float y_c = pos_asserv.pos_order.y; // consigne en y
    float x = odo->state->pos.x;
    float y = odo->state->pos.y;
    float d = sqrt((x_c-x)*(x_c-x) + (y_c-y)*(y_c-y));
    float dt = principal_angle(atan2f(y_c-y,x_c-x) - odo->state->pos.t);
    float v_cons, vt_cons;
    if (d<0.01) {
        *commande_g = 0;
        *commande_d = 0;
    }
    else {
        // si |dt| > pi/2 , on calcul beta = dt-pi et c'est beta la nouvelle consigne
        // calcul de la consigne de vitesse et vitesse angulaire
        if (fabs(dt)>PI/2) {
            d = -d;
            dt = dt-PI;
        }
        v_cons = pos_asserv.kp * d;
        vt_cons = 2*dt/fabs(d)*v_cons; // priorité rotation

        // appliquer les contraintes puis revérifier la priorité rotation
        constrain_speed(v_cons, vt_cons, &v_cons, &vt_cons);
        if (fabs(dt)>0.087){v_cons = 0.5*d*fabs(vt_cons/dt);} // si dt > 5°

        // appel de l'asserve en vitesse avec les bonnes consignes
        speed_asserv.speed_order.v = v_cons;
        speed_asserv.speed_order.vt = vt_cons;
        speed_asserv_step(odo,commande_g,commande_d);
    }
}

// indique si l'asservissement en cours a terminé
int asserv_done(){
    if (asserv_mode == ASSERV_MODE_OFF) {return 1;}
    else if (asserv_mode == ASSERV_MODE_POS) {return pos_asserv.done;}
    else if (asserv_mode == ASSERV_MODE_SPEED) {return speed_asserv.done;}
    else {return 0;}
}