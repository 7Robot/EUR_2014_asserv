// Generated from version 1404111942 of semantic

#include "atp.h"


void SendError() {
    char bytes[] = {
        129,
        253,
        128
    };
    SendBytes(bytes, 3);
}

// You should redefine this function
__attribute__((weak)) void OnGetId() { SendBoardId(); }

void SendId(unsigned char id) {
    char bytes[] = {
        129,
        255,
        1,
        id,
        128
    };
    SendBytes(bytes, 5);
}

// You should redefine this function
__attribute__((weak)) void OnTest(unsigned char B, unsigned int H, unsigned long int I, char b, int h, long int i, float f) { SendTest(B, H, I, b, h, i, f); }

void SendTest(unsigned char B, unsigned int H, unsigned long int I, char b, int h, long int i, float f) {
    char bytes[] = {
        129,
        252,
        1,
        B,
        2,
        ((char*)&H)[0],
        ((char*)&H)[1],
        4,
        ((char*)&I)[0],
        ((char*)&I)[1],
        ((char*)&I)[2],
        ((char*)&I)[3],
        17,
        b,
        18,
        ((char*)&h)[0],
        ((char*)&h)[1],
        20,
        ((char*)&i)[0],
        ((char*)&i)[1],
        ((char*)&i)[2],
        ((char*)&i)[3],
        36,
        ((char*)&f)[0],
        ((char*)&f)[1],
        ((char*)&f)[2],
        ((char*)&f)[3],
        128
    };
    SendBytes(bytes, 28);
}

void SendUnimplemented() {
    char bytes[] = {
        129,
        251,
        128
    };
    SendBytes(bytes, 3);
}

void SendMotionOrders(float deltaX, float deltaV, float deltaA, float alphaX, float alphaV, float alphaA) {
    char bytes[] = {
        129,
        29,
        36,
        ((char*)&deltaX)[0],
        ((char*)&deltaX)[1],
        ((char*)&deltaX)[2],
        ((char*)&deltaX)[3],
        36,
        ((char*)&deltaV)[0],
        ((char*)&deltaV)[1],
        ((char*)&deltaV)[2],
        ((char*)&deltaV)[3],
        36,
        ((char*)&deltaA)[0],
        ((char*)&deltaA)[1],
        ((char*)&deltaA)[2],
        ((char*)&deltaA)[3],
        36,
        ((char*)&alphaX)[0],
        ((char*)&alphaX)[1],
        ((char*)&alphaX)[2],
        ((char*)&alphaX)[3],
        36,
        ((char*)&alphaV)[0],
        ((char*)&alphaV)[1],
        ((char*)&alphaV)[2],
        ((char*)&alphaV)[3],
        36,
        ((char*)&alphaA)[0],
        ((char*)&alphaA)[1],
        ((char*)&alphaA)[2],
        ((char*)&alphaA)[3],
        128
    };
    SendBytes(bytes, 33);
}

void SendOrders(float deltaOrder, float alphaOrder, int leftOrder, int rightOrder, int effectiveLeftOrder, int effectiveRightOrder) {
    char bytes[] = {
        129,
        8,
        36,
        ((char*)&deltaOrder)[0],
        ((char*)&deltaOrder)[1],
        ((char*)&deltaOrder)[2],
        ((char*)&deltaOrder)[3],
        36,
        ((char*)&alphaOrder)[0],
        ((char*)&alphaOrder)[1],
        ((char*)&alphaOrder)[2],
        ((char*)&alphaOrder)[3],
        18,
        ((char*)&leftOrder)[0],
        ((char*)&leftOrder)[1],
        18,
        ((char*)&rightOrder)[0],
        ((char*)&rightOrder)[1],
        18,
        ((char*)&effectiveLeftOrder)[0],
        ((char*)&effectiveLeftOrder)[1],
        18,
        ((char*)&effectiveRightOrder)[0],
        ((char*)&effectiveRightOrder)[1],
        128
    };
    SendBytes(bytes, 25);
}

