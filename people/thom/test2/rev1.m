test_reverse1(array in1^3 <2 3 4>, array out1^3 <2 3 4>, array out2^3 <2 3 4>, array out3^2 <3 4>)
{
	out1 = reverse in1;
	out2 = reverse (out1 + in1);
	out3 = +red in1;
}

test_reverse2 (array in1^3 <2 3 4>, array out1^3 <2 3 4>, array out2^3 <1 3 4>, array out3^2 <3 4>)
{
	out1 = reverse (reverse in1);
        out2 = <1> take (reverse in1);
        out3 = <1> psi (reverse in1);
}

test_reverse3 (array in1^3 <2 3 4>, array out1^3 <2 3 4>, array out2^3 <1 3 4>, array out3^2 <3 4>)
{
        const array five^0 <> = 5;
        const array two^0 <> = 2;

	out1 = reverse (<1> take (reverse in1) cat (<1> drop (reverse in1)));
	out2 = five - (<1> take in1) - (reverse (<1> drop in1) * two);
	out3 = reverse (<1> psi in1);
}
