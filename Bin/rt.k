
awk '
BEGIN {
    Pi = atan2(0, -1)
    B  = L = T = 0
    R  = ""
    xSc = 10
    ySc = 20
}

# --------------------------------------------------------------------
# ------------------------------------------------
function anno (x, y, text, color)  {
    yAnno += dyAnno
    printf "anno %8.4f %8.4f  %s\n", x, y, text
}

# ------------------------------------------------
function circle (x0, y0, rad, col, a)  {
    printf "\nnext\ncolor = %s\n", col

    for (a = 0; a <= 360; a += 10)  {
        w = a * Pi / 180
        printf "  %8.4f %8.4f\n", x0+(rad * cos(w)), y0+(rad * sin(w))
    }
}

# ------------------------------------------------
function line (x0, y0, x1, y1, color)  {
    printf "next\ncolor=%s\n", color
    printf " %8.4f  %8.4f\n", x0, y0
    printf " %8.4f  %8.4f\n", x1, y1
    printf "\n"
}

# ------------------------------------------------
function pts (x0, y0, x1, y1, color)  {
    printf " %8.4f  %8.4f\n", x0, y0
    printf " %8.4f  %8.4f\n", x1, y1
    printf "\n"
}

# --------------------------------------------------------------------
function buttonAdd (row, col, sym)  {
    butSym  [B] = sym
    butRow  [B] = row
    butCol  [B] = col
    B++
}

# ------------------------------------------------
function buttonFind (sym)  {
    for (b = 0; b < B; b++)
        if (butSym [b] == sym)
            return b;
    return -1
}

# ------------------------------------------------
function buttonDraw (b, rad, col)  {
    x =  butCol [b] * xSc
    y = -butRow [b] * ySc

    circle(x, y, rad, col)
    anno(x, y, butSym [b])
}

# ------------------------------------------------
function buttonDrawXy (x, y, rad, sym, col)  {
    circle(x, y, rad, col)
    anno(x, y, sym)
}

# --------------------------------------------------------------------
function linkAdd (row, col, row2, col2)  {
    linkRow  [L, 0] = row
    linkCol  [L, 0] = col
    linkRow  [L, 1] = row2
    linkCol  [L, 1] = col2
    L++
}

# --------------------------------------------------------------------
function turnoutAdd (row, col, sym)  {
    if (dbg) printf " %2d %3d %s %s\n", row, col, c, sym

    t = turnoutFind(sym)
    if (0 > t)  {
        t = T++
        toSym  [t] = sym
        toCol  [t] = col
        toRow  [t] = row
        toType [t] = substr(sym, 1, 1)
    }
    else  {
        toCol2 [t] = col
        toRow2 [t] = row
    }
}

# ------------------------------------------------
function turnoutDisp (t)  {
    printf " [%2d]  <%2d, %2d> <%2d, %2d> %s %s\n", t, \
        toCol [t], toRow [t], toCol2 [t], toRow2 [t], toType [t], toSym [t]
}

# ------------------------------------------------
function turnoutDraw (t, pos, col,   x1, y1, x2, y2)  {
    if (dbg) printf "# turnoutDraw: [%d] %d\n", t, pos

    x1 =  toCol  [t] * xSc
    y1 = -toRow  [t] * ySc
    x2 =  x1 + xSc

    if ("B" == pos || "n" == pos)
        line(x1, y1, x2, y1, col)
    else
        line(x1, y1, x2, y1, "dark-gray")

    x2 =  toCol2 [t] * xSc
    y2 = -toRow2 [t] * ySc
    x3 =  x2 + xSc

    if ("B" == pos || "n" == pos)
        line(x2, y2, x3, y2, col)
    else
        line(x2, y2, x3, y2, "dark-gray")

    anno(x1, y1,  sym)
    anno(x2, y2,  sym)

    if (x1 < x2)
        x2 += xSc
    else
        x1 += xSc

    if ("B" == pos || "r" == pos)
        line(x1, y1, x2, y2, col)
    else
        line(x1, y1, x2, y2, "dark-gray")
}

# ------------------------------------------------
function turnoutFind (sym)  {
    for (t = 0; t < T; t++)
        if (toSym [t] == sym)
            return t;
    return -1
}

# --------------------------------------------------------------------
function dumpTxt ()  {
  # printf "dump:\n"
    for (r = 0; r < row; r++)  {
      # printf " %2d %2d", r, col
        for (c = 0; c < col; c++)  {
            sym = syms [r, c]
            s = ""
            if (0 <= turnoutFind(sym))
                s = sym
            else if (0 <= buttonFind(sym))
                s = sym

            printf " %3s", s
        }
        printf "\n"
    }
}

# ------------------------------------------------
function dump ()  {
  # printf "dump:\n"
    for (r = 0; r < row; r++)  {
        for (c = 0; c < col; c++)  {
            sym = syms [r, c]
            x   =  c * xSc
            y   = -r * ySc

            if (0 <= turnoutFind(sym))  {
                t  = turnoutFind(sym)

                printf "# to <%2d, %2d> %s -", c, r, sym
                turnoutDisp(t)
                turnoutDraw(t, "R", "dark-gray")
            }

            else if (0 <= (b = buttonFind(sym)))  {
              # buttonDraw(x, y, 3, b, "dark-gray")
                buttonDraw(b, 3, "light-gray")
            }
        }
    }
}

# --------------------------------------------------------------------
/ ___ / {
    row = 0
    do {
        if (/^$/)
            break
      # print

        col = 0
        for (i = 4; i < length($0); i += 4)  {
            sym = substr($0, i, 3)
            syms [row, col] = sym

          # printf " %2d %3d %s\n", row, col, sym

            c = substr(sym, 1, 1)
            if ("s" == c || "x" == c)  {
                turnoutAdd(row, col, sym)
                linkAdd(rowLst, colLst, row, col)
            }
            else if ("B" == c)  {   # button
                buttonAdd(row, col, sym)
                linkAdd(rowLst, colLst, row, col)
            }
            else if ("#" == c)  {   # label
                linkAdd(rowLst, colLst, row, col)
            }
            else if ("_" == c)      # link
                ;

            if ("_" != c)  {
                symLst = sym
                colLst = col
                rowLst = row
            }

            col++
        }

        row++
    } while (getline)

    if (D)
        dump()
}

# ------------------------------------------------
##     { Bx1, Bx2, { &s71r, &s70n, &s66r, &s67r }},

/Route_t routes/ {
    nRt = 0
    line(0, 0, 30*xSc, -9*ySc, "black")

    while (getline)  {
        if (! NF)
            continue
        if (nRt++ < R)
            continue

        gsub("[,&]", "", $0)

        buttonDraw(buttonFind($2), 3, "red")
        buttonDraw(buttonFind($3), 3, "red")

        for (n = 5; n <= NF-1; n++)  {
            sym = $n
            t   = turnoutFind(substr(sym, 1, 3))
            if (0 >= t)  {
                gsub("s", "x", sym)
                t = turnoutFind(substr(sym, 1, 3))
            }

            turnoutDraw(t, substr(sym, 4, 1), "red")
        }

        printf "\ntitle %s\n\n", $0
        exit

        if (/^}/)
            break
    }
}

# ------------------------------------------------
END {
}' $*
