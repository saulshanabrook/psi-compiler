/* Copyright (c) 1993 University of Missouri-Rolla
   All rights reserved.

   psi.h - definitions for the psi reduction phase of the compiler.

   5/93 - v0.0 Scott Thibault
   6/93 - v0.1 Scott Thibault
   7/93 - v0.2 Scott Thibault
               Introduced s_expr_t.
   8/93 - v0.3 Scott Thibault
               Introduced statement_t, reduced_t, loop_t, and assign_t.

*/

  /* different types of identifiers (used with ident_t.type) */
#define FLOAT 0         /* a constant number */
#define ARRAY 1         /* a dynamic array (uses dim & shp of ident_t) */
#define CONST_ARRAY 2   /* a constant array (uses dim,shp & cnst of ident_t) */
#define EMBEDED_ARRAY 3 /* a rav that has be converted */
#define IOTA 4          /* an array with compents equal to the rav index */
#define RAV 5           /* composite array (uses dim,shp, & rav of ident_t) */
#define VAR_FLOAT 6     /* a dynamic floating point number */


/* ident_t - this type is used to represent all identifiers.
             Expression may be built with this type.  In that case
	     (type>>4) is the operator, the next field points to
	     the right operand.  The node defines the left operand
	     with the type (type&0xf).  There is no precedance, things
	     are evaluated left to right.  Care must be taken to avoid
	     conflict with the use of the next field for the symbol
	     table. */

struct s_expr;  /* forward reference */

typedef struct tokentree {
  char             string[17];  /* the name of the identifier */
  int              type;
  int              index;
  double           value;
  struct {
    struct tokentree *dim;
    double           *cnst;
    struct s_expr    **rav;
    struct tokentree **shp;
  } array;
  int              flags;
  struct tokentree *next;
} ident_t;


typedef struct s_expr {
  int op;
  int flags;
  struct s_expr   *left;
  struct s_expr   *right;
  ident_t         *ident;
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
#define ALLOCATE 27
#define MOD 28
#define REDUCTION 29


/* vect_t - represents vectors.  Only used internally for shapes and things.
            Vector exressions are built with these nodes using op, left, and
	    right.  The ident field is only used at the leaves of an expression
	    tree. op2 may be IF_NEG, or IF_POS */

typedef struct vect_node {
  int               op;
  int               flags;
  s_expr_t           *index;    /* vect_t[i+loc]=vect_t->ident[i+index] */
  s_expr_t           *loc;
  s_expr_t           *shp;      /* shape */
  struct vect_node  *left;
  ident_t           *ident;
  struct vect_node  *right;
} vect_t;

typedef struct forall_node {
  vect_t *bound;
  ident_t *fa;
} forall_t;


/* expr_t - used to build array expressions.  */

typedef struct expr_node {
  int               op;
  s_expr_t          *dim;
  forall_t          *forall;
  vect_t            *index;
  vect_t            *bound;
  vect_t            *loc;
  vect_t            *shp;
  vect_t            *rot;
  struct expr_node  *left;
  ident_t           *ident;
  struct expr_node  *right;
  unsigned char     flags;
  char              *func;
} expr_t;


/* parser_t - the parser uses these when parsing.  The psi field contains
              information used by the psi reduction process and by shape
	      analysis. */

typedef struct {
  ident_t *ident;
  expr_t *psi;
} parser_t;

/* statement_t - this structure represents a statement */

typedef struct {
  expr_t *expr;
  expr_t *result;
} assign_t;

struct statement;  /* forward reference */

typedef struct {
  expr_t           *lower;
  expr_t           *var;
  expr_t           *upper;
  struct statement *body;
} loop_t;

typedef struct reduced {
  unsigned char  type;
  union {
    expr_t         *frag;
    struct reduced *list;
  } d;
  struct reduced *next;
} reduced_t;

typedef struct statement {
  int              kind;
  union {
    assign_t  *assign;
    loop_t    *loop;
    reduced_t *reduced;
    expr_t    *dynamic;
  } d;
  char             *str;
  struct statement *next;
} statement_t;

/* statement kinds */
#define ASSIGN 0
#define LOOP 1
#define REDUCED 2
#define DYNAMIC 3
#define CALL 4


/* macro definitions to manipulate flags */

/* ident_t flags*/

#define GLOBAL(x) (((x)&0x20)!=0)
#define SETGLOBAL(x) x|=0x20
#define UNSETGLOBAL(x) x&=~(0x20)

#define ISDYNAMIC(x) (((x)&0x10)!=0)
#define SETDYNAMIC(x) x|=0x10
#define UNSETDYNAMIC(x) x&=~(0x10)

#define ISUSED(x) (((x)&0x08)!=0)
#define SETUSED(x) x|=0x08
#define UNSETUSED(x) x&=~(0x08)

#define HASSHAPE(x) (((x)&0x04)!=0)
#define SETSHAPE(x) x|=0x04
#define UNSETSHAPE(x) x&=~(0x04)

#define ISPARAMETER(x) (((x)&0x02)!=0)
#define SETPARAMETER(x) x|=0x02
#define UNSETPARAMETER(x) x&=~(0x02)

#define ISCODED(x) (((x)&0x01)!=0)
#define SETCODED(x) x|=0x01
#define UNSETCODED(x) x&=~(0x01)

/* expr_t flags */
#define ISALLOC(x) (((x)&0x08)!=0)
#define SETALLOC(x) x|=0x08
#define UNSETALLOC(x) x&=~(0x08)

#define ISSCANNED(x) (((x)&0x10)!=0)
#define SETSCANNED(x) x|=0x10
#define UNSETSCANNED(x) x&=~(0x10)


/* type saving macros */

#define SCALAR(s) (((s)->op==NOP)&&((s)->ident->type==FLOAT))
#define NEW_SCALAR(i,number) \
  i=get_ident();\
  (i)->type=FLOAT;\
  (i)->value=number

#ifndef NULL
#define NULL 0
#endif

#ifndef TRUE
#define TRUE 1
#define FALSE 0
#endif
