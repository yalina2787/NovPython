%{
/*
 * Nov Python 1.0
 */

#include <iostream>
#include <string>
#include "nov-python.hpp"
#include "parser.hpp"

using namespace std;

extern int line_no;

/* globals to track current indentation */
int current_line_indent = 0;   /* indentation of the current line */
int indent_level = 0;          /* indentation level passed to the parser */

#define YY_USER_INIT { \
        BEGIN(indent); \
}

%}

%x indent 
%s normal 

%%
<indent>" "      { current_line_indent++; }
<indent>"\t"     { current_line_indent = (current_line_indent + 8) & ~7; }
<indent>"\n"     { current_line_indent = 0; /*ignoring blank line */ }
<indent><<EOF>>   { 
                   if (current_line_indent > indent_level) {
                       indent_level++;
                       return T_INDENT;
                   } else if (current_line_indent < indent_level) {
                       indent_level--;
                       return T_UNINDENT;
                   } else {
                      yyterminate();
                   }
                 }
<indent>.        {
                   unput(*yytext);
                   if (current_line_indent > indent_level) {
                       indent_level++;
                       return T_INDENT;
                   } else if (current_line_indent < indent_level) {
                       indent_level--;
                       return T_UNINDENT;
                   } else {
                       //cout<<"To Normal Mode"<<endl;
                       BEGIN(normal);
                   }
                 }

<normal>"\n"                    { current_line_indent = 0; line_no++; BEGIN(indent); }     
<normal>"#"[^\r\n]*             { /* comments */   }
<normal>" "                     { /* whitespace */ }
<normal>[+*-/^%=#<>():]         { return yytext[0]; }
<normal>"+="                    { return T_PLUS_EQ; }
<normal>"-="                    { return T_MINUS_EQ; }
<normal>"*="                    { return T_TIMES_EQ; }
<normal>"/="                    { return T_DIVIDE_EQ; }
<normal>"^="                    { return T_XOR_EQ; }
<normal>"%="                    { return T_MOD_EQ; }
<normal>"<="                    { return T_LESS_EQ; }
<normal>">="                    { return T_GREATER_EQ; }
<normal>"=="                    { return T_EQUAL; }
<normal>"!="                    { return T_INEQUAL; }
<normal>"True"                  { return T_TRUE; }
<normal>"False"                 { return T_FALSE; }
<normal>"print"                 { return T_PRINT; } 
<normal>"range"                 { return T_RANGE; } 
<normal>"if"                    { return T_IF; }
<normal>"else"                  { return T_ELSE; }
<normal>"while"                 { return T_WHILE; }
<normal>"for"                   { return T_FOR; }
<normal>"in"                    { return T_IN; }
<normal>[0-9]+                  { yylval.intValue = atoi(yytext); return T_INT; }
<normal>[0-9]*\.[0-9]+          { yylval.floatValue = atof(yytext); return T_FLOAT; }
<normal>[_a-zA-Z][a-zA-Z0-9]*   { yylval.identValue = new char[strlen(yytext)+1]; strcpy(yylval.identValue, yytext); return T_IDENT; }
<normal>(\"[^\"\n]*\")          { 
                                    int len = strlen(yytext);
                                    yylval.stringValue = new char[len+1]; 
                                    strncpy(yylval.stringValue, yytext+1, len-2); 
                                    yylval.stringValue[len-2]=0;
                                    return T_STRING; 
                                }
<normal>('[^'\n]*')             { 
                                    int len = strlen(yytext);
                                    yylval.stringValue = new char[len+1]; 
                                    strncpy(yylval.stringValue, yytext+1, len-2); 
                                    yylval.stringValue[len-2]=0;
                                    return T_STRING; 
                                }

<normal><<EOF>>                 { current_line_indent = 0; BEGIN(indent); }
<normal>.                       { return T_ERROR; }
%%

int yywrap() { 
    return 1; 
}