%{
#include <stdio.h>
#include "parser.tab.h"
%}

%option warn noyywrap nodefault
%option header-file="lex.yy.h"

SPACE [ \t]
RPAR \]
LPAR \[
COL ;
DIGIT [0-9]
FLOAT [0-9]+\.[0-9]+

%%

{SPACE}  {  }
{COL} { yylloc.last_line += 1; 
    //printf("COL lexer %d\n", yylloc.first_column);
    if ( !yylloc.first_column )
        yylloc.first_column = yylloc.last_column; 
    else if (yylloc.first_column != yylloc.last_column)
        yylloc.first_column = -1;  
    yylloc.last_column = 0;
    return yytext[0]; 
}
"+"    { return ADD; }
"-"    { return SUB; }
"*"    { return MUL; }
"/"    { return DIV; }
{LPAR} { yylloc.first_column = 0; yylloc.last_column = 0; yylloc.last_line = 0; return LPAR; }
{RPAR} { return RPAR; }
{DIGIT}+ {  yylloc.last_column += 1; yylval.ival = atof(yytext); return NUM; }
{FLOAT} { yylval.dval = atof(yytext); return FLOAT; }
\n     { return EOL; }
.      { printf("What is this: %s.\n", yytext); }
%%
