one_to_two (array in^3 <5 5 5>, array out^3 <9 9 9>)
{
	array	mid1^3 <10 5 5>;
	array	mid2^3 <10 10 5>;
	array 	mid3^3 <10 10 10>;

	mid1 = in   cat omega <2 2> (in   + ((<1> drop in) cat (<1> take in)));
	mid2 = mid1 cat omega <1 1> (mid1 + ((<0 1> drop mid1) cat omega <2 2> (<5 1> take mid1)));
	mid3 = mid2 cat omega <0 0> (mid2 + ((<0 0 1> drop mid2) cat omega <1 1> (<5 5 1> take mid2)));
	out  = <-1 -1 -1> drop mid3;
}
