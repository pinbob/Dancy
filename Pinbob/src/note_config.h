#ifndef NOTE_CONFIG_H
#define NOTE_CONFIG_H

#ifndef DEBUG__
#define DEBUG__
#endif /* DEBUG__ */

#define MAX_NOTE_PANELS 4

const int BEATS_PER_MEASURE = 4;
const int ROWS_PER_BEAT	= 48;    // It is important that this number is evenly divisible by 2, 3, and 4.
const int ROWS_PER_MEASURE = ROWS_PER_BEAT * BEATS_PER_MEASURE;

const unsigned MAX_NUM_ATTACKS = 2*2*2;	// 3 bits to hold the attack index currently

#define min(x, y) ((x) > (y)? (y): (x))
#define isint(x) ((x) >= 48 && (x) <= 57 ? true:false)

#endif /* NOTE_CONFIG_H */
