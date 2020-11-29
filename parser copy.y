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
    bool boolValue;
    double floatValue;
    char* identValue;
    NovExpression* expression;
    NovStatement* statement;
    NovStatementList* statementList;
}

%token<boolValue>       T_TRUE 
%token<boolValue>       T_FALSE 
%token<intValue>        T_INT 
%token<floatValue>      T_FLOAT
%token<identValue>      T_IDENT
%token                  T_SPACE

%left '<'
%left '+' '-'
%left '*' '/' '%' 
%left '^'

%type<expression> E
%type<statement> S
%type<statementList> SL

%%

SL  :   SL S '\n'       {cout<<"Statement\\n"<<endl;}
    |   SL S ';'        {cout<<"Statement;"<<endl;}
    |   /* empty */     { /* empty */ }
    ;

S   :   E '\n'          { cout<<"??"<<endl;Value result = $2->evaluate(); cout<<"Answer:"<<result<<endl;}
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
    |   T_TRUE          { $$ = new NovConstant(Value(true)); }
    |   T_FALSE         { $$ = new NovConstant(Value(false)); }
    |   T_IDENT         { $$ = new NovIdent($1); delete [] $1; }
    ;

%%
