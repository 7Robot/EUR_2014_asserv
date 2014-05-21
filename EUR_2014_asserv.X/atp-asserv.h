// Generated from version 1404111942 of semantic

#ifndef _ATP_ASSERV_H_
#define _ATP_ASSERV_H_

#define BOARD_ID 2
#define BOARD_NAME Asserv


void SendError();

void OnGetId();

void SendId(unsigned char id);

void OnTest(unsigned char B, unsigned int H, unsigned long int I, char b, int h, long int i, float f);

void SendTest(unsigned char B, unsigned int H, unsigned long int I, char b, int h, long int i, float f);

void SendUnimplemented();

void OnAusecours();

void OnBlock();

void OnCatch_arm(unsigned int arm);

void SendDone();

void OnGetPos();

void OnGetSpeed();

void OnInit_arm(unsigned int arm);

void OnLaunch_net();

void OnMotion_angle(float theta);

void OnMotion_pos(float x, float y);

void OnMotion_speed(float v, float vTheta);

void SendPos(float x, float y, float theta);

void OnPull_arm(unsigned int arm);

void OnPush_arm(unsigned int arm);

void SendSpeed(float v, float vTheta);

void OnStock_arm(unsigned int arm);

void OnStop();


int AtpDecode(int id,
        unsigned char *ucharv, int ucharc,
        unsigned int *ushortv, int ushortc,
        unsigned long int *uintv, int uintc,
        char *charv, int charc,
        int *shortv, int shortc,
        long int *intv, int intc,
        float *floatv, int floatc);

#endif // _ASSERV_H_
