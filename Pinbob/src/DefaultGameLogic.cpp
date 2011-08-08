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
		GameInfo* gameInfo, ISoundEngine* soundEngine, GameObject* gameObejct) :
		startTime(startTime), armgr(armgr), gameInfo(gameInfo), lastHit(0), timePassed(
				0), state(IG_DETECT), soundEngine(soundEngine), musicState(
				MUSIC_PRE), gameObject(gameObject), musicOffset(0) {
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
	} else if (state == IG_DETECT) {
		if (armgr->update(0, hit)) {
			printf("detected.\n");
			state = IG_UPDATE;
			return state;
		} else {
			// marker still not detect
			return IG_DETECT;
		}
	}

	if (musicState == MUSIC_PRE && timePassed > PREPARE_TIME) {
		soundEngine->play2D("./asset/models/Canon.ogg", true);
		musicOffset = timePassed - PREPARE_TIME;
		musicState = MUSIC_PLAYING;
	}
	//printf("run\n");
	timePassed += delta;
	if (timePassed < PREPARE_TIME) {
		armgr->updateCountdown(timePassed);
	} else {
		armgr->destroyCountdown();
	}
	armgr->update(delta, hit);
	for (; creationCursor != armgr->arrows.end(); creationCursor++) {
		if (timePassed + TIME_ELAPSED
				> (*creationCursor)->getStartTime() + PREPARE_TIME + musicOffset) {
			float offset = (timePassed + TIME_ELAPSED
					- (*creationCursor)->getStartTime() - PREPARE_TIME
					+ musicOffset) * SPEED;
			(*creationCursor)->setArrowNode(
					ArrowPrototypeFactory::getInstance()->getArrowPrototype(
							(*creationCursor)->getArrowType(), offset));

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
		for (u8 i = 0; i < 4; i++) {

			if (hit & (1 << i)) {

				_judgeHit(timePassed, 1 << i);
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
	//printf("hit is %d\n", hit);
	for (std::list<Arrow*>::iterator hitCursor = armgr->sceneCursor;
			hitCursor != armgr->arrows.end(); hitCursor++) {
		int gap = abs(
				(int) ((*hitCursor)->getStartTime() + PREPARE_TIME + musicOffset
						- timePassed));
		//printf("hit gap %d.\n",);
		if ((*hitCursor)->getArrowNode() == 0 || gap > BAD_EPSILON) {
			break;
		}
		hasArrow = true;
#ifdef _DEBUG
		printf(
				"cursor type: %d, st: %d, cal: %f",
				(*hitCursor)->getArrowType(),
				(*hitCursor)->getStartTime(),
				abs(
						(int) ((*hitCursor)->getStartTime() + TIME_ELAPSED
								- timePassed)));
#endif
		if ((1 << (*hitCursor)->getArrowType()) & hit) {
			// TODO handle increment score
			(*hitCursor)->setHitted(true);
			if (gap < PERFECT_EPSILON) {
				gameInfo->getScore()->perfectHit();
				armgr->setHitImageStatus(HI_PERFECT);
				printf("perfect hit\n");
			} else if (gap < WELLDONE_EPSILON) {
				gameInfo->getScore()->wellDoneHit();
				printf("well done hit\n");
			} else if (gap < GOOD_EPSILON) {
				gameInfo->getScore()->goodHit();
				printf("good hit\n");
			} else {
				gameInfo->getScore()->badHit();
				printf("bad hit\n");
			}
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
	// TODO pass the filename of the song

	// TODO like the song file it should load a certain BSM
	notesLoader.LoadFromFile(NULL, &noteData);
	// TODO maybe do something
	// FILE* fp = fopen(filename, "r");
	// fread();
	// fclose(fp);

	// TODO delete following lines , I randomly generated
	// some arrows
	//noteData.get_panel()
	ROW row;
	u32 arrs;
	for (int i = 0; i < 400; i++) {
		row = noteData.GetNoteAtTime(i * 80);
		if (BITFLAG(row)) {
			arrs = row.left_ ? UP_LEFT_HIT : 0 | row.right_ ? UP_RIGHT_HIT :
					0 | row.down_ ? DOWN_LEFT_HIT :
					0 | row.up_ ? DOWN_RIGHT_HIT : 0;
			armgr->arrows.push_back(
					ArrowFactory::getInstance()->getDefaultArrow(arrs, (i) * 80,
							0));
		}
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

u32 DefaultGameLogic::getState() const {
	return state;
}

void DefaultGameLogic::setState(u32 state) {
	this->state = state;
}

