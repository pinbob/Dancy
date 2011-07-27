/*
 * ASceneNode.cpp
 *
 *  Created on: Jul 26, 2011
 *      Author: yejiabin
 */

#include "ASceneNode.h"

ASceneNode::ASceneNode(scene::ISceneNode* parent, scene::ISceneManager* mgr,
		s32 id, u32 duration) :
		scene::ISceneNode(parent, mgr, id) {
	// TODO Auto-generated constructor stub
	for (int i = 0; i < 9; i++) {
		vertices[i] = video::S3DVertex(ASCENE_NODE_POS[i][0],
				ASCENE_NODE_POS[i][1], 0, 1, 1, 1, SColor(255, 255, 0, 0), 1,
				1);
	}
}

ASceneNode::~ASceneNode() {
	// TODO Auto-generated destructor stub
}

