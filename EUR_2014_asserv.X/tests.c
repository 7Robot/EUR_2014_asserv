#include <xc.h>

#include <stdint.h>        /* Includes uint16_t definition                    */
#include <stdbool.h>       /* Includes true/false definition                  */

#include "user.h"          /* User funct/params, such as InitApp              */
#include "qei.h"           /* QEI definitions for easier use                  */
#include <libpic30.h>
#include "tests.h"
#include "lib_asserv/lib_asserv.h"


/*############################################################################*/
/*                   Tests d'asservissement du robot                          */
/*############################################################################*/

// Asserve en vitesse + vitesse angulaire
void test_Asserv_vitesse(float cons_v,float cons_vt)
{
    Speed speed = {cons_v, cons_vt};

    /* Configure the oscillator for the device */
    ConfigureOscillator();
    /* Initialize IO ports and peripherals */
    InitTimers();
    Init_PWM();
    Init_QEI();
    motion_init(basculer_led);

    motion_speed(speed);
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