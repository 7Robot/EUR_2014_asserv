/* 
* ___________      _           _   
*|___  / ___ \    | |         | |  
*   / /| |_/ /___ | |__   ___ | |_ 
*  / / |    // _ \| '_ \ / _ \| __|
*./ /  | |\ \ (_) | |_) | (_) | |_ 
*\_/   \_| \_\___/|_.__/ \___/ \__|
* 7robot.fr
*/

#include "atp-asserv.h"
#include "../asserv/asserv/libasserv.h"

void OnDist(float dist, float vMax, float aMax) { motion_dist(dist, vMax, aMax); }

void OnDistFree(float dist) { motion_dist_free(dist); }

void OnRot(float rot, float vMax, float aMax) { motion_rot(rot, vMax, aMax); }

void OnRotFree(float rot) { motion_rot_free(rot); }

void OnDistRot(float dist, float rot, float vDistMax, float aDistMax, float vRotMax, float aRotMax) {
    motion_dist_rot(dist, rot, vDistMax, aDistMax, vRotMax, aRotMax);
}

void OnReachX(float x, float vMax, float aMax) { motion_reach_x(x, vMax, aMax); }

void OnReachY(float y, float vMax, float aMax) { motion_reach_y(y, vMax, aMax); }

void OnReachTheta(float theta, float vMax, float aMax) { motion_reach_theta(theta, vMax, aMax); }

void OnSpeed(float speed, float aMax, float dMax) { motion_speed(speed, aMax, dMax); }

void OnSpeedFree(float speed) { motion_speed_free(speed); }

void OnOmega(float omega, float aMax, float dMax) { motion_omega(omega, aMax, dMax); }

void OnOmegaFree(float omega) { motion_omega_free(omega); }

void OnSpeedOmega(float speed, float omega, float aDistMax, float dDistMax, float aRotMax, float dRotMax) {
    motion_speed_omega(speed, omega, aDistMax, dDistMax, aRotMax, dRotMax);
}

void OnStop() { motion_stop(); }

void OnBlock() { motion_block(); }

void OnSetEpsilons(float dist, float speed, float theta, float omega) {
    motion_set_epsilons(dist, speed, theta, omega);
}

void OnSetTicByMeter(unsigned long int tic_by_meter) { odo_set_tic_by_meter((int)tic_by_meter); }

void OnSetSpacing(float spacing) { odo_set_spacing(spacing); }

void OnGetX() { SendX(odo_get_x()); }

void OnGetY() { SendX(odo_get_y()); }

void OnGetTheta() { SendTheta(odo_get_theta()); }

void OnGetPos() { SendPos(odo_get_x(), odo_get_y(), odo_get_theta()); }

void OnSetX(float x) { odo_set_x(x); }

void OnSetY(float y) { odo_set_y(y); }

void OnSetTheta(float theta) { odo_set_theta(theta); }

void OnSetXTheta(float x, float theta) { odo_set_x(x); odo_set_theta(theta); }

void OnSetYTheta(float y, float theta) { odo_set_y(y); odo_set_theta(theta); }

void OnSetXYTheta(float x, float y, float theta) { odo_set_x(x); odo_set_y(y); odo_set_theta(theta); }
