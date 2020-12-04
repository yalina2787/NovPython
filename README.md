# 1. NovPython
Simple python interpreter for CS 4450 - It works especially well in November. 

# 2. Requirement
Using C, C++, the external libraries flex and bison to implement a basic Interpreter for Python

# 3. Team information
##### 3.1 Group name: NovemberSurprise
##### 3.2 Group members: Alian Yu (only one member)

# 4. Supported Features in NovPython Interpreter
## 4.1 If-Else Blocks
```
if 10 % 2 == 0:
  print("Even")
else:
  print("Odd")
```

## 4.2 Variable Definitions
```
i = 0
name = "NovPython"
```
## 4.3 While/For Loops
```
i = 0
while i < 10:
  i+=1
  print(i)

for j in range(5, 100/2):
  print(j)
```

## 4.4 Arithmetic Operators (+, -, *, /, %, ^)
```
print(5 + 6 * 7 / (8 - 5))
print(1 ^ 10)
print(10 % 2)
```

## 4.5 Assignment Operators (=, +=, -=, *=, /=, ^=, %=)
```
a = 0
a^=1
a+=10
a-=2
a*=3
a/=1
a%=2
```

## 4.6 Conditional Statements (<, <=, >, >=, ==, !=)
```
print(3<5)
print(3<=5)
print(3>5)
print(3>=5)
print(3==5)
print(3!=5)
```

## 4.7 Comments (lines that start with a ‘#’)
```
# This is a comment
# This is another comment
print ("This is a comment test. ")  # comment
```

## 4.8 Output (printfunction)
```
print(1+2)  
print("This project is very interesting, I like it very much! ")
print("Have a wonderful day!")
```

## 4.9 Support lexical, Syntax Error Message, and report error line number

```
b = 1 @ 2 => Error: line 4, unrecognized symbol:'@'
iff a == 5: => Error, line 5, syntax error
```

## 4.10 Support indent
```
if 9 % 2 == 0:
  print("Even")
else:
  print("Odd")
```
## 4.11 Support type conversion (int()<=> str())
```
a=str(int(123))
b="abc"
c=int("100")
d=50
print(a+b)
print(c%d + 1)
```
## 4.12 Support using Break to exit the loop
```
for i in range(1, 20):
    print(i)
    if i==5:
        break
```
## 4.13 Support logical operation And and Or
'''
for i in range(0, 100):
    if i>=80 and (i%5==0 or i%10==0):
        print("This number is bigger than 80 and multiples of 5: ")
        print(i)
'''
## 4.14 Support Elif
```
a=99
if a<=0:
    print("Plese enter a correct number")
if a<=60:
    print('E')
elif a<=70:
    print("D")
elif a<=80:
    print("C")
elif a<=90:
    print("B")
elif a<=95:
    print("A")
elif a<=99:
    print("A+")
else:
    print("A++")
```
## 4.15 Support negative number
```
a= -5
b=9
print(a+b)
```

# 5. Compile NovPython
## 5.1 How to manually compile?
```
flex -o lex.cpp lex.l
bison -d -o parser.cpp parser.y
g++ -o nov parser.cpp lex.cpp nov-python.cpp main.cpp
```
## 5.2 How to automatically compile?
```
make
```

# 6. How to use NovPython to compile python source code? (Test files)
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
./nov test/type_conversion.py
./nov test/break.py
./nov test/logical_operation.py
./nov test/elif.py
./nov test/negative_number.py
```
