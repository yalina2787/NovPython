%{
/*
 * Nov Python 1.0
 */

#include "types.h"

extern int line_no;
%} 

%%
"\n"                    { line_no++; return yytext[0]; }
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
"print"                 { return T_PRINT; }
"if"                    { return T_IF; }
"else"                  { return T_ELSE; }
"while"                 { return T_WHILE; }
"for"                   { return T_FOR; }
[0-9]+                  { return T_INT; }
[0-9]*\.[0-9]+          { return T_FLOAT; }
('[^'\n]*')             { return T_STRING; }
(\"[^\"\n]*\")          { return T_STRING; }
[ \t]                   { return T_SPACE; }
[_a-zA-Z][a-zA-Z0-9]*   { return T_IDENT; }
.                       { return T_ERROR; }
%%

int yywrap() { 
    return 1; 
}
