
    R=30
    R2=`expr $R + 10`
  # R2=`expr $R + 6`

    while [ $R -lt $R2 ]; do
        xgr=rt_$R.xgr

        rt.k R=$R westIntLck.cpp | tee $xgr
        xgraph -ng $xgr &

        R=`expr $R + 1`
    done
