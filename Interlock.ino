// New Haven West const interlock

const char version [] = "New Haven West 210703a";

#include <TimerOne.h>
#include "Wire.h"  // I2R operations

#include "westIntlck.h"
#include "mpc23017.h"

enum {
    Loop = 5,       // 5
    LedStr,         // 6
    PcRead,         // 7

    IoWr,           // 8
    IoRd,           // 9

    ButScan,        // 10
    TglTest,        // 11

    MapBut,         // 12
    ButFind,        // 13
    Route,          // 14
    ChkBut,         // 15
};


const int LED = 13;

int dbg     = 1;
int ledMode = 0;

// -----------------------------------------------------------------------------
//         Uno  Mega
//  SDA <- A4   20
//  SCL <- A5   21

#define MAX_CHIP    8

// I2C definitions

const int Chip20 = 0x20;
const int Chip21 = 0x21;
const int Chip22 = 0x22;
const int Chip23 = 0x23;
const int Chip24 = 0x24;
const int Chip25 = 0x25;

const int IoInp  = 0xFF;
const int IoOut  = 0x00;


byte chip    = Chip20;
byte port    = GPIOA;

// ---------------------------------------------------------
void i2cWrite (
    int     chip,
    int     port,
    byte    val )
{
    digitalWrite(IoWr, HIGH);

    chip += chip < Chip20 ? Chip20 : 0;

    if (1 < dbg)  {
        Serial.print   ("  i2cWrite: chip ");
        Serial.print   (chip, HEX);
        Serial.print   (", port ");
        Serial.print   (port, HEX);
        Serial.print   (", val ");
        Serial.println (val, HEX);
    }

    Wire.beginTransmission (chip);
    Wire.write (port);    
    Wire.write (val);    
    Wire.endTransmission ();

    digitalWrite(IoWr, LOW);
}

// ---------------------------------------------------------
byte
i2cRead (
    int     chip,
    int     port )
{
    if (8 & dbg)
        return 0xFF;

    digitalWrite(IoRd, HIGH);

    chip += chip < Chip20 ? Chip20 : 0;

    Wire.beginTransmission (chip);
    Wire.write (port);    
    Wire.endTransmission ();

    Wire.requestFrom (chip, 1); //get 1 byte
    byte val =  Wire.read ();

    if (3 < dbg)  {
        Serial.print   ("  i2cRead: chip ");
        Serial.print   (chip, HEX);
        Serial.print   (", port ");
        Serial.print   (port, HEX);
        Serial.print   (", val ");
        Serial.println (val, HEX);
    }

    digitalWrite(IoRd, LOW);
    return val;
}

// ---------------------------------------------------------
int nChip   = 0;

void i2cCfg (void)
{
    Serial.println ("i2cCfg:");
    for (nChip = 0; nChip < 8; nChip++)  {
        i2cWrite (nChip, IODIRA, IoOut);
        if (IoOut != i2cRead (nChip, IODIRA))
            break;

        i2cWrite (nChip, IODIRB, IoInp);
        if (IoInp != i2cRead (nChip, IODIRB))
            break;

        i2cWrite (nChip, GPPUB,  0xFF);

        Serial.print   ("i2cCfg: nChip ");
        Serial.println (nChip);
    }
}

// ---------------------------------------------------------
// sequentially set each port bit
void
test (
    int     chip)
{
    Serial.print (" test: Gpio-A, chip 0x");
    Serial.println (chip, HEX);

    for (byte bit = 0; bit < 8; bit++)  {
        i2cWrite (chip, GPIOA, 1 << bit);
        delay (500);
    }

    Serial.print (" test: Gpio-B, chip 0x");
    Serial.println (chip, HEX);

    for (byte bit = 0; bit < 8; bit++)  {
        i2cWrite (chip, GPIOB, 1 << bit);
        delay (500);        // msec
    }
}

// ---------------------------------------------------------
int   tglTestCnt   = 0;
byte  tglTestEn    = 0;
byte  tglTestState = 0;
unsigned long  tglTestTime   = 0;
unsigned long  tglTestPeriod = 4000;

void
tglTest (void)
{
    if (! tglTestEn)
        return;

    unsigned long msec = millis();

    if ((msec - tglTestTime) < tglTestPeriod)
        return;

    digitalWrite(TglTest, HIGH);

    tglTestTime   = msec;
    tglTestState ^= 0xFF;

    for (int chip = 0; chip < nChip; chip++)
        i2cWrite (chip, GPIOA, tglTestState);

    Serial.print ("tglTest: time ");
    Serial.print (tglTestTime);
    Serial.print (", cnt ");
    Serial.println (++tglTestCnt);

    digitalWrite(TglTest, LOW);
}

// ---------------------------------------------------------
void bitUpdate (
    byte     chip,
    byte     reg,
    byte     bit,
    byte     bitVal )
{
    byte    val = i2cRead (chip, reg);
    
    val  &= ~(1 << bit);
    val  |= bitVal << bit;

    i2cWrite (chip, reg, val);
}

