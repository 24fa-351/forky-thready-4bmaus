# Compile the main executable
main: main.c forky.c forky.h
	gcc -o main main.c forky.c

