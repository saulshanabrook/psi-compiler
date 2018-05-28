# I can not even do e=2;
# Also, rav is funny. I can do:
Main()
{
 array C^2 < 3 9 >;
 array bv^1 < 72 >;
 array av^1 < 24 >;
 array rv^1 < 3 >;
 array e^0 < >;
 array i^2 <8 1>;
 array sigma^1 <1>;
 const array B^2 < 9 8 > = < 0   1  6  7  2  3  8  9  4  5 10 11 12
                             13 18 19 14 15 20 21 16 17 22 23
                             24 25 26 27 28 29 30 31 32 33 34
                             35 36 37 38 39 40 41 42 43 44 45 46
                             47 48 49 50 51 52 53 54 55 56 57 58
                             59 60 61 62 63 64 65 66 67 68 69 70
                             71 >;
 const array A^2 <3 8> =    <72 73 74 75 76 77 78 79 80 81 82
                             83 84 85 86 87 88 89 90 91 92 93 94
                                  95 >;
 sigma = <0> - <3> ;
 C = sigma take B;
 av = rav A;
 i = iota <3>;
 rv = i psi omega <1 1> av;
}

# but if I replcace C = i psi omega <1 2> B;
# with rv = i psi omega <1 1> av;
# it croaks.