void SendPIDErr(float deltaErr, float deltaDeriv, float deltaInte, float alphaErr, float alphaDeriv, float alphaInte) {
    char bytes[] = {
        129,
        6,
        36,
        ((char*)&deltaErr)[0],
        ((char*)&deltaErr)[1],
        ((char*)&deltaErr)[2],
        ((char*)&deltaErr)[3],
        36,
        ((char*)&deltaDeriv)[0],
        ((char*)&deltaDeriv)[1],
        ((char*)&deltaDeriv)[2],
        ((char*)&deltaDeriv)[3],
        36,
        ((char*)&deltaInte)[0],
        ((char*)&deltaInte)[1],
        ((char*)&deltaInte)[2],
        ((char*)&deltaInte)[3],
        36,
        ((char*)&alphaErr)[0],
        ((char*)&alphaErr)[1],
        ((char*)&alphaErr)[2],
        ((char*)&alphaErr)[3],
        36,
        ((char*)&alphaDeriv)[0],
        ((char*)&alphaDeriv)[1],
        ((char*)&alphaDeriv)[2],
        ((char*)&alphaDeriv)[3],
        36,
        ((char*)&alphaInte)[0],
        ((char*)&alphaInte)[1],
        ((char*)&alphaInte)[2],
        ((char*)&alphaInte)[3],
        128
    };
    SendBytes(bytes, 33);
}

void SendX(float x) {
    char bytes[] = {
        129,
        32,
        36,
        ((char*)&x)[0],
        ((char*)&x)[1],
        ((char*)&x)[2],
        ((char*)&x)[3],
        128
    };
    SendBytes(bytes, 8);
}

void SendY(float y) {
    char bytes[] = {
        129,
        35,
        36,
        ((char*)&y)[0],
        ((char*)&y)[1],
        ((char*)&y)[2],
        ((char*)&y)[3],
        128
    };
    SendBytes(bytes, 8);
}

// You should redefine this function
__attribute__((weak)) void OnAusecours() { SendUnimplemented(); }

// You should redefine this function
__attribute__((weak)) void OnBlock() { SendUnimplemented(); }

// You should redefine this function
__attribute__((weak)) void OnDist(float dist, float vMax, float aMax) { SendUnimplemented(); }

// You should redefine this function
__attribute__((weak)) void OnDistFree(float dist) { SendUnimplemented(); }

// You should redefine this function
__attribute__((weak)) void OnDistRot(float dist, float rot, float vDistMax, float aDistMax, float vRotMax, float aRotMax) { SendUnimplemented(); }

void SendDone() {
    char bytes[] = {
        129,
        3,
        128
    };
    SendBytes(bytes, 3);
}

void SendDoneLaunch() {
    char bytes[] = {
        129,
        72,
        128
    };
    SendBytes(bytes, 3);
}

void SendFreepath(unsigned char id) {
    char bytes[] = {
        129,
        62,
        1,
        id,
        128
    };
    SendBytes(bytes, 5);
}

// You should redefine this function
__attribute__((weak)) void OnGetMotionOrders() { SendUnimplemented(); }

// You should redefine this function
__attribute__((weak)) void OnGetOrders() { SendUnimplemented(); }

// You should redefine this function
__attribute__((weak)) void OnGetPIDErr() { SendUnimplemented(); }

// You should redefine this function
__attribute__((weak)) void OnGetPos() { SendUnimplemented(); }

// You should redefine this function
__attribute__((weak)) void OnGetTheta() { SendUnimplemented(); }

// You should redefine this function
__attribute__((weak)) void OnGetX() { SendUnimplemented(); }

// You should redefine this function
__attribute__((weak)) void OnGetY() { SendUnimplemented(); }

// You should redefine this function
__attribute__((weak)) void OnLaunchBalls(unsigned int amount_left) { SendUnimplemented(); }

void SendMode(int delta, int alpha) {
    char bytes[] = {
        129,
        4,
        18,
        ((char*)&delta)[0],
        ((char*)&delta)[1],
        18,
        ((char*)&alpha)[0],
        ((char*)&alpha)[1],
        128
    };
    SendBytes(bytes, 9);
}

// You should redefine this function
__attribute__((weak)) void OnOdoBroadcastOff() { SendUnimplemented(); }

// You should redefine this function
__attribute__((weak)) void OnOdoBroadcastOn() { SendUnimplemented(); }

// You should redefine this function
__attribute__((weak)) void OnOdoBroadcastToggle() { SendUnimplemented(); }

// You should redefine this function
__attribute__((weak)) void OnOdoDelay(unsigned long int delay) { SendUnimplemented(); }

// You should redefine this function
__attribute__((weak)) void OnOmega(float omega, float aMax, float dMax) { SendUnimplemented(); }

// You should redefine this function
__attribute__((weak)) void OnOmegaFree(float omega) { SendUnimplemented(); }

void SendPos(float x, float y, float theta) {
    char bytes[] = {
        129,
        40,
        36,
        ((char*)&x)[0],
        ((char*)&x)[1],
        ((char*)&x)[2],
        ((char*)&x)[3],
        36,
        ((char*)&y)[0],
        ((char*)&y)[1],
        ((char*)&y)[2],
        ((char*)&y)[3],
        36,
        ((char*)&theta)[0],
        ((char*)&theta)[1],
        ((char*)&theta)[2],
        ((char*)&theta)[3],
        128
    };
    SendBytes(bytes, 18);
}

