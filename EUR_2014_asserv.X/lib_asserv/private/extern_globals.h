#include "asserv.h"
#include "motion.h"
#include "odo.h"
#include "pid.h"
#include "debug.h"

// asserv
extern volatile int asserv_mode;
extern volatile Asserv asserv_pos_g;
extern volatile Asserv asserv_pos_d;
extern volatile Asserv asserv_speed_g;
extern volatile Asserv asserv_speed_d;
extern volatile PositionAsserv pos_asserv;
extern volatile SpeedAsserv speed_asserv;

// motion
extern volatile float motion_initialized;
extern volatile MotionState motionState;
extern volatile MotionConstraint motionConstraint;

// odo
extern volatile Odo odo;

// debug
extern volatile int debug_mode;
extern volatile int debug_count;
//extern volatile SpeedDebug speedDebug;
extern volatile PosDebug posDebug;