#The Makefile of the program

#Student Name: Le Minh Truong
#Student ID: 1078113
#Subject Name: Algorithms and Data Structures
#Subject Code: COMP20003

#Assignment 2

all: map1 map2

map2: map2.o make_tree.o make_list.o utilities.o
	gcc -Wall -o map2 map2.o make_tree.o make_list.o utilities.o -lm

map1: map1.o make_tree.o make_list.o utilities.o
	gcc -Wall -o map1 map1.o make_tree.o make_list.o utilities.o -lm

utilities.o: utilities.c header.h
	gcc -c -Wall utilities.c

make_list.o: make_list.c header.h
	gcc -c -Wall make_list.c

make_tree.o: make_tree.c header.h
	gcc -c -Wall make_tree.c

map2.o: map2.c header.h
	gcc -c -Wall map2.c

map1.o: map1.c header.h
	gcc -c -Wall map1.c
