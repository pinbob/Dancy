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
#include "GSTPlayer.h"
#include <cmath>
#include <GL/glu.h>

DefaultGameLogic::DefaultGameLogic(u32 startTime, ArManager* armgr,
		GameInfo* gameInfo, ISoundEngine* soundEngine, GameObject* gameObejct,
		Song* song) :
		startTime(startTime), armgr(armgr), gameObject(gameObject), gameInfo(
				gameInfo), lastHit(0), timePassed(0), state(IG_DETECT), musicState(MUSIC_PRE), musicOffset(0), totalTime(
				0), song(song),currentSong(0) {
	if (song->main_title().at(song->main_title().size() - 1) == '\r') {
		songdir = new char[song->main_title().size()];
		strncpy(songdir, song->main_title().c_str(), song->main_title().size());
		songdir[strlen(songdir)-1] = '\0';
	} else {
			songdir = new char[song->main_title().size()+1];
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
#ifdef USE_IRR
		if (currentSong) { // sanity check
			currentSong->setIsPaused(true);
		}
#else
		gst_pause_song();
#endif
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
		//char* songPath = (char*) malloc(
		//		strlen("Catch Me") + strlen("/usr/local/games/dancy/asset/songs/") + strlen("/01.ogg")
		//				+ 1);
		//sprintf(songPath, "/usr/local/games/dancy/asset/songs/%s/01.ogg", "Catch Me");
#ifdef USE_IRR
		printf("songpath : %s \n", songPath);
		currentSong = soundEngine->play2D(songPath, false, false, true);
		if (songPath) {
			free(songPath);
		}
#else
		//TODO currently the song path is fixed;
		gst_play();
#endif

		musicOffset = timePassed - PREPARE_TIME;
		musicState = MUSIC_PLAYING;
	} else if (musicState == MUSIC_PAUSE) {
#ifdef USE_IRR
		currentSong->setIsPaused(false);
#else
		gst_resume_song();
#endif
		musicState = MUSIC_PLAYING;
	}
//printf("run\n");
	timePassed += delta;
	if (timePassed < PREPARE_TIME) {
		armgr->updateCountdown(timePassed);
	} else if (timePassed < totalTime + PREPARE_TIME){
		armgr->destroyCountdown();
		if (timePassed - PREPARE_TIME < totalTime) {
			float scale = 1.0
					- (float) (timePassed - PREPARE_TIME) / (float) totalTime;
			armgr->updateTime(scale);
		} else {
			// TODO gameover state
		}
	} else {
		return IG_GAMEOVER;
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
			printf("missed\n");
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

void DefaultGameLogic::close() {
	//currentSong->stop();
	// Drop always comes problem waste some memories...
	//currentSong->drop();
	gst_destroy();
	armgr->close();
}

void DefaultGameLogic::_judgeHit(u32 timePassed, u8 hit) {
// determines whether or not there's arrows in the epsilon area
	bool hasArrow = false;
	for (std::list<Arrow*>::iterator hitCursor = armgr->sceneCursor;
			hitCursor != armgr->arrows.end(); hitCursor++) {
		int gap = abs(
				(int) ((*hitCursor)->getStartTime() + PREPARE_TIME + musicOffset
						- timePassed - 800)); //FIXME fix the time bug later
		printf("hit gap %d.\n",gap);
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
	//TODO fix following fixed variable
	char* oggPath = (char*) malloc(
			strlen("Catch Me") + strlen("/usr/local/games/dancy/asset/songs/") + strlen("/default.bms")
					+ 1);
	sprintf(oggPath, "/usr/local/games/dancy/asset/songs/%s/default.bms", "Catch Me");
	notesLoader.LoadFromFile(oggPath, &noteData, loadedSong);
	if (oggPath) {
		free(oggPath);
	}
	//TODO currently the song path is fixed
	gst_init_player("file:///usr/local/games/dancy/asset/songs/Catch Me/01.ogg");

#ifdef SHOW_DEBUG_INFO
	printf("oggpath : %s \n", oggPath);
	printf("song info: title is %s\n", loadedSong.title_.c_str());
#endif


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

#ifdef SHOW_DEBUG_INFO
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