// You should redefine this function
__attribute__((weak)) void OnReachTheta(float theta, float vMax, float aMax) { SendUnimplemented(); }

// You should redefine this function
__attribute__((weak)) void OnReachX(float x, float vMax, float aMax) { SendUnimplemented(); }

// You should redefine this function
__attribute__((weak)) void OnReachY(float y, float vMax, float aMax) { SendUnimplemented(); }

// You should redefine this function
__attribute__((weak)) void OnRot(float rot, float vMax, float aMax) { SendUnimplemented(); }

// You should redefine this function
__attribute__((weak)) void OnRotFree(float rot) { SendUnimplemented(); }

// You should redefine this function
__attribute__((weak)) void OnSetBalls(unsigned int amount) { SendUnimplemented(); }

// You should redefine this function
__attribute__((weak)) void OnSetEpsilons(float dist, float speed, float theta, float omega) { SendUnimplemented(); }

// You should redefine this function
__attribute__((weak)) void OnSetSpacing(float spacing) { SendUnimplemented(); }

// You should redefine this function
__attribute__((weak)) void OnSetTheta(float theta) { SendUnimplemented(); }

// You should redefine this function
__attribute__((weak)) void OnSetTicByMeter(unsigned long int tic_by_meter) { SendUnimplemented(); }

// You should redefine this function
__attribute__((weak)) void OnSetX(float x) { SendUnimplemented(); }

// You should redefine this function
__attribute__((weak)) void OnSetXTheta(float x, float theta) { SendUnimplemented(); }

// You should redefine this function
__attribute__((weak)) void OnSetXY(float x, float y) { SendUnimplemented(); }

// You should redefine this function
__attribute__((weak)) void OnSetXYTheta(float x, float y, float theta) { SendUnimplemented(); }

// You should redefine this function
__attribute__((weak)) void OnSetY(float y) { SendUnimplemented(); }

// You should redefine this function
__attribute__((weak)) void OnSetYTheta(float y, float theta) { SendUnimplemented(); }

void SendSick(unsigned char id) {
    char bytes[] = {
        129,
        61,
        1,
        id,
        128
    };
    SendBytes(bytes, 5);
}

// You should redefine this function
__attribute__((weak)) void OnSickThreshold(unsigned char id, unsigned int threshold) { SendUnimplemented(); }

// You should redefine this function
__attribute__((weak)) void OnSpeed(float speed, float aMax, float dMax) { SendUnimplemented(); }

// You should redefine this function
__attribute__((weak)) void OnSpeedFree(float speed) { SendUnimplemented(); }

// You should redefine this function
__attribute__((weak)) void OnSpeedOmega(float speed, float omega, float aDistMax, float dDistMax, float aRotMax, float dRotMax) { SendUnimplemented(); }

void SendStart(long int color) {
    char bytes[] = {
        129,
        51,
        20,
        ((char*)&color)[0],
        ((char*)&color)[1],
        ((char*)&color)[2],
        ((char*)&color)[3],
        128
    };
    SendBytes(bytes, 8);
}

void SendStep(float period, long int ticsG, long int ticsD, long int consignG, long int consignD) {
    char bytes[] = {
        129,
        10,
        36,
        ((char*)&period)[0],
        ((char*)&period)[1],
        ((char*)&period)[2],
        ((char*)&period)[3],
        20,
        ((char*)&ticsG)[0],
        ((char*)&ticsG)[1],
        ((char*)&ticsG)[2],
        ((char*)&ticsG)[3],
        20,
        ((char*)&ticsD)[0],
        ((char*)&ticsD)[1],
        ((char*)&ticsD)[2],
        ((char*)&ticsD)[3],
        20,
        ((char*)&consignG)[0],
        ((char*)&consignG)[1],
        ((char*)&consignG)[2],
        ((char*)&consignG)[3],
        20,
        ((char*)&consignD)[0],
        ((char*)&consignD)[1],
        ((char*)&consignD)[2],
        ((char*)&consignD)[3],
        128
    };
    SendBytes(bytes, 28);
}

// You should redefine this function
__attribute__((weak)) void OnStop() { SendUnimplemented(); }

// You should redefine this function
__attribute__((weak)) void OnStopLaunch() { SendUnimplemented(); }

void SendTheta(float theta) {
    char bytes[] = {
        129,
        38,
        36,
        ((char*)&theta)[0],
        ((char*)&theta)[1],
        ((char*)&theta)[2],
        ((char*)&theta)[3],
        128
    };
    SendBytes(bytes, 8);
}


