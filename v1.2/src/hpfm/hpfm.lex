%{
#include "math.h"
#include "scanner.e"
#include "hpfm.tab.h"
 
int line_num = 1;
%}
 
DIGIT           [0-9]
ID              [_a-zA-Z][_a-zA-Z0-9]*
NUMBER          {DIGIT}+
REAL1           {DIGIT}+\.?([eE][-+]?{DIGIT}+)?
REAL2           {DIGIT}*\.{DIGIT}+([eE][-+]?{DIGIT}+)?
REAL            {REAL1}|{REAL2}
%%
 
{NUMBER}        { yylval.ival = atoi (yytext); return (NUMBER1); }
{REAL}          { yylval.fval = atof (yytext); return (FLOAT1); }
{ID}            { yylval.cval = yytext; return (check_reserved(yytext)); }
 
":"		{ yylval.cval = yytext; return (':'); }
","             { yylval.cval = yytext; return (','); }
"."             { yylval.cval = yytext; return ('.'); }
"("             { yylval.cval = yytext; return ('('); }
")"             { yylval.cval = yytext; return (')'); }
"::"		{ yylval.cval = yytext; return (DCOLON1); }
"//"		{ yylval.cval = yytext; return (DSLASH1); }
"(/"		{ yylval.cavl = yytext; return (LEFTCONS1); }
"/)"		{ yylval.cavl = yytext; return (RIGHTCONS1); }
 
"<"             { yylval.cval = yytext; return ('<'); }
".LT."		{ yylval.cval = yytext; return ('<'); }
">"             { yylval.cval = yytext; return ('>'); }
".GT."		{ yylval.cval = yytext; return ('>'); }
"<="            { yylval.cval = yytext; return (LE1); }
".LE."		{ yylval.cval = yytext; return (LE1); }
">="            { yylval.cval = yytext; return (GE1); }
".GE."		{ yylval.cval = yytext; return (GE1); }
"/="            { yylval.cval = yytext; return (NE1); }
".NE."		{ yylval.cval = yytext; return (NE1); }
"=="            { yylval.cval = yytext; return (EQ1); }
".EQ."		{ yylval.cval = yytext; return (EQ1); }
 
".NOT."		{ yylval.cval = yytext; return (NOT1); }
".AND."		{ yylval.cval = yytext; return (AND1); }
".OR."		{ yylval.cval = yytext; return (OR1); }
".EQV."		{ yylval.cval = yytext; return (EQV1); }
".NEQV."	{ yylval.cval = yytext; return (NEQV1); }

"**"            { yylval.cval = yytext; return (POWER1); }
"+"             { yylval.cval = yytext; return ('+'); }
"-"             { yylval.cval = yytext; return ('-'); }
"*"             { yylval.cval = yytext; return ('*'); }
"/"             { yylval.cval = yytext; return ('/'); }
"="             { yylval.cval = yytext; return ('='); }

[ \t]+          { /* do nothing */ }
[\n]            { ++line_num; }
