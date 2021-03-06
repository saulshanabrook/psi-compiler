/**********  Copyright (c) 1993 - University of Missouri  ***********
 *
 * Filename	values.c
 *
 * Discription	Returns constant values of various types
 *
 * Version	0.3.001 10/93 Bart Fitzgerald
 *			Initial code
 *
 ********************************************************************/

#include "psi.h"


/**********************************************************
 * Procedure	 bGetIdentValue
 *
 * Description	 Gets the value of a ident_t argument if
 *		 it is constant.  The argument MUST be a
 *		 value or a one dimension array.
 *
 * Param	 node  - argument to find the diminsion of
 *		 index - the index into the array
 *		 value - the returned value
 *
 * Return	 TRUE if the value is a constant
 *		 FALSE otherwise
 *
 **********************************************************/
int bGetIdentValue(ident_t *node, int index, double *value) {

    switch (node->type) {
	case CONSTANT:
	    *value = node->value;
	    return (TRUE);

	case CONST_ARRAY:
	    if (node->array.shp[0]->type != CONSTANT)
		return (FALSE);
	    if ((double)index > node->array.shp[0]->value)
		return (FALSE);
	    *value = node->array.cnst[index];
	    return (TRUE);

	case IOTA:
	    *value = (double)index;
	    return (TRUE);

	case RAV:
	    if (node->array.shp[0]->type != CONSTANT)
		return (FALSE);
	    if ((double)index > node->array.shp[0]->value)
		return (FALSE);
	    if (node->array.rav[index]->op != NOP)
		return (FALSE);
	    return (bGetIdentValue(node->array.rav[index]->ident, 0, value));

	case EMBEDED_ARRAY:
	    if (node->array.shp[0]->type != CONSTANT)
		return (FALSE);
	    if ((double)index > node->array.shp[0]->value)
		return (FALSE);
	    if (node->array.cnst != NULL) {
		*value = node->array.cnst[index];
		return (TRUE);
		}
	    if (node->array.rav[index]->op != NOP)
		return (FALSE);
	    return (bGetIdentValue(node->array.rav[index]->ident, 0, value));

	}  /* switch (node->type) */

    return (FALSE);

}  /* bGetIdentValue */


/**********************************************************
 * Procedure	 bGetDim
 *
 * Description	 Gets the dimension of a parser_t argument if
 *		 it is constant.
 *
 * Param	 arg - argument to find the diminsion of
 *		 dim - the returned dimension
 *
 * Return	 TRUE if the dimension is a constant
 *		 FALSE otherwise
 *
 **********************************************************/
int bGetDim(parser_t *arg, double *dim) {

    if (arg->psi->dim->op != NOP)
	return(FALSE);
    return (bGetIdentValue(arg->psi->dim->ident, 0, dim));

}  /* bGetDim */


/**********************************************************
 * Procedure	 bGetShp
 *
 * Description	 Gets the one componet of the shape
 *		 of the parser_t argument if it is constant.
 *
 * Param	 arg - argument to find the shp of
 *		 dim - the dimension to select which shape
 *		 shp - the returned shape
 *
 * Return	 TRUE if the shape is a constant
 *		 FALSE otherwise
 *
 **********************************************************/
int bGetShp(parser_t *arg, int dim, double *shp) {

    if (arg->psi->shp->op != NOP)
	return(FALSE);
    return (bGetIdentValue(arg->psi->shp->ident, dim, shp));

}  /* bGetShp */


/**********************************************************
 * Procedure	 bGetSingleDimParserValue
 *
 * Description	 Gets the one value of a single dimisional
 *		 parser_t argument, if it is constant.
 *
 * Param	 arg   - argument to find the shp of
 *		 index - an index into the vector
 *		 value - the returned value
 *
 * Return	 TRUE if the value is a constant
 *		 FALSE otherwise
 *
 **********************************************************/
int bGetSingleDimParserValue(parser_t *arg, int index, double *value) {

    if (arg->psi->op != NOP)
	return(FALSE);
    return (bGetIdentValue(arg->psi->ident, index, value));

}  /* bGetSingleDimParserValue */
