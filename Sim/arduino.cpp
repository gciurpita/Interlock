
#include "Arduino.h"

unsigned long micros(void) {
    static unsigned long usec = 0;
    return usec += 500;
}
