CPPFLAGS = -g -Wall 
CXX = g++

all: crawler search

search: search.h setutility.h pagerank.h search.cpp 
	$(CXX) $(CPPFLAGS) -std=c++11 search.cpp -o search

crawler: crawler.cpp
	$(CXX) $(CPPFLAGS) -std=c++11 crawler.cpp -o crawler