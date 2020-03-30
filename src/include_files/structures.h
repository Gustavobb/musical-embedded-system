/*
 * structures.h
 *
 * Created: 23/03/2020 18:55:09
 *  Author: gubeb
 */ 


#ifndef STRUCTURES_H_
#define STRUCTURES_H_
#define music_max 600

typedef struct {
	int music[music_max];
	int tempo[music_max];
	double velocity;
	int max_value;
	int min_value;
} Song_to_play;

#endif /* STRUCTURES_H_ */