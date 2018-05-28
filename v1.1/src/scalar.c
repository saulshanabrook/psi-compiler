/**********  Copyright (c) 1993 - University of Missouri  ***********
 *
 * Filename	scaler.c
 *
 * Discription	Converts a s_expr_t to a standard form
 *		Supports NOP, PLUS, MINUS, TIMES, DIVIDE, and SKIP
 *
 * Version	0.3.003 10/93 Bart Fitzgerald
 *			Initial code
 *
 ********************************************************************/

#include <stdio.h>
#include <string.h>

#include "psi.h"
#include "sys.h"
#include "poly.h"

#include "psi.e"
#include "sys.e"
#include "poly.e"
#include "parse.e"
#include "values.e"


/************************
 * Module Types
 ************************/

typedef struct BTN {
    int	     iIndex;
    ident_t *pidIdentifier;
    struct BTN *pbtnLeft;
    struct BTN *pbtnRight;
    } BinaryTreeNode_t;     /* prefix - btn */

typedef struct{
    poly_t *ppNumerator;
    poly_t *ppDenominator;
    } FractionalPolygon_t;  /* prefix - fp */


/************************
 * Module Variables
 ************************/

BinaryTreeNode_t *pbtnIdentifiers;
int		  iIdentifierCount;


/************************
 * Forward Declarations
 ************************/
int		     bFindUniqueIdentifiers	 (s_expr_t *pseNode);
BinaryTreeNode_t   **ppbtnGetBinaryTreeNode	 (char *sIdentifier);
void		     IdentifierFound		 (ident_t *pidIdentifier);
void		     IndexIdentifiers		 (BinaryTreeNode_t *pbtnCurrent);
FractionalPolygon_t *pfpFractionalPolygonAdd	 (FractionalPolygon_t *pfpLeft,
						  FractionalPolygon_t *pfpRight);
FractionalPolygon_t *pfpFractionalPolygonTimes	 (FractionalPolygon_t *pfpLeft,
						  FractionalPolygon_t *pfpRight);
void		     FreeFractionalPolygon	 (FractionalPolygon_t *pfpNew);
FractionalPolygon_t *pfpSExprToFractionalPolygon (s_expr_t *pseNode);
s_expr_t	    *psePolyToSExpr		 (poly_t *ppPoly);
s_expr_t	    *get_s_expr		 (void);


/**********************************************************
 * Procedure	 StandardizeSExpr
 *
 * Description	 Takes a s_expr_t and standardizes format
 *
 * Precondition  pseRoot is a valid s_expr_t tree.
 *
 * Postcondition A s_expr_t is returned in standard format
 *		 if no error or unsupported ops are encountered.
 *		 The original s_expr_t is returned otherwise.
 *		 The original s_expr_t is unchanged.
 *
 * Param	 pseRoot - A pointer to the root of a s_expr_t.
 *
 * Return	 A standardized s_expr_t or the original s_expr_t
 *
 **********************************************************/

s_expr_t *StandardizeSExpr(s_expr_t *pseRoot) {
    FractionalPolygon_t *pfpNew;
    s_expr_t		*pseNew;

    if (pseRoot == NULL)
         return(pseRoot);
	 
    pbtnIdentifiers = NULL;
    iIdentifierCount = 0;

    if (!bFindUniqueIdentifiers(pseRoot))
	return (pseRoot);
/*
    IndexIdentifiers(pbtnIdentifiers);
*/
    if ((pfpNew = pfpSExprToFractionalPolygon(pseRoot)) == NULL)
	return (pseRoot);

    if (pfpNew->ppDenominator == NULL)
	pseNew = psePolyToSExpr (pfpNew->ppNumerator);
    else {
	pseNew	      = get_s_expr();
	pseNew->op    = DIVIDE;
	pseNew->left  = psePolyToSExpr (pfpNew->ppNumerator);
	pseNew->right = psePolyToSExpr (pfpNew->ppDenominator);
	} /* else */

    FreeFractionalPolygon(pfpNew);
    return (pseNew);

}  /* StandardizeSExpr */


