#ifndef ROUTES_H
#define ROUTES_H

#include "Arduino.h"

#define N_CHIP   3

typedef unsigned char byte;

// i2c bit definiton
typedef struct {
    byte        chip;
    byte        bit;
    const char* desc;
} I2cBitDef_t;

// buttons
typedef enum  {
    B_0 = 0,
    Ba1 = 10, Ba2, Ba3, Ba4,
    Bb1 = 20, Bb2, Bb3, Bb4,
    Bc1 = 30, Bc2, Bc3, Bc4, Bc5, Bc6, Bc7, Bc8,
    Bx1 = 40, Bx2, Bx3,
    B_N = 100
} But_t;

typedef struct {
    But_t       but;
    I2cBitDef_t io;
} ButIo_t;

extern const PROGMEM ButIo_t butIos[];

// switch machine chip/bit address and polarity
typedef enum  { N, R } SwPos_t;

typedef struct {
    byte        id;
    SwPos_t     pos;
    byte        bitVal;
    I2cBitDef_t io;
} SwMach_t;

extern const SwMach_t*  smListNorm [];
extern const SwMach_t*  smListRev  [];

#define MAX_TO  9

typedef struct {
    But_t     but0;
    But_t     but1;
    const SwMach_t* list [MAX_TO];
} Route_t;

extern const PROGMEM Route_t routes [];

extern int routesSize;
#endif
