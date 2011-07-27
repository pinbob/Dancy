/*
 * ArrowPrototypeFactory.cpp
 *
 *  Created on: Jul 22, 2011
 *      Author: yejiabin
 */

#include "ArrowPrototypeFactory.h"
#include "Config.h"

ArrowPrototypeFactory* ArrowPrototypeFactory::_instance = 0;

ArrowPrototypeFactory::ArrowPrototypeFactory():smgr(0),parent(0) {
	for (int i = 0; i < 4; i++) {
		prototypes[i] = 0;
	}
}

ArrowPrototypeFactory::~ArrowPrototypeFactory() {
}

void ArrowPrototypeFactory::createFactory(ISceneManager* smgr,
		IVideoDriver* driver, ISceneNode* parent) {
	this->parent = parent;
	this->smgr = smgr;
	if (prototypes[0] != 0) {
		for (int i = 0; i < 4; i++) {
			prototypes[i]->drop();
			prototypes[i] = 0;
		}
	}
	for (int i = 0; i < 4; i++) {
		IAnimatedMesh* plane = smgr->addHillPlaneMesh(
				"plane", // Name of mesh
				core::dimension2d<f32>(100, 100), core::dimension2d<u32>(1, 1),
				0, 0, core::dimension2d<f32>(0, 0), //material
				core::dimension2d<f32>(1, 1)); //countHills
		prototypes[i] = smgr->addAnimatedMeshSceneNode(plane, parent, 888,
				vector3df(0, 0, 0));
		driver->setTextureCreationFlag(ETCF_NO_ALPHA_CHANNEL, false);
		prototypes[i]->setMaterialTexture(0,
				driver->getTexture(ARROW_INFOS[i].texture));
		prototypes[i]->setMaterialFlag(EMF_LIGHTING, false);
		prototypes[i]->setMaterialType(EMT_TRANSPARENT_ALPHA_CHANNEL);

		prototypes[i]->setPosition(
				vector3df(ARROW_INFOS[i].posX, ARROW_HEIGHT, ARROW_INFOS[i].posY));
		prototypes[i]->setScale(vector3df(.3, .3, .3));
		prototypes[i]->setVisible(false);
	}
}

ISceneNode* ArrowPrototypeFactory::getArrowPrototype(unsigned char type) {
	ISceneNode* newArrow = prototypes[type]->clone(parent, smgr);
	newArrow->setVisible(true);
	return newArrow;
}