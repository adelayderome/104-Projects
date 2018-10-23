CPPFLAGS = -g -Wall 
CXX = g++

all: stringparser stackstr.o

stackstr.o: stackstr.cpp
	$(CXX) $(CPPFLAGS) -std=c++11 stackstr.cpp -o stackstr.o

stringparser: stringparser.cpp
	$(CXX) $(CPPFLAGS) -std=c++11 stringparser.cpp -o stringparser

