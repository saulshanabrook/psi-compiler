$hostname test2_host.c
$arch network
$procs 4

test2 (array in1^1 <100>, array out1^1 <100>)
{
    printout (in1);
    out1 = in1;
    printout (out1);
}