/**********************************************************
 * Procedure	 bFindUniqueIdentifiers
 *
 * Description	 Stores identifiers
 *
 * Precondition  ppbtnRoot is set to NULL.
 *		 iIndentifierCount = 0.
 *
 * Postcondition A tree is built that contains all identifiers
 *		 and IdentifierCount is the number of unique
 *		 identifiers.
 *
 * Param	 pseNode - A pointer to the root of a s_expr_t.
 *
 * Return	 TRUE is sucessful,
 *		 FALSE otherwise.
 *
 **********************************************************/

int bFindUniqueIdentifiers(s_expr_t *pseNode) {
    double  fDummy;

  TailRecursion:

    if (pseNode == NULL) {
        perror ("FATAL ERROR: Scaler.c (#0), A unexpected NULL was encountered in an s_expr_t.");
	return(FALSE);
	} /* if (pseNode == NULL) */

    switch (pseNode->op) {
	case NOP : {
	    if (!bGetIdentValue (pseNode->ident, 0, &fDummy)) {
		IdentifierFound (pseNode->ident);
		} /* if (!bGetIdentifierValue */
	    } /* case NOP */
	    break;
	    
	case PLUS   :
	case MINUS  :
	case TIMES  :
	case DIVIDE : {
	    if (!bFindUniqueIdentifiers(pseNode->left))
		return(FALSE);
	    pseNode = pseNode->right;
	    goto TailRecursion;
	    } /* case DIVIDE */
	    break;

	case SKIP : {
	    if (pseNode->left == NULL)
		pseNode = pseNode->right;
	    else
		pseNode = pseNode->left;
	    goto TailRecursion;
	    } /* case SKIP */
	    break;

	default :
	    return (FALSE);

	} /* switch (pseNode->op) */

    return (TRUE);

}  /* bFindUniqueIdentifiers */


/**********************************************************
 * Procedure	 IdentifierFound
 *
 * Description	 Stores and counts if an identifier
 *		 is not in the tree.
 *
 * Precondition  ppbtnRoot is a tree if identifiers.
 *
 * Postcondition If the identifier is not found in the tree
 *		 it is added and IdentifierCount is incremented.
 *
 * Param	 sIdentifier - The identifer to be added or found.
 *
 * Return	 void
 *
 **********************************************************/

void IdentifierFound(ident_t *pidIdentifier) {
    BinaryTreeNode_t **ppbtnCurrent;
    BinaryTreeNode_t *pbtnCurrent;

    if ((*(ppbtnCurrent = ppbtnGetBinaryTreeNode(pidIdentifier->string))) == NULL) {
	*ppbtnCurrent = (BinaryTreeNode_t *)get_mem(sizeof(BinaryTreeNode_t));
	pbtnCurrent		   = *ppbtnCurrent;
	pbtnCurrent->iIndex        = iIdentifierCount++;
	pbtnCurrent->pidIdentifier = pidIdentifier;
	pbtnCurrent->pbtnLeft	   = NULL;
	pbtnCurrent->pbtnRight	   = NULL;
	}

}  /* IdentifierFound */


/**********************************************************
 * Procedure	 ppbtnGetBinaryTreeNode
 *
 * Description	 Gets a binary tree node if it exists
 *
 * Precondition  ppbtnCurrent is the address of a root to a binary tree
 *		 that is to be searched for sIdentifier.
 *
 * Postcondition The tree remains unchanged.  A pointer to the
 *		 tree's pointers to the node is returned.  If the
 *		 value of the pointer's pointer is NULL, then this is
 *		 where sIdentifier should be.
 *
 * Param	 sIdentifier - An identifier string
 *
 * Return	 A pointer to the tree's pointer to the node.  If the
 *		 tree's pointer is NULL then the key was not found.
 *
 **********************************************************/

