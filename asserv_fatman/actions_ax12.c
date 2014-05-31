#include <p33Fxxxx.h>      /* Includes device header file                     */
#include <stdint.h>        /* Includes uint16_t definition                    */
#include <stdbool.h>       /* Includes true/false definition                  */
#include "user.h"        /* Function / Parameters                           */
#include <libpic30.h>
#include "ax12.h"
#include <uart.h>
#include <delay.h>
#include "actions_ax12.h"
#include "atp-asserv.h"
#include <math.h>

int S1;
int S2;
int S3;

/*********************************************************************
 *********/
/*************************** Arm Specification ********************************/

/******************************************************************************/

void choose_arm(int arm) {
    if (arm == 1) {
        S1 = SD1;
        S2 = SD2;
        S3 = SD3;
    } else if (arm == 2) {
        S1 = SG1;
        S2 = SG2;
        S3 = SG3;
    }
}


/******************************************************************************/
/****************************** Init Position *********************************/

/******************************************************************************/
void init_arm(int arm) {

    choose_arm(arm);

    PutAX(S1, AX_TORQUE_LIMIT, 650);
    __delay_ms(40);
    PutAX(S2, AX_TORQUE_LIMIT, 650);
    __delay_ms(40);
    PutAX(S3, AX_TORQUE_LIMIT, 650);
    __delay_ms(40);

    PutAX(S1, AX_MOVING_SPEED, 650);
    __delay_ms(40);
    PutAX(S2, AX_MOVING_SPEED, 650);
    __delay_ms(40);
    PutAX(S3, AX_MOVING_SPEED, 650);
    __delay_ms(40);

    PutAX(S1, AX_GOAL_POSITION, 562);
    __delay_ms(100);
    PutAX(S2, AX_GOAL_POSITION, 250);
    __delay_ms(100);
    PutAX(S3, AX_GOAL_POSITION, 205);
    __delay_ms(500);

}

/******************************************************************************/
/******************************* Catch a Fire *********************************/

/******************************************************************************/

void catch_arm(int arm) {
    int position =0;
    int toto = 0; // MA MARQUE DE FABRIQUE
    choose_arm(arm);


    PutAX(S1, AX_TORQUE_LIMIT, 650);
    __delay_ms(50);
    PutAX(S2, AX_TORQUE_LIMIT, 650);
    __delay_ms(50);
    PutAX(S3, AX_TORQUE_LIMIT, 650);
    __delay_ms(50);
    PutAX(S1, AX_MOVING_SPEED, 650);
    __delay_ms(50);
    PutAX(S2, AX_MOVING_SPEED, 650);
    __delay_ms(50);
    PutAX(S3, AX_MOVING_SPEED, 650);
    __delay_ms(50);

    PutAX(S2, AX_GOAL_POSITION, 300);
    __delay_ms(200);    //300
    PutAX(S3, AX_GOAL_POSITION, 512);
    __delay_ms(300);    //500

    PutAX(S2, AX_GOAL_POSITION, 390);
    __delay_ms(100);
    PutAX(S1, AX_GOAL_POSITION, 678);
    __delay_ms(100);


    PutAX(S3, AX_GOAL_POSITION, 300);
    __delay_ms(200);    //300
    PutAX(S3, AX_TORQUE_LIMIT, 420);
    __delay_ms(40);
    PutAX(S3, AX_GOAL_POSITION, 150);
    __delay_ms(200);    //400

    GetAX(S3, AX_PRESENT_POSITION);
    while(!responseReadyAX && toto < 50){
        toto++;
        __delay_ms(1);
    }

    position = (responseAX.params[1]*256 + responseAX.params[0]);
    __delay_ms(40);

    stock_arm(arm);

    SendCaught(position>170);
   
}

/******************************************************************************/
/********************************* Stock a Fire *******************************/

/******************************************************************************/

