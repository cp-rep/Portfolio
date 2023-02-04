/*
 * hangman.h
 *
 * Created: 3/7/2020 9:53:26 AM
 */ 
#ifndef HANGMAN_H_
#define HANGMAN_H_

#define MAX_STR_SIZE 16


struct hang_data {
	char word_buff[MAX_STR_SIZE]; // contains the word from the word list
	char guess_buff[MAX_STR_SIZE]; // contains whatever the current blanks line is including guesses/uncovered spaces
	char buff[MAX_STR_SIZE]; // a simple buffer used when needed
	short word_size; // total length of word, doesn't count spaces
	short string_size; // total size of string including spaces (unused)
	short word_number; // used as the index to get a word from the list of words
	short num_missed; // total mistakes a player made. should be set if reached 5, player loses and queues an audio
	short lives; // player total lives
	short difficulty; // difficulty setting, (tied to number of lives and used as flag for point values and other)
	short score; // player score
	short sound; // sound flag
	short free_words; // number of "ask the audience" words (free words a player can be given without losing a life.  keypad B
	char letter; // the current letter the player has chosen
	short letter_index; // used for indexing into the alphabet and selecting a letter in select_letter()
	short reset_val; // a flag value for resetting the game via * (star) key
};

void init_hangman(struct hang_data *instruct); // the "Default constructor" for hangman data
void splash_screen(char* in_buff_buff); // STAR WARS HANGMAN
void print_line(char *in_string, short position); // prints whatever word is in word buff (starts as underscores and spaces)
void clear_string(char* in_string, short in_str_size); // helper function to set all buffer values to null
void start_screen(char* in_buff_buff, short* in_lives, short* in_difficulty, short* in_sound); // display lives selection and anything else before player plays the game
void get_word(char* in_w_buff, short* w_num, short* w_size, short *str_size); // gets a word from location word_num from word list, saves it's size to word_size
void create_blanks(const short* w_size, const char* in_w_buff, char* in_g_buff); // creates underscores and spaces of size w_size and saves them into blank_buff
void print_blanks(const short* s_size, char* in_g_buff, const short* in_sound, char* in_letter); // draws the blanks to the screen with animation and sound if enabled
void draw_hilt(); // draws hilt to lcd_pos(0,0)
void draw_blade(const short* n_missed, const short* in_sound); // draws animated blade to (0,5) with audio depending on length of num_missed
void new_random_word(char* in_w_buff, char* in_g_buff, char* in_buff_buff, short* in_w_size,
					short* in_str_size, short* in_w_num, short* in_n_missed, short* in_sound, char* in_letter); // generates a new word
void test_guess(char* in_w_buff, char* in_g_buff, short* in_str_size, char in_guess, short* in_n_missed, short* in_score, short* in_difficulty, short* in_sound); // checks if chosen letter is in the word
char make_upper(char in_char); // converts any lowercase to upper case for letter comparisons
short check_completed_word(char* in_g_buff, short* in_str_size); // checks if a word is completed and returns the result
void display_score(char* in_buff_buff, short* in_score, short* in_lives); // display score to the screen (key A)
void select_letter(char* in_buff_buff, char* in_letter, short* in_let_index, short in_alph_row, 
					short in_max_index, short in_alph_col, short in_enum_val, char* in_push_flag); // the "enter" key for the currently display chosen letter
short reset_game(char* in_buff_buff); // resets the game data to the start

#endif /* HANGMAN_H_ */