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

#define SCREEN_WIDTH 1024
#define SCREEN_HEIGHT 600

#define MENU_WIDTH 190
#define MENU_HEIGHT 70

#define ARROW_WIDTH 130
//#define ARROW_HEIGHT 110

#define GP_WIDTH 240
#define GP_TITLE_HEIGHT 80
#define GP_HEIGHT 50
#define GP_AMT 3

#define DETECT_WIDTH 400
#define DETECT_HEIGHT 200

#endif /* CONFIG_H_ */
