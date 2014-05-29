#include <xc.h>
#include "extern_globals.h"
#include "atp.h"
#include "atp-asserv.h"
#include "lib_asserv/lib_asserv.h"
#include "actions_ax12.h"


void OnStop(){motion_free();}
void OnAusecours(){OnStop();}
void OnBlock(){
    Speed speed = {0,0};
    motion_speed(speed);
}

void OnSetPos(float x, float y, float theta){
    Position pos = {x,y,theta};
    set_position(pos);
}
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
void OnMotion_sequence(float x1, float y1, float x2, float y2){
    Position pos1 = {x1,y1,0};
    Position pos2 = {x2,y2,0};
    motion_sequence(pos1,pos2);
}
void OnMotion_push(float x, float y, float d){
    Position pos = {x,y,0};
    motion_push(pos,d);
}

void OnInit_arm(unsigned int choix)
{
    actionBras |= BOUGIE_init_arm ;
    numBras=choix;
    IFS2bits.SPI2IF = 1;
}

void OnCatch_arm(unsigned int choix)
{
    actionBras |= BOUGIE_catch_arm ;
    numBras=choix;
    IFS2bits.SPI2IF = 1;
}


void OnStock_arm(unsigned int choix)
{
    actionBras |= BOUGIE_stock_arm ;
    numBras=choix;
    IFS2bits.SPI2IF = 1;
}

void OnPull_arm(unsigned int choix)
{
    actionBras |= BOUGIE_pull_arm;
    numBras=choix;
    IFS2bits.SPI2IF = 1;
}

void OnPush_arm(unsigned int choix)
{
    actionBras |= BOUGIE_push_arm;
    numBras=choix;
    IFS2bits.SPI2IF = 1;
}

void OnLaunch_net()
{
    actionBras |= BOUGIE_launch_net;
    IFS2bits.SPI2IF = 1;
}


void OnConvoyer()
{
    actionBras |= BOUGIE_convoyer;
    IFS2bits.SPI2IF = 1;
}

void OnSlight_convoyer()
{
    actionBras |= BOUGIE_slight_convoyer;
    IFS2bits.SPI2IF = 1;
}

void OnPoulet()
{
    actionBras |= BOUGIE_poulet;
    IFS2bits.SPI2IF = 1;
}
