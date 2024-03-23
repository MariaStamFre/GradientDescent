CXX = g++
OBJ = main.o
HEADERS = GradientDescent.h
CPPLAGS = -c -Wall -I.


main: $(OBJ)
	$(CXX) $(OBJ) -o $@

main.o: main.cpp $(HEADERS)
	$(CXX) $(CPPLAGS) $< -o $@

clean:
	rm -rf *o main
