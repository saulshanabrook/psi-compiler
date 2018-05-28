/* Copyright (c) 1993 - University of Missouri

   6/93 - v0.2 Scott Thibault

*/
/* psi.h - definitions for the psi reduction phase of the compiler */

  /* different types of identifiers (used with ident_t.type) */
#define FLOAT 0         /* a constant number */
#define ARRAY 1         /* a dynamic array (uses dim & shp of ident_t) */
#define CONST_ARRAY 2   /* a constant array (uses dim,shp & cnst of ident_t) */
#define EMBEDED_ARRAY 3 /* a rav that has be converted */
#define IOTA 4          /* an array with components equal to the rav index */
#define RAV 5           /* composite array (uses dim,shp, & rav of ident_t) */
#define VAR_FLOAT 6     /* a dynamic floating point number */


/* ident_t - this type is used to represent all identifiers.
             Expression may be built with this type.  In that case
	     (type>>4) is the operator, the next field points to
	     the right operand.  The node defines the left operand
	     with the type (type&0xf).  There is no precedence, things
	     are evaluated left to right.  Care must be taken to avoid
	     conflict with the use of the next field for the symbol
	     table. */

struct s_expr;

typedef struct tokentree {
  char             string[17];  /* the name of the identifier */
  int              type;        /* the type of the identifier */
  int              index;       /* used by the parser for identification */
  float            value;       /* value of FLOAT */

  struct {                      /* this is only used for arrays */
    struct tokentree *dim;      /* dim of the array  */
    float            *cnst;     /* the contents of a constant array */
    struct s_expr    **rav;     /* the contents of a raveled array */
    struct tokentree **shp;     /* the shape of the array */
  } array;

  int              flags;       /* used for lots of things */
  struct tokentree *next;       /* used by the symbol table */
} ident_t;


typedef struct s_expr {
  int op;                       /* the operator */
  int flags;                    /* various attributes */
  struct s_expr   *left;        /* the left argument */
  struct s_expr   *right;       /* the right argument */
  ident_t         *ident;       /* a variable if op==NOP */
} s_expr_t;
    

/* these defines are operators for vect_t and expr_t s_expr_t */


#define NOP 0          /* do nothing / variable access */
#define ABS 1          /* take the absolute value */
#define IF_NEG 2       /* for op2, if I'm negative apply me with op */
#define IF_POS 3       /* for op2, if I'm positive apply me with op */
#define PLUS 4         /* add */
#define MINUS 5        /* minus */
#define SKIP 6         /* skip node going left or right, whichever !=NULL */
#define TIMES 7
#define DIVIDE 8
#define MIN 9         /* minimum */
#define MAX 10
#define TAKE 11
#define DROP 12
#define CAT 13         /* concatenation */
#define PSI 14
#define FORALL 15      /* do the left for all values in expr->forall */
#define STORE 16       /* assignment */
#define RSCAN 17
#define OMEGA 18
#define SCALAR_EXTEND 19
#define PTAKE 20
#define PDROP 21
#define PLUS_RED 22         /* add */
#define MINUS_RED 23        /* minus */
#define TIMES_RED 24
#define DIVIDE_RED 25
#define RAVEL 26


/* vect_t - represents vectors.  Only used internally for shapes and things.
            Vector expressions are built with these nodes using op, left, and
	    right.  The ident field is only used at the leaves of an expression
	    tree. op2 may be IF_NEG, or IF_POS */

typedef struct vect_node {
  int               op;         /* the operator */
  int               flags;      /* various attributes */
  s_expr_t           *index;    /* vect_t[i+loc]=vect_t->ident[i+index] */
  s_expr_t           *loc;      /* the location in the expression */
  s_expr_t           *shp;      /* shape */
  struct vect_node  *left;      /* left argument */
  ident_t           *ident;     /* a variable if op==NOP */
  struct vect_node  *right;     /* right argument */
} vect_t;

typedef struct forall_node {
  vect_t *bound;                /* the variable bound */
  ident_t *fa;                  /* the variable */
} forall_t;


/* expr_t - used to build array expressions.  */

typedef struct expr_node {
  int               op;         /* the operator */
  s_expr_t       *dim;          /* dimension of the expression */
  forall_t       *forall;       /* extras for forall expression */
  vect_t         *index;
  vect_t         *bound;
  vect_t         *loc;          /* location */
  vect_t         *shp;          /* shape */
  vect_t         *rot;          /* not used yet */
  struct expr_node  *left;      /* left argument */
  ident_t           *ident;     /* variable if op==NOP */
  struct expr_node  *right;     /* right argument */
  unsigned char  scanned;       /* has the shape been scanned T/F */
} expr_t;


/* parser_t - the parser uses these when parsing.  The psi field contains
              information used by the psi reduction process and by shape
	      analysis. */

typedef struct {
  ident_t *ident;   /* an identifier of null for expressions */
  expr_t *psi;      /* the psi representation */
} parser_t;


/* macro definitions to manipulate flags */

#define ISPARAMETER(x) (((x)&0x02)!=0)
#define SETPARAMETER(x) x|=0x02
#define UNSETPARAMETER(x) x&=~(0x02)

#define HASSHAPE(x) (((x)&0x04)!=0)
#define SETSHAPE(x) x|=0x04
#define UNSETSHAPE(x) x&=~(0x04)

#define ISCODED(x) (((x)&0x01)!=0)
#define SETCODED(x) x|=0x01
#define UNSETCODED(x) x&=~(0x01)


/* type saving macros */

#define SCALAR(s) (((s)->op==NOP)&&((s)->ident->type==FLOAT))
#define NEW_SCALAR(i,number) \
  i=get_ident();\
  (i)->type=FLOAT;\
  (i)->value=number
