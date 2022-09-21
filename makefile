all: run graph clean

run: graph
	@./graph.out

graph: graph.o ponte.o
	@g++ -g -Wall main.cpp -o graph.out graph.o ponte.o

graph.o: graph.cpp graph.h
	@g++ -c graph.cpp

ponte.o: ponte.cpp
	@g++ -c ponte.cpp

clean:
	@rm *.o
	@rm *.out