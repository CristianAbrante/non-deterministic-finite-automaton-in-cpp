# Makefile para compilar la práctica 3 de C&A.
# Cristian Abrante Dorta.

CC = g++
CXXFLAGS = -g --std=c++11
OBJECTS = ./src/NFA/NFA.o ./src/State/State.o ./src/Transition/Transition.o ./src/Alphabet/Alphabet.o ./src/main.o 

Practica2.out: ${OBJECTS}
	$(CC) $(CXXFLAGS) -o nfa.out ${OBJECTS}
