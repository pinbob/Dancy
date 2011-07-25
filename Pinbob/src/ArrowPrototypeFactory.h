/*
 * ArrowPrototypeFactory.h
 *
 *  Created on: Jul 22, 2011
 *      Author: yejiabin
 */

#ifndef ARROWPROTOTYPEFACTORY_H_
#define ARROWPROTOTYPEFACTORY_H_

#include <irrlicht.h>

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
const ArrowInfo ARROW_INFOS[4] = {
		{ 35, -35, "asset/images/ulArrowGame.tga" },
		{ 35, 35,"asset/images/dlArrowGame.tga" },
		{ -35, -35,"asset/images/urArrowGame.tga" },
		{ -35, 35,"asset/images/drArrowGame.tga" } };

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

	ISceneNode* getArrowPrototype(unsigned char type);
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
