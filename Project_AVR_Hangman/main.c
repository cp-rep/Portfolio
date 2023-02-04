/*
 * main.c
 *
 * Created: 3/5/2020 11:17:22 AM
 *
 * Directions to setup floating point --
 * Under AVR/GNU Linker, General
 * Use vprintf library(-WI,-u,vfprintf)"
 *
 * Under AVR/GNU Linker, Miscellaneous
 * In Other Linker Flags: -Wl,-lprintf_flt
 *
 *
 * Directions to Play:
 *  A = Display Score
 *  B = Give Player a Free Word (this value is set in initialization function.  Does not cost lives)
 *  C = Disable Sound
 *  D = Get a new word, take away a life
 *  * = Reset the game
 *  # = The select/enter key such as for selecting a letter
 *  0-9 = Cycle through selection letters at bottom right of screen.
 */
#include <avr/io.h>
#include "stdio.h"
#include "keypad.h"
#include "avr.h"
#include "lcd.h"
#include "en_dict.h"
#include "time.h"
#include "note_data.h"
#include "notes.h"
#include "songs.h"
#include "hangman.h"
#include "alphabet.h"

// general component init prototypes
void init_components();
void disable_jtag();

// music prototypes and global data
void new_wait(unsigned short msec);
void pSong(short numNotes, short choice);
void pNote(int frequency, int duration);
char freq_counter = 0;
int numerator = 25000;
short sound_val = 1;

// adc data
void adc_init();
unsigned short adc_get_sample();
int adc_get_seed_val();

// other global data/flags
char push_flag = 0; // a flag used in letter selection



