### RR Interlock - Bill Lupoli's New Haven

<img width=400 align=right src=https://i.imgur.com/Qs8UcEP.jpg>

Arduino interlock route controller,
aligns multiple turnouts through interlock
by pressing buttons at either end of route.

Controller uses hardware shown at right.
~12V input top left to ~6V down converter to Arduino UNO board bottom left.
Three custom Tortoise Driver and I/O PCBs
using MCP23017 I2C I/O expander
to control up to 8 tortoise switch machines using LM324 op-amps and
eight GPIOs.

<img width=100% src=westLupoli.png>

<img width=100% src=west.png>

<!-- -----------------------------------------------  ---------------------- -->
<h4> PCB Wire Connections </h4>

<table border=1 cellspacing=0 align=right>
 <tr> <th colspan=2> PCB 3
 <tr> <th> Sw <th> But
 <tr> <td align=center>  69 <td align=center>  X1
 <tr> <td align=center>  70 <td align=center>  X2
 <tr> <td align=center>  71 <td align=center>  X3
 <tr> <td align=center>  72 <td align=center>
 <tr> <td align=center> &nbsp; <td align=center>
 <tr> <td align=center> &nbsp; <td align=center>
 <tr> <td align=center> &nbsp; <td align=center>
 <tr> <td align=center> &nbsp; <td align=center>
</table>

<table border=1 cellspacing=0 align=right>
 <tr> <th colspan=2> PCB 2
 <tr> <th> Sw <th> But
 <tr> <td align=center>  59 <td align=center>  C1
 <tr> <td align=center>  61 <td align=center>  C2
 <tr> <td align=center>  63 <td align=center>  C3
 <tr> <td align=center>  64 <td align=center>  C4
 <tr> <td align=center>  65 <td align=center>  C5
 <tr> <td align=center>  66 <td align=center>  C6
 <tr> <td align=center>  67 <td align=center>  C7
 <tr> <td align=center>  68 <td align=center>  C8
</table>

<table border=1 cellspacing=0 align=right>
 <tr> <th colspan=2> PCB 1
 <tr> <th> Sw <th> But
 <tr> <td align=center>  51 <td align=center>  A1
 <tr> <td align=center>  52 <td align=center>  A2
 <tr> <td align=center>  53 <td align=center>  A3
 <tr> <td align=center>  54 <td align=center>  A4

 <tr> <td align=center>  55 <td align=center>  B1
 <tr> <td align=center>  56 <td align=center>  B2
 <tr> <td align=center>  57 <td align=center>  B3
 <tr> <td align=center>  58 <td align=center>  B4
</table>

<a href=https://i.imgur.com/RJTQaR7.jpg target="_blank">
<img src=https://i.imgur.com/RJTQaR7.jpg height=380></a>

<!-- -----------------------------------------------  ---------------------- -->
<h4> Panel Description  </h4>

<i>westIntLck.cpp</i> contains tables describing the panel:
buttons, turnouts and routes.
This description requires a minimal understanding of programming
to make modifications.

<p>
Descriptions of both buttons and turnouts
includes identifying the corresponding
chip and port bit along with a label.

<p>
Buttons are described in <i>butIos []</i>.
<i>Ba1</i> is a numeric symbol uniquely identifying each button,
the <i>B</i> prefix identifies it as a button and
<i>a1</i> corresponds to the label on the panel.
The <i>0, 0, "A1"</i> identifies the input on
chip 0, port bit 0 (the first or least significant bit) and
a text string label, <i>A1</i>.
There are at most 8 bits on each chip,
some spare bits are available.


<blockquote><pre>
const PROGMEM ButIo_t butIos [] = {
    { Ba1, { 0, 0, "A1" }},
    ...
    { Bc6, { 1, 5, "C6" }},
    ...
    { Bc9, { 2, 0, "C9" }},
    { Bx1, { 2, 1, "X1" }},
    { Bx2, { 2, 2, "X2" }},
    ...
    { B_0, { 0, 0, ""   }},
};
</blockquote></pre>

There is an entry for each switch machine position.
<i>s02r</i> is the variable name of the entry used in the <i>routes</i> table.
The first three fields, <i>2, R, 1</i>,
include a numeric value for the switch machine,
a symbol, <i>N/R</i> identifying the position as normal/reverse and
the bit value, 0/1 for that position.
The last three fields,
<i>0, 1, "s02r"</i>, like the button entry
specify the chip, port bit and label.

<blockquote><pre>
// machine address and polarity
const PROGMEM SwMach_t s02n = {  2, N, 0, { 0, 1, "s02n" }};
const PROGMEM SwMach_t s02r = {  2, R, 1, { 0, 1, "s02r" }};

const PROGMEM SwMach_t s14n = { 14, N, 0, { 1, 5, "s14n" }};
const PROGMEM SwMach_t s14r = { 14, R, 1, { 1, 5, "s14r" }};

const PROGMEM SwMach_t s21n = { 21, N, 0, { 2, 4, "s21n" }};
const PROGMEM SwMach_t s21r = { 21, R, 1, { 2, 4, "s21r" }};
</blockquote></pre>

Routes are described in the routes table, <i>routes []</i>.
Each entry specifies a pair a buttons and
one or more switch machine position references (i.e. pointers).

<blockquote><pre>
const PROGMEM Route_t routes [] = {
    { Ba1, Bc1, { &s21r, &s19n, &s15r, &s14n, &s06n }},
    { Ba1, Bc2, { &s21r, &s19n, &s15n, &s10n, &s06n }},
    ...
    { Ba4, Bc4, { &s20n, &s16n, &s17n, &s11n, &s12n, &s07n, &s02r, &s01n }},
    ...
}
</blockquote></pre>

Some routes are ambiguous,
a pair of buttons can select more than one route.
<blockquote><pre>
    { Ba4, Bc3, { &s20n, &s16n, &s17n, &s11n, &s12n, &s07n, &s02r, &s01r }},
    { Ba4, Bc3, { &s20r, &s16n, &s17n, &s11n, &s12n, &s07n, &s02r, &s01r }},
</blockquote>

The code repeatedly
* monitors the button input ports
* detects that two or more buttons have been pressed
* uses <i>butIos []</i> to match the chip and port bit to button IDs
* searches the routes table for an entry with that pair of buttons, and
* sets the corresponding bits to position the switch
for each machine in the route.

<!-- -----------------------------------------------  ---------------------- -->
<hr>
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
<b>butScan (void)</b>
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

