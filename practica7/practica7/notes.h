/*
ICR values for AVR micro controllers to play sound using PWM.
System clock:   8000000 [Hz]
Prescaler:      8
PWM mode:       phase/frequency correct 16 bit

This file was automatically generated using script from 
http://aquaticus.info/pwm-music
*/

#ifndef __PWM_NOTES_H__
#define __PWM_NOTES_H__

/* Pause */

#define P 1
#define PAUSE P
#define p P

/* end of notes table */
#define MUSIC_END 0

/* There are 12 notes in octave + variations (lower case, other names)  */


/* Octave #3 */

#define A3   71 	/* PWM: 219.97 Hz, note freq: 220.00 Hz, error 0.01% */
#define a3   71 	/* PWM: 219.97 Hz, note freq: 220.00 Hz, error 0.01% */
#define b3   63 	/* PWM: 246.91 Hz, note freq: 246.94 Hz, error 0.01% */
#define c3   120   /* PWM: 130.82 Hz, note freq: 130.81 Hz, error 0.01% */
#define E3   95 	/* PWM: 164.80 Hz, note freq: 164.81 Hz, error 0.01% */
#define e3   95 	/* PWM: 164.80 Hz, note freq: 164.81 Hz, error 0.01% */
#define G3x  75 	/* PWM: 207.64 Hz, note freq: 207.65 Hz, error 0.01% */
#define g3x  75 	/* PWM: 207.64 Hz, note freq: 207.65 Hz, error 0.01% */

/* Octave #4 */

#define C4   60 	/* PWM: 261.64 Hz, note freq: 261.63 Hz, error 0.01% */
#define c4   60 	/* PWM: 261.64 Hz, note freq: 261.63 Hz, error 0.01% */
#define e4   47   /* PWM: 329.60 Hz, note freq: 329.63 Hz, error 0.01% */
#define D4   53 	/* PWM: 293.60 Hz, note freq: 293.66 Hz, error 0.02% */
#define d4   53 	/* PWM: 293.60 Hz, note freq: 293.66 Hz, error 0.02% */
#define D4x  50 	/* PWM: 311.14 Hz, note freq: 311.13 Hz, error 0.00% */
#define d4x  50 	/* PWM: 311.14 Hz, note freq: 311.13 Hz, error 0.00% */



#endif /* __PWM_NOTES_H__ */
