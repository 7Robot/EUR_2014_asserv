// Generated from version 1404111942 of semantic

#include "atp.h"
#include "atp-asserv.h"


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

// You should redefine this function
__attribute__((weak)) void OnAusecours() { SendUnimplemented(); }

// You should redefine this function
__attribute__((weak)) void OnBlock() { SendUnimplemented(); }

void SendDone() {
    char bytes[] = {
        129,
        3,
        128
    };
    SendBytes(bytes, 3);
}

// You should redefine this function
__attribute__((weak)) void OnGetPos() { SendUnimplemented(); }

// You should redefine this function
__attribute__((weak)) void OnGetSpeed() { SendUnimplemented(); }

// You should redefine this function
__attribute__((weak)) void OnMotion_angle(float theta) { SendUnimplemented(); }

// You should redefine this function
__attribute__((weak)) void OnMotion_pos(float x, float y) { SendUnimplemented(); }

// You should redefine this function
__attribute__((weak)) void OnMotion_speed(float v, float vTheta) { SendUnimplemented(); }

void SendPos(float x, float y, float theta) {
    char bytes[] = {
        129,
        31,
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

void SendSpeed(float v, float vTheta) {
    char bytes[] = {
        129,
        41,
        36,
        ((char*)&v)[0],
        ((char*)&v)[1],
        ((char*)&v)[2],
        ((char*)&v)[3],
        36,
        ((char*)&vTheta)[0],
        ((char*)&vTheta)[1],
        ((char*)&vTheta)[2],
        ((char*)&vTheta)[3],
        128
    };
    SendBytes(bytes, 13);
}

// You should redefine this function
__attribute__((weak)) void OnStop() { SendUnimplemented(); }


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
    if (id == 30) {
        OnGetPos();
        return 1;
    }
    if (id == 40) {
        OnGetSpeed();
        return 1;
    }
    if (id == 12) {
        OnMotion_angle(floatv[0]);
        return 1;
    }
    if (id == 10) {
        OnMotion_pos(floatv[0], floatv[1]);
        return 1;
    }
    if (id == 11) {
        OnMotion_speed(floatv[0], floatv[1]);
        return 1;
    }
    if (id == 1) {
        OnStop();
        return 1;
    }
    return 0;
}

