draw : main.o curse.o
	gcc -o draw main.o curse.o -l ncurses
main.o : main.c curse.h
	gcc -c main.c
curse.o : curse.c curse.h
	gcc -c curse.c
