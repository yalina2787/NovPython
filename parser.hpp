/* A Bison parser, made by GNU Bison 2.3.  */

/* Skeleton interface for Bison's Yacc-like parsers in C

   Copyright (C) 1984, 1989, 1990, 2000, 2001, 2002, 2003, 2004, 2005, 2006
   Free Software Foundation, Inc.

   This program is free software; you can redistribute it and/or modify
   it under the terms of the GNU General Public License as published by
   the Free Software Foundation; either version 2, or (at your option)
   any later version.

   This program is distributed in the hope that it will be useful,
   but WITHOUT ANY WARRANTY; without even the implied warranty of
   MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
   GNU General Public License for more details.

   You should have received a copy of the GNU General Public License
   along with this program; if not, write to the Free Software
   Foundation, Inc., 51 Franklin Street, Fifth Floor,
   Boston, MA 02110-1301, USA.  */

/* As a special exception, you may create a larger work that contains
   part or all of the Bison parser skeleton and distribute that work
   under terms of your choice, so long as that work isn't itself a
   parser generator using the skeleton or a modified version thereof
   as a parser skeleton.  Alternatively, if you modify or redistribute
   the parser skeleton itself, you may (at your option) remove this
   special exception, which will cause the skeleton and the resulting
   Bison output files to be licensed under the GNU General Public
   License without this special exception.

   This special exception was added by the Free Software Foundation in
   version 2.2 of Bison.  */

/* Tokens.  */
#ifndef YYTOKENTYPE
# define YYTOKENTYPE
   /* Put the tokens into the symbol table, so that GDB and other debuggers
      know about them.  */
   enum yytokentype {
     T_TRUE = 258,
     T_FALSE = 259,
     T_INT = 260,
     T_FLOAT = 261,
     T_STRING = 262,
     T_IDENT = 263,
     T_SPACE = 264,
     T_PLUS_EQ = 265,
     T_PRINT = 266,
     T_INDENT = 267,
     T_UNINDENT = 268,
     T_IF = 269,
     T_ELSE = 270,
     T_WHILE = 271,
     T_FOR = 272,
     T_RANGE = 273,
     T_IN = 274,
     T_MINUS_EQ = 275,
     T_TIMES_EQ = 276,
     T_DIVIDE_EQ = 277,
     T_MOD_EQ = 278,
     T_XOR_EQ = 279,
     T_LESS_EQ = 280,
     T_GREATER_EQ = 281,
     T_EQUAL = 282,
     T_INEQUAL = 283,
     T_ERROR = 284
   };
#endif
/* Tokens.  */
#define T_TRUE 258
#define T_FALSE 259
#define T_INT 260
#define T_FLOAT 261
#define T_STRING 262
#define T_IDENT 263
#define T_SPACE 264
#define T_PLUS_EQ 265
#define T_PRINT 266
#define T_INDENT 267
#define T_UNINDENT 268
#define T_IF 269
#define T_ELSE 270
#define T_WHILE 271
#define T_FOR 272
#define T_RANGE 273
#define T_IN 274
#define T_MINUS_EQ 275
#define T_TIMES_EQ 276
#define T_DIVIDE_EQ 277
#define T_MOD_EQ 278
#define T_XOR_EQ 279
#define T_LESS_EQ 280
#define T_GREATER_EQ 281
#define T_EQUAL 282
#define T_INEQUAL 283
#define T_ERROR 284




#if ! defined YYSTYPE && ! defined YYSTYPE_IS_DECLARED
typedef union YYSTYPE
#line 16 "parser.y"
{
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
/* Line 1529 of yacc.c.  */
#line 119 "parser.hpp"
	YYSTYPE;
# define yystype YYSTYPE /* obsolescent; will be withdrawn */
# define YYSTYPE_IS_DECLARED 1
# define YYSTYPE_IS_TRIVIAL 1
#endif

extern YYSTYPE yylval;

