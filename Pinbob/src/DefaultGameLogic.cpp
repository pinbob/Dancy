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
#include <GL/glu.h>

DefaultGameLogic::DefaultGameLogic(u32 startTime, ArManager* armgr,
		GameInfo* gameInfo, ISoundEngine* soundEngine, GameObject* gameObejct,
		Song* song) :
		startTime(startTime), armgr(armgr), gameObject(gameObject), gameInfo(
				gameInfo), lastHit(0), timePassed(0), state(IG_DETECT), soundEngine(
				soundEngine), musicState(MUSIC_PRE), musicOffset(0), totalTime(
				0), song(song),currentSong(0) {
	if (song->main_title().at(song->main_title().size() - 1) == '\r') {
		songdir = new char[song->main_title().size()];
		strncpy(songdir, song->main_title().c_str(), song->main_title().size());
		songdir[strlen(songdir)-1] = '\0';
	} else {
			songdir = new char[strlen(song->main_title().c_str())+1];
			strcpy(songdir,song->main_title().c_str());
		}
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
		if (currentSong) { // sanity check
			currentSong->setIsPaused(true);
		}
		musicState = MUSIC_PAUSE;
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
		char* songPath = (char*) malloc(
				strlen(songdir) + strlen("asset/songs/") + strlen("/01.ogg")
						+ 1);
		sprintf(songPath, "asset/songs/%s/01.ogg", songdir);
#ifdef TEST_ALL
		printf("songpath : %s \n", songPath);
		currentSong = soundEngine->play2D(songPath, false, false, true);
#elif defined TEST_GAME
		soundEngine->play2D("./asset/songs/Canon.ogg", true);
#endif
		if (songPath) {
			free(songPath);
		}
		musicOffset = timePassed - PREPARE_TIME;
		musicState = MUSIC_PLAYING;
	} else if (musicState == MUSIC_PAUSE) {
		currentSong->setIsPaused(false);
		musicState = MUSIC_PLAYING;
	}
//printf("run\n");
	timePassed += delta;
	if (timePassed < PREPARE_TIME) {
		armgr->updateCountdown(timePassed);
	} else {
		armgr->destroyCountdown();
		if (timePassed - PREPARE_TIME < totalTime) {
			float scale = 1.0
					- (float) (timePassed - PREPARE_TIME) / (float) totalTime;
			armgr->updateTime(scale);
		} else {
			// TODO gameover state
		}
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
//		printf(
//				"cursor type: %d, st: %d, cal: %f",
//				(*hitCursor)->getArrowType(),
//				(*hitCursor)->getStartTime(),
//				abs(
//						(int) ((*hitCursor)->getStartTime() + TIME_ELAPSED
//								- timePassed)));
#endif
		if ((1 << (*hitCursor)->getArrowType()) & hit) {
			(*hitCursor)->setHitted(true);
			bool hasCombo = true;
			if (gap < PERFECT_EPSILON) {
				gameInfo->getScore()->perfectHit();
				armgr->setHitImageStatus(HI_PERFECT);
			} else if (gap < WELLDONE_EPSILON) {
				gameInfo->getScore()->wellDoneHit();
				armgr->setHitImageStatus(HI_WELL_DONE);
			} else if (gap < GOOD_EPSILON) {
				gameInfo->getScore()->goodHit();
				armgr->setHitImageStatus(HI_GOOD);
			} else {
				gameInfo->getScore()->badHit();
				armgr->setHitImageStatus(HI_BAD);
				hasCombo = false;
			}

		} else {
			break;
		}
	}
}

void DefaultGameLogic::_init(const char *filename) {
// TODO pass the filename of the song
	SongInfo loadedSong;
	char* oggPath = (char*) malloc(
			strlen(songdir) + strlen("asset/songs/") + strlen("/default.bms")
					+ 1);
	sprintf(oggPath, "asset/songs/%s/default.bms", songdir);
#ifdef TEST_ALL
	printf("oggpath : %s \n", oggPath);

	notesLoader.LoadFromFile(oggPath, &noteData, loadedSong);
#elif defined TEST_GAME
	notesLoader.LoadFromFile("asset/songs/OBLIVION_7a.bms", &noteData,
			loadedSong);
#endif
	if (oggPath) {
		free(oggPath);
	}
	printf("song info: title is %s\n", loadedSong.title_.c_str());

// TODO song length must be specified
	totalTime = static_cast<u32>(song->time())*1000; // I use 100 seconds for total time arbitrarily
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
#ifdef DEBUG_SHOW_ARROW_GENERATION
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

