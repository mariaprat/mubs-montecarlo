CXXFLAGS = -Wall -std=c++17 -O2

all: main

clean:
	rm -f *.o main

main: main.o montecarlo.o utilities-complex.o
	$(CXX) $^ -o $@

main.o: main.cc montecarlo.h utilities-complex.h

montecarlo.o: montecarlo.cc montecarlo.h

utilities-complex.o: utilities-complex.cc utilities-complex.h
