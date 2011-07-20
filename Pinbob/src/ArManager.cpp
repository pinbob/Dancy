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
	return true;
}

void ArManager::update(u32 last, u32 now, u8 hit) {
	armgr->run();
	armgr->drawBackground();
}

int ArManager::getScore() {
	return 0;
}

ArManager::~ArManager() {
	delete this->armgr;
}

void ArManager::_initAR() {
	ISceneNode *turtleNode = 0, *turtleNode2 = 0;
	ISceneNode *mainNode =
	smgr->addSceneNode("ESNT_EMPTY",0);
	//mainNode->setPosition(vector3df(0, 0, 0));
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

	/* Terrain */
	/* turtle */
	IAnimatedMesh *mesh2 = smgr->getMesh("asset/models/ttt.obj");
	turtleNode2 = smgr->addAnimatedMeshSceneNode(mesh2, 0, 778);
	//node->setMaterialType(EMT_PARALLAX_MAP_SOLID);
	turtleNode2->setMaterialFlag(EMF_LIGHTING, true);
	turtleNode2->setPosition(vector3df(30, 20, 30));
	turtleNode2->setScale(vector3df(2, 2, 2));
	//node->getMaterial(0).Shininess = 30.0;
	turtleNode2->setMaterialType(EMT_SOLID);
	turtleNode2->setMaterialTexture(1,
			driver->getTexture("asset/models/ttt.mtl"));
	turtleNode2->getMaterial(1).Shininess = 30.0;

	vector3df camera_pos = vector3df(0, 0, 0);
	vector3df camera_target = vector3df(0, 0, 1);
	ICameraSceneNode* camera = smgr->addCameraSceneNode(0, camera_pos,
			camera_target);
	// add white light
	smgr->addLightSceneNode(0, core::vector3df(-15, 5, -105),
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
