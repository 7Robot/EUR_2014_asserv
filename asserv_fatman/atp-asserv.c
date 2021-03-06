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
__attribute__((weak)) void OnAskSick(unsigned char id) { SendUnimplemented(); }

// You should redefine this function
__attribute__((weak)) void OnAusecours() { SendUnimplemented(); }

// You should redefine this function
__attribute__((weak)) void OnBlock() { SendUnimplemented(); }

void SendBlocked() {
    char bytes[] = {
        129,
        20,
        128
    };
    SendBytes(bytes, 3);
}

// You should redefine this function
__attribute__((weak)) void OnCatch_arm(unsigned int choix) { SendUnimplemented(); }

void SendCaught(unsigned char success) {
    char bytes[] = {
        129,
        52,
        1,
        success,
        128
    };
    SendBytes(bytes, 5);
}

// You should redefine this function
__attribute__((weak)) void OnConvoyer() { SendUnimplemented(); }

void SendDone() {
    char bytes[] = {
        129,
        3,
        128
    };
    SendBytes(bytes, 3);
}

void SendFreepath(unsigned char id) {
    char bytes[] = {
        129,
        92,
        1,
        id,
        128
    };
    SendBytes(bytes, 5);
}

// You should redefine this function
__attribute__((weak)) void OnGetPos() { SendUnimplemented(); }

// You should redefine this function
__attribute__((weak)) void OnGetSpeed() { SendUnimplemented(); }

// You should redefine this function
__attribute__((weak)) void OnInit_arm(unsigned int choix) { SendUnimplemented(); }

void SendLaid() {
    char bytes[] = {
        129,
        56,
        128
    };
    SendBytes(bytes, 3);
}

// You should redefine this function
__attribute__((weak)) void OnLaunch_net() { SendUnimplemented(); }

// You should redefine this function
__attribute__((weak)) void OnMotion_angle(float theta) { SendUnimplemented(); }

// You should redefine this function
__attribute__((weak)) void OnMotion_pos(float x, float y) { SendUnimplemented(); }

// You should redefine this function
__attribute__((weak)) void OnMotion_push(float x, float y, float d) { SendUnimplemented(); }

// You should redefine this function
__attribute__((weak)) void OnMotion_sequence(float x1, float y1, float x2, float y2) { SendUnimplemented(); }

// You should redefine this function
__attribute__((weak)) void OnMotion_speed(float v, float vTheta) { SendUnimplemented(); }

void SendPos(float x, float y, float theta) {
    char bytes[] = {
        129,
        32,
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
__attribute__((weak)) void OnPoulet() { SendUnimplemented(); }

// You should redefine this function
__attribute__((weak)) void OnPull_arm(unsigned int choix) { SendUnimplemented(); }

// You should redefine this function
__attribute__((weak)) void OnPush_arm(unsigned int choix) { SendUnimplemented(); }

// You should redefine this function
__attribute__((weak)) void OnRaise_arm(unsigned int choix) { SendUnimplemented(); }

// You should redefine this function
__attribute__((weak)) void OnSalut(unsigned int choix) { SendUnimplemented(); }

// You should redefine this function
__attribute__((weak)) void OnSetPos(float x, float y, float theta) { SendUnimplemented(); }

void SendSick(unsigned char id) {
    char bytes[] = {
        129,
        91,
        1,
        id,
        128
    };
    SendBytes(bytes, 5);
}

void SendSickState(unsigned char id, unsigned int state) {
    char bytes[] = {
        129,
        95,
        1,
        id,
        2,
        ((char*)&state)[0],
        ((char*)&state)[1],
        128
    };
    SendBytes(bytes, 8);
}

// You should redefine this function
__attribute__((weak)) void OnSickThreshold(unsigned char id, unsigned int threshold) { SendUnimplemented(); }

// You should redefine this function
__attribute__((weak)) void OnSlight_convoyer() { SendUnimplemented(); }

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

void SendStart(unsigned int color) {
    char bytes[] = {
        129,
        49,
        2,
        ((char*)&color)[0],
        ((char*)&color)[1],
        128
    };
    SendBytes(bytes, 6);
}

// You should redefine this function
__attribute__((weak)) void OnStock_arm(unsigned int choix) { SendUnimplemented(); }

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
    if (id == 94) {
        OnAskSick(ucharv[0]);
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
    if (id == 51) {
        OnCatch_arm(ushortv[0]);
        return 1;
    }
    if (id == 61) {
        OnConvoyer();
        return 1;
    }
    if (id == 31) {
        OnGetPos();
        return 1;
    }
    if (id == 40) {
        OnGetSpeed();
        return 1;
    }
    if (id == 50) {
        OnInit_arm(ushortv[0]);
        return 1;
    }
    if (id == 60) {
        OnLaunch_net();
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
    if (id == 14) {
        OnMotion_push(floatv[0], floatv[1], floatv[2]);
        return 1;
    }
    if (id == 13) {
        OnMotion_sequence(floatv[0], floatv[1], floatv[2], floatv[3]);
        return 1;
    }
    if (id == 11) {
        OnMotion_speed(floatv[0], floatv[1]);
        return 1;
    }
    if (id == 63) {
        OnPoulet();
        return 1;
    }
    if (id == 54) {
        OnPull_arm(ushortv[0]);
        return 1;
    }
    if (id == 55) {
        OnPush_arm(ushortv[0]);
        return 1;
    }
    if (id == 57) {
        OnRaise_arm(ushortv[0]);
        return 1;
    }
    if (id == 58) {
        OnSalut(ushortv[0]);
        return 1;
    }
    if (id == 30) {
        OnSetPos(floatv[0], floatv[1], floatv[2]);
        return 1;
    }
    if (id == 93) {
        OnSickThreshold(ucharv[0], ushortv[0]);
        return 1;
    }
    if (id == 62) {
        OnSlight_convoyer();
        return 1;
    }
    if (id == 53) {
        OnStock_arm(ushortv[0]);
        return 1;
    }
    if (id == 1) {
        OnStop();
        return 1;
    }
    return 0;
}

