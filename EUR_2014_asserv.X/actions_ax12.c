#include <p33Fxxxx.h>      /* Includes device header file                     */
#include <stdint.h>        /* Includes uint16_t definition                    */
#include <stdbool.h>       /* Includes true/false definition                  */
#include "user.h"        /* Function / Parameters                           */
#include <libpic30.h>
#include "ax12.h"
#include <uart.h>
#include <delay.h>
#include "actions_ax12.h"


int S1;
int S2;
int S3;

/******************************************************************************/
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

    PutAX(S1, AX_GOAL_POSITION, 512);
    __delay_ms(100);
    PutAX(S2, AX_GOAL_POSITION, 205);
    __delay_ms(100);
    PutAX(S3, AX_GOAL_POSITION, 205);
    __delay_ms(500);

}

/******************************************************************************/
/******************************* Catch a Fire *********************************/

/******************************************************************************/

void catch_arm(int arm) {

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

    PutAX(S3, AX_GOAL_POSITION, 512);
    __delay_ms(500);

    PutAX(S2, AX_GOAL_POSITION, 380);
    __delay_ms(100);
    PutAX(S1, AX_GOAL_POSITION, 666);
    __delay_ms(100);


    PutAX(S3, AX_GOAL_POSITION, 210);
    __delay_ms(300);
    PutAX(S3, AX_TORQUE_LIMIT, 420);
    __delay_ms(40);
    PutAX(S3, AX_GOAL_POSITION, 180);
    __delay_ms(400);

    stock_arm(arm);
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


    PutAX(S1, AX_GOAL_POSITION, 512);
    __delay_ms(100);
    PutAX(S2, AX_GOAL_POSITION, 300);
    __delay_ms(100);
    PutAX(S3, AX_GOAL_POSITION, 180);
    __delay_ms(1000);

    /*
    /////////l�cher le bordel////////
    __delay_ms(3000);
    PutAX(S3, AX_TORQUE_LIMIT, 600);
    __delay_ms(50);
    PutAX(S3, AX_GOAL_POSITION, 512);
    __delay_ms(1000);
    /////////////////////////////////
     */
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

    PutAX(S2, AX_GOAL_POSITION, 700);
    __delay_ms(280);
    PutAX(S1, AX_GOAL_POSITION, 760);
    __delay_ms(700);

    PutAX(S3, AX_GOAL_POSITION, 512);
    __delay_ms(10);
    PutAX(S3, AX_TORQUE_LIMIT, 650);
    __delay_ms(20);

    PutAX(S2, AX_GOAL_POSITION, 380);
    __delay_ms(10);
    PutAX(S1, AX_GOAL_POSITION, 666);
    __delay_ms(400);


    init_arm(arm);
}

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
    __delay_ms(300);
    PutAX(S1, AX_GOAL_POSITION, 640);
    __delay_ms(500);
    PutAX(S3, AX_GOAL_POSITION, 512);
    __delay_ms(600);
    PutAX(S2, AX_GOAL_POSITION, 760);
    __delay_ms(140);
    PutAX(S1, AX_GOAL_POSITION, 820);
    __delay_ms(200);
    
    init_arm(arm);
}

void launch_net() {
    PutAX(18, AX_TORQUE_LIMIT, 650);
    __delay_ms(40);

    PutAX(18, AX_MOVING_SPEED, 650);
    __delay_ms(40);

    PutAX(18, AX_GOAL_POSITION, 512);
    __delay_ms(50);
    PutAX(18, AX_GOAL_POSITION, 330);
    __delay_ms(500);
    PutAX(18, AX_GOAL_POSITION, 512);
    __delay_ms(50);

}