// -----------------------------------------------------------------------------
int chkButtons (
    But_t*  list,
    byte    nButs,
    But_t   but0,
    But_t   but1,
    But_t   but2 )
{
    digitalWrite(ChkBut, HIGH);

    if (dbg)  {
        Serial.print  ("chkButtons: nButs ");
        Serial.println  (nButs);
    }

    int match = 0;
    for (byte n = 0; n < nButs; n++)  {
        match += but0 == list [n] ? 1 << n : 0;
        match += but1 == list [n] ? 1 << n : 0;
        match += but2 == list [n] ? 1 << n : 0;

        if (dbg)  {
            Serial.print  ("   chkButtons: n ");
            Serial.print  (n);
            Serial.print  (" list ");
            Serial.print  (list [n]);
            Serial.print  (" match ");
            Serial.println  (match);
        }
    }

    digitalWrite(ChkBut, LOW);

    return nButs && (match == ((1 << nButs) -1));
}

// -----------------------------------------------------------------------------
int chkRoutes (
    But_t*  list,
    byte    nButs )
{
    int  res = 0;
    Serial.println ("chkRoutes: ");

    digitalWrite(Route, HIGH);

    for (const Route_t* r = routes;   ; r++)  {
        But_t _but0 = pgm_read_byte (& r->but0);
        But_t _but1 = pgm_read_byte (& r->but1);

        if (B_0 == _but0)
            break;

        if (! chkButtons (list, nButs, _but0, _but1, B_0))
            continue;

        SwMach_t* sm;
        for (int i = 0; (sm = pgm_read_word (& (r->list [i]))); i++)  {
            byte  _id    = pgm_read_byte (& (sm->id));
            byte  _pos   = pgm_read_byte (& (sm->pos));
            byte  _bitVal= pgm_read_byte (& (sm->bitVal));

            byte  _chip  = pgm_read_byte (& (sm->io.chip));
            byte  _bit   = pgm_read_byte (& (sm->io.bit));

            Serial.print   ("    route   _id ");
            Serial.print   (_id);
            Serial.print   (", _pos ");
            Serial.print   (_pos);
            Serial.print   (", _bitVal ");
            Serial.print   (_bitVal);

            Serial.print   (" _chip ");
            Serial.print   (_chip);
            Serial.print   (", _bit ");
            Serial.println (_bit);

            bitUpdate (_chip, GPIOA, _bit, _bitVal);
        }

        res = 1;
    }

    digitalWrite(Route, LOW);
    return res;
}

// ---------------------------------------------------------
But_t
butFind (
    byte    chip,
    byte    bit )
{
    But_t   val = B_0;

    digitalWrite(ButFind, HIGH);

    if (dbg)  {
        Serial.print   ("  butFind: chip ");
        Serial.print   (chip);
        Serial.print   (", bit ");
        Serial.println (bit);
    }

    for (const ButIo_t* b = butIos;    ; b++)  {
        byte _chip = pgm_read_byte (& b->io.chip);
        byte _bit  = pgm_read_byte (& b->io.bit);
        byte _but  = pgm_read_byte (& b->but);

        if (B_0 == _but)
            break;

        if (1 < dbg)  {
            Serial.print   ("        ");
            Serial.print   (", _chip ");
            Serial.print   (_chip);
            Serial.print   (", _bit ");
            Serial.print   (_bit);
            Serial.print   (", _but ");
            Serial.println (_but);
        }

        if (chip == _chip && bit == _bit) {
            if (dbg)  {
                Serial.print   ("    found ");
                Serial.println (_but);
            }
            val = (But_t) _but;
        }
    }

    if (dbg)
        Serial.print ("\n");

    digitalWrite(ButFind, LOW);

    return val;
}

// ---------------------------------------------------------
// map bit changes to buttons
#define MAX_BUTS    3
void
mapButtons (
    byte*   state,
    int     nState )
{
    But_t  list [MAX_BUTS];
    byte   nButs           = 0;

    digitalWrite(MapBut, HIGH);

    for (byte  i = 0; i < nState; i++)  {
        if (dbg)  {
            Serial.print  (" mapButtons: ");
            Serial.print  (i);
            Serial.print  (" ");
            Serial.println (state [i], HEX);
        }

        byte  val = state [i];

        for (int j = 0; j < 8; j++, val >>= 1)  {
            if (! (val & 1))  {
                list [nButs++] = butFind (i, j);

                if (MAX_BUTS == nButs)
                    goto done;
            }
        }
    }

    // process button presses
done:
    if (2 <= nButs)  {
        Serial.print ("mapButtons:");
        for (int j = 0; j < nButs; j++)  {
            Serial.print (" ");
            Serial.print (list [j]);
        }
        Serial.print ("\n");

        if (1 == chkRoutes (list, nButs))
            return;

        // check for test modes
        if (chkButtons (list, nButs, Ba1, Ba3, B_0))  {
            Serial.println ("  test mode");
            if (0 == tglTestEn)  {
                tglTestEn = 1;
                ledMode   = 1;
            }
            else {
                tglTestEn = 0;
                ledMode   = 0;
            }
        }
    }
    digitalWrite(MapBut, LOW);

}

