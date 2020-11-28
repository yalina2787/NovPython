%{
#include <stdio.h>
#include "nov-python.hpp"

extern int yylex();

void yyerror(const char* msg) {}
%}

%token   T_INT 
%token   T_FLOAT

%left '+' '-'
%left '*' '/'


%%

S   :   S E '\n'        { printf("ans = %d\n", $2); }
    |   /* empty */     { /* empty */ }
    ;

E   :   E '+' E         { $$ = $1 + $3; }
    |   E '-' E         { $$ = $1 - $3; }
    |   E '*' E         { $$ = $1 * $3; }
    |   E '/' E         { $$ = $1 / $3; }
    |   T_INT           { $$ = $1; }
    |   T_FLOAT         { $$ = $1; }
    |   '(' E ')'       { $$ = $2; }
    ;

%%
