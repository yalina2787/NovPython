%{
/*
 * Nov Python 1.0
 */
#define T_PLUS_EQ       351
#define T_MINUS_EQ      352
#define T_TIMES_EQ      353
#define T_DIVIDE_EQ     354
#define T_MOD_EQ        355
#define T_POW_EQ        356
#define T_LESS_EQ       371
#define T_GREATER_EQ    373
#define T_EQUAL         374
#define T_INEQUAL       375
#define T_INT           401
#define T_FLOAT         402
#define T_SPACE         403
#define T_IDENT         404
#define T_PRINT         500
#define T_IF            501
#define T_ELSE          502
#define T_WHILE         503
#define T_FOR           504
%}


%%
[+*-/^%=#<>():\n]       { return yytext[0]; }
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
[ \t\n]                 { return T_SPACE; }
[_a-zA-Z][a-zA-Z0-9]*   { return T_IDENT; }
%%

int main(int argc, char* argv[]) {
    int type = 0;
    while (type = yylex()) {
        if(strcmp(yytext, "\n")==0) {
            printf("'\\n'");
        } else {
		    printf("'%s'\n", yytext);
        }
	}
    return 0;
}

int yywrap() { 
    return 1; 
}
