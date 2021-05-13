/*
 * WIRE stubs
 */

#ifndef WIRE_H
# define WIRE_H

# define MAX_CHIP    8
# define MAX_REGS    0x20

# define RD_BUF_SIZE 10

extern unsigned int dbg;

class I2cEmul
{
  private:
    uint8_t chipId;
    uint8_t regAddr;
    int     nRd;
    int     nWr;

    uint8_t regs [MAX_CHIP] [MAX_REGS];
    uint8_t readBuf [RD_BUF_SIZE];

  public:
    I2cEmul ()                              { };

    void dumpRegs (int chip) {
        printf ("  %s: %d - ", __func__, chip);
        for (int reg = 0; reg < MAX_REGS; reg++)  {
            if (! (reg % 4))
                printf (" ");
            printf (" %02x", regs [chip][reg]);
        }
        printf ("\n");
    }

    void begin () {
        if (2 < dbg)
            printf ("  Wire.%s:\n", __func__);
    };

    void beginTransmission (uint8_t chip)   {
        if (2 < dbg)
            printf ("\n  Wire.%s(%d)\n", __func__, chip);
        chipId = chip & 7;
        nWr = 0;
    };

    void beginTransmission (int chip) {
        if (2 < dbg)
            printf ("\n  Wire.%s(%d)\n", __func__, chip);
        chipId = chip & 7;
        nWr = 0;
    };

    uint8_t endTransmission (void) {
        if (2 < dbg)
            printf ("  Wire.%s:\n", __func__);
        return 0;
    };

    uint8_t requestFrom (uint8_t chip, uint8_t nByte) {
        if (2 < dbg)
            printf ("  Wire.%s:\n", __func__);

        if (1 < dbg)  {
            printf ("  Wire.%s: %d", __func__, chip);
            for (int n = 0; n < MAX_REGS; n++)  {
                if (! (n % 4))
                    printf (" ");
                printf (" %02x", regs [chip][n]);
            }
            printf ("\n");
        }

        if (MAX_CHIP <= chip)
            return 0;

        for (int n = 0; n < nByte; n++)  {
            readBuf [n] = regs [chip][regAddr++];
#if 0
            printf ("  Wire.%s: chip %d, reg %d, %02x\n",
                __func__, chip, regAddr, readBuf [n]);
#endif
        }
        nRd = 0;
        return 0;
    };

    uint8_t read (void) {
        if (2 < dbg)
            printf ("  Wire.%s:\n", __func__);
     // dumpRegs (chipId);
        return regs [chipId][regAddr++];
    };

    size_t write (uint8_t val)  {
        if (1 < dbg)
            printf ("   Wire.%s: chip %d, reg 0x%02x, 0x%02x\n",
                __func__, chipId, regAddr, val);
        if (0 == nWr)
            regAddr = val;
        else
            regs [chipId][regAddr++] = val;

        nWr++;
        return 0;
    };

    void wrReg (
        uint8_t     chipId,
        uint8_t     regAddr,
        uint8_t     val )
    {
        regs [chipId][regAddr] = val;
        if (dbg)  {
            printf ("  Wire.%s: chip %d, reg 0x%02x, val 0x%02x\n",
                __func__, chipId, regAddr, val);
        }
     // dumpRegs (chipId);
    };
};

extern I2cEmul Wire;

#endif

