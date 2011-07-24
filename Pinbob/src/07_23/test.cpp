#include "irrlicht.h"
#include "StateMachine.h"

#ifdef WIN32
#include <windows.h>
#pragma comment(lib,"irrlicht.lib")
#endif

using namespace irr;
using namespace core;
using namespace scene;
using namespace video;
using namespace io;
using namespace gui;

int main(int argc, char** argv) {
	//Create our state machine, start it and delete it when it returns
	StateMachine *theMachine=new StateMachine();
	theMachine->run();
	delete theMachine;
	return 0;
}