# ravel gives a bus error, iota a scalar and vector seems to work/lrm
main()
{
 array res0^3 < 3 4 5 >;
 array res1^1 < 60 >;
 array in^2 <60 1>;
 array ind^2 <3 1>;
 array res2^1 <120>;
 const array xnew0^4 < 2 3 4 5 > = < 0 1 6 7 2 3 8 9 4 5 10 11 12
                                  13 18 19 14 15 20 21 16 17 22 23
                                  24 25 26 27 28 29 30 31 32 33 34
                                  35 36 37 38 39 40 41 42 43 44 45 46
                                  47 48 49 50 51 52 53 54 55 56 57 58
                                  59 60 61 62 63 64 65 66 67 68 69 70
                                  71 72 73 74 75 76 77 78 79 80 81 82
                                  83 84 85 86 87 88 89 90 91 92 93 94
                                  95 96 97 98 99 100 101 102 103 104
                                  105 106 107 108 109 110 111 112 113
                                  114 115 116 117 118 119 >;
 const array a^1 <1> = <60>;
 const array s^0 < > = 60;
 const array j^1 <1> = <1> ;

# res0 = j psi xnew0;
# ind =  iota a;
 res2 = rav xnew0;
}