BinaryTreeNode_t **ppbtnGetBinaryTreeNode (char *sIdentifier) {

    int iResult;
    BinaryTreeNode_t **ppbtnCurrent;

    ppbtnCurrent = &pbtnIdentifiers;

  TailRecursion: /* well, almost tail recursion */

    if (*ppbtnCurrent == NULL)
	return (ppbtnCurrent);

    if ((iResult = strcmp (sIdentifier,
			   (*ppbtnCurrent)->pidIdentifier->string)) < 0) {
	ppbtnCurrent = &((*ppbtnCurrent)->pbtnLeft);
	goto TailRecursion;
	}
    else if (iResult > 0) {
	ppbtnCurrent = &((*ppbtnCurrent)->pbtnRight);
	goto TailRecursion;
	}

    return (ppbtnCurrent);

}  /* ppbtnGetBinaryTreeNode */


/**********************************************************
 * Procedure	 pidGetBinaryTreeByIndex
 *
 * Description	 Gets an ident_t in the binary tree with iIndex
 *
 * Precondition  pbtnCurrent is the address of a root to a binary tree
 *		 that is to be searched for iIndex.
 *
 * Postcondition The tree remains unchanged.  A pointer to the
 *		 tree's ident_t poineter is returned.
 *
 * Param	 iIndex      - the index to be found.
 *		 pbtnCurrent - the root of the tree.
 *
 * Return	 A pointer to the tree's ident_t pointer with iIndex.
 *
 **********************************************************/

ident_t *pidGetBinaryTreeByIndex (int iIndex, BinaryTreeNode_t *pbtnCurrent) {
    ident_t *pidReturn;

  TailRecursion:

    if (pbtnCurrent == NULL)
	return (NULL);

    if (pbtnCurrent->iIndex != iIndex)
	if ((pidReturn = pidGetBinaryTreeByIndex(iIndex, pbtnCurrent->pbtnLeft)) == NULL) {
	    pbtnCurrent = pbtnCurrent->pbtnRight;
	    goto TailRecursion;
	    } /* if ((pidReturn =... */
	else
	    return (pidReturn);

    return (pbtnCurrent->pidIdentifier);

}  /* pidGetBinaryTreeByIndex */


/**********************************************************
 * Procedure	 IndexIdentifiers
 *
 * Description	 Assigns an index to an identifier
 *
 * Precondition  iIndentifierCount = 0 and pbtnCurrent is a valid
 *		 binary tree.
 *
 * Postcondition Indexes are assigned in infix order.
 *
 * Param	 pbtnCurrent - the root of the tree.
 *
 * Return	 void
 *
 **********************************************************/

void IndexIdentifiers (BinaryTreeNode_t *pbtnCurrent) {

  TailRecursion:

    if (pbtnCurrent != NULL) {
	IndexIdentifiers (pbtnCurrent->pbtnLeft);
	pbtnCurrent->iIndex = iIdentifierCount++;
	pbtnCurrent = pbtnCurrent->pbtnRight;
	goto TailRecursion;
	}

}  /* pidGetBinaryTreeByIndex */


/**********************************************************
 * Procedure	 pfpSExprToFractionalPolygon
 *
 * Description	 Takes a s_expr_t and converts it to a poly_t.
 *
 * Precondition  pseNode is a valid s_expr_t tree.
 *
 * Postcondition A s_expr_t is returned in standard format.
 *		 The original s_expr_t is unchanged.
 *
 * Param	 pseRoot - A pointer to the root of a s_expr_t.
 *
 * Return	 A poly_t from the s_expr_t.
 *		 NULL - if the s_expr_t was NOT standardized.
 *
 **********************************************************/

