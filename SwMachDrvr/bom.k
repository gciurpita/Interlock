# bom estimate

awk '
! NF || /^#/  {
    next
}

# ------------------------------------------------
/part/ {
  # print
    cost [$2] = $4 / $3
    sum += $4

    printf "%20s",   $2
    printf " %4d",   $3
    printf " %6.2f", $4
    printf " %6.2f", cost [$2]
    printf "\n"

    flag = 1
    next
}

# ------------------------------------------------
1 == flag  {
    printf "%25s %6.2f\n\n", "", sum
    sum  = 0
    flag = 0
}

# ------------------------------------------------
{
    if ("" == cost [$1])  {
        printf " Unknown part - %s,\n", $1
    }

    printf "%20s", $1
    printf " %4d", $2
    printf " %6.2f", cost [$1]
    printf " %6.2f", cost [$1] * $2
    printf "\n"

    sum += cost [$1] * $2
}

# ------------------------------------------------
function parts ()  {
    for (part in cost)
        printf " part  %4.2f  %s\n", cost [part], part
}

# ------------------------------------------------
END  {
    printf "%32s %6.2f\n", "", sum
}' << **END**

# entry desc            quan    Cost
  part  term-3pin       10      3.49
  part  term-2pin       50      10.65
  part  MPC23017        5       9.41
  part  LM324           20      2.61
  part  sckt-28pin      10      1.79
  part  sckt-14pin      20      5.48
  part  C_0.01uF        1       0
  part  R_10K           100     4.21
  part  R_1K            100     4.21
  part  R_4.7K          100     4.21
  part  PCB             10      5.64
  part  standoff        100     6.50

#       Desc     Quan
        PCB         1

        MPC23017    1
        LM324       4

        C_0.01uF    1
        R_10K       3
        R_1K        1
        R_4.7K      1

        sckt-28pin  1
        sckt-14pin  4

        term-2pin   16
        term-3pin   2

        standoff    4
**END**
