// New Haven West turnout and route descriptions

#include "westIntlck.h"

// button i/o position
const PROGMEM ButIo_t butIos [] = {
    { Ba1, { 0, 0, "A1" }},
    { Ba2, { 0, 1, "A2" }},
    { Ba3, { 0, 2, "A3" }},
    { Ba4, { 0, 3, "A4" }},

    { Bb1, { 0, 4, "B1" }},
    { Bb2, { 0, 5, "B2" }},
    { Bb3, { 0, 6, "B3" }},
    { Bb4, { 0, 7, "B4" }},

    { Bc1, { 1, 0, "C1" }},
    { Bc2, { 1, 1, "C2" }},
    { Bc3, { 1, 2, "C3" }},
    { Bc4, { 1, 3, "C4" }},
    { Bc5, { 1, 4, "C5" }},
    { Bc6, { 1, 5, "C6" }},
    { Bc7, { 1, 6, "C7" }},
    { Bc8, { 1, 7, "C8" }},

    { Bx1, { 2, 0, "X1" }},
    { Bx2, { 2, 1, "X2" }},
    { Bx3, { 2, 2, "X3" }},

    { B_0, { 0, 0, ""   }},
};

// machine address and polarity
const PROGMEM SwMach_t x51n = {  1, N, 0, { 0, 0, "x51n" }};
const PROGMEM SwMach_t x51r = {  1, R, 1, { 0, 0, "x51r" }};
const PROGMEM SwMach_t s52n = {  2, N, 0, { 0, 1, "s52n" }};
const PROGMEM SwMach_t s52r = {  2, R, 1, { 0, 1, "s52r" }};
const PROGMEM SwMach_t x53n = {  3, N, 0, { 0, 2, "x53n" }};
const PROGMEM SwMach_t x53r = {  3, R, 1, { 0, 2, "x53r" }};
const PROGMEM SwMach_t x54n = {  4, N, 0, { 0, 3, "x54n" }};
const PROGMEM SwMach_t x54r = {  4, R, 1, { 0, 3, "x54r" }};

const PROGMEM SwMach_t x55n = {  5, N, 0, { 0, 4, "x55n" }};
const PROGMEM SwMach_t x55r = {  5, R, 1, { 0, 4, "x55r" }};
const PROGMEM SwMach_t x56n = {  6, N, 0, { 0, 5, "x56n" }};
const PROGMEM SwMach_t x56r = {  6, R, 1, { 0, 5, "x56r" }};
const PROGMEM SwMach_t x57n = {  7, N, 0, { 0, 6, "x57n" }};
const PROGMEM SwMach_t x57r = {  7, R, 1, { 0, 6, "x57r" }};
const PROGMEM SwMach_t x58n = {  8, N, 0, { 0, 7, "x58n" }};
const PROGMEM SwMach_t x58r = {  8, R, 1, { 0, 7, "x58r" }};


const PROGMEM SwMach_t x59n = {  8, N, 0, { 1, 0, "x59n" }};
const PROGMEM SwMach_t x59r = {  8, R, 1, { 1, 0, "x59r" }};
const PROGMEM SwMach_t x61n = { 61, N, 0, { 1, 1, "x61n" }};
const PROGMEM SwMach_t x61r = { 61, R, 1, { 1, 1, "x61r" }};
const PROGMEM SwMach_t s63n = { 63, N, 0, { 1, 2, "s63n" }};
const PROGMEM SwMach_t s63r = { 63, R, 1, { 1, 2, "s63r" }};
const PROGMEM SwMach_t x64n = { 64, N, 0, { 1, 3, "x64n" }};
const PROGMEM SwMach_t x64r = { 64, R, 1, { 1, 3, "x64r" }};

const PROGMEM SwMach_t x65n = { 65, N, 0, { 1, 4, "x65n" }};
const PROGMEM SwMach_t x65r = { 65, R, 1, { 1, 4, "x65r" }};
const PROGMEM SwMach_t s66n = { 66, N, 0, { 1, 5, "s66n" }};
const PROGMEM SwMach_t s66r = { 66, R, 1, { 1, 5, "s66r" }};
const PROGMEM SwMach_t x67n = { 67, N, 0, { 1, 6, "x67n" }};
const PROGMEM SwMach_t x67r = { 67, R, 1, { 1, 6, "x67r" }};
const PROGMEM SwMach_t x68n = { 68, N, 0, { 1, 7, "x68n" }};
const PROGMEM SwMach_t x68r = { 68, R, 1, { 1, 7, "x68r" }};


