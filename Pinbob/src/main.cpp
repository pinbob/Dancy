/*
 * main.cpp
 *
 *  Created on: Jul 19, 2011
 *      Author: yejiabin
 */

#ifdef TEST

#include <irrlicht.h>
#include <iostream>
#include "ArManager.h"
#include "MyEventReceiver.h"

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
	MyEventReceiver::SMouseState mouseState;
	/* calls ar manager */
	ArManager* arMgr = new ArManager(device, smgr, driver);
	arMgr->init("asset/conf/ar.conf");
	int lastFPS = -1;
	u32 then = device->getTimer()->getTime();
	while (device->run()) {
		if (device->isWindowActive()) {
			const u32 now = device->getTimer()->getTime();
			const u32 deltaTime = now - then; // in ms
			then = now;
			driver->beginScene(true, true, SColor(255, 0, 0, 0));

			smgr->drawAll();
			guienv->drawAll();
			driver->endScene();
			//Shows FPS in the title screen
			int fps = driver->getFPS();
			if (lastFPS != fps) {
				core::stringw str = L"Pinbob [";
				str += driver->getName();
				str += "] FPS:";
				str += fps;
				device->setWindowCaption(str.c_str());
				lastFPS = fps;
			}

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
