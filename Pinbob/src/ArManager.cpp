/*
 * ArManager.cpp
 *
 *  Created on: Jul 19, 2011
 *      Author: yejiabin
 */

#include <cstdio>
#include <cstring>
#include "ArManager.h"
#include "Score.h"
#include "Arrow.h"

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
						cparam_name[strlen(cparam_name)-1] = '\0';
						break;
					case PATTERN:
						patt_name = new char[strlen(bpt)+1];
						strcpy(patt_name, bpt);
						patt_name[strlen(patt_name)-1] = '\0';
						break;
					default:
						vconf = new char[strlen(bpt)+1];
						strcpy(vconf, bpt);
						vconf[strlen(vconf)-1] = '\0';
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
	_loadArrows();
	return true;
}

#define START_TIME 2000 // start after 2 seconds
void ArManager::update(u32 last, u32 now, u8 hit) {
	//TODO just simulate random arrow generation
	if (now > START_TIME) {
		if ((now / 1000 - last / 1000) > 0) {
			//add an arrow
			//IAnimatedMesh *arrowMesh = smgr->getMesh("asset/images/left-bottom.png");
			//ISceneNode *newArrow = smgr->addAnimatedMeshSceneNode(arrowMesh, this->mainNode);
			// arrows.push_back()
			//	printf("It's %d seconds.\n", now/1000);
		}
	}
	printf("It's %d seconds.\n", now / 1000);
	_updateArrows(last, now, hit);
	armgr->run();
	armgr->drawBackground();
}

void ArManager::_loadArrows() {

}

void ArManager::_updateArrows(u32 last, u32 now, u8 hit) {
	IAnimatedMesh* plane = smgr->addHillPlaneMesh("plane", // Name of mesh
			core::dimension2d<f32>(100, 100), //	Size of a tile of the mesh. (10.0f, 10.0f) would be a good value to start, for example.
			core::dimension2d<u32>(1, 1), 0, 0, // 	Specifies how much tiles there will be. If you specifiy for example that a tile has the size (10.0f, 10.0f) and the tileCount is (10,10), than you get a field of 100 tiles which has the dimension 100.0fx100.0f.
			core::dimension2d<f32>(0, 0), //material
			core::dimension2d<f32>(1, 1)); //countHills
	ISceneNode* arrowNode = smgr->addAnimatedMeshSceneNode(plane, mainNode, 888,
			vector3df(0, 0, 20));
	driver->setTextureCreationFlag(ETCF_NO_ALPHA_CHANNEL,false);
	arrowNode->setMaterialTexture(0,
			driver->getTexture("asset/images/right-bottom.png"));
	arrowNode->setMaterialFlag(EMF_LIGHTING, false);
	arrowNode->setMaterialType(EMT_TRANSPARENT_ALPHA_CHANNEL);

	arrowNode->setPosition(vector3df(0,50,0));
	arrowNode->setScale(vector3df(.3, .3, .3));
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
	IAnimatedMesh *mesh = smgr->getMesh("asset/models/ttt.obj");
	turtleNode = smgr->addAnimatedMeshSceneNode(mesh, mainNode, 777);
	//node->setMaterialType(EMT_PARALLAX_MAP_SOLID);
	turtleNode->setMaterialFlag(EMF_LIGHTING, true);
	turtleNode->setPosition(vector3df(0, 20, 30));
	turtleNode->setScale(vector3df(3, 3, 3));
	//node->getMaterial(0).Shininess = 30.0;
	turtleNode->setMaterialType(EMT_SOLID);
	turtleNode->setMaterialTexture(1,
			driver->getTexture("asset/models/ttt.mtl"));
	turtleNode->getMaterial(1).Shininess = 30.0;
	//node->setMaterialType(EMT_SOLID_2_LAYER );
	//node->setMaterialTexture(1, driver->getTexture("asset/models/ttt.mtl"));

	smgr->addLightSceneNode(0, core::vector3df(0, 0, 0),
			video::SColorf(0.5f, 1.0f, 0.5f, 0.0f), 800.0f);
	smgr->setAmbientLight(video::SColorf(0.3, 0.3, 0.3, 1));
	/* Terrain */
//	IAnimatedMesh* plane = smgr->addHillPlaneMesh("plane", // Name of mesh
//			core::dimension2d<f32>(10, 10), //	Size of a tile of the mesh. (10.0f, 10.0f) would be a good value to start, for example.
//			core::dimension2d<u32>(20, 20), 0, 0, // 	Specifies how much tiles there will be. If you specifiy for example that a tile has the size (10.0f, 10.0f) and the tileCount is (10,10), than you get a field of 100 tiles which has the dimension 100.0fx100.0f.
//			core::dimension2d<f32>(0, 0), //material
//			core::dimension2d<f32>(10, 10)); //countHills
	IAnimatedMesh* plane = smgr->getMesh("asset/models/water.obj");
	ISceneNode* sea = smgr->addWaterSurfaceSceneNode(plane->getMesh(0), 5.0f,
			300.0f, 40.0f, mainNode);
	sea->setScale(vector3df(.3, .3, .3));
	sea->setMaterialTexture(0, driver->getTexture("asset/models/mat.png"));
	sea->setMaterialTexture(1, driver->getTexture("asset/models/water.jpg"));
	sea->setMaterialFlag(EMF_LIGHTING, false);
	sea->setMaterialType(video::EMT_REFLECTION_2_LAYER);

	vector3df camera_pos = vector3df(0, 0, 0);
	vector3df camera_target = vector3df(0, 0, 1);
	ICameraSceneNode* camera = smgr->addCameraSceneNode(0, camera_pos,
			camera_target);
	// add white light
	smgr->addLightSceneNode(mainNode, core::vector3df(-15, 5, -105),
			video::SColorf(1.0f, 1.0f, 1.0f));

	// set ambient light
	smgr->setAmbientLight(video::SColor(0, 255, 255, 255));
	//init the camera
	armgr->beginCamera(cparam_name, 0, vconf);
	//node for the lady, attached the the hiro pattern
	//armgr->addARSceneNode(patt_name, node);
	//node for the fairy and water, attached the the sample1 pattern
//	mainNode->addChild(turtleNode);
	armgr->addARSceneNode(patt_name, mainNode, 123);
	//armgr->addARSceneNode(patt_name, turtleNode2, 123);
	armgr->fixCamera(camera);

}
