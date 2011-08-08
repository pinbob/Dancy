/*
 * ArManager.cpp
 *
 *  Created on: Jul 19, 2011
 *      Author: yejiabin
 */

#include <cstdio>
#include <cstring>
#include <ctime>
#include "ArManager.h"
#include "ArrowFactory.h"
#include "ArrowPrototypeFactory.h"
#include "Score.h"
#include "Arrow.h"
#include "Config.h"

#define MAX_BUFFER 1024

ArManager::ArManager(IrrlichtDevice* device, ISceneManager* smgr,
		IVideoDriver* driver) :
		smgr(smgr), driver(driver) {
	this->armgr = new IARManager(device);
}

bool ArManager::init(const char* filename) {
	/* I think this stuff can be done by a parser */
	FILE* fconf = fopen(filename, "r");
	char buffer[MAX_BUFFER];
	if (fconf == NULL) {
		perror("no such file");
		return false;
	}
	const char *cpt;
	char *bpt; // character pointer
	while (fgets(buffer, MAX_BUFFER, fconf) != NULL) {
		if (buffer[0] != '#' && buffer[0] != '\0') {
			bool confirm = true;
			for (int i = 0; i < CONFIG_KEY_LENGTH; i++) {
				for (bpt = buffer, cpt = configKeys[i];
						*bpt != ':' && *cpt != '\0'; bpt++, cpt++) {
					if (*cpt != *bpt) {
						confirm = false;
					}
				}
				if (confirm && *bpt == ':' && *cpt == '\0') {
					bpt++;
					switch (i) {
					case CAMERA:
						cparam_name = new char[strlen(bpt) + 1];strcpy(cparam_name, bpt);
                            cparam_name[strlen(cparam_name) - 1] = '\0';
                            break;
                        case PATTERNS:
                            patt_name = new char[strlen(bpt) + 1];
                            strcpy(patt_name, bpt);
                            patt_name[strlen(patt_name) - 1] = '\0';
                            break;
                        default:
                            vconf = new char[strlen(bpt) + 1];
                            strcpy(vconf, bpt);
                            vconf[strlen(vconf) - 1] = '\0';
                            break;
                    }
					}
				confirm = true;
			}
		} //end if
	}
	fclose(fconf);
#ifdef _DEBUG
	printf("camera : %s\npattern : %s\nvconf : %s\n", cparam_name, patt_name,
			vconf);
#endif
	_initAR();
	//_loadArrows();
	return true;
}

bool ArManager::init_win32(const char* tcparam_name, const char* tpatt_name,
		char* tvconf) {
	cparam_name = new char[strlen(tcparam_name) + 1];strcpy(cparam_name, tcparam_name);
    cparam_name[strlen(cparam_name) - 1] = '\0';

    patt_name = new char[strlen(tpatt_name) + 1];
    strcpy(patt_name, tpatt_name);
    patt_name[strlen(patt_name) - 1] = '\0';

    vconf = new char[strlen(tvconf) + 1];
    strcpy(vconf, tvconf);
    vconf[strlen(vconf) - 1] = '\0';
    _initAR();
    return true;
}

int ArManager::update(u32 deltaTime, u8 hit) {
	if (deltaTime != 0) {
		_repaintArrows(deltaTime);
	}
	if (hitImageStatus != HI_LENGTH) {
		hitImageNode->setVisible(true);
		hitImageNode->setScale(
				vector3df(hitImageScale, hitImageScale, hitImageScale));
		hitImageScale += .05;
		if (hitImageScale >= 1.5) {
			hitImageScale = .1;
			hitImageStatus = HI_LENGTH;
			hitImageNode->setVisible(false);
		}
	}

	int dectected = armgr->run();
	armgr->drawBackground();
	return dectected;
}

int ArManager::update(u32 timePassed) {
    prepareNode->setMaterialTexture(0, prepareImage[timePassed / 1000]);
    f32 scale = 0.001 * (timePassed % 1000) + 0.1;// 0.1 ~ 1.1, turns bigger 0.001 times per msec
    prepareNode->setScale(vector3df(scale, scale, scale));
    armgr->run();
    //error occurs
    armgr->drawBackground();
    
    int dectected = armgr->run();
    armgr->drawBackground();
    return dectected;
}

void ArManager::_loadArrows() {
	// TODO we may have a specific file to load
	//ArrowFactory::getInstance();
	ArrowFactory* arrowFactory = ArrowFactory::getInstance();

	// TODO Just a test
	srand(time(NULL));

#ifdef _DEBUG
	for (std::list<Arrow*>::iterator iter = arrows.begin();
			iter != arrows.end(); iter++) {
		// printf("arrow type: %d.\n", (*iter)->getArrowType());
	}
#endif
}

u32 ArManager::getHitImageStatus() const {
	return hitImageStatus;
}

void ArManager::setHitImageStatus(u32 hitImageStatus) {
	this->hitImageStatus = hitImageStatus;
}