int main(void)
{
	// setup avr and components
	init_components();
	disable_jtag();
	
	// seed the number generator from an entropic source
	srand(adc_get_seed_val());

	// create and initialize hangman data
	struct hang_data hang;
	init_hangman(&hang);

	// prompt splash screen and music
	lcd_clr();
	splash_screen(hang.buff);

	pSong(sizeof(STAR_WARS)/sizeof(STAR_WARS[0]), S_STAR_WARS);
		
	// display start screen, prompt for lives selection
	avr_wait(1);
	lcd_clr();
	start_screen(hang.buff, &hang.lives, &hang.difficulty, &hang.sound);
	lcd_clr();
	avr_wait(1);

	// get word, word number, and size
	get_word(hang.word_buff, &hang.word_number, &hang.word_size, &hang.string_size);

	// draw hilt to screen
	draw_hilt();

	// create blank buff and print blanks to screen using data taken from the selected word from list
	create_blanks(&hang.string_size, hang.word_buff, hang.guess_buff);
	print_blanks(&hang.string_size, hang.guess_buff, &hang.sound, &hang.letter);

	// draw the blade health
	avr_wait(500);
	draw_blade(&hang.num_missed, &hang.sound);
	avr_wait(1);
	
	hang.letter = 0;

	short temp_sound = 0;
    while(1) 
    {
		short keyVal = get_key() - 1;
		switch(keyVal)
		{
			case A: // print score and lives
				lcd_clr();
				display_score(hang.buff, &hang.score, &hang.lives);
				avr_wait(2000);

				lcd_clr();				
				draw_hilt();
				draw_blade(&hang.num_missed, &hang.sound);
				
				print_line(hang.guess_buff, 1);
				
				break;
			case B: // get new word, don't take away life
				lcd_clr();
				if(hang.free_words > 0)
				{				
					hang.free_words--;
					print_line("    NEW WORD", 0);
					avr_wait(3000);
					new_random_word(hang.word_buff, hang.guess_buff, hang.buff, &hang.word_size,
									&hang.string_size, &hang.word_number, &hang.num_missed, &hang.sound, &hang.letter);
				}
				else
				{	
					print_line("  OUT OF FREE",0);
					print_line("     WORDS", 1);
					avr_wait(3000);
					lcd_clr();
					draw_hilt();
					draw_blade(&hang.num_missed, &hang.sound);
					print_line(hang.guess_buff, 1);
				}
				
				break;
			case C: // enable or disable sound
				lcd_clr();
				sprintf(hang.buff, "     SOUND");
				print_line(hang.buff, 0);
				if(hang.sound)
				{
					hang.sound = 0;
					sprintf(hang.buff, "      OFF");
					print_line(hang.buff, 1);
				}
				else
				{
					hang.sound = 1;
					sprintf(hang.buff, "      ON");
					print_line(hang.buff, 1);
				}
				
				avr_wait(2000);
				
				lcd_clr();
				draw_hilt();
				draw_blade(&hang.num_missed, &hang.sound);
				print_line(hang.guess_buff, 1);
				
				break;
			case D: // take away life, display word, get a new word
				print_line(hang.word_buff, 0);
				avr_wait(1);
				if(hang.sound)
					pSong(sizeof(IMP_MARCH)/sizeof(IMP_MARCH[0]), S_MARCH);
				avr_wait(3000);
				lcd_clr();
				
				if(!hang.sound)
				{
					print_line("   Your force", 0);
					print_line("    weakens...",1);
					avr_wait(3500);
				}
				
				lcd_clr();
				hang.lives--;
				if(hang.lives != 0)
					new_random_word(hang.word_buff, hang.guess_buff, hang.buff, &hang.word_size,
									&hang.string_size, &hang.word_number, &hang.num_missed, &hang.sound, &hang.letter);
									
				break;
			case one:
				select_letter(hang.buff, &hang.letter, &hang.letter_index, 0, 4, 3, one, &push_flag);	
				
				break;
			case two:
				select_letter(hang.buff, &hang.letter, &hang.letter_index, 1, 4, 3, two, &push_flag);
					
				break;
			case three:
				select_letter(hang.buff, &hang.letter, &hang.letter_index, 2, 4, 3, three, &push_flag);
				
				break;
			case four:
				select_letter(hang.buff, &hang.letter, &hang.letter_index, 3, 4, 3, four, &push_flag);
				
				break;
			case five:
				select_letter(hang.buff, &hang.letter, &hang.letter_index, 4, 4, 3, five, &push_flag);
				
				break;
			case six:
				select_letter(hang.buff, &hang.letter, &hang.letter_index, 5, 4, 3, six, &push_flag);
					
				break;
			case seven:
				select_letter(hang.buff, &hang.letter, &hang.letter_index, 6, 5, 4, seven, &push_flag);
				
				break;
			case eight:
				select_letter(hang.buff, &hang.letter, &hang.letter_index, 7, 4, 3, eight, &push_flag);
				
				break;
			case nine:
				select_letter(hang.buff, &hang.letter, &hang.letter_index, 8, 5, 4, nine, &push_flag);
				
				break;
			case zero:
				select_letter(hang.buff, &hang.letter, &hang.letter_index, 9, 4, 3, zero, &push_flag);
				
				break;		
			case star: // prompt a reset for the game. if yes, reselect lives/difficulty
				lcd_clr();
				if(reset_game(hang.buff))
				{
					lcd_clr();
					sound_val = hang.sound;
					init_hangman(&hang);
					hang.sound = sound_val;
					lcd_clr();
					splash_screen(hang.buff);
					if(hang.sound)
						pSong(sizeof(STAR_WARS)/sizeof(STAR_WARS[0]), S_STAR_WARS);
					
					lcd_clr();
					start_screen(hang.buff, &hang.lives, &hang.difficulty, &hang.sound);
					lcd_clr();
					new_random_word(hang.word_buff, hang.guess_buff, hang.buff, &hang.word_size,
							&hang.string_size, &hang.word_number, &hang.num_missed, &hang.sound, &hang.letter);
					hang.reset_val = 1;
				}
				else
				{
					lcd_clr();
					draw_hilt();
					draw_blade(&hang.num_missed, &hang.sound);
					print_line(hang.guess_buff, 1);
				}
					
				break;
			case pound: // the enter/select button.  chooses the letter to test against the string
				test_guess(hang.word_buff, hang.guess_buff, &hang.string_size, hang.letter, &hang.num_missed, &hang.score, &hang.difficulty, &hang.sound);
				
				break;
			default:
				break;
		}

		// this enters if a player misses 10 times on a single word
		if(hang.num_missed == 10)
		{
			print_line(hang.word_buff, 0);
			avr_wait(1);
			if(hang.sound)
				pSong(sizeof(IMP_MARCH)/sizeof(IMP_MARCH[0]), S_MARCH);
			avr_wait(2000);
			
			lcd_clr();
			hang.lives--;
			if(hang.lives != 0)
			new_random_word(hang.word_buff, hang.guess_buff, hang.buff, &hang.word_size,
							&hang.string_size, &hang.word_number, &hang.num_missed, &hang.sound, &hang.letter);
		}

		// check if the word is completed
		short completed_w_flag = check_completed_word(hang.guess_buff, &hang.string_size);
		
		// this enters when a player gets a word correct
		if(completed_w_flag)
		{
			if(hang.sound)
				pSong(sizeof(DIT_DOON)/sizeof(DIT_DOON[0]), S_DIT_DOON);
			else
			{
				avr_wait(2000);
				lcd_clr();
				print_line("     GREAT!", 0);
				avr_wait(2000);
				print_line("   Next word...", 1);
				avr_wait(2500);
			}

			lcd_clr();
			new_random_word(hang.word_buff, hang.guess_buff, hang.buff, &hang.word_size,
							&hang.string_size, &hang.word_number, &hang.num_missed, &hang.sound, &hang.letter);			
			hang.score += 100;
		}
		
		// this enters whenever a player runs out of lives by wrong guesses or by pushing D on a last life (1)
		if(hang.lives == 0 && !hang.reset_val)
		{
			lcd_clr();
			sprintf(hang.buff, "      GAME");
			print_line(hang.buff, 0);
			sprintf(hang.buff, "      OVER");
			print_line(hang.buff, 1);
			if(hang.sound)
				pSong(sizeof(LUKE_SONG)/sizeof(LUKE_SONG[0]), S_LUKE);
			else
			{
				avr_wait(4000);
			}
			lcd_clr();
			sprintf(hang.buff, "FINAL SCORE:");
			print_line(hang.buff, 0);
			sprintf(hang.buff, "%d", hang.score);
			print_line(hang.buff, 1);
			avr_wait(4000);

			// maintain current player sound choice when resetting the game
			temp_sound = hang.sound;
			init_hangman(&hang);
			hang.sound = temp_sound;
			
			lcd_clr();
			splash_screen(hang.buff);
			if(hang.sound)
				pSong(sizeof(STAR_WARS)/sizeof(STAR_WARS[0]), S_STAR_WARS);
			
			lcd_clr();
			start_screen(hang.buff, &hang.lives, &hang.difficulty, &hang.sound);
			lcd_clr();
			new_random_word(hang.word_buff, hang.guess_buff, hang.buff, &hang.word_size,
							&hang.string_size, &hang.word_number, &hang.num_missed, &hang.sound, &hang.letter);
		}
		else
			hang.reset_val = 0;

		sprintf(hang.buff, "%c    ", hang.letter);
		lcd_pos(1,15);
		lcd_puts2(hang.buff);
		
		avr_wait(500);
    }
}



