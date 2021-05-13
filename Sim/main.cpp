// 

#include <stdio.h>
#include <stdlib.h>
#include <getopt.h>
#include <string.h>

#include "Arduino.h"
#include "Wire.h"

#include "mpc23017.h"
#include "westIntLck.h"
#include "westIno.h"


char        *progname;
unsigned int flag  = 0;

HardwareSerial  Serial;

I2cEmul Wire = I2cEmul ();


// --------------------------------------------------------------------
#define NTOKS   10
char*   toks [NTOKS];

int
getTokens (
    char*   s)
{
    int  n = 0;
    if (NULL == (toks [n] = strtok (s, " ")))
        return 0;

    for (n = 1;  ; n++)  {
        if (NULL == (toks [n] = strtok (NULL, " ")))
            break;
    }

    return n;
}

// ------------------------------------------------
void
serialMon  (
    const char*   s)
{
    for (uint8_t i = 0; i < strlen (s); i++)  {
        Serial.post (s[i]);
        loop();
    }
}

// ------------------------------------------------
void
application (char *filename)
{
    FILE  *fp;
    char   s[BUFSIZ];

    printf ("%s: %s\n", progname, filename);

    if ( (fp = fopen (filename, "rb")) == NULL)  {
        perror ("app - fopen input");
        exit (1);
    }

    setup ();

    while (fgets (s, BUFSIZ, fp) != NULL)  {
        s [strlen(s)-1] = 0;      // strip linefeed
        int nTok = getTokens (s);

        if (! strncmp (s, "#", 1) || 0 == nTok)
            continue;

        if (! strcmp (toks [0], "quit"))
            return;

        else if (! strcmp (toks [0], "a")       && 2 == nTok)  {
            int n = atoi (toks [1]);
            printf ("%s: align %d\n", __func__, n);
            routeAlign (n);
        }

        else if (! strcmp (toks [0], "loop")    && 2 == nTok)  {
            int n = atoi (toks [1]);
            while (n--)  {
                printf ("loop:\n");
                loop ();
            }
        }

        else if (! strcmp (toks [0], "wrReg") && 4 == nTok)  {
            Wire.wrReg (atoi(toks [1]), strtol(toks [2], NULL, 16),
                                        strtol(toks [3], NULL, 16) );
        }

        else
            printf ("%s: Error unknown - nTok %d, %s, %s\n",
                __func__, nTok, toks [0], s);

        printf ("\n");
    }
}

// --------------------------------------------------------------------
void help (void)  {
    printf (" Usage: %s \n", progname);
}

// --------------------------------------------------------------------
int main (int argc, char **argv)  {
    int   c;

    progname = *argv;

    while ((c = getopt(argc, argv, "D:o")) != -1)  {
        switch (c)  {
        case 'D':
            dbg = atoi (optarg);
            break;

        case 'o':
            break;

        default:
            printf ("Error: unknown option '%c'\n", optopt);
                        help();
            break;
        };
    }

    if (optind == argc)
        help();
    else
        for ( ; optind < argc; optind++)
            application (argv[optind]);

    return 0;
}