const PROGMEM SwMach_t s69n = { 69, N, 0, { 2, 0, "s69n" }};
const PROGMEM SwMach_t s69r = { 69, R, 1, { 2, 0, "s69r" }};
const PROGMEM SwMach_t x70n = { 70, N, 0, { 2, 1, "x70n" }};
const PROGMEM SwMach_t x70r = { 70, R, 1, { 2, 1, "x70r" }};
const PROGMEM SwMach_t x71n = { 71, N, 0, { 2, 2, "x71n" }};
const PROGMEM SwMach_t x71r = { 71, R, 1, { 2, 2, "x71r" }};
const PROGMEM SwMach_t x72n = { 72, N, 0, { 2, 3, "x72n" }};
const PROGMEM SwMach_t x72r = { 72, R, 1, { 2, 3, "x72r" }};

#if 1
const SwMach_t* smListNorm [] = {
   &x51n, &s52n, &x53n, &x54n, &x55n, &x56n, &x57n, &x58n, &x59n,
   &x61n, &s63n, &x65n, &s66n, &x67n, &x68n, &s69n,
   &x70n, &x71n, &x72n, (const SwMach_t*) 0 };

const SwMach_t* smListRev [] = {
   &x51r, &s52r, &x53r, &x54r, &x55r, &x56r, &x57r, &x58r, &x59r,
   &x61r, &s63r, &x65r, &s66r, &x67r, &x68r, &s69r,
   &x70r, &x71r, &x72r, (const SwMach_t*) 0 };
#endif

// #0_ Bx1 ___ x71 ___ ___ ___ ___ ___ ___ ___ x67 Bx2 ___
//                                     s66 x67 ___ ___ ___ ___ ___ ___ x58 ___ ___ ___ ___ ___ ___ Bc1 #9_
// #3_ Ba1 ___ ___ ___ x71 x70 ___ s66 ___ ___ ___ Bb1 x64 ___ ___ x58 ___ x56 ___ ___ ___ ___ x51 Bc2 #7_
// #1_ Ba2 ___ ___ ___ ___ ___ x70 x68 ___ ___ ___ Bb2 x65 x64 ___ ___ x56 ___ Bd1 ___ x53 x51 ___ Bc3 #5_
//                                                                                         s52 ___ Bc4 #3_
// #2_ Ba3 ___ ___ ___ ___ x72 ___ ___ ___ x68 s69 Bb3 ___ ___ x65 ___ ___ x59 x53 ___ s52 ___ ___ Bc5 #1_
//                                                 s69 ___ ___ ___ x61 x59 ___ x57 ___ ___ x54 ___ Bc6 #2_
// #4_ Ba4 ___ ___ x72 ___ ___ ___ ___ ___ ___ ___ Bb4 ___ s63 x61 ___ ___ ___ ___ x57 x55 ___ x54 Bc7 #4_
//                                                 Bx3 s63                                 x55 ___ Bc8 #6_