/*
 disables jtag
*/
void disable_jtag()
{
	MCUCSR = (1 << JTD);
	MCUCSR = (1 << JTD);
}



/*
 a simple function to init all necessary components for hangman
*/
void init_components()
{
	avr_init();
	lcd_init();
	adc_init();
	
	// initialize port A
	DDRA = 0x01;
	PORTA = 0x00;
}



/*
 a wait function using more accurate frequency for playing sound
*/
void new_wait(unsigned short msec)
{
	TCCR0 = 3;
	while (msec--) {
		TCNT0 = (unsigned char)(256 - (XTAL_FRQ / 64) * 0.00001);
		SET_BIT(TIFR, TOV0);
		WDR();
		while (!GET_BIT(TIFR, TOV0));
	}
	TCCR0 = 0;
}



/*
 allow for reading ADC input from pinA2
*/
void adc_init() {
	ADMUX = 2;
	ADCSRA = (1 << ADEN) | (1 << ADPS2) | (1 << ADPS1);
}



/*
 the ADC sample function for getting ADC input
*/
unsigned short adc_get_sample() {
	ADCSRA |= (1 << ADSC);
	while(ADCSRA & (1 << ADSC));
	return(ADC);
}



/*
 get an entropic ADC sample and do calculations to that value and use as the seed value for random numbers 
*/
int adc_get_seed_val()
{
	float *voltage01;
	long temp01;

	voltage01 = malloc(sizeof(float));
	*voltage01 = adc_get_sample();
	*voltage01 = *voltage01/1023;
	temp01  = *voltage01 * 100000;

	temp01 *= -1;
	
	free(voltage01);
	return temp01;
}



