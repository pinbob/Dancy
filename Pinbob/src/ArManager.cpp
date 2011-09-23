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
		smgr(smgr), driver(driver),
		hitImageStatus(HI_LENGTH),lastHitStatus(HI_LENGTH){
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

void ArManager::updateCountdown(u32 timePassed) {
	prepareNode->setVisible(true);
	prepareNode->setMaterialTexture(0, prepareImage[timePassed / 1000]);
	f32 scale = 0.001 * (timePassed % 1000) + 0.1; // 0.1 ~ 1.1, turns bigger 0.001 times per msec
	prepareNode->setScale(vector3df(scale, scale, scale));
}

void ArManager::destroyCountdown() {
	if (prepareNode->isVisible())
		prepareNode->setVisible(false);
}

void ArManager::close() {
	armgr->closeAR();
}

int ArManager::update(u32 deltaTime, u8 hit) {
	if (deltaTime != 0) {
		_repaintArrows(deltaTime);
	}
        
        //set combo: perfect, well done, good to be true
        //else to be false
        if (score.getCombo() > 0){
            comboImageNode->setVisible(true);
        }else{
            comboImageNode->setVisible(false);
        }
        
	/* show it information */
	if (hitImageStatus != HI_LENGTH) {     
		hitImageNode->setVisible(true);
		if (hitImageStatus != lastHitStatus) {
			hitImageScale = 1.2;
			hitImageNode->setMaterialTexture(0, hitImage[hitImageStatus]);
			lastHitStatus = hitImageStatus;
		} else {
			hitImageScale -= .03;
			if (hitImageScale <= 0.035) {
				lastHitStatus = HI_LENGTH;
				hitImageStatus = HI_LENGTH;
			} else {
				hitImageNode->setScale(vector3df(hitImageScale,hitImageScale,hitImageScale));
			}
		}
	} else {
		hitImageNode->setVisible(false);
	}
	int dectected = armgr->run();
	armgr->drawBackground();
	return dectected;
}

void ArManager::updateTime(float scale) {
	timerNode->setScale(vector3df(scale,1,1));
	timerNode->setPosition(TIMER_POS);
}

void ArManager::_loadArrows() {
	//TODO no more use of this method
	// please do clean up work if you see it
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

	IAnimatedMesh* plane = smgr->addHillPlaneMesh("sea", dimension2df(150, 150),
			dimension2d<u32>(1, 1));
	//smgr->getMesh("asset/models/water.obj");
	ISceneNode* sea = smgr->addAnimatedMeshSceneNode(plane, mainNode);
	//smgr->addWaterSurfaceSceneNode(plane->getMesh(0), 5.0f,
	//	300.0f, 40.0f, mainNode);

	//sea->setScale(vector3df(.3, .3, .3));
	sea->setMaterialTexture(0, driver->getTexture("asset/images/mat.tga"));
	//sea->setMaterialTexture(1, driver->getTexture("asset/models/water.jpg"));
	sea->setMaterialFlag(EMF_LIGHTING, false);
	sea->setMaterialType(EMT_TRANSPARENT_ALPHA_CHANNEL);
	sea->setPosition(vector3d<f32>(100,0,100));

	//sea->setMaterialType(video::EMT_REFLECTION_2_LAYER);

	/****** init ball ******/

	ballNode = smgr->addSphereSceneNode(20, 32, mainNode);
	ballNode->setMaterialTexture(0,
			driver->getTexture("asset/models/fireball.bmp"));
	ballNode->setMaterialFlag(EMF_LIGHTING, false);
	ballNode->addAnimator(
			smgr->createFlyStraightAnimator(vector3df(100, -20, 100),
					vector3df(100, 50, 100), 500, true, true));
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
	for (int i = 0; i < HI_LENGTH; i++) {
		hitImage[i] = driver->getTexture(hitImageFile[i]);
	}

	IMesh* hitImageMesh = smgr->addHillPlaneMesh(
			"hitImage", // Name of mesh
			core::dimension2d<f32>(50, 25), core::dimension2d<u32>(1, 1), 0,
			0, core::dimension2d<f32>(0, 0), //material
			core::dimension2d<f32>(1, 1));

	hitImageNode = smgr->addMeshSceneNode(hitImageMesh,
			smgr->getRootSceneNode());
	hitImageNode->setPosition(vector3df(55, -57, 200));
	hitImageNode->setVisible(true);
	hitImageNode->setMaterialTexture(0, hitImage[0]);
	hitImageNode->setRotation(vector3df(90, 0, 0));
	hitImageNode->setMaterialFlag(EMF_LIGHTING, false);
	hitImageNode->setMaterialType(EMT_TRANSPARENT_ALPHA_CHANNEL);
	hitImageNode->setVisible(false);
	//actually alpha
	hitImageScale = 1;
        
        /* combo */
        comboImage = driver->getTexture("asset/images/combo.png");
        IMesh* comboMesh = smgr->addHillPlaneMesh("comboImage",
                core::dimension2d<f32>(50, 12.5), core::dimension2d<u32>(1, 1), 0,
                0, core::dimension2d<f32>(0, 0), //material
                core::dimension2d<f32>(1, 1));
        comboImageNode = smgr->addMeshSceneNode(comboMesh, smgr->getRootSceneNode());
        comboImageNode->setPosition(vector3df(
                driver->getScreenSize().Width / 2 - 100, -40, 200));
        comboImageNode->setVisible(true);
	comboImageNode->setMaterialTexture(0, comboImage);
	comboImageNode->setRotation(vector3df(90, 0, 0));
	comboImageNode->setMaterialFlag(EMF_LIGHTING, false);
	comboImageNode->setMaterialType(EMT_TRANSPARENT_ALPHA_CHANNEL);
	comboImageNode->setVisible(false);

	/* setting preparation */
	prepareImage[0] = driver->getTexture("asset/images/start/3.png");
	prepareImage[1] = driver->getTexture("asset/images/start/2.png");
	prepareImage[2] = driver->getTexture("asset/images/start/1.png");
	prepareImage[3] = driver->getTexture("asset/images/start/ready.png");
	prepareImage[4] = driver->getTexture("asset/images/start/start.png");

	IMesh* prepareImageMesh = smgr->addHillPlaneMesh(
			"prepareImage", // Name of mesh
			core::dimension2d<f32>(100, 100), core::dimension2d<u32>(1, 1), 0,
			0, core::dimension2d<f32>(0, 0), //material
			core::dimension2d<f32>(1, 1));

	prepareNode = smgr->addMeshSceneNode(prepareImageMesh,
			smgr->getRootSceneNode());
	prepareNode->setPosition(vector3df(0, 0, 200));
	prepareNode->setMaterialTexture(0, prepareImage[0]);
	prepareNode->setRotation(vector3df(90, 0, 0));
	prepareNode->setMaterialFlag(EMF_LIGHTING, false);
	prepareNode->setMaterialType(EMT_TRANSPARENT_ALPHA_CHANNEL);
	prepareNode->setVisible(false);


	timerNode = smgr->addMeshSceneNode(
			smgr->addHillPlaneMesh("timerImage",
			core::dimension2d<f32>(300,2),
			core::dimension2d<u32>(1,1)), smgr->getRootSceneNode());
	timerNode->setPosition(TIMER_POS);
	timerNode->setMaterialTexture(0, driver->getTexture("asset/images/yellow.tga"));
	timerNode->setRotation(vector3df(90, 0, 0));
	timerNode->setMaterialFlag(EMF_LIGHTING, false);
	timerNode->setMaterialType(EMT_TRANSPARENT_ALPHA_CHANNEL);

	// set ambient light
	//smgr->setAmbientLight(video::SColor(0, 255, 255, 255));
	//init the camera

	armgr->beginCamera(cparam_name, 0, vconf);
	armgr->addARSceneNode(patt_name, mainNode, 123);
	armgr->fixCamera(camera);
	ArrowPrototypeFactory::getInstance()->createFactory(smgr, driver, mainNode);

}