FractionalPolygon_t *pfpSExprToFractionalPolygon(s_expr_t *pseNode) {

  int index;

    if (pseNode == NULL) {
	perror ("FATAL ERROR: Scaler.c (#2), unexpected NULL found in s_expr_t");
	return (NULL);
	}


    switch (pseNode->op) {
	case NOP : {
	    double fValue;
	    FractionalPolygon_t *pfpNew = (FractionalPolygon_t *)get_mem(sizeof(FractionalPolygon_t));
	    pfpNew->ppDenominator = NULL;

	    if (bGetIdentValue(pseNode->ident, 0, &fValue)) {
		pfpNew->ppNumerator = poly_constant(fValue,iIdentifierCount);
		} /* if (bGetIdentValue... */
	    else {
		double afCoeficients[] = {0.0f, 1.0f};

		index=(*ppbtnGetBinaryTreeNode(pseNode->ident->string))->iIndex;
		pfpNew->ppNumerator = poly_expand(2, afCoeficients,index,
						  iIdentifierCount);
		} /* else */
	    return (pfpNew);
	    } /* case NOP */
	    break;

	case SKIP :
	    if (pseNode->left == NULL)
		return (pfpSExprToFractionalPolygon(pseNode->right));
	    else
		return (pfpSExprToFractionalPolygon(pseNode->left));
	    break;

	case PLUS :
	    return (pfpFractionalPolygonAdd (pfpSExprToFractionalPolygon (pseNode->left),
					     pfpSExprToFractionalPolygon (pseNode->right)));
	    break;

	case MINUS : {
	    FractionalPolygon_t *pfpRight =
		    pfpSExprToFractionalPolygon(pseNode->right);
	    poly_t *ppNegativeOne = poly_constant(-1.0,iIdentifierCount);
	    pfpRight->ppNumerator = poly_times(pfpRight->ppNumerator,
					       ppNegativeOne);
	    return (pfpFractionalPolygonAdd (pfpSExprToFractionalPolygon (pseNode->left),
					     pfpRight));
	    } /* case MINUS */
	    break;

	case TIMES :
	    return (pfpFractionalPolygonTimes (pfpSExprToFractionalPolygon (pseNode->left),
					       pfpSExprToFractionalPolygon (pseNode->right)));
	    break;

	case DIVIDE : {
	    FractionalPolygon_t *pfpRight = pfpSExprToFractionalPolygon (pseNode->right);
	    poly_t		*ppInvert = pfpRight->ppDenominator;
	    pfpRight->ppDenominator	  = pfpRight->ppNumerator;
	    pfpRight->ppNumerator	  = ppInvert;
	    return (pfpFractionalPolygonTimes (pfpSExprToFractionalPolygon (pseNode->left),
					       pfpRight));
	    } /* case DIVIDE */
	    break;

	default :
	    perror ("WARNING: Scaler.c (#3), an unexpected s_expr_t op was encountered.");

	} /* switch (pseNode->op) */

    return (NULL);

}  /* pfpSExprToFractionalPolygon */


/**********************************************************
 * Procedure	 pfpFractionalPolygonTimes
 *
 * Description	 Multiplies two fractional ploygons and distroyes operands.
 *
 * Precondition  pfpLeft and pfpRight are valid FractionalPolygon_t.
 *
 * Postcondition A new FractionalPolygon_t is created and returned.
 *		 Memory used by pfpLeft and pfpRight is freed.
 *
 * Param	 pfpLeft - A FractionalPolygon_t operand
 *		 pfpLeft - A FractionalPolygon_t operand
 *
 * Return	 A new polygon that is the product of pfpLeft and pfpRight.
 *
 **********************************************************/
