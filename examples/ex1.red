Reducing:
Ams=RAMY + AMY
#<2 3 4> take (<0 0 0> drop _Ams[])=<2 3 4> take (<0 0 0> drop (+)) stride=<1 1 1>
#  <2 3 4> take (<0 0 0> drop _Ams[])=<2 3 4> take (<0 0 0> drop ) stride=<1 1 1>

#  <2 3 4> take (<0 0 0> drop _Ams[])+=<2 3 4> take (<0 0 0> drop ) stride=<1 1 1>

Reducing:
Amts=Y cat  omega <1.000000 1.000000> (Ams + RAMY)
#<2 3 8> take (<0 0 0> drop _Amts[])=<2 3 8> take (<0 0 0> drop 
  forall (forall_i0 in <2 3>) {
    ((forall_i0[] Psi )++(forall_i0[] Psi (_Ams[]+)))
  }) stride=<1 1 1>
#  <1 1 8> take ((<forall_i0[0] forall_i0[1]>++<0>) drop _Amts[])=<8> take (<0> drop ((forall_i0[] Psi )++(forall_i0[] Psi (_Ams[]+)))) stride=<1>
#    <1 1 4> take ((<forall_i0[0] forall_i0[1]>++<0>) drop _Amts[])=<4> take (<0> drop (forall_i0[] Psi )) stride=<1>
#      <1 1 4> take ((<forall_i0[0] forall_i0[1]>++<0>) drop _Amts[])=<1 1 4> take ((<forall_i0[0] forall_i0[1]>++<0>) drop ) stride=<1 1 1>

#    <1 1 4> take ((<forall_i0[0] forall_i0[1]>++<4>) drop _Amts[])=<4> take (<0> drop (forall_i0[] Psi (_Ams[]+))) stride=<1>
#      <1 1 4> take ((<forall_i0[0] forall_i0[1]>++<4>) drop _Amts[])=<1 1 4> take ((<forall_i0[0] forall_i0[1]>++<0>) drop (_Ams[]+)) stride=<1 1 1>
#        <1 1 4> take ((<forall_i0[0] forall_i0[1]>++<4>) drop _Amts[])=<1 1 4> take ((<forall_i0[0] forall_i0[1]>++<0>) drop _Ams[]) stride=<1 1 1>

#        <1 1 4> take ((<forall_i0[0] forall_i0[1]>++<4>) drop _Amts[])+=<1 1 4> take ((<forall_i0[0] forall_i0[1]>++<0>) drop ) stride=<1 1 1>

Reducing:
A=V psi Amts
#<8> take (<0> drop _A[])=<8> take (<0> drop ( Psi _Amts[])) stride=<1>
#  <8> take (<0> drop _A[])=<1 1 8> take (<1 1 0> drop _Amts[]) stride=<1 1 1>

Reducing:
Amts=<2.000000> take (<2.000000> drop (RAMY cat AMY))
#<2 3 4> take (<0 0 0> drop _Amts[])=<2 3 4> take (<0 0 0> drop (<2 > Tk (<2 > Dr (++)))) stride=<1 1 1>
#  <2 3 4> take (<0 0 0> drop _Amts[])=<2 3 4> take (<0 0 0> drop (<2 > Dr (++))) stride=<1 1 1>
#    <2 3 4> take (<0 0 0> drop _Amts[])=<2 3 4> take (<2 0 0> drop (++)) stride=<1 1 1>
#      empty expression

#      <2 3 4> take (<0 0 0> drop _Amts[])=<2 3 4> take (<0 0 0> drop ) stride=<1 1 1>