// routes
const PROGMEM Route_t routes [] = {
    { Bx1, Bx2, { &x71r, &x70n, &s66r, &x67r }},
    { Bx1, Bb1, { &x71r, &x70n, &s66n }},
    { Bx1, Bb2, { &x71r, &x70r, &x68n }},
    { Bx1, Bb3, { &x71r, &x70r, &x68r, &s69n }},



    { Ba1, Bx2, { &x71n, &x70n, &s66r, &x67r }},
    { Ba1, Bb1, { &x71n, &x70n, &s66n }},
    { Ba1, Bb2, { &x71n, &x70r, &x68n }},
    { Ba1, Bb3, { &x71n, &x70r, &x68r, &s69n }},



    { Ba2, Bb2, { &x70n, &x68n }},
    { Ba2, Bb3, { &x70n, &x68r, &s69n }},



    { Ba3, Bb3, { &x72n, &x68n, &s69n }},



    { Ba4, Bb4, { &x72n }},



    { Bx1, Bc1, { &x71r, &x70n, &s66r, &x67n, &x58n }},
    { Bx1, Bc2, { &x71r, &x70n, &s66n, &x64n, &x58n, &x56n, &x51n }},
    { Bx1, Bc3, { &x71r, &x70r, &x68n, &x65n, &x64n, &x56n, &x53n, &x51n }},
    { Bx1, Bc4, { &x71r, &x70r, &x68r, &s69n, &x65n, &x59n, &x53n, &s52r }},

    { Bx1, Bc5, { &x71r, &x70r, &x68r, &s69n, &x65n, &x59n, &x53n, &s52n }},
    { Bx1, Bc6, { &x71r, &x70r, &x68r, &s69r, &x61n, &x59n, &x57n, &x54n }},
    { Bx1, Bc7, { &x71r, &x70r, &x68r, &s69r, &x61n, &x59n, &x57r, &x54n }},
    { Bx1, Bc8, { &x71r, &x70r, &x68r, &s69r, &x61n, &x59n, &x57r, &x55r }},


    { Ba1, Bc1, { &x71n, &x70n, &s66r, &x67n, &x58n }},
    { Ba1, Bc2, { &x71n, &x70n, &s66n, &x64n, &x58n, &x56n, &x51n }},
    { Ba1, Bc3, { &x71n, &x70r, &x68n, &x65n, &x64n, &x56n, &x53n, &x51n }},
    { Ba1, Bc4, { &x71n, &x70r, &x68r, &s69n, &x65n, &x59n, &x53n, &s52r }},

    { Ba1, Bc5, { &x71n, &x70r, &x68r, &s69n, &x65n, &x59n, &x53n, &s52n }},
    { Ba1, Bc6, { &x71n, &x70r, &x68r, &s69r, &x61n, &x59n, &x57n, &x54n }},
    { Ba1, Bc7, { &x71n, &x70r, &x68r, &s69r, &x61n, &x59n, &x57r, &x54n }},
    { Ba1, Bc8, { &x71n, &x70r, &x68r, &s69r, &x61n, &x59n, &x57r, &x55r }},



    { Ba2, Bc2, { &x70n, &x64n, &x56n, &x51r }},
    { Ba2, Bc3, { &x70n, &x68n, &x65n, &x64n, &x56n, &x51n }},
    { Ba2, Bc4, { &x70n, &x68r, &s69n, &x65n, &x59n, &x53n, &s52r }},
    { Ba2, Bc5, { &x70n, &x68r, &s69n, &x65n, &x59n, &x53n, &s52n }},
    { Ba2, Bc6, { &x70n, &x68r, &s69r, &x61n, &x59n, &x57n, &x54n }},
    { Ba2, Bc7, { &x70n, &x68r, &s69r, &x61n, &x59n, &x57r, &x54n }},
    { Ba2, Bc8, { &x70n, &x68r, &s69r, &x61n, &x59n, &x57r, &x55r }},



    { Ba3, Bc2, { &x72n, &x68n, &s69n, &x65n, &x59n, &x53r, &x51r }},
    { Ba3, Bc3, { &x72n, &x68n, &s69n, &x65n, &x59n, &x53r }},
    { Ba3, Bc4, { &x72n, &x68n, &s69n, &x65n, &x59n, &x53n, &s52r }},
    { Ba3, Bc5, { &x72n, &x68n, &s69n, &x65n, &x59n, &x53n, &s52n }},
    { Ba3, Bc6, { &x72n, &x68n, &s69r, &x61n, &x59n, &x57n, &x54n }},
    { Ba3, Bc7, { &x72n, &x68n, &s69r, &x61n, &x59n, &x57r, &x55n, &x54n }},
    { Ba3, Bc8, { &x72n, &x68n, &s69r, &x61n, &x59n, &x57r, &x55r }},



    { Ba4, Bc2, { &x72r, &x68n, &s69n, &x65n, &x59n, &x53r, &x51r }},
    { Ba4, Bc3, { &x72r, &x68n, &s69n, &x65n, &x59n, &x53r, &x51n }},
    { Ba4, Bc4, { &x72r, &x68n, &s69n, &x65n, &x59n, &x53n, &s52r }},
    { Ba4, Bc5, { &x72r, &x68n, &s69n, &x65n, &x59n, &x53n, &s52n }},
    { Ba4, Bc6, { &x72n, &s63n, &x61r, &x57n, &x54n }},
    { Ba4, Bc7, { &x72r, &x68n, &s69r, &x61n, &x59n, &x57r, &x55n }},
    { Ba4, Bc8, { &x72r, &x68n, &s69r, &x61n, &x59n, &x57r, &x55r }},



    { Bx3, Bc2, { &s63r, &x61r, &x59r, &x53r, &x51r }},
    { Bx3, Bc3, { &s63r, &x61r, &x59r, &x53r, &x51n }},
    { Bx3, Bc4, { &s63r, &x61r, &x59r, &x53n, &s52r }},
    { Bx3, Bc5, { &s63r, &x61r, &x59r, &x53n, &s52n }},
    { Bx3, Bc6, { &s63r, &x61r, &x59n, &x57n, &x54n }},
    { Bx3, Bc7, { &s63r, &x61n, &x57n, &x55n }},
    { Bx3, Bc8, { &s63r, &x61n, &x57n, &x55r }},

    { },
};

int routesSize = sizeof(routes);
