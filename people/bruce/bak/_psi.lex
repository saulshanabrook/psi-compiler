%{
#include "psi.h"
#include "ops.h"
#include "_psi.tab.h"

int line_num = 1;
%}

DIGIT		[0-9]
ID		[_a-zA-Z][_a-zA-Z0-9]*
NUMBER		{DIGIT}+
REAL1		{DIGIT}+\.?([eE][-+]?{DIGIT}+)?
REAL2		{DIGIT}*\.{DIGIT}+([eE][-+]?{DIGIT}+)?
REAL		{REAL1}|{REAL2}
%%

{NUMBER}	{ return (NUMBER1); }
{REAL}		{ return (FLOAT1); }
{ID}		{ return (check_reserved(yytext)); }

";"		{ return (';'); }
","		{ return (','); }
"("		{ return ('('); }
")"		{ return (')'); }
"{"             { return ('{'); }
"}"		{ return ('}'); }

"<"		{ return ('<'); }
"<="		{ return (LTE1); }
">"		{ return ('>'); }

"+"		{ return ('+'); }
"-"		{ return ('-'); }
"*"		{ return ('*'); }
"/"		{ return ('/'); }
"="		{ return ('='); }
"^"		{ return ('^'); }

[ \t]+		{ /* do nothing */ }
[\n]		{ ++line_num; }
"#"[^\n]*       { /* do nothing */ }		
