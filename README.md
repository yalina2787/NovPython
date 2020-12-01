# NovPython
Simple python interpreter for CS 4450 - It works especially well in November. 

# Compile NovPython
## How to manually compile?
```
flex -o lex.cpp lex.l
bison -d -o parser.cpp parser.y
g++ -o nov parser.cpp lex.cpp nov-python.cpp main.cpp
```
## How to automatically compile?
```
make
```

# How to use NovPython to compile python source code?
```
./nov test/if-else.py
./nov test/vars-def.py
./nov test/while.py
./nov test/for.py
./nov test/arithmetic-op.py
./nov test/assignment-op.py
./nov test/condition-stmt.py
./nov test/comment.py
./nov test/output.py
./nov test/lexical-error.py
./nov test/syntax-error.py
```
