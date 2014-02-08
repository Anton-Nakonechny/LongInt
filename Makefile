all:test main

.PHONY : clean

OBJECTS = LongInt.o Digits.o

${OBJECTS}:%.o: %.cpp %.hpp Vector.hpp BitVector.hpp
	g++ $< -o $@ -c -g3 -O0

main: ${OBJECTS} main.cpp
	g++ ${OBJECTS} main.cpp -o main -g3 -O0
	
test: ${OBJECTS} unit_test.cpp
	g++ ${OBJECTS} unit_test.cpp -o test -lgtest_main -lgtest -lpthread -g3 -O0

clean:
	rm -rf test main ${OBJECTS}
