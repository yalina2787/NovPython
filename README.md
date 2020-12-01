# NovPython
Simple python interpreter for CS 4450 - It works especially well in November. 

# Supported Features in NovPython Interpreter
## If-Else Blocks
```
if 10 % 2 == 0:
  print("Even")
else:
  print("Odd")
```

## Variable Definitions
```
i = 0
name = "NovPython"
```
## While/For Loops
```
i = 0
while i < 10:
  i+=1
  print(i)

for j in range(5, 100/2):
  print(j)
```

## Arithmetic Operators:
```
print(5 + 6 * 7 / (8 - 5))
print(1 ^ 10)
print(10 % 2)
```

## Assignment Operators:
```
a = 0
a^=1
a+=10
a-=2
a*=3
a/=1
a%=2
```

## Conditional Statements
```
print(3<5)
print(3<=5)
print(3>5)
print(3>=5)
print(3==5)
print(3!=5)
```

## Comments
```
# This is a comment
# This is another comment
print ("This is a comment test. ")  # comment
```

## Output
```
print(1+2)  
print("This project is very interesting, I like it very much! ")
print("Have a wonderful day!")
```

## Lexical & Syntax Error Message
```
b = 1 @ 2 => Error: line 4, unrecognized symbol:'@'
iff a == 5: => Error, line 5, syntax error
```

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
