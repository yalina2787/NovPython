%{
#include <stdio.h>
#include <math.h>
#include "nov-python.hpp"
#include "parser.hpp"

extern int yylex();


void yyerror(const char* msg) {}
%}

%union {
    int intValue;
    double floatValue;
    char* identValue;
    NovExpression* expression;
}

%token<intValue>        T_INT 
%token<floatValue>      T_FLOAT
%token<identValue>      T_IDENT

%left '<'
%left '+' '-'
%left '*' '/' '%' 
%left '^'

%type<expression> E

%%

S   :   S E '\n'        { Value result = $2->evaluate(); cout<<"Answer:"<<result<<endl;}
    |   /* empty */     { /* empty */ }
    ;

E   :   E '+' E         { $$ = new NovExpression($1, '+' ,$3); }
    |   E '-' E         { $$ = new NovExpression($1, '-' ,$3); }
    |   E '*' E         { $$ = new NovExpression($1, '*' ,$3); }
    |   E '/' E         { $$ = new NovExpression($1, '/' ,$3); }
    |   E '^' E         { $$ = new NovExpression($1, '^' ,$3); }
    |   E '<' E         { $$ = new NovExpression($1, '<' ,$3); }
    |   T_INT           { $$ = new NovConstant(Value($1)); }
    |   T_FLOAT         { $$ = new NovConstant(Value($1)); }
    |   T_IDENT         { $$ = new NovIdent($1); }
    ;

%%
