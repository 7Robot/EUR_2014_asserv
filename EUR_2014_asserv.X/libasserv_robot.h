#ifndef _LIBASSERV_ROBOT_H_
#define _LIBASSERV_ROBOT_H_

#define DEFAULT_DELTA_POS_COEFS { 1, 0, 0 }
#define DEFAULT_ALPHA_POS_COEFS { 1, 0, 0 }
#define DEFAULT_DELTA_SPEED_COEFS { 1, 0, 0 }


#define DEFAULT_DIST_SPEED_MAX  1.5
#define DEFAULT_DIST_ACC_MAX    0.5
#define DEFAULT_DIST_DEC_MAX    0.5
#define DEFAULT_ROT_SPEED_MAX   0.8
#define DEFAULT_ROT_ACC_MAX     0.5
#define DEFAULT_ROT_DEC_MAX     0.5

#define DEFAULT_EPSILON_DIST    0.01
#define DEFAULT_EPSILON_SPEED   0.001
#define DEFAULT_EPSILON_THETA   0.05
#define DEFAULT_EPSILON_OMEGA   0.001

#define DEFAULT_TIC_BY_METER    13969
#define DEFAULT_SPACING         0.219

#define MOTOR_1A_TRIS _TRISB9
#define MOTOR_1B_TRIS _TRISB11
#define MOTOR_2A_TRIS _TRISB13
#define MOTOR_2B_TRIS _TRISB14

#define MOTOR_1A_O _LATB9
#define MOTOR_1B_O _LATB11
#define MOTOR_2A_O _LATB13
#define MOTOR_2B_O _LATB14

#define CONSIGNE_NULLE 0
#define CONSIGNE_MAX 5000

#endif // _LIBASSERV_ROBOT_H_
