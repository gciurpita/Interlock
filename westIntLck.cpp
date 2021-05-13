// New Haven West turnout and route descriptions

#include "westIntlck.h"

// button i/o position
const PROGMEM ButIo_t butIos [] = {
    { Ba1, { 0, 0, "A1" }},
    { Ba2, { 0, 1, "A2" }},
    { Ba3, { 0, 2, "A3" }},
    { Ba4, { 0, 3, "A4" }},
    { Ba5, { 0, 4, "A5" }},
    { Ba6, { 0, 5, "A6" }},

    { Bc1, { 1, 0, "C1" }},
    { Bc2, { 1, 1, "C2" }},
    { Bc3, { 1, 2, "C3" }},
    { Bc4, { 1, 3, "C4" }},
    { Bc5, { 1, 4, "C5" }},
    { Bc6, { 1, 5, "C6" }},
    { Bc7, { 1, 6, "C7" }},
    { Bc8, { 1, 7, "C8" }},
    { Bc9, { 2, 0, "C9" }},
    { Bx1, { 2, 1, "X1" }},
    { Bx2, { 2, 2, "X2" }},

    { B_0, { 0, 0, ""   }},
};

// machine address and polarity
const PROGMEM SwMach_t s01n = {  1, N, 0, { 0, 0, "s01n" }};
const PROGMEM SwMach_t s01r = {  1, R, 1, { 0, 0, "s01r" }};
const PROGMEM SwMach_t s02n = {  2, N, 0, { 0, 1, "s02n" }};
const PROGMEM SwMach_t s02r = {  2, R, 1, { 0, 1, "s02r" }};
const PROGMEM SwMach_t s03n = {  3, N, 0, { 0, 2, "s03n" }};
const PROGMEM SwMach_t s03r = {  3, R, 1, { 0, 2, "s03r" }};
const PROGMEM SwMach_t s04n = {  4, N, 0, { 0, 3, "s04n" }};
const PROGMEM SwMach_t s04r = {  4, R, 1, { 0, 3, "s04r" }};
const PROGMEM SwMach_t s05n = {  5, N, 0, { 0, 4, "s05n" }};
const PROGMEM SwMach_t s05r = {  5, R, 1, { 0, 4, "s05r" }};
const PROGMEM SwMach_t s06n = {  6, N, 0, { 0, 5, "s06n" }};
const PROGMEM SwMach_t s06r = {  6, R, 1, { 0, 5, "s06r" }};
const PROGMEM SwMach_t s07n = {  7, N, 0, { 0, 6, "s07n" }};
const PROGMEM SwMach_t s07r = {  7, R, 1, { 0, 6, "s07r" }};
const PROGMEM SwMach_t s08n = {  8, N, 0, { 0, 7, "s08n" }};
const PROGMEM SwMach_t s08r = {  8, R, 1, { 0, 7, "s08r" }};

const PROGMEM SwMach_t s09n = {  9, N, 0, { 1, 0, "s09n" }};
const PROGMEM SwMach_t s09r = {  9, R, 1, { 1, 0, "s09r" }};
const PROGMEM SwMach_t s10n = { 10, N, 0, { 1, 1, "s10n" }};
const PROGMEM SwMach_t s10r = { 10, R, 1, { 1, 1, "s10r" }};
const PROGMEM SwMach_t s11n = { 11, N, 0, { 1, 2, "s11n" }};
const PROGMEM SwMach_t s11r = { 11, R, 1, { 1, 2, "s11r" }};
const PROGMEM SwMach_t s12n = { 12, N, 0, { 1, 3, "s12n" }};
const PROGMEM SwMach_t s12r = { 12, R, 1, { 1, 3, "s12r" }};
const PROGMEM SwMach_t s13n = { 13, N, 0, { 1, 4, "s13n" }};
const PROGMEM SwMach_t s13r = { 13, R, 1, { 1, 4, "s13r" }};
const PROGMEM SwMach_t s14n = { 14, N, 0, { 1, 5, "s14n" }};
const PROGMEM SwMach_t s14r = { 14, R, 1, { 1, 5, "s14r" }};
const PROGMEM SwMach_t s15n = { 15, N, 0, { 1, 6, "s15n" }};
const PROGMEM SwMach_t s15r = { 15, R, 1, { 1, 6, "s15r" }};
const PROGMEM SwMach_t s16n = { 16, N, 0, { 1, 7, "s16n" }};
const PROGMEM SwMach_t s16r = { 16, R, 1, { 1, 7, "s16r" }};

