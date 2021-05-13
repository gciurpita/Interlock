// New Haven West const interlock

const char version [] = "New Haven West 191120a";

#include "Arduino.h"    // simulation

#include "Wire.h"  // I2R operations

#include "westIntlck.h"
#include "mpc23017.h"


const int LED = 13;

unsigned int dbg    = 1;
int ledMode         = 0;

// ---------------------------------------------------------
void prTxtVal (
    const char* text,
    int         val,
    int         fmt,
    bool        nl )
{
    Serial.print (text);
    Serial.print (val, fmt);
    if (nl)
        Serial.print ("\n");
}

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
    chip += chip < Chip20 ? Chip20 : 0;

    if (0 < dbg)  {
        prTxtVal   ("   i2cWrite: chip ", chip, HEX, 0);
        prTxtVal   (", port ",            port, HEX, 0);
        prTxtVal   (", val ",             val,  HEX, 1);
    }

    Wire.beginTransmission (chip);
    Wire.write (port);    
    Wire.write (val);    
    Wire.endTransmission ();
}

// ---------------------------------------------------------
byte
i2cRead (
    int     chip,
    int     port )
{
    if (8 & dbg)
        return 0xFF;

    chip += chip < Chip20 ? Chip20 : 0;

    Wire.beginTransmission (chip);
    Wire.write (port);    
    Wire.endTransmission ();

    Wire.requestFrom (chip, 1); //get 1 byte
    byte val =  Wire.read ();

    if (3 < dbg)  {
        prTxtVal   ("   i2cRead:  chip ", chip, HEX, 0);
        prTxtVal   (", port ",            port, HEX, 0);
        prTxtVal   (", val ",             val,  HEX, 1);
    }

    return val;
}

// ---------------------------------------------------------
int nChip   = 0;

void i2cCfg (void)
{
    Serial.println (" i2cCfg:");
    for (nChip = 0; nChip < 8; nChip++)  {
        i2cWrite (nChip, IODIRA, IoOut);
        if (IoOut != i2cRead (nChip, IODIRA))
            break;

        i2cWrite (nChip, IODIRB, IoInp);
        if (IoInp != i2cRead (nChip, IODIRB))
            break;

        i2cWrite (nChip, GPPUB,  0xFF);

        prTxtVal (" i2cCfg: nChip ", nChip, DEC, 1);
    }
}

// ---------------------------------------------------------
// toggle output bits every 4 sec 
int   tglTestCnt   = 0;
byte  tglTestEn    = 0;
byte  tglTestState = 0;
unsigned long  tglTestTime   = 0;
unsigned long  tglTestPeriod = 4000;

static void
tglTest (void)
{
    if (! tglTestEn)
        return;

    unsigned long msec = millis();

    if ((msec - tglTestTime) < tglTestPeriod)
        return;

    tglTestTime   = msec;
    tglTestState ^= 0xFF;

    for (int chip = 0; chip < nChip; chip++)
        i2cWrite (chip, GPIOA, tglTestState);

    prTxtVal ("tglTest: time ", tglTestTime, DEC, 0);
    prTxtVal (", cnt ", ++tglTestCnt,        DEC, 1);
}

// -----------------------------------------------------------------------------
void
routeAlign (
    int     routeIdx )
{
    static byte state [MAX_CHIP] =  {};

    const Route_t*  r = &routes [routeIdx];
    const SwMach_t* sm;

    prTxtVal (" routeAlign: route idx ", routeIdx, DEC, 1);

    for (int i = 0; (sm = pgm_read_word (& (r->list [i]))); i++)  {
        byte  _id    = pgm_read_byte (& (sm->id));
        byte  _pos   = pgm_read_byte (& (sm->pos));
        byte  _bitVal= pgm_read_byte (& (sm->bitVal));

        byte  _chip  = pgm_read_byte (& (sm->io.chip));
        byte  _bit   = pgm_read_byte (& (sm->io.bit));

        prTxtVal   ("  routeAlign: mach id ", _id, DEC, 0);
        prTxtVal   (", pos ",      _pos,    DEC, 0);
        prTxtVal   (", bitVal ",   _bitVal, DEC, 0);
        prTxtVal   (", _chip ",    _chip,   DEC, 0);
        prTxtVal   (", _bit ",     _bit,    DEC, 1);

        state [_chip] = _bitVal
                        ? state [_chip] |   1 << _bit
                        : state [_chip] & ~(1 << _bit);
    }

    for (byte chip = 0; chip < nChip; chip++)
        i2cWrite (chip, GPIOA, state [chip]);
}

// -----------------------------------------------------------------------------
// search for route matching buttons
// update bits in state []
// write state to chips

static int routeFind (
    But_t*  list,
    byte    nButs )
{
    int  res = 0;
    Serial.println (" routeFind: ");

    for (int i = 0;   ; i++)  {
        const Route_t* r = &routes [i];

        But_t _but0 = pgm_read_byte (& r->but0);
        But_t _but1 = pgm_read_byte (& r->but1);

        if (B_0 == _but0)
            break;

        if (   (_but0 == list [0] && _but1 == list [1])
            || (_but1 == list [0] && _but0 == list [1]) ) {
            routeAlign (i);
            break;
        }
    }

    return res;
}

