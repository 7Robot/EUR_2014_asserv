// Generated from version 1404111942 of semantic

#ifndef _ASSERVBOARD_H_
#define _ASSERVBOARD_H_

#define BOARD_ID 1
#define BOARD_NAME Asserv


void SendError();

void OnGetId();

void SendId(unsigned char id);

void OnTest(unsigned char B, unsigned int H, unsigned long int I, char b, int h, long int i, float f);

void SendTest(unsigned char B, unsigned int H, unsigned long int I, char b, int h, long int i, float f);

void SendUnimplemented();

void OnAusecours();

void OnBlock();

void SendDone();

void OnGetPos();

void OnGetSpeed();

void OnMotion_angle(float theta);

void OnMotion_pos(float x, float y);

void OnMotion_speed(float v, float vTheta);

void SendPos(float x, float y, float theta);

void SendSpeed(float v, float vTheta);

void OnStop();

void OnInit_arm(int);

void OnCatch_arm(int);

void OnStock_arm(int);

void OnPull_arm(int);

void OnPush_arm(int);

void Onlaunch_net(void);










int AtpDecode(int id,
        unsigned char *ucharv, int ucharc,
        unsigned int *ushortv, int ushortc,
        unsigned long int *uintv, int uintc,
        char *charv, int charc,
        int *shortv, int shortc,
        long int *intv, int intc,
        float *floatv, int floatc);

#endif // _ASSERVBOARD_H_
