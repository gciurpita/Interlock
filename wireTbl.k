
awk '

# --------------------------------------------------------------------
## { Bx2, { 2, 2, "X2" }},
/butIos/ {
    while (getline)  {
        if (! NF)
            continue
        if (/B_0/)
            break
      # print
        gsub(",", "")
        but [int($4), int($5)] = $2
    }
}

# --------------------------------------------------------------------
## const PROGMEM SwMach_t s21r = { 21, R, 1, { 2, 4, "s21r" }};
/const .* SwMach_t/ {
  # print
    sw [int($11), int($12)] = "sw" int($7)
}

# --------------------------------------------------------------------
function table (chip)  {
    printf "<table border=1 cellspacing=0 width=300>\n"
    for (bit = 0; bit < 8; bit++)  {
        printf " <tr> <th> %2d", bit
        printf " <td> %5s", sw  [chip, bit]
        printf " <td> %5s", but [chip, bit]
        printf "\n"
    }
    printf "</table>\n\n"
}

# --------------------------------------------------------------------
function chart ()  {
    printf "<table border=1 cellspacing=0 width=600>\n"
    printf " <tr> <th colspan=7> %s\n", "New Haven West Interlock"

    printf " <tr> <th> Bit"
    for (chip = 0; chip < 3; chip++)
        printf " <th colspan=2> Chip-%d", chip
    printf "\n"
        
    for (bit = 0; bit < 8; bit++)  {
        printf " <tr> <th> %2d", bit

        for (chip = 0; chip < 3; chip++)  {
            printf " <td align=center> %4s", sw  [chip, bit]
            printf " <td align=center> %3s", but [chip, bit]
        }
        printf "\n"
    }
    printf "</table>\n\n"
}

# --------------------------------------------------------------------
END {
    chart()
}' $*
