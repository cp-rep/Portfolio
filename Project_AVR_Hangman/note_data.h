/*
 * note_data.h
 *
 * Created: 2/18/2020 12:45:18 AM
 */ 


#ifndef NOTE_DATA_H_
#define NOTE_DATA_H_

enum NOTE_DUR { dur_err, dur_1, dur_2, dur_3};

struct note {
	int freq;
	int dur;
};


#endif /* NOTE_DATA_H */