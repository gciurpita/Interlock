// Serial emulation

#ifndef SERIAL_H
# define SERIAL_H

# include <stdio.h>

enum { DEC, HEX };

class HardwareSerial
{
  private:
    char    c;

  public:
    HardwareSerial (void)   { c = 0; };

    bool available (void)   { return c != 0; }

    void begin (int)        {};

    char read (void)
    {
        char  ch = c;
        c  = 0;
        return ch;
    }

    void post (char ch)  { c = ch; }

    void print   (const char* s)  { printf ("%s", s); }
    void print   (int val, int mode = DEC)
    {
        switch (mode)  {
            case HEX:
                printf ("%X", val);
                break;

            case DEC:
            default:
                printf ("%d", val);
                break;
        }
    }

    void println (const char* s)  { printf ("%s\n", s); }
    void println (int val, int mode = DEC)
    {
        switch (mode)  {
            case HEX:
                printf ("%X\n", val);
                break;

            case DEC:
            default:
                printf ("%d\n", val);
                break;
        }
    }
};

extern HardwareSerial Serial;

#endif
