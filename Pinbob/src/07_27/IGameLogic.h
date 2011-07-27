/*
 * IGameLogic.h
 *
 *  Created on: Jul 24, 2011
 *      Author: yejiabin
 */

#ifndef IGAMELOGIC_H_
#define IGAMELOGIC_H_

#include "GameInfo.h"
#include "ArManager.h"

typedef enum {
	GAME_READY, // show count-down animation
	GAME_START, // in normal playing mode
	GAME_PAUSED, // game is paused, and a menu is shown
	GAME_END
// game is over when time's up
} DEFAULT_STATE;

class IGameLogic {
public:
	virtual int update(u32 delta, u32 now, u8 hit) = 0;
	virtual u32 getState() const {
		return state;
	}
	virtual void setState(u32 newState) {
		state = newState;
	}
protected:
	friend class ArManager;
	u32 state;

};

#endif /* IGAMELOGIC_H_ */
