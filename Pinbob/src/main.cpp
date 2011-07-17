/*
 * main.cpp
 *
 *  Created on: Jul 17, 2011
 *      Author: yejiabin
 */

#include <irrlicht.h>
#include <iostream>
#include <list>
#include <cstdlib>
#include <time.h>
#include "Config.h"
#include "MyEventReceiver.h"

using namespace std;
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

struct IrrlichtDelayFPS {
  int maxFPS;
  int lastFPS;
  int yieldCounter;
  IrrlichtDevice *device;
  IrrlichtDelayFPS() { maxFPS = 50;  yieldCounter = 0;  device = 0; }
  void delay() {
    int lastFPS = driver->getFPS();
    for( int i = 0 ; i < yieldCounter ; i++ ) {
      device->yield();
    }
    if ( lastFPS >maxFPS ) { yieldCounter++ ; }
    else {
      if (yieldCounter > 0 ) { --yieldCounter; }
      else { yieldCounter = 0 ; }
    }
  }
} delayFPS;

struct GameStat {
	unsigned short currentStat;
	u32 curCount;
	u32 startTime;
	GameStat() :
			currentStat(PREPARE),curCount(0) {
	}
} gameStat;

struct ArrowInfo {
	bool isRight;
	s32 curPos;
	unsigned short type;
};

const int IMG_LENGTH = 7;
const int RESOURCE_LENGTH = 11;

std::list<ArrowInfo> arrowQueue;

//typedef float pointf2D[2];
const core::rect<s32> arrowSize = rect<s32>(0, 0, 40, 40);

char* filenames[] = { "asset/images/menu.png", "asset/images/ulArea.png",
		"asset/images/dlArea.png", "asset/images/urArea.png",
		"asset/images/drArea.png", "asset/images/lBar.png",
		"asset/images/rBar.png", "asset/images/ulArrow.png",
		"asset/images/dlArrow.png", "asset/images/urArrow.png",
		"asset/images/drArrow.png" };

core::position2d<s32> imgPos[IMG_LENGTH] = { position2d<s32>(225, 410),
		position2d<s32>(0, 130), position2d<s32>(0, 240), position2d<s32>(510,
				130), position2d<s32>(510, 240), position2d<s32>(0, 5),
		position2d<s32>(320, 5) };

core::rect<s32> imgSize[IMG_LENGTH] = { rect<s32>(0, 0, 190, 70), rect<s32>(0,
		0, 130, 110), rect<s32>(0, 0, 130, 110), rect<s32>(0, 0, 130, 110),
		rect<s32>(0, 0, 130, 110), rect<s32>(0, 0, 319, 80), rect<s32>(0, 0,
				319, 80) };

/* forward declarations */
void init(void);
void loadImages(void);
void handleMousePosition(const MyEventReceiver::SMouseState& receiver);
void drawArrows(const u32 delta);
void handleMenuPrepare(void);
void handlePrepare(void);
void handleInGame(const u32 now,const u32 delta);
void handleGameOver(void);

void init(void) {
	driver = device->getVideoDriver();
	smgr = device->getSceneManager();
	guienv = device->getGUIEnvironment();
}

void loadImages(void) {
	images = new ITexture*[RESOURCE_LENGTH];
	for (int i = 0; i < RESOURCE_LENGTH; i++) {
		images[i] = driver->getTexture(filenames[i]);
	}
}

void handleMousePosition(const MyEventReceiver::SMouseState& receiver) {
	int mouseX = receiver.Position.X;
	int mouseY = receiver.Position.Y;
	if (receiver.LeftButtonDown) {
		if (mouseX <= 130) {
			if (mouseY >= 130 && mouseY < 240) {

			} else if (mouseY >= 240 && mouseY <= 350) {

			}
		} else if (mouseX >= 510) {
			if (mouseY >= 130 && mouseY < 240) {

			} else if (mouseY >= 240 && mouseY <= 350) {

			}
		} else if (mouseX >= 225 && mouseX <= 415 && mouseY >= 410) {
			// menu area
			// TODO complete it
			switch (gameStat.currentStat) {
			case PREPARE:
				handleMenuPrepare();
				break;
			case IN_GAME:
				break;
			case GAME_OVER:
				break;
			default:
				break;
			}
		}
	} else {

	}
}

