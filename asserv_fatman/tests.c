#include <xc.h>

#include <stdint.h>        /* Includes uint16_t definition                    */
#include <stdbool.h>       /* Includes true/false definition                  */
#include <uart.h>

#include "user.h"          /* User funct/params, such as InitApp              */
#include "qei.h"           /* QEI definitions for easier use                  */
#include "motor.h"
#include <libpic30.h>
#include "tests.h"
#include "ax12.h"
#include "actions_ax12.h"
#include "lib_asserv/lib_asserv.h"
#include "lib_asserv/private/tools.h"



/*############################################################################*/
/*                   Tests d'asservissement du robot                          */
/*############################################################################*/

// Asserve en vitesse + vitesse angulaire
void test_Asserv_vitesse()
{
    Speed speed0 = {0, 0};
    Speed speed6 = {0.6, 0};
    Speed speed6n = {-0.6, 0};
    Speed speed3 = {0.3, 0};
    Speed speed3n = {-0.3, 0};
    Speed speed5r = {0,5};
    Speed speed5rn = {0,-5};
    Speed speedv_vt_1 = {0.5,2};
    Speed speedv_vt_1n = {0.5,-2};
    Speed speed_test = {0.3,0};

    // initialize
    Init_All();
    motion_speed(speed_test);
    __delay_ms(1000);

    /*
    // test de réponse à une commande
    set_debug_mode(1);
    motion_speed(speed0);
    __delay_ms(100);
    motion_speed(speed3);
    __delay_ms(1500);
    motion_speed(speed5r);
    __delay_ms(1000);
    motion_speed(speed5rn);
    __delay_ms(1700);
    motion_speed(speed3n);
    __delay_ms(1500);
    motion_speed(speed0);
    __delay_ms(1500);
    motion_free();
     */
    while(1);
}

// asserve en position
void test_Asserv_pos(){
    Position pos0 = {0, 0, 0};
    Position pos1 = {0.2,0,0};
    Position pos2 = {0.1,0.1,0};
    Position pos3 = {0.2,0.2,0};
    Position pos4 = {0,0.2,0};
    Position pos_test = {-3.0,0,0};

    // initialize
    Init_All();

    // test de réponse à une commande
    //set_debug_mode(1);
    //motion_pos(pos_test);
    //while (!motion_done());
    //while(1){};
    
    motion_pos(pos1);
    while (!motion_done());
    motion_pos(pos2);
    while (!motion_done());
    motion_pos(pos3);
    while (!motion_done());
    motion_pos(pos4);
    while (!motion_done());
    motion_pos(pos0);
    while (!motion_done());
    motion_free();
}

// asserve en angle
void test_Asserv_angle(){
    float a0 = 0;
    float a1 = PI/2;
    float a2 = -PI/2;
    float a3 = PI;
    float alpha = a2;
    int i = 0;

    // initialize
    Init_All();

    // test de réponse à une commande
    set_debug_mode(1);
    for (i=0;i<1;i++){
        motion_angle(alpha);
        while (!motion_done());
        alpha = alpha + a2;
    }
    motion_free();
}

// test des ax12 integrés à l'asserve
void test_ax12(){

    // initialize
    Init_All();
   // responseReadyAX = 0;
    while(1){

        convoyer();
        __delay_ms(1000);
    }
}

// test des ax12 integrés à l'asserve
void test_atp(){
    Init_All();
    while(1);
}


/******************************************************************************/
/*                      Tests avec les interruptions                          */
/******************************************************************************/

// allumer la led à une fréquence de 1Hz
void test_interrupt_led(int periode){
    static int compteur = 0;
    compteur++;
    if (compteur==periode) {
        basculer_led();
        compteur = 0;
    }
}

void basculer_led(){
    led = !led;
}