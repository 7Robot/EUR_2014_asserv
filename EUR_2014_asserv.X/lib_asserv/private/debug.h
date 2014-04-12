#ifndef _DEBUG_H_
#define _DEBUG_H_

#define DEBUG_COUNT_MAX 400

// pour le réglage de l'asserv (tableaux à récupérer en mode debug)
typedef struct {
    // consignes en vitesse et vitesse angulaire du robot
    float v[DEBUG_COUNT_MAX];
    float vt[DEBUG_COUNT_MAX];
    float cons_v[DEBUG_COUNT_MAX];
    float cons_vt[DEBUG_COUNT_MAX];
    /*
    // consignes des roues gauche et droites
    float vg[DEBUG_COUNT_MAX];
    float vd[DEBUG_COUNT_MAX];
    float cons_vg[DEBUG_COUNT_MAX];
    float cons_vd[DEBUG_COUNT_MAX];
    */
} SpeedDebug;

/*#############################    Fonctions    ##############################*/

void set_debug_mode(int mode);
void debug_init();
void debug_speed_asserv();


#endif // _DEBUG_H_