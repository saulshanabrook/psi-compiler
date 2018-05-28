

#ifndef RAMBAMH
#define RAMBAMH

/*		The RAMBAM.H file.		*/

/*		Copyright (c) LJW August 1992.	*/
/*		All rights reserved.			*/

#define U unsigned long

#ifndef	ljw_index	
typedef unsigned long ljw_index;
#endif

#ifndef	ljw_cursor
typedef unsigned long ljw_cursor;
#endif

/* The return codes from the rambam functions (ints) */
enum _return_codes  {
 ljw_ok            =  0,
 ljw_no_space      = -1,
 ljw_not_found     = -2,
 ljw_notfound      = -2,
 ljw_found         = -3,
 ljw_trace_error   = -4,
 ljw_invalid_input = -5,
 ljw_prefix_found  = -6,
 ljw_failure       = -32768 
};

 
/* define	ljw_failure	2147483647L */

/* Allow for both spellings */
#ifndef ljw_nospace
#define ljw_nospace ljw_no_space
#endif


#ifndef	ljw_graph
#define	ljw_graph	unsigned long
#endif

#ifndef	ljw_graph_cursor
#define	ljw_graph_cursor	unsigned long
#endif

#ifndef	ljw_qctr
long	ljw_qctr(char	*name, int line_number);
#endif

#ifndef	ljw_ctr
	extern	long	ljw_ctr;
#endif

#ifndef	ljw_ctr_start
	extern	long	ljw_ctr_start;
#endif

#ifndef	ljw_ctr_end
	extern	long	ljw_ctr_end;
#endif
/*	----------------------------------------	*/
/*	Make sure that the global variable erf		*/
/*	is defined, so the trace functions can 		*/
/*	be used.								*/
/*	----------------------------------------	*/
#ifndef	erf_file
	extern	FILE	*erf_file;
#endif

/*	-------------------------------------------------	*/
/*	The debugging "q" macros:					*/
/*	-------------------------------------------------	*/
#ifdef	DEBUG
	extern	int	q_to_a_file;
	#ifndef	q0
	#define	q0	ljw_q0(__FILE__,__LINE__);
	#endif
#else
	#ifndef	q0
	#define	q0
	#endif
#endif

#ifdef	DEBUG
	#ifndef	q1
	#define	q1(message)	ljw_q1(__FILE__,__LINE__,message);
	#endif
#else
	#ifndef	q1
	#define	q1(message)
	#endif
#endif
	
#ifdef	DEBUG
	#ifndef	q2
	#define	q2(msg1,msg2)	ljw_q9(__FILE__,__LINE__,msg1,msg2);
	#endif
#else
	#ifndef	q2
	#define	q2(msg1,msg2)
	#endif
#endif
	
#ifdef	DEBUG
	#ifndef	q3
	#define	q3(msg1,msg2,msg3)	ljw_q9(__FILE__,__LINE__,msg1,msg2,msg3);
	#endif
#else
	#ifndef	q3
	#define	q3(msg1,msg2,msg3)
	#endif
#endif
	
#ifdef	DEBUG
	#ifndef	q4
	#define	q4(msg1,msg2,msg3,msg4)	ljw_q9(__FILE__,__LINE__,msg1,msg2,msg3,msg4);
	#endif
#else
	#ifndef	q4
	#define	q4(msg1,msg2,msg3,msg4)
	#endif
#endif
	
#ifdef	DEBUG
	#ifndef	q5
	#define	q5(msg1,msg2,msg3,msg4,msg5)	ljw_q9(__FILE__,__LINE__,msg1,msg2,msg3,msg4,msg5);
	#endif
#else
	#ifndef	q5
	#define	q5(msg1,msg2,msg3,msg4,msg5)
	#endif
#endif
	
#ifdef	DEBUG
	#ifndef	q6
	#define	q6(msg1,msg2,msg3,msg4,msg5,msg6)	ljw_q9(__FILE__,__LINE__,msg1,msg2,msg3,msg4,msg5,msg6);
	#endif
#else
	#ifndef	q6
	#define	q6(msg1,msg2,msg3,msg4,msg5,msg6)
	#endif
#endif
	
