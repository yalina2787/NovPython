%{
#include <stdio.h>
#include <math.h>
#include "nov-python.hpp"
#include "parser.hpp"

extern int line_no;
extern int yyterminate();
extern int yylex();

void yyerror(const char* msg) {
    cout<<"Error, line "<<line_no<<", syntax error"<<endl; 
}
%}

%union {
    int intValue;
    bool boolValue;
    double floatValue;
    char* identValue;
    char* stringValue;
    NovExpression* expression;
    NovStatement* statement;
    NovStatementList* statementList;
    NovProgram* program;
}

%token<boolValue>       T_TRUE 
%token<boolValue>       T_FALSE 
%token<intValue>        T_INT 
%token<floatValue>      T_FLOAT
%token<stringValue>     T_STRING
%token<identValue>      T_IDENT
%token                  T_SPACE
%token                  T_PLUS_EQ
%token                  T_PRINT
%token                  T_INDENT
%token                  T_UNINDENT
%token                  T_IF
%token                  T_ELSE
%token                  T_WHILE
%token                  T_FOR
%token                  T_RANGE
%token                  T_IN
%token                  T_MINUS_EQ
%token                  T_TIMES_EQ
%token                  T_DIVIDE_EQ
%token                  T_MOD_EQ
%token                  T_XOR_EQ
%token                  T_LESS_EQ
%token                  T_GREATER_EQ
%token                  T_EQUAL
%token                  T_INEQUAL
%token                  T_ERROR

%left '<' '>' T_LESS_EQ T_GREATER_EQ T_EQUAL T_INEQUAL
%left '+' '-'
%left '*' '/' '%' 
%left '^'

%type<program>          Program
%type<statementList>    StatementList
%type<statementList>    WStatementList
%type<statement>        Statement
%type<statement>        Assignment
%type<statement>        StmtIfElse
%type<statement>        StmtWhile
%type<statement>        StmtFor
%type<expression>       Expression



%%
Program         :   StatementList                   { $$ = new NovProgram($1); $$->evaluate();}
                |   /* empty */                     { /* empty */ }
                ;

WStatementList  :   T_INDENT WStatementList T_UNINDENT        { $$ = $2;}
                |   T_INDENT StatementList T_UNINDENT         { $$ = $2;}
                ;

StatementList   :   StatementList Statement         { $1->push($2); $$ = $1;}
                |   Statement                       { $$ = new NovStatementList(); $$->push($1);}
                ;

Statement       :   Assignment                      { }
                |   StmtIfElse                      { }
                |   StmtWhile                       { }
                |   StmtFor                         { }
                ;
            

Assignment      :   T_IDENT '=' Expression          { $$ = new NovAssignment($1, "=", $3); delete [] $1; }
                |   T_IDENT T_PLUS_EQ Expression    { $$ = new NovAssignment($1, "+=", $3); delete [] $1; }
                |   T_IDENT T_MINUS_EQ Expression   { $$ = new NovAssignment($1, "-=", $3); delete [] $1; }
                |   T_IDENT T_TIMES_EQ Expression   { $$ = new NovAssignment($1, "*=", $3); delete [] $1; }
                |   T_IDENT T_DIVIDE_EQ Expression  { $$ = new NovAssignment($1, "/=", $3); delete [] $1; }
                |   T_IDENT T_MOD_EQ Expression     { $$ = new NovAssignment($1, "%=", $3); delete [] $1; }
                |   T_IDENT T_XOR_EQ Expression     { $$ = new NovAssignment($1, "^=", $3); delete [] $1; }
                |   T_PRINT '(' Expression ')'      { $$ = new NovAssignment("", "print", $3); }
                ; 

StmtIfElse      :   T_IF Expression ':' WStatementList T_ELSE ':' WStatementList { $$ = new NovStmtIfElse($2, $4, $7); }
                |   T_IF Expression ':' WStatementList { $$ = new NovStmtIfElse($2, $4, NULL); }
                ;

StmtWhile       :   T_WHILE Expression ':' WStatementList { $$ = new NovStmtWhile($2, $4); }
                ;

StmtFor         :   T_FOR T_IDENT T_IN T_RANGE '(' Expression ',' Expression ')' ':' WStatementList { $$ = new NovStmtFor($2, $6, $8, $11); }
                ;

Expression      :   Expression '+' Expression           { $$ = new NovExpression($1, "+" ,$3); }
                |   Expression '-' Expression           { $$ = new NovExpression($1, "-" ,$3); }
                |   Expression '*' Expression           { $$ = new NovExpression($1, "*" ,$3); }
                |   Expression '/' Expression           { $$ = new NovExpression($1, "/" ,$3); }
                |   Expression '%' Expression           { $$ = new NovExpression($1, "%" ,$3); }
                |   Expression '^' Expression           { $$ = new NovExpression($1, "^" ,$3); }
                |   Expression '<' Expression           { $$ = new NovExpression($1, "<" ,$3); }
                |   Expression '>' Expression           { $$ = new NovExpression($1, ">" ,$3); }
                |   Expression T_LESS_EQ Expression     { $$ = new NovExpression($1, "<=" ,$3); }
                |   Expression T_GREATER_EQ Expression  { $$ = new NovExpression($1, ">=" ,$3); }
                |   Expression T_EQUAL Expression       { $$ = new NovExpression($1, "==" ,$3); }
                |   Expression T_INEQUAL Expression     { $$ = new NovExpression($1, "!=" ,$3); }
                |   T_INT                               { $$ = new NovConstant(Value($1)); }
                |   T_FLOAT                             { $$ = new NovConstant(Value($1)); }
                |   T_STRING                            { $$ = new NovConstant(Value(string($1))); delete [] $1; }
                |   T_TRUE                              { $$ = new NovConstant(Value(true)); }
                |   T_FALSE                             { $$ = new NovConstant(Value(false)); }
                |   T_IDENT                             { $$ = new NovIdent(string($1)); delete [] $1; }
                |   '(' Expression ')'                  { $$ = $2; }
                ;

%%
