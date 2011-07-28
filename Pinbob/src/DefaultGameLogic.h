/*
 * DefaultGameLogic.h
 *
 *  Created on: Jul 24, 2011
 *      Author: yejiabin
 */

#ifndef DEFAULTGAMELOGIC_H_
#define DEFAULTGAMELOGIC_H_

#include "IState.h"
#include "IGameLogic.h"
#include <list>
#include "Arrow.h"
#include "ArManager.h"

class DefaultGameLogic: public IGameLogic {
public:
	friend class ArManager;
	DefaultGameLogic(u32 startTime, ArManager* armgr,GameInfo* gameinfo);

	/**
	 * Override the parent update function
	 */
	virtual int update(u32 delta, u32 now, u8 hit);

	virtual ~DefaultGameLogic();
protected:
	void _judgeHit(u32 now, u8 hit);
	// TODO automatically generating arrows according a
	// specific file
	void _init(const char* filename);
	/* a pointer determines current playing progress */
	std::list<Arrow*>::iterator creationCursor;
	std::list<Arrow*>::iterator missedCursor;
	ArManager* armgr;
	GameInfo* gameInfo;
	u32 state;
	u32 startTime;
	u32 timePassed;
	u8 lastHit;
};

#endif /* DEFAULTGAMELOGIC_H_ */
