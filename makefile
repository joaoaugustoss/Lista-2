all: run

run: graph
	@./graph

graph: graph.o ponte.o
	@g++ -g -Wall main.cpp -o graph graph.o ponte.o

graph.o: graph.cpp graph.h
	@g++ -c graph.cpp

ponte.o: ponte.cpp
	@g++ -c ponte.cpp

clean:
	@rm *.o graph