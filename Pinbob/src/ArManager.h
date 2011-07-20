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
#include <irrlicht.h>
#include "Score.h"
#include "irrAR.h"

using namespace irr;

using namespace core;
using namespace scene;
using namespace video;
using namespace io;
using namespace gui;

/* forward declarations */
class Arrow;

#define CONFIG_KEY_LENGTH 3
#define CAMERA 0
#define PATTERN 1
#define VCONF 2
const char configKeys[CONFIG_KEY_LENGTH][8] = { "camera", "pattern", "vconf" };

class ArManager {
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
	/**
	 * the function update the status of scene that AR simulates
	 * @param last the last frame timestamp
	 * @param now the current frame timestamp
	 * @param hit the hit information given by main scene
	 */
	void update(u32 last, u32 now, u8 hit);
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
	/* the arrows wait for displaying */
	std::queue<Arrow> arrowQueue;
	/* the arrows displaying in the scene */
	std::list<Arrow> displayQueue;
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
};

#endif /* ARMANAGER_H_ */