#ifdef	DEBUG
	#ifndef	q7
	#define	q7(msg1,msg2,msg3,msg4,msg5,msg6,msg7)	ljw_q9(__FILE__,__LINE__,msg1,msg2,msg3,msg4,msg5,msg6,msg7);
	#endif
#else
	#ifndef	q7
	#define	q7(msg1,msg2,msg3,msg4,msg5,msg6,msg7)
	#endif
#endif
	
#ifdef	DEBUG
	#ifndef	q8
	#define	q8(msg1,msg2,msg3,msg4,msg5,msg6,msg7,msg8)	ljw_q9(__FILE__,__LINE__,msg1,msg2,msg3,msg4,msg5,msg6,msg7,msg8);
	#endif
#else
	#ifndef	q8
	#define	q8(msg1,msg2,msg3,msg4,msg5,msg6,msg7,msg8)
	#endif
#endif
	
#ifdef	DEBUG
	#ifndef	q9
	#define	q9(msg1,msg2,msg3,msg4,msg5,msg6,msg7,msg8,msg9)	ljw_q9(__FILE__,__LINE__,msg1,msg2,msg3,msg4,msg5,msg6,msg7,msg8,msg9);
	#endif
#else
	#ifndef	q9
	#define	q9(msg1,msg2,msg3,msg4,msg5,msg6,msg7,msg8,msg9)
	#endif
#endif
	
#ifdef	DEBUG
	void	ljw_q0(char	*program, int	line);
	
	void	ljw_q1(char	*program, int	line, char *msg);
	
	void	ljw_q9(char	*program, int	line, char *msg, ...);
#endif

/*	-------------------------------------------- */
/*	Use the following declarations for indexing	*/
/*	functions.							*/
/*	-------------------------------------------- */
int   i_index(ljw_index *index, int options, int num_priorities);
int   ui_index(ljw_index *index);
int   scan_index(ljw_index *index, void display_funct(U));
int   num_pfs(ljw_index *index);
long  num_entries(ljw_index *index);

int   ainsert(ljw_index *index, char *K, int len, U data_pointer);
int   uinsert(ljw_index *index, U *K, int len, U data_pointer);
int	 rinsert(U *org, char *K, int ct, U d_pointer);
int   encode31(U *result, char *K, int num_bits);

int   adelete(ljw_index *index, char *key, int len );
int   udelete(ljw_index *index, U *key, int len );
int   stp(ljw_cursor *cursor, int priority_number, long priority);
int   afind(ljw_index *index, char *key, int len, U *data_pointer);
int   ufind(ljw_index *index, U *key, int len, U *data_pointer);
int	 rfind(U *org, char *K, int ct, U *d_pointer);
int   fprefix(ljw_index *index, char *key, int len,
			 int *match_count, U *data_pointer);	
int   fwprefix(ljw_cursor *cursor, ljw_index *index, 
			char *key, int len,
		 	int *match_count, U *data_pointer);
int   afindc(ljw_cursor *cursor, ljw_index *index, char *key,
		 int len);
int   ufindc(ljw_cursor *cursor, ljw_index *index, U *key,
		 int len);
int	idlt(ljw_cursor *cursor, ljw_index *index, char *K, int len);
int	idng(ljw_cursor *cursor, ljw_index *index, char *K, int len);
#define	id_le	idng
int	ideq(ljw_cursor *cursor, ljw_index *index, char *K, int len);
int	idne(ljw_cursor *cursor, ljw_index *index, char *K, int len);
int	idge(ljw_cursor *cursor, ljw_index *index, char *K, int len);
int	idgt(ljw_cursor *cursor, ljw_index *index, char *K, int len);
int	idioo(ljw_cursor *cursor, ljw_index *index,
	char *K1, int L1, char *K2, int L2);
int   idioc(ljw_cursor *cursor, ljw_index	*index,
	char *K1, int L1, char *K2, int L2);
int   idico(ljw_cursor *cursor, ljw_index *index,
	char *K1, int L1, char *K2, int L2);
int   idicc(ljw_cursor *cursor, ljw_index *index,
	char *K1, int L1, char *K2, int L2);
int   idintsec(ljw_cursor *result_cursor, ljw_cursor *cursor1,
	ljw_cursor *cursor2);
int   idunion(ljw_cursor *result_cursor, ljw_cursor *cursor1, 
	ljw_cursor *cursor2);
