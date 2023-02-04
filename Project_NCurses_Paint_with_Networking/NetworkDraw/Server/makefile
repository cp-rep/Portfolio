serverDraw : serverMain.o server01.o serverCurses.o
	gcc -o serverDraw serverMain.o server01.o serverCurses.o -l ncurses
serverMain.o : serverMain.c server01.h serverCurses.h
	gcc -c serverMain.c
server01.o : server01.c server01.h
	gcc -c server01.c
serverCurses.o : serverCurses.c serverCurses.h
	gcc -c serverCurses.c