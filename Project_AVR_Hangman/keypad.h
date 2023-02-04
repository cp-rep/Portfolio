/*
 * keypad.c
 *
 * Created: 2/26/2020 2:11:17 AM
 */ 
#ifndef KEYPAD_H_
#define KEYPAD_H_


enum keys
{
	one,
	two,
	three,
	A,
	four,
	five,
	six,
	B,
	seven,
	eight,
	nine,
	C,
	star,
	zero,
	pound,
	D
};

int get_key();
int is_pressed(int r, int c);



#endif /* KEYPAD_H */