/*
 plays a song from the list in songs.h,  allows key interruptions
*/
void pSong(short numNotes, short choice)
{
	short interrupt_song = 0;
	
	for(short i = 0; i < numNotes; i++)
	{
		if(choice == S_STAR_WARS)
			pNote(STAR_WARS[i].freq, STAR_WARS[i].dur);
		else if(choice == S_MARCH)
			pNote(IMP_MARCH[i].freq, IMP_MARCH[i].dur);
		else if(choice == S_LUKE)
			pNote (LUKE_SONG[i].freq, LUKE_SONG[i].dur);
		else if(choice == S_SPACES)
			pNote(SPACES[i].freq, SPACES[i].dur);
		else if(choice == S_DIT_DOON)
			pNote(DIT_DOON[i].freq, DIT_DOON[i].dur);
		else if(choice == S_LUKE_SHORT)
			pNote (LUKE_SHORT[i].freq, LUKE_SHORT[i].dur);
			
		interrupt_song = get_key() - 1;
			
		if(interrupt_song != (-1))
			break;
	}
}



/*
 play an individual note
*/
void pNote(int frequency, int duration)
{
	int period = numerator/frequency;
	int T = period / 2;
	int hold_note = frequency * duration;
	
	for(int i = 0; i < hold_note; i++)
	{
		SET_BIT(PORTA,0);	
		new_wait(T);
		CLR_BIT(PORTA,0);
		new_wait(T);
	}
}



/*
	the "Default constructor" for hangman data
*/
void init_hangman(struct hang_data *instruct)
{
	clear_string(instruct->word_buff, MAX_STR_SIZE);
	clear_string(instruct->guess_buff, MAX_STR_SIZE);
	clear_string(instruct->buff, MAX_STR_SIZE);
	instruct->word_size = 0;
	instruct->string_size = 0;
	instruct->word_number = 0;
	instruct->num_missed = 0;
	instruct->lives = 0;
	instruct->difficulty = 0;
	instruct->score = 0;
	instruct->sound = 1;
	instruct->free_words = 1;
	instruct->letter_index = 0;
	instruct->reset_val = 0;
}



/*
 helper function to set all buffer values to null
*/
void clear_string(char* in_string, short in_str_size)
{
	for(short i = 0; i < in_str_size; i++)
	{
		in_string[i] = 0;
	}
}



/*
 STAR WARS HANGMAN
*/
void splash_screen(char* in_buff_buff)
{
	sprintf(in_buff_buff, "   STAR WARS");
	print_line(in_buff_buff, 0);	
	sprintf(in_buff_buff, "    HANGMAN");
	print_line(in_buff_buff, 1);
}



/*
 prints whatever word is in word buff (starts as underscores and spaces)
*/
void print_line(char *in_string, short position)
{
	lcd_pos(position,0);
	lcd_puts2("               ");
	lcd_pos(position,0);
	lcd_puts2(in_string);
}



/*
 display lives selection and anything else before player plays the game
*/
void start_screen(char* in_buff_buff, short* in_lives, short* in_difficulty, short* in_sound)
{
	sprintf(in_buff_buff, " Select your #");
	print_line(in_buff_buff, 0);
	sprintf(in_buff_buff, "   of lives");
	print_line(in_buff_buff, 1);
	avr_wait(3000);
	

	sprintf(in_buff_buff, "1=One 2=Three ");
	print_line(in_buff_buff, 0);
	sprintf(in_buff_buff, "3=Five 0=Max  ");
	print_line(in_buff_buff, 1);
	
	while(1)
	{	
		short select_val = 0;
		short getKey = -1;
		
		getKey = get_key() - 1;
		
		switch(getKey)
		{
			case one:
				*in_lives = 1;
				*in_difficulty = 1;
				select_val = 1;
				break;
			case two:
				*in_lives = 3;
				*in_difficulty = 2;
				select_val = 1;
				break;
			case three:
				*in_lives = 5;
				*in_difficulty = 3;
				select_val = 1;
				break;
			case zero:
				*in_lives = 255;
				*in_difficulty = 0;
				select_val = 1;
				break;

			default:
				break;
		}
		
		if(select_val == 1)
			break;	
	}

	lcd_clr();
	sprintf(in_buff_buff, "   Trust Your");
	print_line(in_buff_buff, 0);
	sprintf(in_buff_buff, "   Feelings...");
	print_line(in_buff_buff, 1);
	if(*in_sound)
		pSong(sizeof(LUKE_SHORT)/sizeof(LUKE_SHORT[0]), S_LUKE_SHORT);
	else
		avr_wait(3000);
	avr_wait(200);
	lcd_clr();
}



