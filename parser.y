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
    NovProgram* program;
}

%token<boolValue>       T_TRUE 
%token<boolValue>       T_FALSE 
%token<intValue>        T_INT 
%token<floatValue>      T_FLOAT
%token<identValue>      T_IDENT
%token                  T_SPACE
%token                  T_PLUS_EQ

%left '<'
%left '+' '-'
%left '*' '/' '%' 
%left '^'

%type<program>          Program
%type<statementList>    StatementList
%type<statement>        Statement
%type<statement>        Assignment
%type<expression>       Expression


%%
Program         :   /* empty */                         { /* empty */ }
                |   StatementList                       { $$ = new NovProgram($1); $$->evaluate();}
                ;

StatementList   :   StatementList Statement        { cout<<"Statement\\n"<<endl; $1->push($2); $$ = $1;}
                |   Statement                           { $$ = new NovStatementList(); $$->push($1);}
                ;

Statement       :   Assignment                      { }
                ;

Assignment      :   T_IDENT '=' Expression          { $$ = new NovAssignment($1, "=", $3); delete [] $1; }
                |   T_IDENT T_PLUS_EQ Expression    { $$ = new NovAssignment($1, "+=", $3); delete [] $1; }
                ;
 
Expression      :   Expression '+' Expression       { $$ = new NovExpression($1, '+' ,$3); }
                |   Expression '-' Expression       { $$ = new NovExpression($1, '-' ,$3); }
                |   Expression '*' Expression       { $$ = new NovExpression($1, '*' ,$3); }
                |   Expression '/' Expression       { $$ = new NovExpression($1, '/' ,$3); }
                |   Expression '^' Expression       { $$ = new NovExpression($1, '^' ,$3); }
                |   Expression '<' Expression       { $$ = new NovExpression($1, '<' ,$3); }
                |   T_INT                           { $$ = new NovConstant(Value($1)); }
                |   T_FLOAT                         { $$ = new NovConstant(Value($1)); }
                |   T_TRUE                          { $$ = new NovConstant(Value(true)); }
                |   T_FALSE                         { $$ = new NovConstant(Value(false)); }
                |   T_IDENT                         { $$ = new NovIdent($1); delete [] $1; }
                ;

%%
