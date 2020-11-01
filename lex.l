%{
/*
 * Nov Python 1.0
 */
int test = 10;
%}



%%
"+"      { return yytext[0]; }
"-"      { return yytext[0]; }
"*"      { return yytext[0]; }
"/"      { return yytext[0]; }
%%

int yywrap()
{ return 1; }