const PROGMEM SwMach_t s17n = { 17, N, 0, { 2, 0, "s17n" }};
const PROGMEM SwMach_t s17r = { 17, R, 1, { 2, 0, "s17r" }};
const PROGMEM SwMach_t s18n = { 18, N, 0, { 2, 1, "s18n" }};
const PROGMEM SwMach_t s18r = { 18, R, 1, { 2, 1, "s18r" }};
const PROGMEM SwMach_t s19n = { 19, N, 0, { 2, 2, "s19n" }};
const PROGMEM SwMach_t s19r = { 19, R, 1, { 2, 2, "s19r" }};
const PROGMEM SwMach_t s20n = { 20, N, 0, { 2, 3, "s20n" }};
const PROGMEM SwMach_t s20r = { 20, R, 1, { 2, 3, "s20r" }};
const PROGMEM SwMach_t s21n = { 21, N, 0, { 2, 4, "s21n" }};
const PROGMEM SwMach_t s21r = { 21, R, 1, { 2, 4, "s21r" }};

#if 1
const SwMach_t* smListNorm [] = {
   &s01n, &s02n, &s03n, &s04n, &s05n, &s06n, &s07n, &s08n, &s09n,
   &s10n, &s11n, &s12n, &s13n, &s14n, &s15n, &s16n, &s17n, &s18n, &s19n,
   &s20n, &s21n, (const SwMach_t*) 0 };

const SwMach_t* smListRev [] = {
   &s01r, &s02r, &s03r, &s04r, &s05r, &s06r, &s07r, &s08r, &s09r,
   &s10r, &s11r, &s12r, &s13r, &s14r, &s15r, &s16r, &s17r, &s18r, &s19r,
   &s20r, &s21r, 0 };
#endif

//lbl A   s13
//lbl B   xB_
//lbl C   x12
//                                     s18 Bx1                 s09 Bx2
// _._ Ba1 ___ x21 ___ ___ ___ ___ s18 ___ ___ x14 ___ ___ s09 ___ ___ ___ ___ ___ ___ ___ ___ ___ Bc1 #11
//                                     s15 x14 ___ ___ ___ ___ ___ ___ x06 ___ ___ ___ ___ ___ ___ Bc2
// #3_ Ba2 ___ ___ ___ x21 x19 ___ s15 ___ ___ ___ Bb3 y10 ___ ___ x06 ___ y07 ___ ___ ___ ___ x01 Bc3 #3_
// #1_ Ba3 ___ ___ ___ ___ ___ x19 x16 ___ ___ ___ Bb4 y11 y10 ___ ___ y07 ___ Bd1 ___ x02 x01 ___ Bc4 #1_
//                                                                                         s03 ___ Bc5
// #2_ Ba4 ___ ___ ___ ___ x20 ___ ___ ___ x16 s17 Bb5 ___ ___ y11 ___ x12 ___ x02 ___ s03 ___ ___ Bc6 #2_
//                                                 s17 ___ ___ ___ B,C ___ ___ x08 ___ ___ y04 ___ Bc7
// #4_ Ba5 ___ ___ x20 ___ ___ ___ ___ ___ ___ ___ Bb7 ___ ___ A,B ___ ___ ___ ___ x08 s05 ___ y04 Bc8 #4_
//                                                 Bb8 ___ s13                             s05 ___ Bc9

