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

{NUMBER}	{ yylval.ival = atoi (yytext); return (NUMBER1); }
{REAL}		{ yylval.dval = atof (yytext); return (FLOAT1); }
{ID}		{ yylval.cval = (char *) get_mem (strlen(yytext));
		  sprintf (yylval.cval, "%s", yytext);
		  return (check_reserved(yytext)); }

";"		{ yylval.cval = yytext; return (';'); }
","		{ yylval.cval = yytext; return (','); }
"("		{ yylval.cval = yytext; return ('('); }
")"		{ yylval.cval = yytext; return (')'); }
"{"             { yylval.cval = yytext; return ('{'); }
"}"		{ yylval.cval = yytext; return ('}'); }

"<"		{ yylval.cval = yytext; return ('<'); }
"<="		{ yylval.cval = yytext; return (LTE1); }
">"		{ yylval.cval = yytext; return ('>'); }

"+"		{ yylval.cval = yytext; return ('+'); }
"-"		{ yylval.cval = yytext; return ('-'); }
"*"		{ yylval.cval = yytext; return ('*'); }
"/"		{ yylval.cval = yytext; return ('/'); }
"="		{ yylval.cval = yytext; return ('='); }
"^"		{ yylval.cval = yytext; return ('^'); }

[ \t]+		{ /* do nothing */ }
[\n]		{ ++line_num; }
"#"[^\n]*       { /* do nothing */ }		
