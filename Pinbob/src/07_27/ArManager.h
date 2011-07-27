/*
 * ArManager.h
 *
 *  Created on: Jul 19, 2011
 *      Author: yejiabin
 */

#ifndef ARMANAGER_H_
#define ARMANAGER_H_

#include <list>
#include <queue>
#include "irrlicht.h"
#ifdef WIN32
#pragma comment(lib,"irrlicht.lib")
#endif
#include "Score.h"
#include "irrAR.h"
#include "Config.h"
#include "IGameLogic.h"

using namespace irr;

using namespace core;
using namespace scene;
using namespace video;
using namespace io;
using namespace gui;

/* forward declarations */
class Arrow;

enum CONFIG_KEY{
	CAMERA,PATTERNS,VCONF,CONFIG_KEY_LENGTH
};

typedef float pos2d[2];
const char configKeys[CONFIG_KEY_LENGTH][8] = { "camera", "pattern", "vconf" };
const pos2d arrowPos[4] = {{-35,35},{35,35},{35,35},{-35,-35}};

class ArManager {
public:
	friend class IGameLogic;
	friend class DefaultGameLogic;
public:
	/**
	 * The constructor
	 * @param device the irrlicht device pointer for renderring
	 * @param smgr the scene manger pointer for renderring
	 */
	ArManager(IrrlichtDevice* device, ISceneManager* smgr,
			IVideoDriver* driver);
	/**
	 * initialize the armanager by given configuration file
	 * @param filename the filename of the configuration file
	 * @return true if success, otherwise false
	 */
	bool init(const char* filename);
	/************************************************************************/
	/* init for win32 version                                                                     */
	/************************************************************************/
	bool init_win32(const char* cparam_name,const char* patt_name,char* vconf);
	/**
	 * the function update the status of scene that AR simulates
	 * @param deltaTime the current frame timestamp
	 * @param hit the hit information given by main scene
	 */
	void update(u32 deltaTime, u8 hit);
	/**
	 * get the current calculated score to MainScene
	 * @return current score
	 */
	int getScore();
	/**
	 * The destructor
	 */
	virtual ~ArManager();
private:
	/* the speed of dropping arrow */
	float speed;
	/* score information of the current session */
	Score score;
	/* the scene manager */
	IARManager* armgr;
	/* the scene manager passed by parent */
	ISceneManager* smgr;
	/* the video driver passed by parent */
	IVideoDriver* driver;
	/* camera file path */
	char *cparam_name;
	/* pattern file path */
	char *patt_name;
	/* gstreamer string */
	char *vconf;
	/* initialize ar environment for internal call */
	void _initAR();
	/* load arrow information */
	void _loadArrows();
	/* update arrows */
	void _repaintArrows(u32 deltaTime);
	/* our dancer : turtles */
	ISceneNode* turtleNode;
	/* arrow nodes displaying in the scene */
	std::list<Arrow*> arrows;
	/* the parent node of the scene */
	ISceneNode* mainNode;
	/* first iterator for displaying */
	std::list<Arrow*>::iterator sceneCursor;
};

#endif /* ARMANAGER_H_ */