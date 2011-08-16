/*
 * Config.h
 *
 *  Created on: 2011-7-16
 *      Author: Ye Jiabin
 */

/* defines pre-complied marcos */

#ifndef CONFIG_H_
#define CONFIG_H_



/* hit check */
#define UP_LEFT_HIT 01
#define DOWN_LEFT_HIT 02
#define UP_RIGHT_HIT 04
#define DOWN_RIGHT_HIT 010
#define MENU_HIT 020

/* game status */
//TODO the game procedured may change
#define PREPARE 0
#define IN_GAME 1
#define GAME_OVER 2

/* defines the arrow height */
#define ARROW_HEIGHT 150.0
#define SPEED .05
#define TIME_ELAPSED 3000 // ARROW_HEIGHT/SPEED

#define SCORE_WIDTH 5
#define COMBO_WIDTH 3

#endif /* CONFIG_H_ */
