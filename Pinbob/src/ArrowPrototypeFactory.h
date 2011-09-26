/*
 * ArrowPrototypeFactory.h
 *
 *  Created on: Jul 22, 2011
 *      Author: yejiabin
 */

#ifndef ARROWPROTOTYPEFACTORY_H_
#define ARROWPROTOTYPEFACTORY_H_

#include "irrlicht.h"
#ifdef WIN32
#pragma comment(lib,"irrlicht.lib")
#endif

using namespace irr;

using namespace core;
using namespace scene;
using namespace video;
using namespace io;
using namespace gui;

struct ArrowInfo {
	float posX, posY;
	const char *texture;
};
#define DIST 37
#define CENTER_X 0
#define CENTER_Y 0

const ArrowInfo ARROW_INFOS[4] = {
		{ CENTER_X+DIST, CENTER_Y-DIST, "asset/images/ulArrowGame.tga" },
		{ CENTER_X+DIST, CENTER_Y+DIST,"asset/images/dlArrowGame.tga" },
		{ CENTER_X-DIST, CENTER_Y-DIST,"asset/images/urArrowGame.tga" },
		{ CENTER_X-DIST, CENTER_Y+DIST,"asset/images/drArrowGame.tga" } };

class ArrowPrototypeFactory {
public:
	static ArrowPrototypeFactory* getInstance() {
		if (_instance == 0) {
			_instance = new ArrowPrototypeFactory;
		}
		return _instance;
	}

	void createFactory(ISceneManager* smgr, IVideoDriver* driver,
			ISceneNode* parent);

	/**
	 * The offset of the height (for sync time)
	 */
	ISceneNode* getArrowPrototype(unsigned char type, float offset = 0.0);
protected:
	ArrowPrototypeFactory();
private:
	static ArrowPrototypeFactory* _instance;
	virtual ~ArrowPrototypeFactory();

	ISceneNode* prototypes[4];
	ISceneNode* parent;
	ISceneManager* smgr;
};

#endif /* ARROWPROTOTYPEFACTORY_H_ */
