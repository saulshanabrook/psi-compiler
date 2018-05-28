main ()

{
  array A^1 <10>;
  const array B^1 <10>=<0 1 2 3 4 5 6 7 8 9>;
  A= ((<2> drop B) cat (<2> take B)) cat B;
}

