# NovPython
Simple python interpreter for CS 4450 - It works especially well in November. 

# How to manually compile?
flex lex.l
bison -vdty syntax.y
g++ lex.yy.c y.tab.c -o nov

# How to compile python source code?
### 