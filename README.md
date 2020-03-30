# APS-Musical

A embedded system that can **play monophonic music**. Here`s a [link](google.com) to a video that demonstrates the project working.

##### Table of contents:

[Components](#components)

[Connections](#connections)

[Set-up/Running the project](#setup)

[Code Structure](#codeStructure)

[References/Credits](#referencescredits)

<a name="components"></a>Components
======
Here are all components used in this project:

*  **Atmel SAM E70 XPLAINED** ([link](https://www.microchip.com/developmenttools/ProductDetails/atsame70-xpld))
* **OLED1XPLAINEDpro** ([link](https://www.microchip.com/developmenttools/ProductDetails/atoled1-xpro))
* **1x BUZZER**
*  **2x JUMPERS (female-to-female or male-to-female)**
*  **1x PROTOBOARD (only necessary when jumpers are male-to-female)**

<a name="connections"></a>Connections
======
The connection needs to be as the following:

![alt text](https://github.com/Gustavobb/musical-embedded-system/blob/master/APS-Musical/connections.png)

<a name="setup"></a>Set-up/Running the project
======

After connecting the [components](#components), the cable must be plugged in the computer USB. To compile the program, the software used is **Atmel Studio 7.0**, so it needs to be opened in order to run the project. 

#### The  buttons, led, buzzer and screen works as the following:


| Type| Action| Connection|
| ------------- |:-------------:| -----:|
| Button 1      | Previous music | PIOD28 |
| Button 2      | Play / Pause|   PIOC31 |
| Button 3 | Next Music      |    PIA19 |
| Led 1 | Lower frequencies      |    PA0 |
| Led 2 | Mid frequencies      |    PIOC30 |
| Led 3 | Higher frequencies      |    PIOB2 |
| Buzzer| Play frequency      |    PIOA3 / GND |
| Screen | Displays music name      |    --------------- |

<a name="codeStructure"></a>Code Structure
===

The code structure is expalined below: 

#### :file_folder: screen/
```c
// Files used by OLED display.
```
#### :file_folder: include_files/pios.h
```c
// Header file that define all OLED buttons, led and the buzzer PIO`s.
```
#### :file_folder: include_files/structures.h
```c
// Header file that define the music struct.
typedef  struct {
...
} Song_to_play;
```
#### :file_folder: include_files/musics.h
(all [credits](#referencescredits))
```c
// Header file that define the musics frequencies and tempo`s.
int mario_main[]
int mario_main_tempo[]
int pirates_of_the_caribean[]
int pirates_of_the_caribean_tempo[]
int underworld_mario[]
int underworld_mario_tempo[]
```
#### :file_folder: include_files/frequencies.h
```c
// Header file that define all frequencies.
```
#### :file_folder: include_files/init_functions.h
```c
// Header file that define all initial configurations.

void create_songs() { ... } // Create all songs and transform them into structures for function passing
void init(void) { ... } // Clock init, create interruptions, set pio output and input

// Callbacks functions for interruption
void but_next_callback(void){ ... }
void but_prev_callback(void){ ... }
void but_play_callback(void){ ... } 
```
#### :file_folder: include_files/core_functions.h
```c
// Header file that define all core and functional functions.

void pause() { ... } // Pause music
void oled_draw(char*  string, int  size) { ... } // Function that display the given string to oled with text centralization
void buzz(int  frequency, int  length, int  max, int  min) { ... } // Make the buzzer play the song frequency and control the LED`s.
void play(Song_to_play  song) { ... } // Play the given song, call buzz() whenever a note needs to be played and pause() whenever the pause button is pressed

```
#### :page_with_curl: asf.h
```c
// Header file that includes all API header files for the selected drivers from ASF.
```

#### :page_with_curl: aps.h
```c
// Header file that includes all include_files/ and screen/ header file.
#include  "include_files/*.h" 
```
#### :bookmark_tabs: main.c
```c
// c file that control wich core_functions are called, skip, play and return to previous music. Uses the init_functions to create songs and init pio clock
int main(void) {

	init();
	create_songs();
	
	while (1) { ... } // Play, pause, draw, ...
}
```

<a name="referencescredits"></a>References/Credits
===

#### :musical_note: Super Mario Main Theme
##### by Prince @ princetronics.com

#### :musical_note: Pirates of The Caribbean
##### by Xitang 2016.06.27  @ github

#### :musical_note: Underworld Mario
##### by Prince @ princetronics.com

#### :page_with_curl: Code adapted from:
##### https://www.princetronics.com/supermariothemesong/