void handleMenuPrepare() {
	gameStat.currentStat = IN_GAME;
	gameStat.startTime = device->getTimer()->getTime();
	std::cout << "game start!\n";
}

/* various handlers */
void handlePrepare() {

}

void handleInGame(const u32 now, const u32 delta) {
	u32 curCount = static_cast<u32>((now - gameStat.startTime)/1000);
	for (std::list<ArrowInfo>::iterator iter = arrowQueue.begin();
				iter != arrowQueue.end(); iter++) {
		if (iter->curPos >= 280) {
			iter = arrowQueue.erase(iter);
		}
	}
	if (curCount != gameStat.curCount) {
		ArrowInfo newArrow;
		newArrow.type = static_cast<unsigned short>(rand()%4
				+ UP_LEFT_ARROW);
		newArrow.isRight = (newArrow.type - UP_LEFT_ARROW)/2 == 1;
		newArrow.curPos = 0;
		arrowQueue.push_back(newArrow);
		gameStat.curCount = curCount;
	}
	drawArrows(delta);
}

void handleGameOver(void) {

}

void drawArrows(const u32 delta) {
	s32 pos;
	f32 speed = 180;
	f32 offset;
	for (std::list<ArrowInfo>::iterator iter = arrowQueue.begin();
			iter != arrowQueue.end(); iter++) {
		offset = speed * static_cast<f32>(delta) / 1000.0;
	//	cout << "offset " << offset << "\n";
		if (iter->isRight) {
			pos = 640 - (iter->curPos + offset + 40);
		} else {
			pos = iter->curPos + offset;
		}
		iter->curPos += offset;
//		std::cout << "offset " << offset << " pos " << pos
//						<< " delta " << delta << '\n';
		driver->draw2DImage(images[iter->type],
				position2d<s32>(pos, 23), arrowSize, 0,
				video::SColor(255, 255, 255, 255), true);
	}
}

int main(int argc, char** argv) {
	MyEventReceiver receiver;
	/* Initialize the random number generator with a seed */
	srand((unsigned)time(NULL));

	device = createDevice(video::EDT_OPENGL, dimension2d<u32>(640, 480), 32,
			false, false, false, &receiver);
	if (!device) {
		std::cerr << "no device found\n";
	}
	device->setWindowCaption(L"Pinbob");
	init();
	loadImages();
	MyEventReceiver::SMouseState mouseState;
	int lastFPS = -1;
	u32 then = device->getTimer()->getTime();

	while (device->run()) {
		const u32 now = device->getTimer()->getTime();
		const u32 deltaTime = now - then; // in ms
		then = now;
		if (device->isWindowActive()) {
			driver->beginScene(true, true, SColor(250, 0, 0, 0));
			handleMousePosition(receiver.getMouseState());
			switch (gameStat.currentStat) {
			case PREPARE:
				handlePrepare();
				break;
			case IN_GAME:
				handleInGame(now, deltaTime);
				break;
			case GAME_OVER:
				handleGameOver();
				break;
			default:
				break;
			}
			for (int i = 0; i < IMG_LENGTH; i++) {
				driver->draw2DImage(images[i], imgPos[i], imgSize[i], 0,
						video::SColor(255, 255, 255, 255), true);
			}
//
			smgr->drawAll();
			guienv->drawAll();
			driver->endScene();
			int fps = driver->getFPS();

			if (lastFPS != fps) {
				core::stringw str = L"Pinbob [";
				str += driver->getName();
				str += "] FPS:";
				str += fps;
				device->setWindowCaption(str.c_str());
				lastFPS = fps;
			}
		//	delayFPS.delay();
		} else {
			device->yield();
		}
		device->sleep(39);
		//delayFPS.delay();

	}

	device->drop();

	return 0;
}
