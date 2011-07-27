/*
 * ArrowFactory.cpp
 *
 *  Created on: Jul 22, 2011
 *      Author: yejiabin
 */

#include "ArrowFactory.h"
#include "Config.h"

ArrowFactory* ArrowFactory::_instance = 0;
std::map<unsigned char, unsigned char> ArrowFactory::BIT_MAP;

ArrowFactory::ArrowFactory() {
	//positions.insert(UP_LEFT_HIT);
	printf("ArrowFactory initialized\n");
	BIT_MAP[UP_LEFT_HIT] = 0;
	BIT_MAP[DOWN_LEFT_HIT] = 1;
	BIT_MAP[UP_RIGHT_HIT] = 2;
	BIT_MAP[DOWN_RIGHT_HIT] = 3;
}

ArrowFactory::~ArrowFactory() {
}

Arrow* ArrowFactory::getDefaultArrow(unsigned char type, u32 startTime,
		u32 duration) {
	return new Arrow(BIT_MAP[type],startTime, duration, 0);
}
