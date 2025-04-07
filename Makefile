CC 		= $(shell which g++)
CFLAGS	= -lx86disass -lelflib -w -g
SRC 	= main.cpp ./src/*.cc
OUT		= ./main

all: build

build:
	clear
	$(CC) $(SRC) $(CFLAGS) -o $(OUT)

debug:
	$(CC) $(SRC) $(CFLAGS) -g -o $(OUT)

run: build
#	./main ./a.out ./oi.fuck.you
	./main -i ./a.out -m ./m_pass.o -o ./oi.fuck.you
# 	./main ../stuff/ret2win2 ./oi.fuck.you
