#ifndef WEST_INO_H
# define WEST_INO_H

void i2cWrite (int chip, int port, byte val);
byte i2cRead  (int chip, int port);


void routeAlign (int     routeIdx);

#endif
