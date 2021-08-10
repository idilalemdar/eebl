CC = g++
CFLAGS = -O3 -std=c++14 -Wall -g -Iinclude -lpthread
SRC = src/*.cpp

lead:
	$(CC) -o lead lead.cpp $(SRC) $(CFLAGS)

follower:
	$(CC) -o follower follower.cpp $(SRC) $(CFLAGS)

