$arch mpimac
$procs 4

test1 (array A^2 <40 40>, array B^2 <40 40>, array C^2 <40 40>)
{
    C=+red omega <2> (A [* omega <0 1>] omega <1 2> B);
}