FractionalPolygon_t *pfpFractionalPolygonTimes(FractionalPolygon_t *pfpLeft,
					       FractionalPolygon_t *pfpRight) {

    FractionalPolygon_t *pfpProduct;
    pfpProduct = (FractionalPolygon_t *)get_mem(sizeof(FractionalPolygon_t));
    pfpProduct->ppDenominator = NULL;

    if ((pfpProduct->ppDenominator = pfpLeft->ppDenominator) == NULL)
	pfpProduct->ppDenominator = pfpRight->ppDenominator;
    else {
	if (pfpRight->ppDenominator != NULL) {
	    pfpProduct->ppDenominator = poly_times (pfpLeft->ppDenominator,
						    pfpRight->ppDenominator);
	    free_poly (pfpLeft->ppDenominator);
	    free_poly (pfpRight->ppDenominator);
	    } /* if (pfpRight->ppDenominator != NULL) */
	} /* else */

    pfpProduct->ppNumerator = poly_times (pfpLeft->ppNumerator,
					  pfpRight->ppNumerator);

		/* free memory - NOTE: Denominator handled above */
    free_poly(pfpLeft->ppNumerator);
    free_poly(pfpRight->ppNumerator);
    free_mem (pfpLeft);
    free_mem (pfpRight);

    return (pfpProduct);

} /* pfpFractionalPolygonTimes */

/**********************************************************
 * Procedure	 pfpFractionalPolygonAdd
 *
 * Description	 Adds two fractional ploygons and distroyes the operands.
 *
 * Precondition  pfpLeft and pfpRight are valid FractionalPolygon_t.
 *
 * Postcondition A new FractionalPolygon_t is created and returned.
 *		 Memory used by pfpLeft and pfpRight is freed.
 *
 * Param	 pfpLeft - A pointer to FractionalPolygon_t to be distroyed
 *		 pfpLeft - A pointer to FractionalPolygon_t to be distroyed
 *
 * Return	 A new polygon that is the sum of pfpLeft and pfpRight.
 *
 **********************************************************/
FractionalPolygon_t *pfpFractionalPolygonAdd(FractionalPolygon_t *pfpLeft,
					     FractionalPolygon_t *pfpRight) {

    FractionalPolygon_t *pfpSum =
	    (FractionalPolygon_t *)get_mem(sizeof(FractionalPolygon_t));
    pfpSum->ppDenominator = NULL;

    if (pfpLeft->ppDenominator != NULL) {
	pfpRight->ppNumerator = poly_times(pfpRight->ppNumerator,
					   pfpLeft->ppDenominator);
	pfpSum->ppDenominator = pfpLeft->ppDenominator;
	} /* if (pfpLeft->ppDenominator != NULL) */

    if (pfpRight->ppDenominator != NULL) {
	pfpLeft->ppNumerator = poly_times(pfpLeft->ppNumerator,
					  pfpRight->ppDenominator);
	if (pfpSum->ppDenominator == NULL)
	    pfpSum->ppDenominator = pfpRight->ppDenominator;
	else {
	    pfpSum->ppDenominator = poly_times (pfpLeft->ppDenominator,
						pfpRight->ppDenominator);
	    free_poly (pfpLeft->ppDenominator);
	    free_poly (pfpRight->ppDenominator);
	    } /* else */
	} /* if (pfpLeft->ppDenominator != NULL) */

    pfpSum->ppNumerator = poly_add (pfpLeft->ppNumerator,
				    pfpRight->ppNumerator);

		/* free memory - NOTE: Denominator handled above */
    free_poly(pfpLeft->ppNumerator);
    free_poly(pfpRight->ppNumerator);
    free_mem (pfpLeft);
    free_mem (pfpRight);

    return(pfpSum);

} /* pfpFractionalPolygonAdd */


/**********************************************************
 * Procedure	 psePolyToSExpr
 *
 * Description	 Takes a poly_t and converts it to an s_expr_t
 *
 * Precondition  pseRoot is a valid s_expr_t tree.
 *
 * Postcondition A s_expr_t is returned from a poly_t
 *
 * Param	 ppPoly 	- the poly_t to be converted.
 *
 * Return	 The s_expr_t from the poly_t
 *
 **********************************************************/

