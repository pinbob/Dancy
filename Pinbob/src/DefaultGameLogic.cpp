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
#include <cmath>

DefaultGameLogic::DefaultGameLogic(u32 startTime, ArManager* armgr) :
		startTime(startTime), armgr(armgr), gameInfo(new GameInfo) {
	armgr->init("asset/conf/ar.conf");
	//TODO OKay, no file name specified
	_init(NULL);
}

DefaultGameLogic::~DefaultGameLogic() {
	delete gameInfo;
}

int DefaultGameLogic::update(u32 delta, u32 now, u8 hit) {
	// check new arrows to be show

	armgr->update(delta, hit);
	for (; creationCursor != armgr->arrows.end(); creationCursor++) {
		if (now > (*creationCursor)->getStartTime()) {
			(*creationCursor)->setArrowNode(
					ArrowPrototypeFactory::getInstance()->getArrowPrototype(
							(*creationCursor)->getArrowType()));
		} else {
			break;
		}
	}
	if (hit != 0) {
		for (u8 i = 1; i <= MENU_HIT; i <<= 1) {
			if (hit & i) {
				_judgeHit(now, i);
			}
		} // end for
	} // end if
	return 0;
}

// TODO remove it
#define DEFAULT_EPSILON 300
void DefaultGameLogic::_judgeHit(u32 now, u8 hit) {
	u32 real = now - startTime;
	for (; hitCursor != armgr->arrows.end(); hitCursor++) {
		if (abs((*hitCursor)->getStartTime() + TIME_ELAPSED - real)
				< DEFAULT_EPSILON) {
			// TODO handle increment score
			printf("hitted.\n");
		} else {
			// TODO handle decrement score and miss
			printf("missed.\n");
			break;
		}
	}
}

void DefaultGameLogic::_init(const char *filename) {
	// TODO maybe do something
	// FILE* fp = fopen(filename, "r");
	// fread();
	// fclose(fp);

	// TODO delete following lines , I randomly generated
	// some arrows
	for (int i = 0; i < 10; i++) {
		armgr->arrows.push_back(
				ArrowFactory::getInstance()->getDefaultArrow(1 << (rand() % 4),
						(rand() % 10) * 1000, 0));
	}
	// TODO delete following lines
#ifdef DEBUG_SHOW_ARROW_GENERATION
	printf("Generating following %d arrows:\n", armgr->arrows.size());
	for (std::list<Arrow*>::iterator iter = armgr->arrows.begin();
			iter != armgr->arrows.end(); iter++) {
		printf("arrows: type %d\n", (*iter)->getArrowType());
	}
	printf("print over\n");
#endif
	creationCursor = armgr->arrows.begin();
	hitCursor = armgr->arrows.begin();
}

