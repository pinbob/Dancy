/*
 * main.cpp
 *
 *  Created on: Jul 17, 2011
 *      Author: yejiabin
 */

#include <irrlicht.h>
#include <iostream>
#include "MyEventReceiver.h"

using namespace irr;

using namespace core;
using namespace scene;
using namespace video;
using namespace io;
using namespace gui;

/* global variables */
IrrlichtDevice *device;
ISceneManager* smgr;
IGUIEnvironment* guienv;
IVideoDriver *driver;
ITexture** images;

const int IMG_LENGTH = 7;
const int RESOURCE_LENGTH = 11;

//typedef float pointf2D[2];

char* filenames[] = {"asset/images/menu.png",
		"asset/images/ulArea.png","asset/images/dlArea.png",
		"asset/images/urArea.png","asset/images/drArea.png",
		"asset/images/lBar.png","asset/images/rBar.png",
		"asset/images/ulArrow.png","asset/images/dlArrow.png",
		"asset/images/urArrow.png","asset/images/drArrow.png"};

core::position2d<s32> imgPos[IMG_LENGTH] = {
		position2d<s32>(225,350),position2d<s32>(0,210),
		position2d<s32>(0,320),position2d<s32>(550,210),
		position2d<s32>(550,320),position2d<s32>(0,10),
		position2d<s32>(320,10)
};

core::rect<s32> imgSize[IMG_LENGTH] = {
		rect<s32>(0,0,190,130),
		rect<s32>(0,0,130,110),
		rect<s32>(0,0,130,110),
		rect<s32>(0,0,130,110),
		rect<s32>(0,0,130,110),
		rect<s32>(0,0,319,70),
		rect<s32>(0,0,319,70)
};
//float pointf2D[IMG_LENGTH][4] =
//	{{{220.0, -60.0}, {220.0, 40.0}, {420.0, 40.0}, {420.0, -60.0}},
//	{{0.0, 240.0}, {0.0, 340.0}, {120.0, 340.0}, {120.0, 240.0}},
//	{{0.0, 140.0}, {0.0, 240.0}, {120.0, 240.0}, {120.0, 140.0}},
//	{{520.0, 240.0}, {520.0, 340.0}, {640.0, 340.0}, {640.0, 240.0}},
//	{{520.0, 140.0}, {520.0, 240.0}, {640.0, 240.0}, {640.0, 140.0}},
//	{{0.0, 370.0}, {0.0, 470.0}, {320.0, 470.0}, {320.0, 370.0}},
//	{{320.0, 370.0}, {320.0, 470.0}, {640.0, 470.0}, {640.0, 370.0}}};

/* forward declarations */
void init(void);
void loadImages(void);
void handleMousePosition(const MyEventReceiver::SMouseState& receiver);

void init(void) {
	driver = device->getVideoDriver();
	smgr = device->getSceneManager();
	guienv = device->getGUIEnvironment();
}

void loadImages(void){
	images = new ITexture*[RESOURCE_LENGTH];
	for (int i=0; i<RESOURCE_LENGTH; i++) {
		images[i] = driver->getTexture(filenames[i]);
	}
}

void handleMousePosition(const MyEventReceiver::SMouseState& receiver) {
	if (receiver.LeftButtonDown) {

	} else {

	}
}

int main(int argc, char** argv) {
	MyEventReceiver receiver;

	device = createDevice(video::EDT_OPENGL,
			dimension2d<u32>(640, 480),32, false, false, false, &receiver);
	if (!device) {
		std::cerr << "no device found\n";
	}
	device->setWindowCaption(L"Pinbob");
	init();
	loadImages();
	MyEventReceiver::SMouseState mouseState;
	while (device->run()) {
		driver->beginScene(true, true, SColor(250, 0, 0, 0));
		handleMousePosition(receiver.getMouseState());
		for (int i=0; i<IMG_LENGTH; i++) {
			driver->draw2DImage(images[i], imgPos[i],
					imgSize[i],0,video::SColor(255,255,255,255),true);
		}
//		                                core::rect<s32>(0,0,50,50), 0,
//		                                video::SColor(255,255,255,255), true);
		smgr->drawAll();
		guienv->drawAll();
		driver->endScene();
	}

	device->drop();

	return 0;
}
