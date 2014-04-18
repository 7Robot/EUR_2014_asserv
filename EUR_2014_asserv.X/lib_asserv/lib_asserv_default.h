#ifndef _LIB_ASSERV_DEFAULT_H_
#define _LIB_ASSERV_DEFAULT_H_

#ifndef NULL
#define NULL 0
#endif


/*############################################################################*/
/*                                  Motion                                    */
/*############################################################################*/

#ifndef DEFAULT_CONSTRAINT_V_MAX
#define DEFAULT_CONSTRAINT_V_MAX {0.5, 1.6}
#endif

#ifndef DEFAULT_CONSTRAINT_A_MAX
#define DEFAULT_CONSTRAINT_A_MAX {0.5, 1, 0.1}
#endif

/*############################################################################*/
/*                                    Odo                                     */
/*############################################################################*/

#ifndef DEFAULT_ODO_COEFS
#define DEFAULT_ODO_COEFS {54640, 0.000018302, 0.275}
#endif

#ifndef DEFAULT_PERIOD
#define DEFAULT_PERIOD 0.005
#endif

/*############################################################################*/
/*                                  Asserv                                    */
/*############################################################################*/

#ifndef DEFAULT_ASSERV_MODE
#define DEFAULT_ASSERV_MODE ASSERV_MODE_OFF
#endif

/*############################################################################*/
/*                                   PID                                      */
/*############################################################################*/

// 4 asserv différentes (position et vitese pour chaque roue) donc 4 PID
#ifndef DEFAULT_PID_COEFS_PG
#define DEFAULT_PID_COEFS_PG {10,0,0,0,0}
#endif
#ifndef DEFAULT_PID_COEFS_PD
#define DEFAULT_PID_COEFS_PD {10,0,0,0,0}
#endif
#ifndef DEFAULT_PID_COEFS_VG
#define DEFAULT_PID_COEFS_VG {400,4,50,0.7,0.7}
#endif
#ifndef DEFAULT_PID_COEFS_VD
#define DEFAULT_PID_COEFS_VD {400,4,50,0.7,0.7}
#endif

// valeurs max de l'intégrale en position et en vitesse
#ifndef DEFAULT_PID_MAX_INT_POS
#define DEFAULT_PID_MAX_INT_POS 14
#endif
#ifndef DEFAULT_PID_MAX_INT_SPEED
#define DEFAULT_PID_MAX_INT_SPEED 12
#endif

// ainsi que les conditions d'arrêt des PID en position et vitesse
#ifndef DEFAULT_PID_EPS_POS
#define DEFAULT_PID_EPS_POS {0.01,0.02}
#endif
#ifndef DEFAULT_PID_EPS_SPEED
#define DEFAULT_PID_EPS_SPEED {0.01,0.02}
#endif

/*############################################################################*/
/*                                  DEBUG                                     */
/*############################################################################*/

#ifndef DEFAULT_DEBUG_MODE
#define DEFAULT_DEBUG_MODE 0
#endif

#endif // _LIB_ASSERV_DEFAULT_H_