void stock_arm(int arm) {

    choose_arm(arm);

    PutAX(S3, AX_TORQUE_LIMIT, 420);
    __delay_ms(50);
    PutAX(S1, AX_TORQUE_LIMIT, 650);
    __delay_ms(50);
    PutAX(S2, AX_TORQUE_LIMIT, 650);
    __delay_ms(50);


    PutAX(S1, AX_MOVING_SPEED, 650);
    __delay_ms(50);
    PutAX(S2, AX_MOVING_SPEED, 650);
    __delay_ms(50);
    PutAX(S3, AX_MOVING_SPEED, 650);
    __delay_ms(50);


    PutAX(S1, AX_GOAL_POSITION, 562);
    __delay_ms(100);
    PutAX(S2, AX_GOAL_POSITION, 300);
    __delay_ms(100);
    PutAX(S3, AX_GOAL_POSITION, 150);
    __delay_ms(1000);

    SendDone();
}



/******************************************************************************/
/************************* place le bras dans une position ********************/
/***********       qui permet de  s'aprocher des foyer sans soucis ************/
/******************************************************************************/
void raise_arm(int arm){

    choose_arm(arm);

    PutAX(S2, AX_TORQUE_LIMIT, 650);
    __delay_ms(50);
    PutAX(S2, AX_MOVING_SPEED, 650);
    __delay_ms(50);

    PutAX(S2, AX_GOAL_POSITION, 340);
    __delay_ms(50);

}

/******************************************************************************/
/************************* Put Fire on the 1st Face ***************************/

/******************************************************************************/

void pull_arm(int arm) {

    choose_arm(arm);

    PutAX(S3, AX_TORQUE_LIMIT, 420);
    __delay_ms(50);
    PutAX(S1, AX_TORQUE_LIMIT, 650);
    __delay_ms(50);
    PutAX(S2, AX_TORQUE_LIMIT, 650);
    __delay_ms(50);

    PutAX(S1, AX_MOVING_SPEED, 650);
    __delay_ms(50);
    PutAX(S2, AX_MOVING_SPEED, 650);
    __delay_ms(50);
    PutAX(S3, AX_MOVING_SPEED, 650);
    __delay_ms(50);

    PutAX(S2, AX_GOAL_POSITION, 480);
    __delay_ms(300);
    PutAX(S1, AX_GOAL_POSITION, 635);
    __delay_ms(400);
    PutAX(S2, AX_GOAL_POSITION, 760);
    __delay_ms(300);
    PutAX(S1, AX_GOAL_POSITION, 825);
    __delay_ms(400);

    PutAX(S3, AX_GOAL_POSITION, 512);
    __delay_ms(10);
    PutAX(S3, AX_TORQUE_LIMIT, 650);
    __delay_ms(20);

    PutAX(S2, AX_GOAL_POSITION, 380);
    __delay_ms(10);
    PutAX(S1, AX_GOAL_POSITION, 666);
    __delay_ms(400);


    init_arm(arm);
    SendLaid();
}

/******************************************************************************/
/************************* Put Fire on the 2nd Face ***************************/

/******************************************************************************/
void push_arm(int arm) {

    choose_arm(arm);

    PutAX(S3, AX_TORQUE_LIMIT, 420);
    __delay_ms(50);
    PutAX(S1, AX_TORQUE_LIMIT, 650);
    __delay_ms(50);
    PutAX(S2, AX_TORQUE_LIMIT, 650);
    __delay_ms(50);

    PutAX(S1, AX_MOVING_SPEED, 650);
    __delay_ms(50);
    PutAX(S2, AX_MOVING_SPEED, 650);
    __delay_ms(50);
    PutAX(S3, AX_MOVING_SPEED, 650);
    __delay_ms(50);

    PutAX(S2, AX_GOAL_POSITION, 400);
    __delay_ms(200);
    PutAX(S1, AX_GOAL_POSITION, 640);
    __delay_ms(500);
    PutAX(S3, AX_GOAL_POSITION, 512);
    __delay_ms(400);
    PutAX(S2, AX_GOAL_POSITION, 700);
    __delay_ms(140);
    PutAX(S1, AX_GOAL_POSITION, 750);
    __delay_ms(200);

    init_arm(arm);
    SendLaid();
}

