$hostname test3_host.c
$arch network
$procs 4

test3 (array in1^3 <20 30 10>, array in2^3 <20 30 10>, array out1^3 <12 30 10>)
{
    printout (in1);
    printout (in2);
    out1 = (<12> take in1) + (<12> take in2);
    printout (out1);
}
