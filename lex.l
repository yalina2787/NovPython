%{
/*
 * Nov Python 1.0
 */
int test = 10;
%}



%%
"+"              { printf("'%c'", yytext[0]); return yytext[0]; }
"-"              { printf("'%c'", yytext[0]); return yytext[0]; }
"*"              { printf("'%c'", yytext[0]); return yytext[0]; }
"/"              { printf("'%c'", yytext[0]); return yytext[0]; }
"^"              { printf("'%c'", yytext[0]); return yytext[0]; }
"="              { printf("'%c'", yytext[0]); return yytext[0]; }
[0-9]+           { printf("Int"); return 300; }
[0-9]*\.[0-9]+   { printf("Float"); return 301; }
[ \t\n]          { printf(" "); return 302; }
%%

int main(int argc, char* argv[]) {
    int type = 0;
    while (type = yylex()) {
		printf(": '%s'\n", yytext);
	}
    return 0;
}

int yywrap() { 
    return 1; 
}
