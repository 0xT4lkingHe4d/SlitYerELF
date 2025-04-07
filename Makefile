CC 	    = $(shell which g++)
CFLAGS	= -lx86disass -lelflib -w -g
SRC 	= main.cpp ./src/*.cc
OUT	    = ./main

all: build

build:
	clear
	$(CC) $(SRC) $(CFLAGS) -o $(OUT)

debug:
	$(CC) $(SRC) $(CFLAGS) -g -o $(OUT)

run: build
	./main -i ./a.out -m ./m_pass.o -o ./output