int   idsans(ljw_cursor *result_cursor, ljw_cursor *cursor1,
      ljw_cursor *cursor2);
int   id_pf_of(ljw_cursor	*result_cursor, ljw_index *index,	
		char *K, int len);
int   id_pf_by(ljw_cursor	*cursor, ljw_index *index,
		char *K, int len);
int   i_cursor(ljw_cursor *cursor, ljw_index *index);
int   ui_cursor(ljw_cursor *cursor);
int   get_key(ljw_cursor *cursor, char** key,int	*len);
int   get_data(ljw_cursor *cursor, U *data_pointer);
long   gtp(ljw_cursor *cursor, int priority_number);
int   next(ljw_cursor *cursor, U *data_pointer);
int   fmp(ljw_cursor *cursor, int priority_number);
int rambam_init(long , long);

/*	------------------------------------------------------	*/
/*	The following are utility functions.				*/
/*	------------------------------------------------------	*/

int	ljw_rdf(char *file_name, unsigned char **byte_string);
/*	------------------------------------------------------	*/
/*	Read a file, file_name, into memory at byte_string,	*/
/*	and return the size of the file in memory.			*/
/*	It uses malloc to allocate byte_string.				*/
/*	It returns zero if it did not read the file.			*/
/*	------------------------------------------------------	*/

int	ljw_rdf4(char *file_name, unsigned char **byte_string);
/*	------------------------------------------------------	*/
/*	Same as above, but leave a 4-byte border at the front	*/
/*	and the end of the file in memory.  Return the actual	*/
/*	number of bytes read.  Store the pointer (**byte_string)*/
/*	to the 4-byte border on the front of the file in memory.*/
/*	------------------------------------------------------	*/
#endif

#ifndef	ljw_invalid
extern	int	ljw_invalid;	
/*23456789 123456789 123456789 123456789 123456789 123456789 12*/
#endif
#ifndef	qvect_t
#define	qvect_t(name,Vect_t)				      {	\
q3("--------------\n                 vect_t: x%lx var: %s",Vect_t,name);\
if ((Vect_t) == 0L)					{	\
q1("---- NULL POINTER ----");					\
							}	\
else							{	\
q2("op:  %d",Vect_t->op);					\
q2("flags: %d",Vect_t->flags);					\
q2("index: x%lx",Vect_t->index);				\
q2("loc:   x%lx",Vect_t->loc);					\
q2("shp:   x%lx",Vect_t->shp);					\
q2("left:   x%lx",Vect_t->left);				\
q2("ident:   x%lx",Vect_t->ident);				\
q2("right:   x%lx",Vect_t->right);			}     }
#endif

#ifndef	qident
#define	qident(name,Ident)				     {	\
char	some_char[32];						\
q3("--------------\n                 ident: x%lx var: %s",Ident,name);	\
if ((Ident) == 0L)					{	\
q1("---- NULL POINTER ----");					\
							}	\
else							{	\
q2("string: %s",Ident->string);					\
q2("type: %d",Ident->type);					\
sprintf(some_char,"%f",Ident->value);				\
q2("value: %s",some_char);					\
q2("index: %d",Ident->index);					\
q2("flags: %d",Ident->flags);					\
q2("Ident->array.dim = x%lx",Ident->array.dim);			\
q2("Ident->array.cnst = x%lx",Ident->array.cnst);		\
q2("Ident->array.rav = x%lx",Ident->array.rav);			\
q2("Ident->array.shp = x%lx",Ident->array.shp);			\
q2("Ident->array.rule = x%lx",Ident->array.rule);		\
							}    }
#endif

#ifndef	qsexpr
#define	qsexpr(name,Sexpr)					\
q2("---------------\n                s_expr_t: x%lx var: %s",Sexpr,name);\
q2("op: %d",Sexpr->op);						\
if ((Sexpr) == 0L)					{	\
q1("---- NULL POINTER ----");					\
							}	\
else							{	\
q2("flags: %d",Sexpr->flags)					\
q2("s_expr_t left: x%lx",Sexpr->left);				\
q2("s_expr_t right: x%lx",Sexpr->right);			\
q2("ident: x%lx",Sexpr->ident);				}
#endif
