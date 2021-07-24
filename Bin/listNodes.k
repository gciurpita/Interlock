
awk '
/___/ {
  # print

    for (n = 2; n <= NF; n++)  {
        c = substr($n, 1, 1)
        if ("s" == c || "x" == c)
            printf " %s\n", $n
    }
}' $*
