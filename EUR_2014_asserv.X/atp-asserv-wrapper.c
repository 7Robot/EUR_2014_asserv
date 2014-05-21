#include "extern_globals.h"
#include "atp.h"
#include "atp-asserv.h"
#include "lib_asserv/lib_asserv.h"
#include "actions_ax12.h"


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

void OnInit_arm(unsigned int choix)
{
    actionBras |= BOUGIE_init_arm ;
    numBras=choix;
}

void OnCatch_arm(unsigned int choix)
{
    actionBras |= BOUGIE_catch_arm ;
    catch_arm(choix);
}


void OnStock_arm(unsigned int choix)
{
    actionBras |= BOUGIE_stock_arm ;
    stock_arm(choix);
}

void OnPull_arm(unsigned int choix)
{
    actionBras |= BOUGIE_pull_arm;
    pull_arm(choix);
}

void OnPush_arm(unsigned int choix)
{
    actionBras |= BOUGIE_push_arm;
    push_arm(choix);
}

void Onlaunch_net()
{
    actionBras |= BOUGIE_launch_net;
    launch_net();
}

void On() {

}

