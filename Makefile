all: des.o
	gcc -O3 run_des.c des.o -o rundes.o
libs:
	gcc -O3 des.c -o des.o