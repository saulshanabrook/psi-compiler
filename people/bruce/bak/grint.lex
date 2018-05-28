%{
#include "math.h"
#include "scanner.e"
#include "grint.tab.h"

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
{REAL}		{ yylval.fval = atof (yytext); return (FLOAT1); }
{ID}		{ yylval.cval = yytext; return (check_reserved(yytext)); }

","		{ yylval.cval = yytext; return (','); }
"."		{ yylval.cval = yytext; return ('.'); }
"("		{ yylval.cval = yytext; return ('('); }
")"		{ yylval.cval = yytext; return (')'); }

"<*"		{ yylval.cval = yytext; return (OVECT1); }
"*>"		{ yylval.cval = yytext; return (CVECT1); }
"<"		{ yylval.cval = yytext; return ('<'); }
">"		{ yylval.cval = yytext; return ('>'); }
"<="		{ yylval.cval = yytext; return (LTE1); }
">="		{ yylval.cval = yytext; return (GTE1); }
"!="		{ yylval.cval = yytext; return (NEQ1); }
"=="		{ yylval.cval = yytext; return (EQU1); }

"&&"		{ yylval.cval = yytext; return (AND1); }
"||"		{ yylval.cval = yytext; return (OR1); }

"^"		{ yylval.cval = yytext; return ('^'); }
"+"		{ yylval.cval = yytext; return ('+'); }
"-"		{ yylval.cval = yytext; return ('-'); }
"*"		{ yylval.cval = yytext; return ('*'); }
"/"		{ yylval.cval = yytext; return ('/'); }
"="		{ yylval.cval = yytext; return ('='); }

[ \t]+		{ /* do nothing */ }
[\n]		{ ++line_num; }
