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

// You should redefine this function
__attribute__((weak)) void OnGetPos(unsigned char id) { SendUnimplemented(); }

// You should redefine this function
__attribute__((weak)) void OnOff() { SendUnimplemented(); }

// You should redefine this function
__attribute__((weak)) void OnOn() { SendUnimplemented(); }

void SendPos(unsigned char id, unsigned char distance, unsigned char angle) {
    char bytes[] = {
        129,
        11,
        1,
        id,
        1,
        distance,
        1,
        angle,
        128
    };
    SendBytes(bytes, 9);
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
    if (id == 10) {
        OnGetPos(ucharv[0]);
        return 1;
    }
    if (id == 2) {
        OnOff();
        return 1;
    }
    if (id == 1) {
        OnOn();
        return 1;
    }
    return 0;
}

