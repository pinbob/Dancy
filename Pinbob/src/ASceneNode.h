/*
 * ASceneNode.h
 *
 *  Created on: Jul 26, 2011
 *      Author: yejiabin
 */

#ifndef ASCENENODE_H_
#define ASCENENODE_H_

<<<<<<< HEAD
#include "irrlicht.h"
#include "ISceneNode.h"
#ifdef WIN32
#pragma comment(lib,"irrlicht.lib")
#endif
=======
#include <irrlicht.h>
#include <ISceneNode.h>
>>>>>>> yjb

using namespace irr;
using namespace core;
using namespace scene;
using namespace video;
using namespace io;
using namespace gui;

const float ASCENE_NODE_POS[9][2] = { { 28, 14 }, { 50, 30 }, { 67, 14 },
		{ 81, 26 }, { 78.80 }, { 25, 81 }, { 14, 68 }, { 29, 51 }, { 13, 37 } };

class ASceneNode: public irr::scene::ISceneNode {
public:
	ASceneNode(scene::ISceneNode* parent, scene::ISceneManager* mgr, s32 id,
			u32 duration);
	virtual void OnRegisterSceneNode() {
		if (IsVisible)
			SceneManager->registerNodeForRendering(this);
		ISceneNode::OnRegisterSceneNode();
	}
	virtual void render() {
		u16 indices[] = { 0, 2, 3, 2, 1, 3, 1, 0, 3, 2, 0, 1 };
		video::IVideoDriver* driver = SceneManager->getVideoDriver();

		driver->setMaterial(Material);
		driver->setTransform(video::ETS_WORLD, AbsoluteTransformation);
		driver->drawVertexPrimitiveList(&vertices[0], 4, &indices[0], 4,
				video::EVT_STANDARD, scene::EPT_TRIANGLES, video::EIT_16BIT);
	}
	virtual const core::aabbox3d<f32>& getBoundingBox() const {
		return Box;
	}

	virtual u32 getMaterialCount() const {
		return 1;
	}

	virtual video::SMaterial& getMaterial(u32 i) {
		return Material;
	}

	virtual ~ASceneNode();
private:
	core::aabbox3d<f32> Box;
	video::S3DVertex vertices[9];
	video::SMaterial Material;
};

#endif /* ASCENENODE_H_ */