/*
 gets a word from location word_num from word list, saves it's size to word_size
*/
void get_word(char* in_w_buff, short* w_num, short* w_size, short *str_size)
{
	*w_num = rand() % TOTAL_WORDS;
	
	for(int i = 0;;i++)
	{
		in_w_buff[i] = words[*w_num][i];
		if(in_w_buff[i] == ' ')
		{
			(*w_size)--;
		}
		else if(in_w_buff[i] == '-')
		{
			(*w_size)--;
		}
		
		if(in_w_buff[i] == 0)
			break;
		
		(*w_size)++;
		(*str_size)++;
	}
}



/*
 draws hilt to lcd_pos(0,0)
*/
void draw_hilt()
{
	char hilt[] = "0===|";
	print_line(hilt, 0);
}



/*
 creates underscores and spaces of size w_size and saves them into blank_buff
*/
void create_blanks(const short* w_size, const char* in_w_buff, char* in_g_buff)
{
	for(short i = 0; i < *w_size; i++)
	{
		if(in_w_buff[i] == ' ')
		{
			in_g_buff[i] = ' ';
		}
		else if( (in_w_buff[i] >= 'A' && in_w_buff[i] <= 'Z') ||
				 (in_w_buff[i] >= 'a' && in_w_buff[i] <= 'z') ||
				 (in_w_buff[i] >= '1' && in_w_buff[i] <= '9'))
		{
			in_g_buff[i] = '_';
		}
		else if(in_w_buff[i] == '-')
		{
			in_g_buff[i] = '-';
		}
	}
}



/*
 draws the blanks to the screen with animation and sound if enabled
*/
void print_blanks(const short* s_size, char* in_g_buff, const short* in_sound, char* in_letter)
{
	char underscore[] = "_";
	char space[] = " ";
	char hyphen[] = "-";

	for(short i = 0; i < *s_size; i++)
	{
		lcd_pos(1,i);

		if(in_g_buff[i] == ' ')
			lcd_puts2(space);
		else if (in_g_buff[i] == '-')
			lcd_puts2(hyphen);
		else
		{
			lcd_puts2(underscore);
			if(*in_sound)
				pNote(SPACES[i].freq, SPACES[i].dur);
		}
	}
}



/*
 draws animated blade to (0,5) with audio depending on length of num_missed
*/
void draw_blade(const short* n_missed, const short* in_sound)
{
	numerator = 2000;
	char dash[] = "/";
	short j = MAX_STR_SIZE;

	for(short i = 5; i < (15 - *n_missed); i++, j--)
	{
		lcd_pos(0,i);
		lcd_puts2(dash);
		if(*in_sound)
			pNote(SPACES[j].freq, SPACES[j].dur);
	}

	numerator = 25000;
}



/*
 generates a new word
*/
void new_random_word(char* in_w_buff, char* in_g_buff, char* in_buff_buff, short* in_w_size,
					 short* in_str_size, short* in_w_num, short* in_n_missed, short* in_sound, char* in_letter)
{
	// clear necessary data while maintaining current score and lives
	clear_string(in_w_buff, MAX_STR_SIZE);
	clear_string(in_g_buff, MAX_STR_SIZE);
	clear_string(in_buff_buff, MAX_STR_SIZE);
	*in_w_size = 0;
	*in_str_size = 0;
	*in_w_num = 0;
	*in_n_missed = 0;
	
	// get a new word	
	get_word(in_w_buff, in_w_num, in_w_size, in_str_size );

	// draw the new screen
	draw_hilt();
	create_blanks(in_str_size, in_w_buff, in_g_buff);
	print_blanks(in_str_size, in_g_buff, in_sound, in_letter);	
	draw_blade(in_n_missed, in_sound);
}



