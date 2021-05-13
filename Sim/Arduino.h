
#ifndef ARDUINO_H
# define ARDUINO_H

# include <stdio.h>
# include <stdint.h>

# include "Serial.h"

# define PROGMEM

# define HIGH 0x1
# define LOW  0x0

# define INPUT 0x0
# define OUTPUT 0x1
# define INPUT_PULLUP 0x2

extern unsigned int dbg;

inline void pinMode (uint8_t pin, uint8_t val) {
    if (2 < dbg)
        printf ("    %s: %d 0x%02x\n", __func__, pin, val);
}
inline void digitalWrite (uint8_t pin, uint8_t val)  {
    if (2 < dbg)
        printf ("    %s: %d 0x%02x\n", __func__, pin, val);
}
inline int  digitalRead(uint8_t pin) {
    if (2 < dbg)
        printf ("    %s: %d\n", __func__, pin);
    return 0;
}

int  analogRead(uint8_t);
void analogReference(uint8_t mode);
void analogWrite(uint8_t, int);

inline unsigned long millis(void)   {
    if (2 < dbg)
        printf ("    %s:\n", __func__);
    return 0;
}

unsigned long micros(void);

inline void delay(unsigned long) {
    if (2 < dbg)
        printf ("    %s:\n", __func__);
}
void delayMicroseconds(unsigned int us);

unsigned long pulseIn(uint8_t pin, uint8_t state, unsigned long timeout);
unsigned long pulseInLong(uint8_t pin, uint8_t state, unsigned long timeout);

void shiftOut(uint8_t dataPin, uint8_t clockPin, uint8_t bitOrder, uint8_t val);
uint8_t shiftIn(uint8_t dataPin, uint8_t clockPin, uint8_t bitOrder);

void attachInterrupt(uint8_t, void (*)(void), int mode);
void detachInterrupt(uint8_t);

void setup(void);
void loop(void);

# define   pgm_read_byte    *
# define   pgm_read_word    *

#endif
