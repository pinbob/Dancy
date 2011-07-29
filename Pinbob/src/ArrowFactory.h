/*
 * ArrowFactory.h
 *
 *  Created on: Jul 22, 2011
 *      Author: yejiabin
 */

#ifndef ARROWFACTORY_H_
#define ARROWFACTORY_H_

#include "Arrow.h"
#include <map>
<<<<<<< HEAD
#include "irrlicht.h"
#ifdef WIN32
#pragma comment(lib,"irrlicht.lib")
#endif
=======
#include <irrlicht.h>
>>>>>>> yjb
typedef float pos2d[2];
using namespace irr;

using namespace core;
using namespace scene;
using namespace video;
using namespace io;
using namespace gui;

class ArrowFactory {
public:
	static std::map<unsigned char, unsigned char> BIT_MAP;
public:
	static ArrowFactory* getInstance() {
		if (_instance == 0) {
			_instance = new ArrowFactory();
		}
		return _instance;
	}
	Arrow* getDefaultArrow(unsigned char type, u32 startTime, u32 duration);
private:
	ArrowFactory();
	static ArrowFactory* _instance;
	virtual ~ArrowFactory();
	std::map<unsigned char, pos2d> positions;
};

#endif /* ARROWFACTORY_H_ */