// routes
const PROGMEM Route_t routes [] = {
    { Ba1, Bc1, { &s21r, &s19n, &s15r, &s14n, &s06n }},
    { Ba1, Bc2, { &s21r, &s19n, &s15n, &s10n, &s06n }},
    { Ba1, Bc3, { &s21r, &s19r, &s16n, &s11n, &s10n, &s07n, &s01n }},
    { Ba1, Bc4, { &s21r, &s19r, &s16r, &s17n, &s11n, &s02n, &s03r }},
    { Ba1, Bc5, { &s21r, &s19r, &s16r, &s17n, &s11n, &s02n, &s03n }},
    { Ba1, Bc6, { &s21r, &s19r, &s16r, &s17r, &s12n, &s08n, &s04n }},
    { Ba1, Bc7, { &s21r, &s19r, &s16r, &s17r, &s12n, &s08r, &s05n, &s04n }},
    { Ba1, Bc8, { &s21r, &s19r, &s16r, &s17r, &s12n, &s08r, &s05n, &s04n }},

    { Ba1, Bc9, { &s21r, &s19r, &s16r, &s17r, &s12n, &s08r, &s05r }},

    { Ba1, Bx1, { &s21n, &s18r }},
    { Ba1, Bx2, { &s21n, &s18n, &s09r }},

    { Ba2, Bc1, { &s21n, &s15r, &s14r, &s09n } },
    { Ba2, Bc2, { &s21n, &s19n, &s15r, &s14n, &s06n } },
    { Ba2, Bc3, { &s21n, &s19n, &s15n, &s10n, &s06n, &s07n, &s01n }},
    { Ba2, Bc4, { &s21n, &s19r, &s16n, &s11n, &s10n, &s07n, &s01n }},
    { Ba2, Bc5, { &s21n, &s19r, &s16r, &s17n, &s11n, &s12n, &s02n, &s03r }},
    { Ba2, Bc6, { &s21n, &s19r, &s16r, &s17n, &s11n, &s12n, &s02n, &s03n }},
    { Ba2, Bc7, { &s21n, &s19r, &s16r, &s17r, &s12n, &s08n, &s04n }},
    { Ba2, Bc8, { &s21n, &s19r, &s16r, &s17r, &s12n, &s08r, &s05n, &s04n }},

    { Ba2, Bc9, { &s21n, &s19r, &s16r, &s17r, &s12n, &s08r, &s05r }},

    { Ba2, Bx2, { &s21n, &s15r, &s14r, &s09r } },

    { Ba3, Bc3, { &s19n, &s16n, &s11n, &s10n, &s07n, &s02n, &s01r }},
    { Ba3, Bc4, { &s19n, &s16n, &s11n, &s10n, &s07n, &s02n, &s01n }},
    { Ba3, Bc5, { &s19n, &s16r, &s17n, &s11n, &s12n, &s02n, &s03r }},
    { Ba3, Bc6, { &s19n, &s16r, &s17n, &s11n, &s12n, &s02n, &s03n }},
    { Ba3, Bc7, { &s19n, &s16r, &s17r, &s08n, &s04n }},
    { Ba3, Bc8, { &s19n, &s16r, &s17r, &s08r, &s04n }},
    { Ba3, Bc9, { &s19n, &s16r, &s17r, &s08r, &s05r }},

    { Ba4, Bc3, { &s20n, &s16n, &s17n, &s11n, &s12n, &s07n, &s02r, &s01r }},
    { Ba4, Bc3, { &s20r, &s16n, &s17n, &s11n, &s12n, &s07n, &s02r, &s01r }},
    { Ba4, Bc4, { &s20n, &s16n, &s17n, &s11n, &s12n, &s07n, &s02r, &s01n }},
    { Ba4, Bc4, { &s20r, &s16n, &s17n, &s11n, &s12n, &s07n, &s02r, &s01n }},
    { Ba4, Bc5, { &s20n, &s16n, &s17n, &s11n, &s12n, &s07n, &s02n, &s03r }},
    { Ba4, Bc5, { &s20r, &s16n, &s17n, &s11n, &s12n, &s07n, &s02n, &s03r }},
    { Ba4, Bc6, { &s20n, &s16n, &s17n, &s11n, &s12n, &s07n, &s02n, &s03n }},
    { Ba4, Bc6, { &s20r, &s16n, &s17n, &s11n, &s12n, &s07n, &s02n, &s03n }},
    { Ba4, Bc7, { &s20n, &s16n, &s17r, &s08n, &s04n }},
    { Ba4, Bc7, { &s20r, &s16n, &s17r, &s08n, &s04n }},
    { Ba4, Bc8, { &s20n, &s13n, &s08n, &s05n, &s04n }},
    { Ba4, Bc8, { &s20n, &s16n, &s17r, &s08r, &s05n, &s04n }},
    { Ba4, Bc9, { &s20n, &s13n, &s08n, &s05r }},
    { Ba4, Bc9, { &s20n, &s16n, &s17r, &s08r, &s05r }},

    { },
};

int routesSize = sizeof(routes);