s_expr_t *psePolyToSExpr(poly_t *ppPoly) {
    int *aiPower;
    int iIndex;
    int iMaximum = 1;
    int iDimension;
    int iPower;
    int bIncrement;
    double     fValue;
    s_expr_t *pseReturn = NULL;
    s_expr_t *pseTerm;
    s_expr_t *pseFactor;
    s_expr_t *pseOperator;
    ident_t  *pidCoefficient;

    if (iIdentifierCount>0)    /* zero the powers array */
      aiPower = (int *)get_mem(iIdentifierCount * sizeof(int));
    for (iDimension = 0; iDimension < iIdentifierCount; iDimension++) {
	aiPower[iDimension] = 0;
	iMaximum *= ppPoly->shp[iDimension];
	} /* for (iDimension = 0... */

			    /* build the s_expr_t */
    for (iIndex = 0; iIndex < iMaximum; iIndex++) {
	if ((fValue = ppPoly->rav[iIndex]) != 0) {
			    /* a non-zero coefficent */
	    pseTerm	   = get_s_expr();
	    pseTerm->ident = pidCoefficient = get_ident();
	    pidCoefficient->string[0]  = '\0';
	    pidCoefficient->type       = CONSTANT;
	    pidCoefficient->value      = fValue;
	    pidCoefficient->index      = pidCoefficient->flags = 0;
	    pidCoefficient->array.dim  = NULL;
	    pidCoefficient->array.cnst = NULL;
	    pidCoefficient->array.rav  = NULL;
	    pidCoefficient->array.shp  = NULL;
	    pidCoefficient->next       = NULL;

			    /* look for factors for this term */
	    for (iDimension = 0; iDimension < iIdentifierCount; iDimension++) {
		if (aiPower[iDimension] > 0) {
			    /* create factors with a non-zero power */
		    pseFactor	     = get_s_expr();
		    pseFactor->ident = pidGetBinaryTreeByIndex(iDimension, pbtnIdentifiers);

			    /* multiply the factor to the term */
		    for (iPower = aiPower[iDimension]; iPower > 0; iPower--) {
			pseOperator	   = get_s_expr();
			pseOperator->op	   = TIMES;
			pseOperator->left  = pseTerm;
			pseOperator->right = pseFactor;
			pseTerm		   = pseOperator;
			} /* for (iPower = 0... */
		    } /* if (aiPower[iDimension] > 0) */
		} /* for (iDimension = 0;... */

		    /* add the new term */
	    if (pseReturn == NULL)
		pseReturn = pseTerm;
	    else {
		pseOperator	   = get_s_expr();
		pseOperator->op	   = PLUS;
		pseOperator->left  = pseTerm;
		pseOperator->right = pseReturn;
		pseReturn	   = pseOperator;
		} /* else */

	    } /* if (pfpAll->ppPoly->rav[iIndex] != 0) */

			    /* Increament powers for next term */
	bIncrement = TRUE;
	for (iDimension = 0; (iDimension < iIdentifierCount) && bIncrement; iDimension++)
	    if (++aiPower[iDimension] >= ppPoly->shp[iDimension])
		aiPower[iDimension] = 0;
	    else
		bIncrement = FALSE;

	} /* for (iIndex = 0; iIndex < iMaximum; iIndex++) */

    if (pseReturn==NULL) 
      pseReturn=&s_const0;

    return (pseReturn);
}  /* psePolyToSExpr */


/**********************************************************
 * Procedure	 FreeFractionalPolygon
 *
 * Description	 frees memory used by pfpNew.
 *
 * Precondition  pfpNew contains a valid FractionalPolygon_t.
 *
 * Postcondition Memory that pfpNew used is freed and pfpNew is
 *		 set to NULL.
 *
 * Param	 pfpNew - A pointer to FractionalPolygon_t to be distroyed
 *
 * Return	 void
 *
 **********************************************************/

void FreeFractionalPolygon(FractionalPolygon_t *pfpNew) {

    if (pfpNew->ppNumerator != NULL)
	free_poly(pfpNew->ppNumerator);
    if (pfpNew->ppDenominator != NULL)
	free_poly(pfpNew->ppDenominator);
    free_mem (pfpNew);
    pfpNew = NULL;

}  /* FreeFractionalPolygon */
