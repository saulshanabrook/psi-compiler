Reducing:
out5=( +  omega <2.000000> in) + ( *  omega <1.000000> in)
#<(5) (5)> Tk (<0 0> Dr [_out5])=<(5) (5)> Tk (<0 0> Dr (
  forall forall_i0 in <(5)> {
    +red((([forall_i1] Psi ([forall_i0] Psi [_in]))+NULL))
  }+
  forall forall_i2 in <(5) (5)> {
    *red((([forall_i3] Psi ([forall_i2] Psi [_in]))*NULL))
  }))
#  <(5) (5)> Tk (<0 0> Dr [_out5])=<(5) (5)> Tk (<0 0> Dr 
    forall forall_i0 in <(5)> {
      +red((([forall_i1] Psi ([forall_i0] Psi [_in]))+NULL))
    })
#    <1 5> Tk ((<(int) forall_i0[0+(0)]>++<0>) Dr [_out5])=<(5)> Tk (<0> Dr +red((([forall_i1] Psi ([forall_i0] Psi [_in]))+NULL)))
#      <1 5> Tk ((<(int) forall_i0[0+(0)]>++<0>) Dr [_out5])=<1 5> Tk (<0 0> Dr <0>)

#      <(5)> Tk (<0 0> Dr [temp1])=<(5)> Tk (<(0)> Dr (([forall_i1] Psi ([forall_i0] Psi [_in]))+NULL))
#        <(5)> Tk (<0 0> Dr [temp1])=<(5)> Tk (<(0)> Dr ([forall_i1] Psi ([forall_i0] Psi [_in])))
#          <5> Tk (<0 0> Dr [temp1])=<1 5> Tk ((<(int) forall_i1[0+(0)]>++<(0)>) Dr ([forall_i0] Psi [_in]))
#            <5> Tk (<0 0> Dr [temp1])=<1 1 5> Tk ((<(int) forall_i0[0+(0)]>++(<(int) forall_i1[0+(0)]>++<(0)>)) Dr [_in])

#      <1 5> Tk ((<(int) forall_i0[0+(0)]>++<0>) Dr [_out5])+=<(5)> Tk (<0> Dr [temp1])

#  <(5) (5)> Tk (<0 0> Dr [_out5])+=<(5) (5)> Tk (<0 0> Dr 
    forall forall_i2 in <(5) (5)> {
      *red((([forall_i3] Psi ([forall_i2] Psi [_in]))*NULL))
    })
#    <1 1> Tk (<0 0> Dr [temp2])=(<>++<>) Tk ((<>++<>) Dr *red((([forall_i3] Psi ([forall_i2] Psi [_in]))*NULL)))
#      <1 1> Tk (<0 0> Dr [temp2])=<1> Tk (<0 0> Dr <1>)

#      <> Tk (<0 0> Dr [temp3])=<> Tk (<> Dr (([forall_i3] Psi ([forall_i2] Psi [_in]))*NULL))
#        <> Tk (<0 0> Dr [temp3])=<> Tk (<> Dr ([forall_i3] Psi ([forall_i2] Psi [_in])))
#          <> Tk (<0 0> Dr [temp3])=<1> Tk (<(int) forall_i3[0+(0)]> Dr ([forall_i2] Psi [_in]))
#            <> Tk (<0 0> Dr [temp3])=<1 1 1> Tk ((<(int) forall_i2[0+(0)] (int) forall_i2[1+(0)]>++<(int) forall_i3[0+(0)]>) Dr [_in])

#      <1 5> Tk (<0 0> Dr [temp2])*=<(5)> Tk (<> Dr [temp3])

#    <(5) (5)> Tk (<(int) forall_i2[0+(0)] (int) forall_i2[1+(0)]> Dr [_out5])+=<(5) (5)> Tk (<> Dr [temp2])