// ---------------------------------------------------------
#define WAIT_CNT    10

void butScan (void)
{
    if (4 & dbg)
        return;

    static byte state [N_CHIP] = {};
    static byte cnt   [N_CHIP] = {};
    int    change   = 0;

 // if (tglTestEn) return;

    digitalWrite(ButScan, HIGH);

    // capture debounced inputs
    for (byte  i = 0; i < N_CHIP; i++)  {
        byte chip = Chip20 + i;
        byte val  = i2cRead (chip, GPIOB);

        if (state [i] == val)
            cnt [i] = 0;
        else  {
            if (0 == cnt [i])
                cnt [i] = WAIT_CNT;
            else if (0 == --cnt [i])  {
                state [i] = val;
                change++;

                if (dbg)  {
                    Serial.print   ("   chip ");
                    Serial.print   (chip, HEX);
                    Serial.print   ("  ");
                    Serial.println (val, HEX);
                }
            }

            delay (1);      // msec
        }
    }

    // no further processing is no button input
    if (change)
        mapButtons (state, sizeof(state));

    digitalWrite(ButScan, LOW);
}
// -----------------------------------------------------------------------------
// -----------------------------------------------------------------------------
// process commands from serial monitor
void
pcRead (void)
{
    digitalWrite(PcRead, HIGH);

    static int  val = 0;

    if (Serial.available()) {
        int c = Serial.read ();

        switch (c)  {
        case '0':
        case '1':
        case '2':
        case '3':
        case '4':
        case '5':
        case '6':
        case '7':
        case '8':
        case '9':
            val = c - '0' + (10 * val);
            Serial.println (val);
            break;

        case ' ':
            val = 0;
            break;

        case 'D':
            dbg = val;
            val = 0;
            break;

        case 'c':
            chip = val;
            val  = 0;
            break;

        case 'p':
            port = val;
            val  = 0;
            break;

        case 'R':
            i2cCfg ();
            break;

        case 'r':
            Serial.print   ("read: chip ");
            Serial.print   (chip, HEX);
            Serial.print   (", port ");
            Serial.print   (port, HEX);
            Serial.print   (",  ");
            Serial.println (i2cRead (chip, port));
            break;

        case 's':
            for (int port = 0; port <= 0x15; port++)  {
                Serial.print   (" read: chip ");
                Serial.print   (chip, HEX);
                Serial.print   (", port ");
                Serial.print   (port, HEX);
                Serial.print   (",  ");
                Serial.println (i2cRead (chip, port), HEX);
            }
            break;

        case 'T':
            tglTestEn  ^= 1;
            ledMode = tglTestEn ? 1 : 0; 
            break;

        case 't':
            test (chip);
            break;

        case 'w':
            i2cWrite (chip, port, val);
            val  = 0;
            break;

        case 'v':
            Serial.print ("\nversion: ");
            Serial.println (version);
           break;

        case '?':
            Serial.print ("  # c  set chip 0-7 val\n");
            Serial.print ("  # p  set port (0-output/1-input) val\n");
            Serial.print ("    R  reconfig chips\n");
            Serial.print ("    r  read chip, port\n");
            Serial.print ("    s  read all registers of chip\n");
            Serial.print ("    T  en/disable tglTest\n");
            Serial.print ("    t  sequentially set each bit in GPIO-A/B\n");
            Serial.print ("  # w  write 8-bit val to chip/port\n");
            Serial.print ("    v  version\n");
            break;

        case '\n':      // ignore
            break;

        default:
            Serial.print ("unknown: ");
            Serial.println (c);
            break;
        }
    }
    digitalWrite(PcRead, LOW);
}

// -----------------------------------------------------------------------------
typedef struct {
    unsigned long   on;
    unsigned long   off;
} LedMode_t;

LedMode_t ledModes [] = {
    { 100, 900 },
    {  50, 200 },
    { 100, 150 },
};

unsigned long   msec = 0;
unsigned long   last = 0;

void
ledStrobe ()
{
    digitalWrite(LedStr, HIGH);
    msec = millis();
    if (HIGH == digitalRead (LED))  {
        if (ledModes [ledMode].on < (msec - last))  {
            digitalWrite(LED, LOW);
            last = msec;
        }
    }
    else  {
        if (ledModes [ledMode].off < (msec - last))  {
            digitalWrite(LED, HIGH);
            last = msec;
        }
    }
    digitalWrite(LedStr, LOW);
}

// -------------------------------------
void
loop ()
{
    digitalWrite(Loop, HIGH);
    ledStrobe ();

    butScan ();
    pcRead ();

    tglTest ();
    digitalWrite(Loop, LOW);
}

// -----------------------------------------------------------------------------
void setup()
{
    Serial.begin(9600);
    Serial.println (version);

    for (int pin = 5; pin <= 13; pin++)  {
        pinMode(pin, OUTPUT);
        digitalWrite(pin, LOW);
    }

    Wire.begin();    //start I2C bus

    i2cCfg ();
}
