/*
 * Arrow.cpp
 *
 *  Created on: Jul 19, 2011
 *      Author: yejiabin
 */

#include "Arrow.h"

Arrow::Arrow() :
		arrowType(1), duration(0), arrowNode(0),startTime(0) {
}

Arrow::Arrow(unsigned char arrowType, u32 startTime, u32 duration,
		ISceneNode* node) :
		arrowType(arrowType), startTime(startTime), duration(duration), arrowNode(
				node) {

}

unsigned char Arrow::getArrowType() {
	return arrowType;
}

void Arrow::setArrowType(unsigned char arrowType) {
	this->arrowType = arrowType;
}

ISceneNode *Arrow::getArrowNode() const {
	return arrowNode;
}

void Arrow::setArrowNode(ISceneNode *arrowNode) {
	this->arrowNode = arrowNode;
	currentPosition = this->arrowNode->getPosition();
}

u32 Arrow::getDuration() const {
	return duration;
}

void Arrow::setDuration(u32 duration) {
	this->duration = duration;
}

bool Arrow::update(float dist) {
	currentPosition.Y -= dist;
#ifdef _DEBUG
	//printf("dist %f\n", dist);
	// printf("current z is %f.\n", currentPosition.Y);
#endif
	if (currentPosition.Y < 5) {
		arrowNode->remove();
		// delete arrowNode;
		// arrowNode = 0;
		// printf("dropped\n");
		return false;
	} else {
		arrowNode->setPosition(currentPosition);
		return true;
	}
}

u32 Arrow::getStartTime() const {
	return startTime;
}

void Arrow::setStartTime(u32 startTime) {
	this->startTime = startTime;
}

