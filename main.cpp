#include <stdio.h>
#include <iostream>
#include <string>
#include "types.h"

using namespace std;

extern int yylex();
extern int yyparse();
extern void yyterminate();
extern const char *yytext;
extern FILE *yyin;
extern FILE *yyout;

int line_no = 0;

void parse_error(string msg, int line_no)
{
    cout << endl;
    cout << line_no << ": error: " << msg;
}

int main(int argc, char *argv[])
{

    if (argc > 1)
    {
        yyin = fopen(argv[1], "r+");
        if (yyin == NULL)
        {
            parse_error("failed to load file", 0);
            return 0;
        }
    }
    //yyout = stdout;

    yyparse();

    //return yyparse();
    /*
    int type = 0;

    while ((type = yylex()))
    {
        if (type == T_ERROR)
        {
            parse_error("undefined token", line_no);
            return 0;
        }
        else if (strcmp(yytext, "\n") == 0)
        {
            printf("=> \\n\n");
        }
        else if (strcmp(yytext, " ") == 0)
        {
            printf("=> '%s'\n", yytext);
        }
        else
        {
            printf("=> %s\n", yytext);
        }
    }*/
    return 0;
}