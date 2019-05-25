CC = gcc
CXX= g++
FLAGS= -Wall -O2
OBJ = json11.o json2bin.o

json2bin: $(OBJ)
	$(CXX) -o ../json2bin $^ $(FLAGS)
	@rm json11.o json2bin.o

%.o: %.c
	$(CC) -c -o $@ $< $(FLAGS)

%.o: %.cpp
	$(CXX) -c -o $@ $< $(FLAGS)
