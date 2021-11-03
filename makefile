CXX = g++
CXXFLAGS = -Wall

mytest: mytest.cpp puzzle.o
	$(CXX) $(CXXFLAGS) mytest.cpp puzzle.o -o mytest

puzzle.o: puzzle.h puzzle.cpp
	$(CXX) $(CXXFLAGS) -c puzzle.cpp

run:
	./mytest

clean:
	rm *~
