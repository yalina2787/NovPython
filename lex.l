%{
/*
 * Nov Python 1.0
 */

#include <iostream>
#include <string>
#include "types.h"
#include "nov-python.hpp"
#include "parser.hpp"

using namespace std;

extern int line_no;
%} 

%%
"#"[^\r\n]*             { /* comments */   }
"\n"                    { line_no++; /*return yytext[0];*/ }
[ \t\n]                 { /* whitespace */ }
[+*-/^%=#<>():]         { return yytext[0]; }
"+="                    { return T_PLUS_EQ; }
"-="                    { return T_MINUS_EQ; }
"*="                    { return T_TIMES_EQ; }
"/="                    { return T_DIVIDE_EQ; }
"%="                    { return T_MOD_EQ; }
"^="                    { return T_POW_EQ; }
"<="                    { return T_LESS_EQ; }
">="                    { return T_GREATER_EQ; }
"=="                    { return T_EQUAL; }
"!="                    { return T_INEQUAL; }
"True"                  { return T_TRUE; }
"False"                 { return T_FALSE; }
"print"                 { return T_PRINT; } 
"if"                    { return T_IF; }
"else"                  { return T_ELSE; }
"while"                 { return T_WHILE; }
"for"                   { return T_FOR; }
[0-9]+                  { yylval.intValue = atoi(yytext); return T_INT; }
[0-9]*\.[0-9]+          { yylval.floatValue = atof(yytext); return T_FLOAT; }
[_a-zA-Z][a-zA-Z0-9]*   { yylval.identValue = new char[strlen(yytext)+1]; strcpy(yylval.identValue, yytext); return T_IDENT; }
(\"[^\"\n]*\")          { yylval.stringValue = new char[strlen(yytext)-1]; strncpy(yylval.stringValue, yytext+1, strlen(yytext)-2); return T_STRING; }

.                       { return T_ERROR; }
%%

int yywrap() { 
    return 1; 
}
