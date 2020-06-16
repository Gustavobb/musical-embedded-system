/*
 * init_functions.h
 *
 * Created: 23/03/2020 19:07:56
 *  Author: gubeb
 */ 


#ifndef INIT_FUNCTIONS_H_
#define INIT_FUNCTIONS_H_

void init(void);
void create_songs();

volatile char but_next_flag;
volatile char but_prev_flag;
volatile char but_play_flag;

void but_next_callback(void) { but_next_flag = 1; }
void but_prev_callback(void) { but_prev_flag = 1; }
void but_play_callback(void) { but_play_flag = 1; }

void init(void){
	board_init();
	sysclk_init();

	WDT->WDT_MR = WDT_MR_WDDIS;
	
	delay_init();
	gfx_mono_ssd1306_init();

	pmc_enable_periph_clk(BUT1_PIO_ID);
	pmc_enable_periph_clk(BUT2_PIO_ID);
	pmc_enable_periph_clk(BUT3_PIO_ID);
	pmc_enable_periph_clk(BUZZ_PIO_ID);
	pmc_enable_periph_clk(LED1_PIO_ID);
	pmc_enable_periph_clk(LED2_PIO_ID);
	pmc_enable_periph_clk(LED3_PIO_ID);
	
	pio_set_output(BUZZ_PIO, BUZZ_PIO_IDX_MASK, 0, 0, 0);
	pio_set_output(LED1_PIO, LED1_PIO_IDX_MASK, 0, 0, 0);
	pio_set_output(LED2_PIO, LED2_PIO_IDX_MASK, 0, 0, 0);
	pio_set_output(LED3_PIO, LED3_PIO_IDX_MASK, 0, 0, 0);
	
	pio_handler_set(BUT1_PIO, BUT1_PIO_ID, BUT1_PIO_IDX_MASK, PIO_IT_FALL_EDGE, but_prev_callback);
	pio_enable_interrupt(BUT1_PIO, BUT1_PIO_IDX_MASK);
	
	NVIC_EnableIRQ(BUT1_PIO_ID);
	NVIC_SetPriority(BUT1_PIO_ID, BUT1_PRIORITY);
	
	pio_handler_set(BUT2_PIO, BUT2_PIO_ID, BUT2_PIO_IDX_MASK, PIO_IT_FALL_EDGE, but_play_callback);
	pio_enable_interrupt(BUT2_PIO, BUT2_PIO_IDX_MASK);
	
	NVIC_EnableIRQ(BUT2_PIO_ID);
	NVIC_SetPriority(BUT2_PIO_ID, BUT2_PRIORITY);
	
	pio_handler_set(BUT3_PIO, BUT3_PIO_ID, BUT3_PIO_IDX_MASK, PIO_IT_FALL_EDGE, but_next_callback);
	pio_enable_interrupt(BUT3_PIO, BUT3_PIO_IDX_MASK);
	
	NVIC_EnableIRQ(BUT3_PIO_ID);
	NVIC_SetPriority(BUT3_PIO_ID, BUT3_PRIORITY);
	
	pio_set(LED1_PIO, LED1_PIO_IDX_MASK);
	pio_set(LED2_PIO, LED2_PIO_IDX_MASK);
	pio_set(LED3_PIO, LED3_PIO_IDX_MASK);
}

void setup_music_values(Song_to_play *song, int song_data[], int song_size, int song_time[], int velocity) {
	song->max_value = song_data[0];
	song->min_value = song_data[0];
	
	for (int i = 0; i < song_size; i++) {
		
		song->music[i] = song_data[i];
		song->tempo[i] = song_time[i];
		
		if (song->max_value < song_data[i]) song->max_value = song_data[i];
		if (song->min_value > song_data[i] && song_data[i] != 0) song->min_value = song_data[i];
	}
	song->velocity = velocity;
}

void create_songs() {
	
	mario_main_song.max_value = mario_main[0];
	mario_main_song.min_value = mario_main[0];
	setup_music_values(&mario_main_song, mario_main, sizeof(mario_main) / sizeof(int), mario_main_tempo, 0.15);
	
	pirates_of_the_caribean_song.max_value = pirates_of_the_caribean[0];
	pirates_of_the_caribean_song.min_value = pirates_of_the_caribean[0];
	setup_music_values(&pirates_of_the_caribean_song, pirates_of_the_caribean, sizeof(pirates_of_the_caribean) / sizeof(int), pirates_of_the_caribean_tempo, 1.5);
	
	underworld_mario_song.max_value = underworld_mario[0];
	underworld_mario_song.min_value = underworld_mario[0];
	setup_music_values(&underworld_mario_song, underworld_mario, sizeof(underworld_mario) / sizeof(int), underworld_mario_tempo, 1);
}

#endif /* INIT_FUNCTIONS_H_ */