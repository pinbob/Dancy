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
		GameInfo* gameInfo, GameObject* gameObejct, SongCollection* songs,
		int modes) :
		startTime(startTime), armgr(armgr), gameObject(gameObject), gameInfo(
				gameInfo), lastHit(0), timePassed(0), state(IG_DETECT), musicState(
				MUSIC_PRE), musicOffset(0), totalTime(0), songs(songs), modes(
				modes) {

	char pattPath[128];
	for (int i = 0; i < songs->song_list().size(); i++) {
		sprintf(pattPath, "/usr/local/games/dancy/asset/songs/%s/pat",
				songs->GetSong(i).main_title().c_str());
		armgr->pushAPattern(pattPath);
	}


#ifdef WIN32
	armgr->init_win32("asset/win32_ar/Data/camera_para.dat","asset/win32_ar/Data/patt.hiro","asset/win32_ar/Data\\WDM_camera_flipV.xml");
#else
	armgr->init("asset/conf/ar.conf");
#endif
//TODO OKay, no file name specified
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
		if ((modes & NO_SOUND) == 0) {
			gst_pause_song();
		}
#endif
		musicState = MUSIC_PAUSE;
		return IG_PAUSE;
	} else if (state == IG_DETECT) {
		if (hit == MENU_HIT) {
			state = IG_PAUSE;
			return IG_PAUSE;
		}
		if (armgr->update(0, hit)) {
			printf("detected.\n");
			_init(armgr->detectedID());
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
		if ((modes & NO_SOUND) == 0) {
			puts("calls gst play");
			gst_play();
		}
#endif

		musicOffset = timePassed - PREPARE_TIME;
		musicState = MUSIC_PLAYING;
	} else if (musicState == MUSIC_PAUSE) {
#ifdef USE_IRR
		currentSong->setIsPaused(false);
#else
		if ((modes & NO_SOUND) == 0) {
			gst_resume_song();
		}
#endif
		musicState = MUSIC_PLAYING;
	}
//printf("run\n");
	timePassed += delta;
	if (timePassed < PREPARE_TIME) {
		armgr->updateCountdown(timePassed);
	} else if (timePassed < totalTime + PREPARE_TIME) {
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
	//printf("current Time: %d, delta: %d\n", timePassed, delta);
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
			if ((modes & NO_FAIL) == 0 &&
					gameInfo->getScore()->getMissedCount() >= FAIL_COUNT) {
				return IG_GAMEOVER;
			}
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
	if ((modes & NO_SOUND) == 0) {
		gst_destroy();
	}
	armgr->close();
}

void DefaultGameLogic::_judgeHit(u32 timePassed, u8 hit) {
// determines whether or not there's arrows in the epsilon area
	for (std::list<Arrow*>::iterator hitCursor = armgr->sceneCursor;
			hitCursor != armgr->arrows.end(); hitCursor++) {
		int gap = abs(
				(int) ((*hitCursor)->getStartTime() + PREPARE_TIME + musicOffset
						- timePassed)); //FIXME fix the time bug later
		if ((*hitCursor)->getArrowNode() == 0)
			break;

		if ( gap > BAD_EPSILON) {
			break;
		}
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

void DefaultGameLogic::_init(int id) {
// TODO pass the filename of the song
	printf("Init id is %d\n", id);
	SongInfo loadedSong;
	//TODO fix following fixed variable
	Song *song = &songs->GetSong(id);
	char oggPath[128];
	char songPath[128];

	armgr->setMainNode(id);
	sprintf(oggPath, "/usr/local/games/dancy/asset/songs/%s/default.bms",
			song->main_title().c_str());

	notesLoader.LoadFromFile(oggPath, &noteData, loadedSong);

	//TODO currently the song path is fixed
	if ((modes & NO_SOUND) == 0) {
		sprintf(songPath, "file:///usr/local/games/dancy/asset/songs/%s/01.ogg",
				song->main_title().c_str());
		gst_init_player(songPath);
		printf("songPath is %s.\n", songPath);
	}
#ifdef SHOW_DEBUG_INFO
	printf("oggpath : %s \n", oggPath);
	printf("song info: title is %s\n", loadedSong.title_.c_str());
#endif

	totalTime = static_cast<u32>(song->time()) * 1000; // I use 100 seconds for total time arbitrarily
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

#ifdef _DEBUG
	printf("Generating following %d arrows:\n", armgr->arrows.size());
	for (std::list<Arrow*>::iterator iter = armgr->arrows.begin();
			iter != armgr->arrows.end(); iter++) {
		printf("arrows: type %d, time %d\n", (*iter)->getArrowType(),
				(*iter)->getStartTime());
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

