/* filename - poly.e

  10/93 - Bart Fitzgerald
	   Added extern functions

*/


/* new_poly - allocate a new polynomial of d symbolic variables.  d is
	the dimension of the array representation. */
poly_t *new_poly(int d);


/* free_poly - deallocate a polynomial */
void free_poly(poly_t *p);

/* poly_add - add to polygons and return the result in a new polynomial */
poly_t *poly_add(poly_t *left, poly_t *right);


/* poly_scale - */
poly_t *poly_scale(double k, int *j, poly_t *p);


/* poly_times - multiply to polynomials and return the result as a new
	polynomial */
poly_t *poly_times(poly_t *p1, poly_t *p2);

/* poly_expand - this is used to create a new polynomial.  d is the
	number of symbolic variables.  The newly created polynomial will
	initialized to a polynomial of one variable.  var specifies which
	of the d variables is the variable in this polynomial of one 
	variable.  terms is the degree of the one variable polynomial and
	p is a pointer to the coeficients of the one variable polynomial. */
poly_t *poly_expand(int terms, double *p, int var, int d);

poly_t *poly_constant(double c, int d);

/* poly_print - you guessed it - it prints a polynomial */
void poly_print(poly_t *p);
