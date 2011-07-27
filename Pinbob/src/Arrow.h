/*
 * Arrow.h
 *
 *  Created on: Jul 19, 2011
 *      Author: yejiabin
 */

#ifndef ARROW_H
#define ARROW_H

#include <irrlicht.h>
#include <map>
typedef float pos2d[2];
const std::map<unsigned char, pos2d> arrowMap;

using namespace irr;

using namespace core;
using namespace scene;
using namespace video;
using namespace io;
using namespace gui;
class Arrow {
public:
	Arrow();
	Arrow(unsigned char arrowType, u32 startTime,  u32 duration,
			ISceneNode * node);
	unsigned char getArrowType();

	void setArrowType(unsigned char arrowType);

	ISceneNode *getArrowNode() const;

	void setArrowNode(ISceneNode *arrowNode);

	/**
	 * return false if arrow should be dismissed
	 */
	bool update(float dist);
	u32 getDuration() const;
	void setDuration(u32 duration);
    u32 getStartTime() const;
    void setStartTime(u32 startTime);
    bool isHitted() const;
    void setHitted(bool hitted);

	virtual ~Arrow() {
		printf("Arrow is destroyed.\n");
	}
private:
	unsigned char arrowType;
	bool hitted;
	u32 startTime;
	u32 duration;
	ISceneNode* arrowNode;
	vector3df currentPosition;
};

#endif
