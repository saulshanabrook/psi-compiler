#SOMEM_1 (array in1^3 <5 5 5>, array in2^3 <5 5 5>, array out^3 <3 3 5>)
#{
#	out = + red (+ red omega <2> (<3 3> ptake in1)) + omega <2 1> (<2 2> pdrop in2);
#}

SOMEM_2 (array in1^3 <5 5 5>, array in2^3 <5 5 5>, array out^2 <5 5>)
{
	out = (+ red omega <1> in1) - (+ red omega <2> in2);
}

