TAKE1_M (array in1^3 <2 3 4>, array out^3 <1 3 4>)
{
        out = <1> take in1;
}

DROP_M (array in1^3 <2 3 4>, array out^3 <1 3 4>)
{
        out = <1> drop in1;
}


TAKE2_M (array in1^3 <2 3 4>, array out^1 <1>)
{
	out = <1 1 1> take (<1 1> take (<2 -2> take in1));
}

DROP2_M (array in1^3 <2 3 4>, array out^1 <1>)
{
	out = <0 0 -3> drop (<0 1> drop (<0 -1> drop (<-1> drop in1)));
}

PTD1_M (array in1^3 <2 3 4>, array out^1 <4>)
{
	out = <1 1> psi (<0 -1> take (<0 -1> drop in1));
}

PSI1_M (array in1^3 <2 3 4>, array out^2 <3 4>)
{
       out = <1> psi in1;
}

PSI2_M (array in1^3 <2 3 4>, array out^1 <4>)
{
	out = <1 2> psi in1;
}

