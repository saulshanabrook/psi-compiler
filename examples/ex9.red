Reducing:
A=One drop (One take (Zero drop ((One take C) cat (Two drop D))))
#empty expression
#  empty expression
#    empty expression
#      empty expression
#        empty expression
#          empty expression

#        empty expression
#          empty expression

Reducing:
B=One drop ((A cat ((Two drop C) cat (One take D))) cat (One drop D))
#<3 3 4> take (<0 0 0> drop _B[])=<3 3 4> take (<0 0 0> drop ( Dr ((_A[]++(( Dr )++( Tk )))++( Dr )))) stride=<1 1 1>
#  <3 3 4> take (<0 0 0> drop _B[])=<3 3 4> take (<1 0 0> drop ((_A[]++(( Dr )++( Tk )))++( Dr ))) stride=<1 1 1>
#    <1 3 4> take (<0 0 0> drop _B[])=<1 3 4> take (<1 0 0> drop (_A[]++(( Dr )++( Tk )))) stride=<1 1 1>
#      empty expression

#      <1 3 4> take (<0 0 0> drop _B[])=<1 3 4> take (<1 0 0> drop (( Dr )++( Tk ))) stride=<1 1 1>
#        empty expression
#          empty expression

#        <1 3 4> take (<0 0 0> drop _B[])=<1 3 4> take (<0 0 0> drop ( Tk )) stride=<1 1 1>
#          <1 3 4> take (<0 0 0> drop _B[])=<1 3 4> take (<0 0 0> drop ) stride=<1 1 1>

#    <2 3 4> take (<1 0 0> drop _B[])=<2 3 4> take (<0 0 0> drop ( Dr )) stride=<1 1 1>
#      <2 3 4> take (<1 0 0> drop _B[])=<2 3 4> take (<1 0 0> drop ) stride=<1 1 1>

