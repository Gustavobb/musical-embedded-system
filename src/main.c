/**
 * 5 semestre - Eng. da Computação - Insper
 * André Weber- andreew@insper.edu.br
 * Gustavo Braga- gustavobb@insper.edu.br
 * Aps 1 musical
 */


/************************************************************************************************************************/
/* Code adaptation from                                                                                                 */
/* https://www.princetronics.com/supermariothemesong/                                                                   */
/************************************************************************************************************************/

#include "asf.h"
#include "aps.h"

int main(void)
{
	init();
	create_songs();
	
	int rand_song = 1;
	int start_playing = 0;
	
	but_next_flag = 0;
	but_prev_flag = 0;
	but_play_flag = 0;
	
	char mario_string[] = "Mario Main Theme";
	char pirates_string[] = "Pirates of the Caribbean";
	char underworld_string[] = "Underworld Mario Theme";
	
	gfx_mono_draw_string("CLICK BUT 2", 10, 8, &sysfont);
		
	while (1)
	{
		if (start_playing) {
			if (rand_song == 1) { oled_draw(mario_string, sizeof(mario_string)/sizeof(char)); play(mario_main_song); }
			if (rand_song == 2) { oled_draw(pirates_string, sizeof(pirates_string)/sizeof(char)); play(pirates_of_the_caribean_song); }
			if (rand_song == 3) { oled_draw(underworld_string, sizeof(underworld_string)/sizeof(char)); play(underworld_mario_song); }
		}
		
		start_playing = 0;
		
		if (but_next_flag) {
			if (rand_song == 3) rand_song = 0;
			rand_song ++;
			start_playing = 1;
			but_next_flag = 0;
		}
		
		if (but_prev_flag) {
			if (rand_song == 1) rand_song = 4;
			rand_song --;
			start_playing = 1;
			but_prev_flag = 0;
		}

		if (but_play_flag) {
			start_playing = 1;
			but_play_flag = 0;
		}
	}
	return 0;
}
