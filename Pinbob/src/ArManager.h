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
#include "StateMachine.h"

using namespace irr;

using namespace core;
using namespace scene;
using namespace video;
using namespace io;
using namespace gui;

/* forward declarations */
class Arrow;

enum CONFIG_KEY {
	CAMERA, PATTERNS, VCONF, CONFIG_KEY_LENGTH
};

enum HitImage {
	HI_PERFECT, HI_WELL_DONE, HI_GOOD, HI_BAD, HI_MISSED, HI_LENGTH
};


typedef float pos2d[2];
const char configKeys[CONFIG_KEY_LENGTH][8] = { "camera", "pattern", "vconf" };
const pos2d arrowPos[4] = { { -50, 50 }, { 50, 50 }, { 50, 50 }, { -50, -50 } };
const vector3df TIMER_POS = vector3df(0, 64, 200);

static const char* hitImageFile[HI_LENGTH] = { "asset/images/perfect.png",
		"asset/images/wellDone.png", "asset/images/good.png",
		"asset/images/bad.png", "asset/images/missed.png" };

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
			IVideoDriver* driver, StateMachine* state_machine, int modes);
	/**
	 * initialize the armanager by given configuration file
	 * @param filename the filename of the configuration file
	 * @return true if success, otherwise false
	 */
	bool init(const char* filename);
	/************************************************************************/
	/* init for win32 version                                                                     */
	/************************************************************************/
	bool init_win32(const char* cparam_name, const char* patt_name,
			char* vconf);
	/**
	 * the function update the status of scene that AR simulates
	 * @param deltaTime the current frame timestamp
	 * @param hit the hit information given by main scene
	 * @return zero if marker
	 */
	int update(u32 deltaTime, u8 hit);
	void updateTime(float scale);
	/**
	 * get the current calculated score to MainScene
	 * @return current score
	 */
	int getScore();
	void updateCountdown(u32 timePassed);
	void destroyCountdown();
	void close();
	void pushAPattern(const char *patt) {
		if (this->patt_count < 10) {
			this->patt_names[this->patt_count] = strdup(patt);
			this->patt_count ++;
		}
	}
	/**
	 * The destructor
	 */
	virtual ~ArManager();
	u32 getHitImageStatus() const;

	void setMainNodeMaterial(const char *texture_path) {
		sea->setMaterialTexture(0, driver->getTexture(texture_path));
	}
	void setHitImageStatus(u32 hitImageStatus);
	u8 getShowHitPlane() const;
	void setShowHitPlane(u8 showHitPlane);
	int detectedID() { return armgr->getCurrentID(); }
	void setMainNode(int id) {
		armgr->setARSceneNode(mainNode, id);
	}
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
	char *patt_names[10];
	int patt_count;
	/* gstreamer string */
	char vconf[200];
	/* initialize ar environment for internal call */
	void _initAR();
	/* load arrow information */
	void _loadArrows();
	/* update arrows */
	void _repaintArrows(u32 deltaTime);
	/* our dancer : turtles */
	//ISceneNode* turtleNode;
	/* arrow nodes displaying in the scene */
	std::list<Arrow*> arrows;
	/* the parent node of the scene */
	ISceneNode* mainNode;
	/* first iterator for displaying */
	std::list<Arrow*>::iterator sceneCursor;

	ITexture* prepareImage[5];
	ISceneNode* prepareNode;

	ISceneNode* ballNode;
	ISceneNode* hitImageNode;
	ISceneNode* timerNode;
	ITexture* hitImage[HI_LENGTH];

	ISceneNode* comboImageNode;
	ITexture* comboImage;
	ISceneNode* sea; /* Actually, it means mat */

	/* records  hit status */
	u32 hitImageStatus;
	u32 lastHitStatus;
	f32 hitImageScale;

	int modes;

};

#endif /* ARMANAGER_H_ */
