#include "atp.h"
#include "atp-asserv.h"
#include "lib_asserv/lib_asserv.h"

void OnStop(){motion_free();}
void OnAusecours(){OnStop();}


void OnGetPos(){SendPos(get_position().x , get_position().y , get_position().t);}
void OnGetSpeed(){SendSpeed(get_speed().v , get_speed().vt);}

void OnMotion_angle(float theta){motion_angle(theta);}
void OnMotion_pos(float x, float y){
    Position pos = {x, y, 0};
    motion_pos(pos);
}
void OnMotion_speed(float v, float vTheta){
    Speed speed = {v,vTheta};
    motion_speed(speed);
}