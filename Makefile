
all: a.out

Points.o: Points.cpp
	g++ -c -std=c++11 Points.cpp

hello:
	echo "Hello Alex"

a.out: Points.o arithmetic.h
	g++ -std=c++11 Points.o
	./a.out
