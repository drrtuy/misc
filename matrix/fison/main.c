#include <stdio.h>
#include "parser.tab.h"
#include "lex.yy.h"

extern int yydebug;

int 
main(int argc, char** argv) {

    if(argc > 1)
        yydebug = 1;

//  yyscan_t scanner;

//  yylex_init(&scanner);
//  yyset_in(stdin, scanner);

//  yyparse(scanner);
    yyparse();

//  yylex_destroy(scanner);

  return 0;
}
