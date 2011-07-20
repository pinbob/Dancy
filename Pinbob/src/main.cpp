/*
 * main.cpp
 *
 *  Created on: Jul 19, 2011
 *      Author: yejiabin
 */

#ifndef TEST

#include <irrlicht.h>
#include <iostream>
#include "ArManager.h"

using namespace irr;

using namespace core;
using namespace scene;
using namespace video;
using namespace io;
using namespace gui;

int main(int argc, char** argv) {
#ifdef TEST_ARMANAGER
	IrrlichtDevice *device = createDevice(video::EDT_OPENGL,
			dimension2d<u32>(640, 480), 24, false, false, false, 0);
	if (!device)
		return 1;
	IVideoDriver* driver = device->getVideoDriver();
	ISceneManager* smgr = device->getSceneManager();
	IGUIEnvironment* guienv = device->getGUIEnvironment();

	/* calls ar manager */
	ArManager* arMgr = new ArManager(device, smgr, driver);
	arMgr->init("asset/conf/ar.conf");
	while (device->run()) {
		if (device->isWindowActive()) {
			driver->beginScene(true, true, SColor(255, 0, 0, 0));
			arMgr->update(0, 0, 0);
			smgr->drawAll();
			guienv->drawAll();
			driver->endScene();
		} else {
			device->yield();
		}
	}
	delete arMgr;
	driver->drop();

#endif
	return 0;
}

#endif