// ---------------------------------------------------------
// search button table for matching chip/bit
static But_t
butFind (
    byte    chip,
    byte    bit )
{
    But_t   val = B_0;

    for (const ButIo_t* b = butIos;    ; b++)  {
        byte _chip = pgm_read_byte (& b->io.chip);
        byte _bit  = pgm_read_byte (& b->io.bit);
        byte _but  = pgm_read_byte (& b->but);

        if (B_0 == _but)
            break;

        if (chip == _chip && bit == _bit) {
            if (dbg)  {
                prTxtVal ("    butFind: chip ", chip, DEC, 0);
                prTxtVal (", bit ", bit, DEC, 0);
                prTxtVal (", but ", _but, DEC, 1);
            }
            val = (But_t) _but;
        }
    }

    if (val == B_0 && dbg)  {
        prTxtVal ("    butFind: chip ", chip, DEC, 0);
        prTxtVal (", bit ", bit, DEC, 0);
        prTxtVal (", unknown ", 0, DEC, 1);
    } 

    return val;
}

// ---------------------------------------------------------
// map bit change to button using butFind()
//    passing results to routeFind() or
//    checking for test modes
#define MAX_BUTS    3
static void
mapButtons (
    byte*   state,
    int     nState )
{
    But_t  list [MAX_BUTS];
    byte   nButs           = 0;

    for (byte  i = 0; i < nState; i++)  {
        if (dbg)  {
            prTxtVal ("  mapButtons: i ", i, DEC, 0);
            prTxtVal (", state ", state [i], HEX, 1);
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
        if (1 == routeFind (list, nButs))
            return;

        // check for test modes
        if (state [0] == 0xF8)  {   // 1st 3 buttons
            ledMode = tglTestEn ^= 1;
            prTxtVal ("  mapButtons: test mode - ", tglTestEn, DEC, 1);
        }
    }
}

// ---------------------------------------------------------
// read/compare each input byte to previous state
//    wait # periods, reset count if change
//    call mapButtons() if valid change
#define WAIT_CNT    3
#define SCAN_DELAY  1000

unsigned long _butLastUsec = 0;
unsigned long _butUsec;

static void butScan (void)
{
    if (4 & dbg)
        return;

    _butUsec = micros();
    if (SCAN_DELAY > (_butUsec - _butLastUsec))
        return;

    _butLastUsec = _butUsec;

    static byte state [MAX_CHIP] = {};
    static byte pend  [MAX_CHIP] = {};
    static byte cnt;

    // capture debounced inputs
    for (byte  i = 0; i < nChip; i++)  {
        byte chip = Chip20 + i;
        byte val  = i2cRead (chip, GPIOB);

        if (pend [i] != val)  {
            pend [i] = val;
            cnt      = WAIT_CNT;

            if (1 < dbg) {
                prTxtVal (" butScan: i", i, DEC, 0);
                prTxtVal (", pend", pend [i], HEX, 1);
            }
        }
    }

    if (0 < cnt)  {
        if (0 == --cnt)  {
            for (byte  i = 0; i < nChip; i++)  {
                state [i] = pend [i];

                if (0 < dbg)  {
                    prTxtVal (" butScan: chip ", i, HEX, 0);
                    prTxtVal (", state ", state [i], HEX, 1);
                }
            }

            mapButtons (state, sizeof(state));
        }
    }
}

// -----------------------------------------------------------------------------
// -----------------------------------------------------------------------------
// process commands from serial monitor
static void
pcRead (void)
{
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

        case 'a':
            routeAlign (val);
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
            prTxtVal ("read: chip ", chip, HEX, 0);
            prTxtVal (", port ",     port, HEX, 0);
            prTxtVal (", val ",    i2cRead (chip, port), HEX, 1);
            break;

        case 's':
            for (int port = 0; port <= 0x15; port++)  {
                prTxtVal (" read: chip ", chip, HEX, 0);
                prTxtVal (", port ",     port, HEX, 0);
                prTxtVal (", val ",    i2cRead (chip, port), HEX, 1);
            }
            break;

        case 'T':
            tglTestEn  ^= 1;
            ledMode = tglTestEn ? 1 : 0; 
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
            Serial.print ("  # a      align route\n");
            Serial.print ("  # c      set chip val\n");
            Serial.print ("  # p      set port(reg) val\n");
            Serial.print ("    R      reconfig chips\n");
            Serial.print ("    r      read chip, port\n");
            Serial.print ("    s      read all registers of chip\n");
            Serial.print ("    T      en/disable tglTest\n");
            Serial.print ("    t      sequentially set bits in GPIO-A/B\n");
            Serial.print ("  # w      write val to chip, port(reg)\n");
            Serial.print ("    v      version\n");
            break;

        default:
            Serial.print ("unknown: ");
            Serial.println (c);
            break;
        }
    }
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
}

// -------------------------------------
void
loop ()
{
    ledStrobe ();

    butScan ();
    pcRead ();

    tglTest ();
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
