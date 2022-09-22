all: run graph clean

run: graph
	@./graph.out

graph: graph.o ponte.o utilitario.o
	@g++ -std=c++11 -g -Wall main.cpp -o graph.out graph.o ponte.o utilitario.o

graph.o: graph.cpp graph.h
	@g++ -std=c++11 -c graph.cpp

ponte.o: ponte.cpp
	@g++ -std=c++11 -c ponte.cpp

utilitario.o: utilitario.cpp
	@g++ -std=c++11 -c utilitario.cpp

clean:
	@rm *.o
	@rm *.out