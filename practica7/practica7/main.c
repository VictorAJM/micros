#define F_CPU 2000000UL
#include <avr/io.h>
#include <util/delay.h>

// The output file from notegen.pl script
#include "notes.h"

/// Default volume, value assigned to OCR1B
#define DEFAULT_VOLUME 100

/**
	Initialize timer1

	PWM output on OCR1B
*/

void InitMusic()
{
	// Configure OC1B pin as output

	DDRB = 0xFF;
	PORTB = 0;
// Configuración del Timer0 (para PWM)
TCCR0 = 0b00011011;
}


/**
	Plays music.
*/

void PlayMusic( const int* pMusicNotes /** Pointer to table containing music data */,
				uint8_t tempo /** paying tempo from 0 to 100. Higher value = slower playback*/ )
{
	int duration;
	int note;
	int i;
	uint16_t delay = tempo * 1000;

	while( *pMusicNotes )
	{
		note = *pMusicNotes;
		pMusicNotes++;

		duration = *pMusicNotes;
		pMusicNotes++;

		if( p == note )
		{
			//pause, do not generate any sound
			
		}
		else
		{
			//not a pause, generate tone
			TCCR0 = 0b00011011;
			OCR0 = note;
		}

		for (int i=0;i<duration/4;i++) _delay_ms(150); 

	}
				TCCR0 = 0;
				OCR0 = note;
}

	

// Fur Elise
const int furelise[] = 
{
    e4, 8, d4x, 8, e4, 8, d4x, 8, e4, 8, b3, 8, d4, 8, c4, 8, a3,8, p, 8,
    c3, 8, e3, 8, a3, 8,  b3, 4, p, 8, e3, 8, g3x, 8, b3, 8, c4, 4, p, 8, e3, 8,
    e3, 8, d4x, 8, e4, 8, d4x, 8, e4, 8, b3, 8, d4, 8, c4, 8, a3, 8, p, 8, c3, 8,
    e3, 8, a3, 8, b3, 4, p, 8, e3, 8, c4, 8, b3, 8, a3, 4,
    MUSIC_END
};




main()
{
	InitMusic();

	while(1)
	{



		PlayMusic( furelise, 20 );
		for (int i=0;i<4;i++)
		_delay_ms(1000);



	}

}