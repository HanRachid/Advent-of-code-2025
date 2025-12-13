CC = gcc
CFLAGS = -g -Wall -Wextra -Werror
SRC = helpers/array_helpers.c Day1/day1.c Day2/day2.c Day3/day3.c Day4/day4.c Day5/day5.c Day6/day6.c Day7/day7.c Day8/day8.c main.c
OUT = bin/main

all:
	mkdir -p bin
	$(CC) $(CFLAGS) -o $(OUT) $(SRC)

# Generate compile_commands.json for clangd
compile_commands.json:
	bear -- make all

