/*
 * songs.h
 *
 * Created: 2/18/2020 12:41:33 AM
 */ 


#ifndef SONGS_H_
#define SONGS_H_
#include "notes.h"
#include "note_data.h"


enum songs {S_STAR_WARS, S_MARCH, S_LUKE, S_SPACES, S_SABER, S_DIT_DOON, S_LUKE_SHORT};

struct note STAR_WARS[] = { {N_G0, dur_2}, {N_D1, dur_3}, {N_C1, dur_1}, {N_B0, dur_1}, {N_A0, dur_1}, {N_G1, dur_1}, {N_D1, dur_3}, {N_C1, dur_1},
							{N_B0, dur_1}, {N_A0, dur_1}, {N_G1, dur_1}, {N_D1, dur_3}, {N_C1, dur_1}, {N_B0, dur_1}, {N_C1, dur_1}, {N_A0, dur_3} };

struct note IMP_MARCH[] = { {N_E0, dur_2}, {N_E0, dur_2}, {N_E0, dur_2}, {N_C0, dur_2}, {N_G0, dur_1}, {N_E0, dur_2},  {N_C0, dur_2}, {N_G0, dur_1},{N_E0, dur_2} };
	
struct note LUKE_SONG[] = { {N_CS0, 2}, {N_CS0, 1}, {N_FS0, 3}, {N_GS0, 2}, {N_A0, 1}, {N_B0, 1}, {N_A0, 2}, {N_CS0, 2}, 
						    {N_CS0, 2}, {N_CS0, 1}, {N_FS0, 3}, {N_GS0, 2}, {N_A0, 1}, {N_FS0, 1}, {N_A0, 1}, {N_FS0, 1}, {N_CS1, 1}, {N_B0, 4},
						    {N_CS0, 1}, {N_CS0, 1}, {N_FS0, 3}, {N_GS0, 2}, {N_A0, 1}, {N_FS0, 1}, {N_CS1, 1}, {N_A0, 1}, {N_FS1, 3},
						    {N_A0, 2}, {N_GS0, 1}, {N_FS0, 1}, {N_CS1, 3}, {N_A0,1}, {N_GS0, 1}, {N_CS0, 1}, {N_CS0, 1}, {N_FS0, 4} };
						
struct note SPACES[] = { {N_C0, dur_1}, {N_CS0, dur_1}, {N_D0, dur_1}, {N_DS0, dur_1}, {N_E0, dur_1}, {N_F0, dur_1}, {N_FS0, dur_1}, {N_G0, dur_1}, {N_GS0, dur_1}, {N_A0, dur_1}, 
						 {N_AS0, dur_1}, {N_B0, dur_1}, {N_C1, dur_1}, {N_CS1, dur_1}, {N_D1, dur_1}, {N_DS1, dur_1} };

struct note SABER[] = { {N_C0, dur_1}, {N_CS0, dur_1}, {N_D0, dur_1}, {N_DS0, dur_1}, {N_E0, dur_1}, {N_F0, dur_1}, {N_FS0, dur_1}, {N_G0, dur_1}, {N_GS0, 1}, 
					    {N_A0, dur_1}, {N_AS0, dur_1}, {N_B0, dur_1}, {N_C1, dur_1}, {N_CS1, dur_1}, {N_D1, dur_1}, {N_DS1, dur_1} };
							
struct note DIT_DOON[]= { {N_C1, dur_1}, {N_B0, dur_1}, {N_C1, dur_1}, {N_A0, dur_3} };
	
struct note LUKE_SHORT[] = { {N_CS0, 2}, {N_CS0, 1}, {N_FS0, 3}, {N_GS0, 2}, {N_A0, 1}, {N_B0, 1}, {N_A0, 2}, {N_CS0, 2}};

#endif /* SONGS_H_ */