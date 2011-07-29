/*
 * DefaultGameLogic.cpp
 *
 *  Created on: Jul 24, 2011
 *      Author: yejiabin
 */

#include "DefaultGameLogic.h"
#include "Config.h"
#include "ArrowFactory.h"
#include "ArrowPrototypeFactory.h"
#include "GameObject.h"
#include <cmath>

DefaultGameLogic::DefaultGameLogic(u32 startTime, ArManager* armgr,
		GameInfo* gameInfo) :
		startTime(startTime), armgr(armgr), gameInfo(gameInfo), lastHit(0),
		timePassed(0), state(IG_UPDATE) {
#ifdef WIN32
	armgr->init_win32("asset/win32_ar/Data/camera_para.dat","asset/win32_ar/Data/patt.hiro","asset/win32_ar/Data\\WDM_camera_flipV.xml");
#else
	armgr->init("asset/conf/ar.conf");
#endif
	//TODO OKay, no file name specified
	_init(NULL);
}

DefaultGameLogic::~DefaultGameLogic() {
	delete gameInfo;
}

int DefaultGameLogic::update(u32 delta, u32 now, u8 hit) {
	// check new arrows to be show
	// TODO maybe there's a bug
	if (((hit == MENU_HIT) && state == IG_UPDATE) || state == IG_PAUSE) {
		state = IG_PAUSE;
		armgr->update(0, hit);
		//printf("paused\n");
		return IG_PAUSE;
	}
	//printf("run\n");
	timePassed += delta;
	armgr->update(delta, hit);
	for (; creationCursor != armgr->arrows.end(); creationCursor++) {
		if (timePassed > (*creationCursor)->getStartTime()) {
			(*creationCursor)->setArrowNode(
					ArrowPrototypeFactory::getInstance()->getArrowPrototype(
							(*creationCursor)->getArrowType()));
		} else {
			break;
		}
	}
	//calculate missing
	for (; missedCursor != armgr->sceneCursor; missedCursor++) {
		if (!(*missedCursor)->isHitted()) {
			gameInfo->getScore()->missedHit();
		}
	}
	//increment hit cursor
	if (hit != lastHit && hit != 0) {
		for (u8 i = 1; i <= MENU_HIT; i <<= 1) {
			if (hit & i) {
				_judgeHit(timePassed, i);
			}
		} // end for
	} // end if
	lastHit = hit;
	return IG_UPDATE;
}

// TODO remove it
#define DEFAULT_EPSILON 500
void DefaultGameLogic::_judgeHit(u32 timePassed, u8 hit) {
	// determines whether or not there's arrows in the epsilon area
	bool hasArrow = false;
	for (std::list<Arrow*>::iterator hitCursor = armgr->sceneCursor;
			hitCursor != armgr->arrows.end(); hitCursor++) {
		if ((*hitCursor)->getArrowNode() == 0
				|| abs((int)((*hitCursor)->getStartTime() + TIME_ELAPSED - timePassed))
						> DEFAULT_EPSILON) {
			break;
		}
		hasArrow = true;
		printf("cursor type: %d, st: %d, cal: %f", (*hitCursor)->getArrowType(),
				(*hitCursor)->getStartTime(),
				abs((int)((*hitCursor)->getStartTime() + TIME_ELAPSED - timePassed)));
		if ((1 << (*hitCursor)->getArrowType()) & hit) {
			// TODO handle increment score
			(*hitCursor)->setHitted(true);
			gameInfo->getScore()->perfectHit();
			printf(" %d (hit).\n", hit);
		} else {
			// TODO handle decrement score and miss
			//gameInfo->getScore()->missedHit();
			break;
		}
	}
	if (!hasArrow) {
		//gameInfo->getScore()->missedHit();
	}
}

void DefaultGameLogic::_init(const char *filename) {
	// TODO maybe do something
	// FILE* fp = fopen(filename, "r");
	// fread();
	// fclose(fp);

	// TODO delete following lines , I randomly generated
	// some arrows
	for (int i = 0; i < 40; i++) {
		armgr->arrows.push_back(
				ArrowFactory::getInstance()->getDefaultArrow(1 << (rand() % 4),
						(i) * 1000, 0));
	}
	armgr->sceneCursor = armgr->arrows.begin();
	// TODO delete following lines
#ifndef DEBUG_SHOW_ARROW_GENERATION
	printf("Generating following %d arrows:\n", armgr->arrows.size());
	for (std::list<Arrow*>::iterator iter = armgr->arrows.begin();
			iter != armgr->arrows.end(); iter++) {
		printf("arrows: type %d\n", (*iter)->getArrowType());
	}
	printf("print over\n");
#endif
	creationCursor = armgr->arrows.begin();
	missedCursor = armgr->arrows.begin();
}

u32 DefaultGameLogic::getState() const
{
    return state;
}

void DefaultGameLogic::setState(u32 state)
{
    this->state = state;
}



