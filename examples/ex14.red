Reducing:
A=nsh take (vdrop drop (one drop (mone drop C)))
#<1 2 3> take (<0 0 0> drop _A[])=<1 2 3> take (<0 0 0> drop ( Tk ( Dr ( Dr ( Dr ))))) stride=<1 1 1>
#  <1 2 3> take (<0 0 0> drop _A[])=<1 2 3> take (<0 0 0> drop ( Dr ( Dr ( Dr )))) stride=<1 1 1>
#    <1 2 3> take (<0 0 0> drop _A[])=<1 2 3> take (<0 1 1> drop ( Dr ( Dr ))) stride=<1 1 1>
#      <1 2 3> take (<0 0 0> drop _A[])=<1 2 3> take (<1 1 1> drop ( Dr )) stride=<1 1 1>
#        <1 2 3> take (<0 0 0> drop _A[])=<1 2 3> take (<1 1 1> drop ) stride=<1 1 1>

