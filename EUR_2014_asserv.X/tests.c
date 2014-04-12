#include <xc.h>

#include <stdint.h>        /* Includes uint16_t definition                    */
#include <stdbool.h>       /* Includes true/false definition                  */

#include "user.h"          /* User funct/params, such as InitApp              */
#include "qei.h"           /* QEI definitions for easier use                  */
#include "motor.h"
#include <libpic30.h>
#include "tests.h"
#include "lib_asserv/lib_asserv.h"


/*############################################################################*/
/*                   Tests d'asservissement du robot                          */
/*############################################################################*/

// Asserve en vitesse + vitesse angulaire
void test_Asserv_vitesse_reglage()
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

    /* Configure the oscillator for the device */
    ConfigureOscillator();
    /* Initialize IO ports and peripherals */
    InitTimers();
    Init_PWM();
    Init_QEI();
    motion_init(basculer_led);

    // test de réponse à une commande
    set_debug_mode(1);
    motion_speed(speed0);
    __delay_ms(100);
    motion_speed(speedv_vt_1);
    __delay_ms(1500);
    motion_speed(speedv_vt_1n);
    __delay_ms(3000);
    motion_speed(speed0);
    __delay_ms(1000);
    motion_free();
}

// asserve en position
void test_Asserv_pos(){
    Position pos0 = {0, 0, 0};
    Position pos05 = {0.5,0,0};

    /* Configure the oscillator for the device */
    ConfigureOscillator();
    /* Initialize IO ports and peripherals */
    InitTimers();
    Init_PWM();
    Init_QEI();
    motion_init(basculer_led);

    // test de réponse à une commande
    set_debug_mode(1);
    motion_pos(pos0);
    __delay_ms(100);
    motion_pos(pos05);
    __delay_ms(3000);
    motion_pos(pos0);
    __delay_ms(1000);
    motion_free();
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