Program: main.o Executive.o Operator.o
	g++ -std=c++11 -g -Wall main.o Executive.o Operator.o -o Program

main.o: main.cpp Executive.h
	g++ -std=c++11 -g -Wall -c main.cpp

Executive.o: Executive.h Executive.cpp
	g++ -std=c++11 -g -Wall -c Executive.cpp

Operator.o: Operator.h Operator.cpp
	g++ -std=c++11 -g -Wall -c Operator.cpp

clean:
	rm *.o Program
