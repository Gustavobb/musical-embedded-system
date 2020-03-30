/*
 * Created: 23/03/2020 18:46:01
 *  Author: gubeb
 */ 


#ifndef INCFUNCTIONS_H_
#define INCFUNCTIONS_H_

void pause();
void oled_draw(char* string, int size);
void buzz(int frequency, int length, int max, int min);
void play(Song_to_play song);

void oled_draw(char* string, int size) {
	
	int space_loc;
	char up_part[14];
	char below_part[14];
	
	if (size > 26) { gfx_mono_draw_string("Error", 50, 10, &sysfont); return; }
		
	if ( size > 13) {
		
		for (int i = 0; i <= 12; i++) { if (*(string + i) == ' ') { space_loc = i; } }
		
		for (int i = 0; i < 13; i++) { up_part[i] = ' '; below_part[i] = ' '; }
		up_part[13] = '\0';
		below_part[13] = '\0';
				
		int a = (14 - (size - 1 - space_loc))/2;
		int b = (14 - space_loc)/2;
		
		for (int i = 0; i < space_loc; i++) { up_part[i + b] = string[i]; }
		
		for (int i = 0; i < size - space_loc - 2; i++) { below_part[i + a] = string[space_loc + i + 1]; }
		
		gfx_mono_draw_string(up_part, 0, -2, &sysfont);
		gfx_mono_draw_string(below_part, 0, 9, &sysfont);
		
	} else { gfx_mono_draw_string(string, 0, 10, &sysfont); }
	
	gfx_mono_draw_string("PLAY ", 50, 20, &sysfont);
}

void buzz(int frequency, int length, int max, int min) {
	
	int delay = 1000000 / frequency;
	int range = (max - min)/3;
	
	if (frequency <= min + range) { pio_clear(LED1_PIO, LED1_PIO_IDX_MASK); }
	if (frequency > min + range && frequency <= min + 2*range) { pio_clear(LED2_PIO, LED2_PIO_IDX_MASK); }
	if (frequency > min + 2*range) { pio_clear(LED3_PIO, LED3_PIO_IDX_MASK); }
	
	for (int i = 0; i < (length * 1000)/delay; i++) {
		
		if (but_play_flag) { pause(); }
		
		if (but_next_flag || but_prev_flag) { break; }
			
		pio_set(BUZZ_PIO, BUZZ_PIO_IDX_MASK);
		delay_us(delay/2);
		pio_clear(BUZZ_PIO, BUZZ_PIO_IDX_MASK);
		delay_us(delay/2);
	}
	
	pio_set(LED1_PIO, LED1_PIO_IDX_MASK);
	pio_set(LED2_PIO, LED2_PIO_IDX_MASK);
	pio_set(LED3_PIO, LED3_PIO_IDX_MASK);
}

void pause() {
	
	but_play_flag = 0;
	gfx_mono_draw_string("PAUSE", 50, 20, &sysfont);
	
	while (1) {
		if (but_play_flag) { but_play_flag = 0; break; }
		if (but_prev_flag || but_next_flag) { break; }
	}
	
	gfx_mono_draw_string("PLAY ", 50, 20, &sysfont);
}

void play(Song_to_play song) {
	
	int size_of_song = sizeof(song.music) / sizeof(int);
	int note_duration;
	
	for (int note = 0; note < size_of_song; note++) {
		
		note_duration = song.tempo[note] / song.velocity;
		
		if (but_play_flag) { pause(); }
			
		buzz(song.music[note], note_duration, song.max_value, song.min_value);
		
		if (but_next_flag || but_prev_flag) { break; }
		
		delay_ms(note_duration * 1.30);
	}
		
	gfx_mono_draw_string("PAUSE", 50, 20, &sysfont);
}

#endif /* INCFUNCTIONS_H_ */