void launch_net() {
    PutAX(LAU, AX_TORQUE_LIMIT, 650);
    __delay_ms(40);

    PutAX(LAU, AX_MOVING_SPEED, 650);
    __delay_ms(40);

    PutAX(LAU, AX_GOAL_POSITION, 512);
    __delay_ms(50);
    PutAX(LAU, AX_GOAL_POSITION, 330);
    __delay_ms(500);
    PutAX(LAU, AX_GOAL_POSITION, 512);
    __delay_ms(50);
    SendDone();

}

void convoyer() // fonction qui enclenche le tapis roulant
{

        PutAX(CONV, AX_CW_ANGLE_LIMIT, 0); // on met le servo en "roue libre"
        __delay_ms(50);
        PutAX(CONV, AX_CCW_ANGLE_LIMIT, 0);
        __delay_ms(50);

        PutAX(CONV, AX_MOVING_SPEED, 0b11111111111); // le bit de poids fort gère le sens, les autres la vitesse
        __delay_ms(5000); // temps de déroulage du tapis


        PutAX(CONV, AX_CW_ANGLE_LIMIT, 255); // arret de la roue libre
        __delay_ms(100);

        SendDone();
}

void slight_convoyer() // fonction qui enclenche le tapis roulant
{

        PutAX(CONV, AX_CW_ANGLE_LIMIT, 0); // on met le servo en "roue libre"
        __delay_ms(50);
        PutAX(CONV, AX_CCW_ANGLE_LIMIT, 0);
        __delay_ms(50);

        PutAX(CONV, AX_MOVING_SPEED, 0b11011111111); // le bit de poids fort gère le sens, les autres la vitesse
        __delay_ms(700); // temps de déroulage du tapis

        PutAX(CONV, AX_MOVING_SPEED, 0);
        __delay_ms(100);

        SendDone();
}

void poulet() {

    int j;

    for (j=1;j<3;j++)
    {
    choose_arm (j);
    PutAX(S1, AX_TORQUE_LIMIT, 580);
    __delay_ms(50);
    PutAX(S2, AX_TORQUE_LIMIT, 580);
    __delay_ms(50);
    PutAX(S3, AX_TORQUE_LIMIT, 580);
    __delay_ms(50);

    PutAX(S1, AX_MOVING_SPEED, 650);
    __delay_ms(50);
    PutAX(S2, AX_MOVING_SPEED, 650);
    __delay_ms(50);
    PutAX(S3, AX_MOVING_SPEED, 650);
    __delay_ms(50);

    PutAX(S2, AX_GOAL_POSITION, 800);
    __delay_ms(300);
    PutAX(S1, AX_GOAL_POSITION, 720);
    __delay_ms(100);
    PutAX(S3, AX_GOAL_POSITION, 320);
    __delay_ms(100);
    }

    int i;

    for (i=0;i<20;i++)
    {
        for (j=1;j<3;j++)
        {
            choose_arm(j);
    PutAX(S1, AX_GOAL_POSITION, 730+sin(i)*60);
    __delay_ms(35);
    PutAX(S2, AX_GOAL_POSITION, 666+sin(i*0.8)*100);
    __delay_ms(35);
    PutAX(S3, AX_GOAL_POSITION, 320+sin(i*0.8)*100);
    __delay_ms(35);
        }
    }

    init_arm(1);
    init_arm(2);

    SendDone();
}


void salut(int arm)
{


    choose_arm(arm);

    PutAX(S1, AX_TORQUE_LIMIT, 650);
    __delay_ms(50);
    PutAX(S2, AX_TORQUE_LIMIT, 650);
    __delay_ms(50);
    PutAX(S3, AX_TORQUE_LIMIT, 650);
    __delay_ms(50);

    PutAX(S1, AX_MOVING_SPEED, 650);
    __delay_ms(50);
    PutAX(S2, AX_MOVING_SPEED, 650);
    __delay_ms(50);
    PutAX(S3, AX_MOVING_SPEED, 650);
    __delay_ms(50);

    PutAX(S2, AX_GOAL_POSITION, 480);
    __delay_ms(300);
    PutAX(S1, AX_GOAL_POSITION, 635);
    __delay_ms(400);
    PutAX(S2, AX_GOAL_POSITION, 820);
    __delay_ms(300);
    PutAX(S1, AX_GOAL_POSITION, 830);
    __delay_ms(400);

}