int AtpDecode(int id,
        unsigned char *ucharv, int ucharc,
        unsigned int *ushortv, int ushortc,
        unsigned long int *uintv, int uintc,
        char *charv, int charc,
        int *shortv, int shortc,
        long int *intv, int intc,
        float *floatv, int floatc)
{
    if (id == 254) {
        OnGetId();
        return 1;
    }
    if (id == 252) {
        OnTest(ucharv[0], ushortv[0], uintv[0], charv[0], shortv[0], intv[0], floatv[0]);
        return 1;
    }
    if (id == 1) {
        OnAusecours();
        return 1;
    }
    if (id == 2) {
        OnBlock();
        return 1;
    }
    if (id == 12) {
        OnDist(floatv[0], floatv[1], floatv[2]);
        return 1;
    }
    if (id == 14) {
        OnDistFree(floatv[0]);
        return 1;
    }
    if (id == 16) {
        OnDistRot(floatv[0], floatv[1], floatv[2], floatv[3], floatv[4], floatv[5]);
        return 1;
    }
    if (id == 9) {
        OnGetMotionOrders();
        return 1;
    }
    if (id == 7) {
        OnGetOrders();
        return 1;
    }
    if (id == 5) {
        OnGetPIDErr();
        return 1;
    }
    if (id == 39) {
        OnGetPos();
        return 1;
    }
    if (id == 36) {
        OnGetTheta();
        return 1;
    }
    if (id == 30) {
        OnGetX();
        return 1;
    }
    if (id == 33) {
        OnGetY();
        return 1;
    }
    if (id == 71) {
        OnLaunchBalls(ushortv[0]);
        return 1;
    }
    if (id == 44) {
        OnOdoBroadcastOff();
        return 1;
    }
    if (id == 43) {
        OnOdoBroadcastOn();
        return 1;
    }
    if (id == 45) {
        OnOdoBroadcastToggle();
        return 1;
    }
    if (id == 46) {
        OnOdoDelay(uintv[0]);
        return 1;
    }
    if (id == 22) {
        OnOmega(floatv[0], floatv[1], floatv[2]);
        return 1;
    }
    if (id == 23) {
        OnOmegaFree(floatv[0]);
        return 1;
    }
    if (id == 19) {
        OnReachTheta(floatv[0], floatv[1], floatv[2]);
        return 1;
    }
    if (id == 17) {
        OnReachX(floatv[0], floatv[1], floatv[2]);
        return 1;
    }
    if (id == 18) {
        OnReachY(floatv[0], floatv[1], floatv[2]);
        return 1;
    }
    if (id == 13) {
        OnRot(floatv[0], floatv[1], floatv[2]);
        return 1;
    }
    if (id == 15) {
        OnRotFree(floatv[0]);
        return 1;
    }
    if (id == 74) {
        OnSetBalls(ushortv[0]);
        return 1;
    }
    if (id == 11) {
        OnSetEpsilons(floatv[0], floatv[1], floatv[2], floatv[3]);
        return 1;
    }
    if (id == 42) {
        OnSetSpacing(floatv[0]);
        return 1;
    }
    if (id == 37) {
        OnSetTheta(floatv[0]);
        return 1;
    }
    if (id == 41) {
        OnSetTicByMeter(uintv[0]);
        return 1;
    }
    if (id == 31) {
        OnSetX(floatv[0]);
        return 1;
    }
    if (id == 47) {
        OnSetXTheta(floatv[0], floatv[1]);
        return 1;
    }
    if (id == 50) {
        OnSetXY(floatv[0], floatv[1]);
        return 1;
    }
    if (id == 49) {
        OnSetXYTheta(floatv[0], floatv[1], floatv[2]);
        return 1;
    }
    if (id == 34) {
        OnSetY(floatv[0]);
        return 1;
    }
    if (id == 48) {
        OnSetYTheta(floatv[0], floatv[1]);
        return 1;
    }
    if (id == 63) {
        OnSickThreshold(ucharv[0], ushortv[0]);
        return 1;
    }
    if (id == 20) {
        OnSpeed(floatv[0], floatv[1], floatv[2]);
        return 1;
    }
    if (id == 21) {
        OnSpeedFree(floatv[0]);
        return 1;
    }
    if (id == 24) {
        OnSpeedOmega(floatv[0], floatv[1], floatv[2], floatv[3], floatv[4], floatv[5]);
        return 1;
    }
    if (id == 1) {
        OnStop();
        return 1;
    }
    if (id == 73) {
        OnStopLaunch();
        return 1;
    }
    return 0;
}