/*
 checks if chosen letter is in the word
*/
void test_guess(char* in_w_buff, char* in_g_buff, short* in_str_size, char in_guess, short* in_n_missed, short* in_score, short* in_difficulty, short* in_sound)
{
	short found_flag = 0;
	char temp = 0;
	
	for(short i = 0; i < *in_str_size; i++)
	{
		// award no points if the letter has already been revealed
		if(make_upper(in_g_buff[i]) == make_upper(in_guess))
		{
			found_flag = 1;
			break;
		}
		else
			temp = in_w_buff[i];
			
		if((temp >= 'a' && temp <= 'z') )
		{
			temp = make_upper(in_w_buff[i]);
		}
		
		if((temp == make_upper(in_guess) ||
					( (temp >= '1' && temp <= '9') && (in_guess >= '1' && in_guess <= '9'))) )
		{
			in_g_buff[i] = in_w_buff[i];
			found_flag = 1;
			
			if(*in_difficulty == 1)
				*in_score += 650;
			else if(*in_difficulty == 2)
				*in_score += 200;
			else if(*in_difficulty == 3)
				*in_score += 50;
			else if(*in_difficulty == 0)
				*in_score += 3;
		}
	}
	
	if(!found_flag)
	{
		(*in_n_missed)++;
		numerator = 10000;
		if(*in_sound)
			pNote(SPACES[*in_n_missed].freq, SPACES[*in_n_missed].dur);
			
		print_line("     MISS!", 1);
		avr_wait(1000);	
		
		numerator = 25000;
	}
	else
	{
		if(*in_sound)
			pNote(SPACES[14].freq, SPACES[14].dur);
	}
	
	short temp_sound = *in_sound;
	
	*in_sound = 0;
	
	lcd_clr();
	draw_hilt();
	draw_blade(in_n_missed, in_sound);
	print_line(in_g_buff, 1);
	*in_sound = temp_sound;
}



/*
 converts any lowercase to upper case for letter comparisons
*/
char make_upper(char in_char)
{
	if(in_char >= 'a' && in_char <= 'z')
	{
		in_char -= 32;
	}
	
	return in_char;
}



/*
 checks if a word is completed and returns the result
*/
short check_completed_word(char* in_g_buff, short* in_str_size)
{
	short flag_val = 1;
	
	for(short i = 0; i < *in_str_size; i++)
	{
		if(in_g_buff[i] == '_')
			flag_val = 0;
	}
	
	return flag_val;
}



/*
 display score to the screen (key A)
*/
void display_score(char* in_buff_buff, short* in_score, short* in_lives)
{
	sprintf(in_buff_buff, "SCORE: %d", *in_score);
	print_line(in_buff_buff, 0);
	sprintf(in_buff_buff,"LIVES: %d", *in_lives);
	print_line(in_buff_buff, 1);
}



/*
 the "enter" key for the currently display chosen letter
*/
void select_letter(char* in_buff_buff, char* in_letter, short* in_let_index, short in_alph_row, 
										short in_max_index, short in_alph_col, short in_enum_val, char* in_push_flag)
{
	if(*in_push_flag != in_enum_val)
	{
		*in_let_index = 0;
		*in_push_flag = in_enum_val;
	}
	else
	{
		(*in_let_index)++;
		if(*in_let_index == in_max_index)
		{
			*in_let_index = 0;
		}
	}
					
	*in_letter = key_alphabet[in_alph_row][*in_let_index];
	
	if(*in_letter != key_alphabet[in_alph_row][in_max_index])
		*in_letter = make_upper(*in_letter);
}



/*
 resets the game data to the start
*/
short reset_game(char* in_buff_buff)
{
	sprintf(in_buff_buff, "Reset the game?");
	print_line(in_buff_buff, 0);
	sprintf(in_buff_buff, "1=Yes  2=No");
	print_line(in_buff_buff, 1);

	short reset = 0;

	while(1)
	{
		short select_val = 0;
		short getKey = -1;
	
		getKey = get_key() - 1;
	
		switch(getKey)
		{
			case one:
				reset = 1;
				select_val = 1;
				break;
			case two:
				reset = 0;
				select_val = 1;
				break;
			default:
				break;
		}
		
		if(select_val == 1)
			break;
	}
	
	return reset;
}