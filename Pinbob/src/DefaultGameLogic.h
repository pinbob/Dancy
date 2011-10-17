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
#include "../include/conio.h"
#ifdef USE_IRR
#include "irrKlang.h"
#endif
#include "NotesLoader.h"
#include "NoteData.h"
#include "SongCollection.h"

class ArManager;
class GameObject;

//enum MUSIC_STATE {
#define 	MUSIC_PRE 0
#define 	MUSIC_PLAYING 1
#define	 MUSIC_PAUSE 2
//} ;

#define FAIL_COUNT 20
#define PREPARE_TIME 5000

class DefaultGameLogic: public IGameLogic {
public:
	friend class ArManager;
	DefaultGameLogic(u32 startTime, ArManager* armgr, GameInfo* gameinfo,
			GameObject* gameObject, SongCollection* songs, int modes);

	/**
	 * Override the parent update function
	 */
	virtual int update(u32 delta, u32 now, u8 hit);
	virtual void close();
	virtual ~DefaultGameLogic();
	u32 getState() const;
	void setState(u32 state);
protected:
	void _judgeHit(u32 now, u8 hit);
	// TODO automatically generating arrows according a
	// specific file
	void _init(int id);
	/* a pointer determines current playing progress */
	std::list<Arrow*>::iterator creationCursor;
	std::list<Arrow*>::iterator missedCursor;
	int modes;
	ArManager* armgr;
	GameInfo* gameInfo;
	GameObject* gameObject;
	u32 state;
	/* variables controlling time */
	u32 startTime;
	u32 timePassed;
	u32 totalTime;
	u8 lastHit;
	u32 musicOffset;

#ifdef USE_IRR
	ISoundEngine* soundEngine;
#endif

	NotesLoader notesLoader;
	NoteData noteData;
	int musicState;
	char* songdir;
	SongCollection* songs;
};

#endif /* DEFAULTGAMELOGIC_H_ */
