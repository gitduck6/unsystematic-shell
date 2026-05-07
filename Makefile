#The makefile is currently quite simple,
#We just take every .c file in src and compile it into one 

SRC := $(wildcard src/*.c)
CC	:= gcc
OUT	:= ush

$(OUT) : $(SRC)
	$(CC) $(SRC) -o $(OUT)
