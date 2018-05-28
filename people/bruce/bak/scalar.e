/**********  Copyright (c) 1993 - University of Missouri  ***********
 *
 * Filename	scaler.e
 *
 * Discription	Converts a s_expr_t to a standard form
 *		Supports NOP, PLUS, MINUS, TIMES, DIVIDE, and SKIP
 *
 * Version	0.3.003 10/93 Bart Fitzgerald
 *			Initial code
 *
 ********************************************************************/

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

extern s_expr_t *StandardizeSExpr(s_expr_t *pseRoot);
