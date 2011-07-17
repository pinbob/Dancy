/*
 * Config.h
 *
 *  Created on: 2011-7-16
 *      Author: Ye Jiabin
 */

/* defines pre-complied marcos */

#ifndef CONFIG_H_
#define CONFIG_H_

#define MENU 0
#define UP_LEFT_AREA 1
#define DOWN_LEFT_AREA 2
#define UP_RIGHT_AREA 3
#define DOWN_RIGHT_AREA 4
#define LEFT_BAR 5
#define RIGHT_BAR 6
#define UP_LEFT_ARROW 7
#define DOWN_LEFT_ARROW 8
#define UP_RIGHT_ARROW 9
#define DOWN_RIGHT_ARROW 10

/* hit check */
#define UP_LEFT_HIT 01
#define DOWN_LEFT_HIT 02
#define UP_RIGHT_HIT 04
#define DOWN_RIGHT_HIT 010

/* game status */
//TODO the game procedured may change
#define PREPARE 0
#define IN_GAME 1
#define GAME_OVER 2



#endif /* CONFIG_H_ */
