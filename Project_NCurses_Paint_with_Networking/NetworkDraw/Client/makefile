clientDraw : client01.o clientMain.o clientCurses.o
	gcc -o clientDraw clientMain.o client01.o clientCurses.o -l ncurses
clientMain.o : clientMain.c client01.h clientCurses.h
	gcc -c clientMain.c
client01.o : client01.c client01.h
	gcc -c client01.c
clientCurses.o : clientCurses.c clientCurses.h
	gcc -c clientCurses.c