void ArManager::_repaintArrows(u32 deltaTime) {
	float dist = (deltaTime) * SPEED;
	for (std::list<Arrow*>::iterator iter = sceneCursor; iter != arrows.end();
			iter++) {
		if ((*iter)->getArrowNode() == 0) {
			break;
		}
		if (!(*iter)->update(dist)) {
			// destroy the arrow
			mainNode->removeChild((*iter)->getArrowNode());
			// TODO it may have garbage collection here
			sceneCursor++;
			//	printf("erased\n");
		}
	}
	//printf("walk through.\n");
}

int ArManager::getScore() {
	return 0;
}

ArManager::~ArManager() {
	delete this->armgr;
}

void ArManager::_initAR() {
	mainNode = smgr->getDefaultSceneNodeFactory()->addSceneNode(ESNT_EMPTY, 0);
	mainNode->setPosition(vector3df(0, 0, 0));
	/* turtle */
//	IAnimatedMesh *mesh = smgr->getMesh("asset/models/ttt.obj");
//	turtleNode = smgr->addAnimatedMeshSceneNode(mesh, smgr->getRootSceneNode(),
//			777);
//	//node->setMaterialType(EMT_PARALLAX_MAP_SOLID);
//	turtleNode->setMaterialFlag(EMF_LIGHTING, true);
//	turtleNode->setPosition(vector3df(0, 0, 300));
//	turtleNode->setScale(vector3df(3, 3, 3));
//	//node->getMaterial(0).Shininess = 30.0;
//	turtleNode->setMaterialType(EMT_SOLID);
//	turtleNode->setMaterialTexture(1,
//			driver->getTexture("asset/models/ttt.mtl"));
//	turtleNode->getMaterial(1).Shininess = 30.0;
	smgr->addLightSceneNode(0, core::vector3df(0, 0, 0),
			video::SColorf(0.5f, 1.0f, 0.5f, 0.0f), 800.0f);
	smgr->setAmbientLight(video::SColorf(0.3, 0.3, 0.3, 1));
	IAnimatedMesh* plane = smgr->getMesh("asset/models/water.obj");
	ISceneNode* sea = smgr->addWaterSurfaceSceneNode(plane->getMesh(0), 5.0f,
			300.0f, 40.0f, mainNode);
	sea->setScale(vector3df(.3, .3, .3));
	sea->setMaterialTexture(0, driver->getTexture("asset/images/mat.tga"));
	//sea->setMaterialTexture(1, driver->getTexture("asset/models/water.jpg"));
	sea->setMaterialFlag(EMF_LIGHTING, false);
	//sea->setMaterialType(video::EMT_REFLECTION_2_LAYER);

	/****** init ball ******/

	ballNode = smgr->addSphereSceneNode(20, 32, mainNode);
	ballNode->setMaterialTexture(0,
			driver->getTexture("asset/models/fireball.bmp"));
	ballNode->setMaterialFlag(EMF_LIGHTING, false);
	ballNode->addAnimator(
			smgr->createFlyStraightAnimator(vector3df(0, -20, 0),
					vector3df(0, 50, 0), 500, true, true));
//
	/******* End of init ball *******/

	vector3df camera_pos = vector3df(0, 0, 0);
	vector3df camera_target = vector3df(0, 0, 1);
	ICameraSceneNode* camera = smgr->addCameraSceneNode(0, camera_pos,
			camera_target);
	smgr->addLightSceneNode(0, core::vector3df(-0, 0, 50),
			video::SColorf(1.0f, 1.0f, 1.0f), 500);
	// add white light
	smgr->addLightSceneNode(mainNode, core::vector3df(-15, 5, -105),
			video::SColorf(1.0f, 1.0f, 1.0f));

	/* setting hit images */
	for (int i = 0; i < 1; i++) {
		hitImage[i] = driver->getTexture("asset/images/perfect.png");
	}

	IMesh* hitImageMesh = smgr->addHillPlaneMesh(
			"hitImage", // Name of mesh
			core::dimension2d<f32>(200, 100), core::dimension2d<u32>(1, 1), 0,
			0, core::dimension2d<f32>(0, 0), //material
			core::dimension2d<f32>(1, 1));

	hitImageNode = smgr->addMeshSceneNode(hitImageMesh,
			smgr->getRootSceneNode());
	hitImageNode->setPosition(vector3df(0, 0, 200));
	hitImageNode->setVisible(true);
	hitImageNode->setMaterialTexture(0, hitImage[0]);
	hitImageNode->setRotation(vector3df(90, 0, 0));
	hitImageNode->setMaterialFlag(EMF_LIGHTING, false);
	hitImageNode->setMaterialType(EMT_TRANSPARENT_ALPHA_CHANNEL);
	hitImageNode->setVisible(false);
	hitImageStatus = HI_LENGTH;
	hitImageScale = .1;

	/* set the hit plane */

	// set ambient light
	//smgr->setAmbientLight(video::SColor(0, 255, 255, 255));
	//init the camera
	armgr->beginCamera(cparam_name, 0, vconf);
	armgr->addARSceneNode(patt_name, mainNode, 123);
	armgr->fixCamera(camera);
	ArrowPrototypeFactory::getInstance()->createFactory(smgr, driver, mainNode);

}
