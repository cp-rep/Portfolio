/*
 * keypad.c
 *
 * Created: 2/26/2020 2:11:17 AM
 */ 
#include <avr/io.h>
#include "keypad.h"
#include "avr.h"



int get_key()
{
	int r, c;
	for(r = 0; r < 4; r++)
	{
		for(c = 0; c < 4; c++)
		{
			if(is_pressed(r, c))
			{
				return (r * 4) + c + 1;
			}
		}
	}
	return 0;
}



int is_pressed(int r, int c)
{
	DDRC = 0;
	PORTC = 0;
	
	SET_BIT(DDRC, r);
	SET_BIT(PORTC, c + 4);
	
	avr_wait(1);

	if(GET_BIT(PINC, c + 4))
	{
		return 0;
	}
	
	return 1;
}