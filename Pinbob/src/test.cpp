#include "irrlicht.h"
#include "StateMachine.h"



#ifdef WIN32
#include <windows.h>
#pragma comment(lib,"irrlicht.lib")
#endif

#define TEST_ALL

using namespace irr;
using namespace core;
using namespace scene;
using namespace video;
using namespace io;
using namespace gui;

int main(int argc, char** argv) {
#ifdef TEST_ALL
    //Create our state machine, start it and delete it when it returns
    StateMachine *theMachine = new StateMachine();
    theMachine->run();
    delete theMachine;
#else
    IrrlichtDevice *device =
            createDevice(video::EDT_OPENGL, dimension2d<u32 > (640, 480), 16,
            false, false, false, 0);
    device->setWindowCaption(L"Hello World! - Irrlicht Engine Demo");
    IVideoDriver* driver = device->getVideoDriver();
    ISceneManager* smgr = device->getSceneManager();
    IGUIEnvironment* guienv = device->getGUIEnvironment();
    smgr->addCameraSceneNode(0, vector3df(0, 30, -40), vector3df(0, 5, 0));
    while (device->run()) {
        /*
        Anything can be drawn between a beginScene() and an endScene()
        call. The beginScene() call clears the screen with a color and
        the depth buffer, if desired. Then we let the Scene Manager and
        the GUI Environment draw their content. With the endScene()
        call everything is presented on the screen.
         */
        driver->beginScene(true, true, SColor(255, 255, 255, 255));

        smgr->addSphereSceneNode();

        smgr->drawAll();
        guienv->drawAll();

        driver->endScene();
    }
    device->drop();

#endif
    return 0;
}
