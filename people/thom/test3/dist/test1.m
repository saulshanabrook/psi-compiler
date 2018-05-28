$hostname test1_host.c 
$arch network
$procs 4

test1 (array A^2 <40 40>, array C^2 <40 40>)
{
    printout2 (A);
    C=A;
    printout2 (C);
}
