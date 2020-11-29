%{
#include <stdio.h>
#include <math.h>
#include "nov-python.hpp"

extern int yylex();

void yyerror(const char* msg) {}
%}

%union {
	double floatValue;
    NovExpression* expression
}

%token   T_INT 
%token   T_FLOAT

%left '+' '-'
%left '*' '/' '%' 
%left '^'

%type<floatValue> S
%type<floatValue> E
%type<floatValue> T_INT
%type<floatValue> T_FLOAT

%%

S   :   S E '\n'        { printf("ans = %d\n", $2); }
    |   /* empty */     { /* empty */ }
    ;

E   :   E '+' E         { $$ = new NovExpression($1, '+', $3); }
    |   E '-' E         { $$ = $1 - $3; }
    |   E '*' E         { $$ = $1 * $3; }
    |   E '/' E         { $$ = $1 / $3; }
    |   E '%' E         { $$ = $1 % $3; }
    |   E '^' E         { $$ = pow($1, $3); }
    |   T_INT           { $$ = $1; }
    |   T_FLOAT         { $$ = $1; }
    |   '(' E ')'       { $$ = $2; }
    ;

%%
