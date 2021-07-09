### RR Interlock - Bill Lupoli's New Haven

<img width=400 align=right src=west.png>

Arduino code to route (align turnouts) through interlock
by pressing buttons on either end of route.

<img width=400 align=right src=https://i.imgur.com/Qs8UcEP.jpg>

Controller uses hardware shown at right
using MCP23017 I2C I/O expander
to control up to 8 tortoise switch machines
using LM324 op-amps and as 8 GPIOs.

<h4> Code Description </h4>

<b>setup ()</b> 
sets the serial monitor bit rate,
configures pins 5-13 as outputs,
initializes the I2C interface (i.e. <i>Wire</i>) and
calls <i>i2cCfg ()</i> to configure the
I/O expanders on each switch machine driver board.

<p>
<b>loop ()</b> invokes
<ul>
 <li> <i>ledStrobe ()</i>
 <li> <i>butScan ()</i>
 <li> <i>pcRead ()</i>
 <li> <i>tglTest ()</i>
</ul>

<p>
<b>ledStrobe (void)</b>
flashes/winks an LED at one of three different sequences,
on/off periods.

<p>
<b>ledStrobe (void)</b>
reads GPIO-B, the button input port of each chip,
checks for a change in state,
waits WAIT_CNT iterations to debounce
before recognizing that one or more buttons have been pressed and 
calling <i>mapButtons ()</i> 

<p>
<b>mapButtons ()</b>
translates the chip and port bit of the button
into a button ID (e.g. <i>Ba1</i>) using <i>butFind ()</i>,
appending the button ID to <i>list []</i> 
<i>chkRoutes ()</i> is invoked
if two or more buttons are pressed.
<i>tglTestEn</i> is toggled
if the three: <i>Ba1, Ba3</i> and <i>Ba0</i> are pressed.

<p>
<b>butFind ()</b>
searches <i>butIos []</i> for
entries matching the chip and port bit arguments.
The following <i>butIos []</i> entry
specifies a button-ID, chip, port-bit and label
<blockquote>
    { Ba1, { 0, 0, "A1" }},
</blockquote>

<p>
<b>int chkRoutes ()</b> 
searches for a route entry with matching buttons.
The following <i>routes []</i> entry
specifies two buttons followed by one or more 
pointers (e.g. <i>&amp;s21n</i> to <i>SwMach_t</i>)
<blockquote>
    { Ba1, Bc1, { &s21r, &s19n, &s15r, &s14n, &s06n }},
</blockquote>
<i>chkButtons ()</i> is used to compare the button entries from a route
to the buttons in <i>list []</i> from <i>mapButtons ()</i>.

<p>
A <i>SwMach_t</i> entry specifies
a switch machine ID, position (i.e. N/R),
bit value for that position and <i>I2cBitDef_t</i> 
which specified a chip, port bit and label
<blockquote>
const PROGMEM SwMach_t s21r = { 21, R, 1, { 2, 4, "s21r" }};
</blockquote>

<p>
<b>int chkButtons ()</b>
compares each of three possible button arguments
to each entry in <i>list []</i>.

<p>
<b>void bitUpdate ()</b> 
updates a specific port bit on a specified chip
by reading and masking the port value 
to only update the state (0, 1) of the specified bit.

<p>
<b>i2cCfg () </b> 
configures GPIO-A and B direction registers
for output and input respectively.
It enables the pull-up resistors on GPIO-B.
set GPIO-B

<p>
<b>i2cWrite (int chip, int port, byte val) </b> 
writes the 8-bit value to the specific chip and port.
After writing the direction registers
it attempts to read them back and
discontinue the loop assuming not chip exists at that bus address.

<p>
<b>i2cWrite (int chip, int port, byte val) </b> 
writes the 8-bit value to the specific chip and port.

<p>
<b>test ()</b>
sequentially sets each port bit for 500 msec
first for GPIO-A and then GPIO-B (should have no effect).

<p>
<b>tglTest (void)</b>,
when enabled,
toggles all 8-its of GPIO-A on each chip every 4 seconds.
It first tests if <i>tglTestEn</i> is set.
It then tests if the time has expired.
It then inverts <i>tglTestState</i> and
writes it to GPIO-A of each chip.

