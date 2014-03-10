/* Device header file */
#if defined(__XC16__)
    #include <xc.h>
#elif defined(__C30__)
    #if defined(__dsPIC33E__)
    	#include <p33Exxxx.h>
    #elif defined(__dsPIC33F__)
    	#include <p33Fxxxx.h>
    #endif
#endif


#include <stdint.h>        /* Includes uint16_t definition                    */
#include <stdbool.h>       /* Includes true/false definition                  */

#include "system.h"        /* System funct/params, like osc/peripheral config */
#include "user.h"          /* User funct/params, such as InitApp              */
#include "asserv.h"
#include "qei.h"           /* QEI definitions for easier use                  */
#include <libpic30.h>
#include "tests.h"

// teste si la fréquence du PWM est bien la bonne
void test_frequence_fixe_moteurs(float frequence)
{
    while (1)
    {
        PWM_Moteurs_Detail(frequence, 25, 25);
        __delay_ms(10);
    }
}

// teste si la fréquence a une influence importante sur les perfs
// la fréquence va varier de f_min a f_max en temps secondes
void test_frequence_variable_moteurs(float f_min,float f_max, float temps)
{
    float f;
    float pas = (f_max-f_min)/(100*temps);

    for (f=f_min; f<f_max; f+=pas)
    {
        PWM_Moteurs_Detail(f, 25, 25);
        __delay_ms(10);
    }
}
