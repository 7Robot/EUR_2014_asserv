// Generated from version 1404111942 of semantic

#ifndef _ASSERV_H_
#define _ASSERV_H_

#define BOARD_ID 1
#define BOARD_NAME Asserv


void SendError();

void OnGetId();

void SendId(unsigned char id);

void OnTest(unsigned char B, unsigned int H, unsigned long int I, char b, int h, long int i, float f);

void SendTest(unsigned char B, unsigned int H, unsigned long int I, char b, int h, long int i, float f);

void SendUnimplemented();

void SendMotionOrders(float deltaX, float deltaV, float deltaA, float alphaX, float alphaV, float alphaA);

void SendOrders(float deltaOrder, float alphaOrder, int leftOrder, int rightOrder, int effectiveLeftOrder, int effectiveRightOrder);

void SendPIDErr(float deltaErr, float deltaDeriv, float deltaInte, float alphaErr, float alphaDeriv, float alphaInte);

void SendX(float x);

void SendY(float y);

void OnAusecours();

void OnBlock();

void OnDist(float dist, float vMax, float aMax);

void OnDistFree(float dist);

void OnDistRot(float dist, float rot, float vDistMax, float aDistMax, float vRotMax, float aRotMax);

void SendDone();

void OnGetMotionOrders();

void OnGetOrders();

void OnGetPIDErr();

void OnGetPos();

void OnGetTheta();

void OnGetX();

void OnGetY();

void SendMode(int delta, int alpha);

void OnOdoBroadcastOff();

void OnOdoBroadcastOn();

void OnOdoBroadcastToggle();

void OnOdoDelay(unsigned long int delay);

void OnOmega(float omega, float aMax, float dMax);

void OnOmegaFree(float omega);

void SendPos(float x, float y, float theta);

void OnReachTheta(float theta, float vMax, float aMax);

void OnReachX(float x, float vMax, float aMax);

void OnReachY(float y, float vMax, float aMax);

void OnRot(float rot, float vMax, float aMax);

void OnRotFree(float rot);

void OnSetEpsilons(float dist, float speed, float theta, float omega);

void OnSetSpacing(float spacing);

void OnSetTheta(float theta);

void OnSetTicByMeter(unsigned long int tic_by_meter);

void OnSetX(float x);

void OnSetXTheta(float x, float theta);

void OnSetXY(float x, float y);

void OnSetXYTheta(float x, float y, float theta);

void OnSetY(float y);

void OnSetYTheta(float y, float theta);

void OnSpeed(float speed, float aMax, float dMax);

void OnSpeedFree(float speed);

void OnSpeedOmega(float speed, float omega, float aDistMax, float dDistMax, float aRotMax, float dRotMax);

void SendStep(float period, long int ticsG, long int ticsD, long int consignG, long int consignD);

void OnStop();

void SendTheta(float theta);


int AtpDecode(int id,
        unsigned char *ucharv, int ucharc,
        unsigned int *ushortv, int ushortc,
        unsigned long int *uintv, int uintc,
        char *charv, int charc,
        int *shortv, int shortc,
        long int *intv, int intc,
        float *floatv, int floatc);

#endif // _ASSERV_H_
