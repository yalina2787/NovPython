nov:main.cpp lex.cpp parser.cpp nov-python.cpp
	g++ -o nov parser.cpp lex.cpp nov-python.cpp main.cpp

lex.cpp: lex.l
	flex -o lex.cpp lex.l;

parser.cpp: parser.y
	bison -d -o parser.cpp parser.y

clean:
	-rm nov