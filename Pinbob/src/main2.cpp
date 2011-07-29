/*
 * main.cpp
 *
 *  Created on: Jul 17, 2011
 *      Author: yejiabin
 */
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

<<<<<<< HEAD

#define TEST_ARROW
	//Create our state machine, start it and delete it when it returns
#ifndef TEST_ARROW
int main(int argc, char** argv) {
=======
int main(int argc, char** argv) {
#define TEST_ARROW
	//Create our state machine, start it and delete it when it returns
#ifdef TEST_ARROW
>>>>>>> yjb
	StateMachine *theMachine=new StateMachine();
	theMachine->run();
	delete theMachine;
	return 0;
}
#elif defined TEST_YJB
	IrrlichtDevice *device = createDevice(video::EDT_OPENGL,
				dimension2d<u32>(640, 480), 24, false, false, false, 0);
		if (!device)
			return 1;
		IVideoDriver* driver = device->getVideoDriver();
		ISceneManager* smgr = device->getSceneManager();
		IGUIEnvironment* guienv = device->getGUIEnvironment();
		/* calls ar manager */

		int lastFPS = -1;
		u32 then = device->getTimer()->getTime();
		while (device->run()) {
			if (device->isWindowActive()) {
				const u32 now = device->getTimer()->getTime();
				const u32 deltaTime = now - then; // in ms
				then = now;
				driver->beginScene(true, true, SColor(255, 0, 0, 0));

				smgr->drawAll();
				guienv->drawAll();
				driver->endScene();
				//Shows FPS in the title screen
				int fps = driver->getFPS();
				if (lastFPS != fps) {
					core::stringw str = L"Pinbob [";
					str += driver->getName();
					str += "] FPS:";
					str += fps;
					device->setWindowCaption(str.c_str());
					lastFPS = fps;
				}

			} else {
				device->yield();
			}
		}
		driver->drop();
	return 0;
}
#endif
#ifdef RECOVER
#include <irrlicht.h>
#include <iostream>
#include <list>
#include <cstdlib>
#include <time.h>
#include <AR/video.h>
#include <AR/param.h>
#include <AR/ar.h>
#include "Config.h"
#include "MyEventReceiver.h"
#include "MyNode.h"
#include "irrAR.h"

using namespace std;
using namespace irr;

using namespace core;
using namespace scene;
using namespace video;
using namespace io;
using namespace gui;

/* global variables */
IrrlichtDevice *device;
ISceneManager* smgr;
IGUIEnvironment* guienv;
IVideoDriver *driver;
ITexture** images;
MyEventReceiver myReceiver;

/* global variable for ARToolkit */
#define   MINIWIN_MAX    8
#define   GMINI          2
char *vconf =
		"v4l2src device=/dev/video0 ! video/x-raw-yuv,width=320,height=240 ! ffmpegcolorspace ! capsfilter caps=video/x-raw-rgb,bpp=24 ! identity name=artoolkit ! fakesink";

int xsize, ysize;
int thresh = 100;
int count = 0;

char *cparam_name =
		"/home/yejiabin/Documents/ARToolKit/bin/Data/camera_para.dat";
ARParam cparam;

char *patt_name = "/home/yejiabin/Documents/ARToolKit/bin/Data/patt.hiro";
int patt_id;
double patt_width = 80.0;
double patt_center[2] = { 0.0, 0.0 };
double patt_trans[3][4];

static int gl_hmd_flag = 0;
static double gZoom;
static int gImXsize, gImYsize;
static int gXsize, gYsize;
static int gMiniXsize, gMiniYsize;
static int gMiniXnum, gMiniYnum;
static int gWinXsize, gWinYsize;
static ARParam gCparam;
static float gl_cpara[16];

void argConvGLcpara(ARParam *param, double gnear, double gfar, float m[16]);
static void argConvGLcpara2(double cparam[3][4], int width, int height,
		double gnear, double gfar, float m[16]);
void init_camera(ARParam *cparam, double zoom, int fullFlag, int xwin, int ywin,
		int hmd_flag);

struct IrrlichtDelayFPS {
	int maxFPS;
	int lastFPS;
	int yieldCounter;
	IrrlichtDevice *device;
	IrrlichtDelayFPS() {
		maxFPS = 50;
		yieldCounter = 0;
		device = 0;
	}
	void delay() {
		int lastFPS = driver->getFPS();
		for (int i = 0; i < yieldCounter; i++) {
			device->yield();
		}
		if (lastFPS > maxFPS) {
			yieldCounter++;
		} else {
			if (yieldCounter > 0) {
				--yieldCounter;
			} else {
				yieldCounter = 0;
			}
		}
	}
} delayFPS;

struct GameStat {
	unsigned short currentStat;
	u32 curCount;
	u32 startTime;
	s32 curScore;
	GameStat() :
			currentStat(PREPARE), curCount(0), curScore(0) {
	}
} gameStat;

struct ArrowInfo {
	bool isRight;
	s32 curPos;
	unsigned short type;
};

const int IMG_LENGTH = 7;
const int RESOURCE_LENGTH = 11;

std::list<ArrowInfo> arrowQueue;

//typedef float pointf2D[2];
const core::rect<s32> arrowSize = rect<s32>(0, 0, 40, 40);

char* filenames[] = { "asset/images/menu.png", "asset/images/ulArea.png",
		"asset/images/dlArea.png", "asset/images/urArea.png",
		"asset/images/drArea.png", "asset/images/lBar.png",
		"asset/images/rBar.png", "asset/images/ulArrow.png",
		"asset/images/dlArrow.png", "asset/images/urArrow.png",
		"asset/images/drArrow.png" };

/* set the alpha channel of the area */
//u32 imgAlpha[IMG_LENGTH] = { 255, 255, 255, 255, 255, 255, 255 };
core::position2d<s32> imgPos[IMG_LENGTH] = { position2d<s32>(225, 410),
		position2d<s32>(0, 130), position2d<s32>(0, 240), position2d<s32>(510,
				130), position2d<s32>(510, 240), position2d<s32>(0, 5),
		position2d<s32>(320, 5) };

core::rect<s32> imgSize[IMG_LENGTH] = { rect<s32>(0, 0, 190, 70), rect<s32>(0,
		0, 130, 110), rect<s32>(0, 0, 130, 110), rect<s32>(0, 0, 130, 110),
		rect<s32>(0, 0, 130, 110), rect<s32>(0, 0, 319, 80), rect<s32>(0, 0,
				319, 80) };

/* forward declarations */
void init(void);
void loadImages(void);
void handleMousePosition(const MyEventReceiver::SMouseState& receiver);
void drawArrows(const u32 delta);
void handleMenuPrepare(void);
void handlePrepare(void);
void handleInGame(const u32 now, const u32 delta);
void handleGameOver(void);
void checkHit(unsigned short);
void initAR();
ITexture* create_ITexture_from_ARimage(ARUint8 *ardata, int width, int height);
ITexture* update_ITexture_from_ARimage(ITexture *dest, ARUint8 *ardata,
		int width, int height);
void AttachNode(ISceneNode *thenode, ARUint8 *dataPtr);
void convert_trans_para(double para[3][4], double gl_para[16]);

void init(void) {
	driver = device->getVideoDriver();
	smgr = device->getSceneManager();

	guienv = device->getGUIEnvironment();
	smgr->setAmbientLight(SColorf(.1, .1, .1, .1));
	//smgr->addLightSceneNode(0,vector3df(100,-200,200,0));
}

void loadImages(void) {
	images = new ITexture*[RESOURCE_LENGTH];
	for (int i = 0; i < RESOURCE_LENGTH; i++) {
		images[i] = driver->getTexture(filenames[i]);
	}
}

void handleMousePosition(const MyEventReceiver::SMouseState& receiver) {
	int mouseX = receiver.Position.X;
	int mouseY = receiver.Position.Y;
	/* handles mouse click events */
	if (receiver.LeftButtonDown && !myReceiver.getLastHitStatus()) {
		// TODO if the receiver receives touch screen information
		if (mouseX <= 130) {
			if (mouseY >= 130 && mouseY < 240) {
				checkHit(UP_LEFT_ARROW);
			} else if (mouseY >= 240 && mouseY <= 350) {
				checkHit(DOWN_LEFT_ARROW);
			}
		} else if (mouseX >= 510) {
			if (mouseY >= 130 && mouseY < 240) {
				checkHit(UP_RIGHT_ARROW);
			} else if (mouseY >= 240 && mouseY <= 350) {
				checkHit(DOWN_RIGHT_ARROW);
			}
		} else if (mouseX >= 225 && mouseX <= 415 && mouseY >= 410) {
			// menu area
			// TODO complete it
			switch (gameStat.currentStat) {
			case PREPARE:
				handleMenuPrepare();
				break;
			case IN_GAME:
				break;
			case GAME_OVER:
				break;
			default:
				break;
			}
		}
		myReceiver.setLastHitStatus(true);
	} else if (!receiver.LeftButtonDown) {
		myReceiver.setLastHitStatus(false);
	}

	/* handle mouse hover on event */
//	if (mouseX <= 130) {
//		if (mouseY >= 130 && mouseY < 240) {
//			imgAlpha[UP_LEFT_ARROW] = 100;
//		} else if (mouseY >= 240 && mouseY <= 350) {
//			imgAlpha[DOWN_LEFT_ARROW] = 100;
//		}
//	} else if (mouseX >= 510) {
//		if (mouseY >= 130 && mouseY < 240) {
//			imgAlpha[UP_RIGHT_ARROW] = 100;
//		} else if (mouseY >= 240 && mouseY <= 350) {
//			imgAlpha[DOWN_RIGHT_ARROW] = 100;
//		}
//	}
}

void handleMenuPrepare() {
	gameStat.currentStat = IN_GAME;
	gameStat.startTime = device->getTimer()->getTime();
	std::cout << "game start!\n";
}

/* various handlers */
void handlePrepare() {

}

void handleInGame(const u32 now, const u32 delta) {
	u32 curCount = static_cast<u32>((now - gameStat.startTime) / 1000);for (std::list<ArrowInfo>::iterator iter = arrowQueue.begin();
				iter != arrowQueue.end(); iter++) {
		if (iter->curPos >= 300) {
			iter = arrowQueue.erase(iter);
		}
	}
	if (curCount != gameStat.curCount) {
		ArrowInfo newArrow;
		newArrow.type = static_cast<unsigned short>(rand()%4
				+ UP_LEFT_ARROW);
		newArrow.isRight = (newArrow.type - UP_LEFT_ARROW)/2 == 1;
		newArrow.curPos = 0;
		arrowQueue.push_back(newArrow);
		gameStat.curCount = curCount;
	}
	drawArrows(delta);
}

void handleGameOver(void) {

}

void drawArrows(const u32 delta) {
	s32 pos;
	f32 speed = 110;
	f32 offset;
	for (std::list<ArrowInfo>::iterator iter = arrowQueue.begin();
			iter != arrowQueue.end(); iter++) {
		offset = speed * static_cast<f32>(delta) / 1000.0;
		//	cout << "offset " << offset << "\n";
		if (iter->isRight) {
			pos = 640 - (iter->curPos + offset + 40);
		} else {
			pos = iter->curPos + offset;
		}
		iter->curPos += offset;
//		std::cout << "offset " << offset << " pos " << pos
//						<< " delta " << delta << '\n';
		driver->draw2DImage(images[iter->type], position2d<s32>(pos, 23),
				arrowSize, 0, video::SColor(255, 255, 255, 255), true);
	}
}

void checkHit(unsigned short hit) {
	if (gameStat.currentStat != IN_GAME) {
		return;
	} else {
		bool hitted = false;
		for (std::list<ArrowInfo>::iterator iter = arrowQueue.begin();
				iter != arrowQueue.end(); iter++) {
			if (iter->type == hit && iter->curPos >= 280) {
				hitted = true;
				cout << "pos: " << iter->curPos << '\n';
				arrowQueue.erase(iter);
				break;
			}
		}
		if (hitted) {
			cout << "hitted\n";
//			gameStat.curScore += 1;
		} else {
			cout << "missed\n";
//			gameStat.curScore -= 1;
		}
//		cout << "currentScore is " << gameStat.curScore << '\n';
	}
}

int main(int argc, char** argv) {

	/* Initialize the random number generator with a seed */
	srand((unsigned) time(NULL));
	//initAR();
	device = createDevice(video::EDT_OPENGL, dimension2d<u32>(640, 480), 16,
			false, false, false, &myReceiver);
	if (!device) {
		std::cerr << "no device found\n";
	}
	device->setWindowCaption(L"Pinbob");
	init();
	loadImages();
	MyEventReceiver::SMouseState mouseState;
	int lastFPS = -1;
	u32 then = device->getTimer()->getTime();


	//MyNode *myNode = new MyNode(smgr->getRootSceneNode(), smgr, 666);
#ifdef ART
	/* AR part */
		ARUint8 *dataPtr;

		if ((dataPtr = (ARUint8 *) arVideoGetImage()) == NULL
		)
			printf("no image loaded\n");

	ISceneNode *myNode = 0;

	IAnimatedMesh *mesh = smgr->getMesh("asset/models/zzz.obj");
	myNode = smgr->addAnimatedMeshSceneNode(mesh,0,777);


	matrix4 projection_matrix;
	vector3df camera_pos = vector3df(0, 0, 0);
	vector3df camera_target = vector3df(0, 0, -10);
	ICameraSceneNode* camera = smgr->addCameraSceneNode(0, camera_pos,
			camera_target);
	ITexture* ARimage = create_ITexture_from_ARimage(dataPtr, xsize, ysize);
	projection_matrix.setM(gl_cpara);
	camera->setProjectionMatrix(projection_matrix);
	printf("up vector:%f %f %f\n", camera->getUpVector().X,
			camera->getUpVector().Y, camera->getUpVector().Z);
#else
		ISceneNode *node = 0;

		IAnimatedMesh *mesh = smgr->getMesh("asset/models/zzz.obj");
		node = smgr->addAnimatedMeshSceneNode(mesh,0,777);
	//camera stuff
		vector3df camera_pos = vector3df(0,0,0);
		vector3df camera_target = vector3df(0,0,1);
		ICameraSceneNode* camera = smgr->addCameraSceneNode(0, camera_pos, camera_target);

		//AR stuff
		IARManager* armgr = new IARManager(device);
		//init the camera
		armgr->beginCamera(cparam_name, 0, vconf);
		//node for the lady, attached the the hiro pattern
		armgr->addARSceneNode(patt_name, node);
		//node for the fairy and water, attached the the sample1 pattern
		//armgr->addARSceneNode("ardata/patt.sample1", fairy);
		//node for the dwarf, attached to a multi-pattern
		//armgr->addARMultiSceneNode("ardata/multi/marker.dat", dwarf);
		//now fix our camera to display right
		armgr->fixCamera(camera);

#endif
	while (device->run()) {
		const u32 now = device->getTimer()->getTime();
		const u32 deltaTime = now - then; // in ms
		then = now;
		if (device->isWindowActive()) {
//			if (dataPtr = (ARUint8 *) arVideoGetImage())
//				update_ITexture_from_ARimage(ARimage, dataPtr, xsize, ysize);
//			driver->draw2DImage(ARimage, rect<s32>(0, 0, 640, 480),
//							rect<s32>(0, 0, 320, 240));
			driver->beginScene(true, true, SColor(255, 0, 0, 0));
			//make movements and bring in new image
					armgr->run();

					//draw the background image centered and scaled
					armgr->drawBackground();

//			driver->draw2DImage(ARimage,
//					core::rect<s32>(0,0,640,480),
//					core::rect<s32>(0, 0, 320, 240), 0,
//					video::SColor(255, 255, 250, 255), false);

			//AttachNode(myNode, dataPtr);
			handleMousePosition(myReceiver.getMouseState());
			switch (gameStat.currentStat) {
			case PREPARE:
				handlePrepare();
				break;
			case IN_GAME:
				handleInGame(now, deltaTime);
				break;
			case GAME_OVER:
				handleGameOver();
				break;
			default:
				break;
			}

			for (int i = 0; i < IMG_LENGTH; i++) {
				driver->draw2DImage(images[i], imgPos[i], imgSize[i], 0,
						video::SColor(255, 255, 255, 255), true);
			}
//
			smgr->drawAll();
			guienv->drawAll();
			driver->endScene();
			int fps = driver->getFPS();

			if (lastFPS != fps) {
				core::stringw str = L"Pinbob [";
				str += driver->getName();
				str += "] FPS:";
				str += fps;
				device->setWindowCaption(str.c_str());
				lastFPS = fps;
			}
			//	delayFPS.delay();
		} else {
			device->yield();
		}
		//device->sleep(39);
		//delayFPS.delay();

	}

	device->drop();

	return 0;
}

ITexture* update_ITexture_from_ARimage(ITexture *dest, ARUint8 *ardata,
		int width, int height) {
	u8* pixels;
	pixels = (u8*) (dest->lock());
	if (pixels) {
		int max_pixels = width * height;

		for (int i = 0; i < max_pixels; i++) {
			*pixels = *ardata;
			pixels++;
			ardata++;
			*pixels = *ardata;
			pixels++;
			ardata++;
			*pixels = *ardata;
			pixels++;
			ardata++;

			pixels++;
		}

		dest->unlock();
	} else {
		printf("some hellish error\n");
	}

	return dest;
}

ITexture* create_ITexture_from_ARimage(ARUint8 *ardata, int width, int height) {

	ITexture* m_poTileTexture = driver->addTexture(
			core::dimension2d<u32>(width, height), "TileTex",
			video::ECF_A1R5G5B5);

	ITexture* m_poTileNormalMap = driver->addTexture(
			core::dimension2d<u32>(width, height), "NormTex",
			video::ECF_A1R5G5B5);

	// read the pixels directly into the texture
	u8* pixels;
	pixels = (u8*) (m_poTileTexture->lock());
	if (pixels) {
		int max_pixels = width * height;

		for (int i = 0; i < max_pixels; i++) {
			*pixels = *ardata;
			pixels++;
			ardata++;
			*pixels = *ardata;
			pixels++;
			ardata++;
			*pixels = *ardata;
			pixels++;
			ardata++;
			pixels++;
		}

		m_poTileTexture->unlock();
	} else {
		printf("some hellish error\n");
	}

	return m_poTileTexture;
}

void initAR() {
	//nearly verbatum rip from ARToolKit's simpleTest.c, minus the "g" stuff that is used for integrating with glut
	ARParam wparam;

	/* open the video path */
	if (arVideoOpen(vconf) < 0)
		exit(0);
	/* find the size of the window */
//	if (arVideoInqSize(&xsize, &ysize) < 0)
	int newXSize = xsize * 2, newYSize = ysize * 2;
	if (arVideoInqSize(&xsize, &ysize) < 0)
		exit(0);
	printf("Image size (x,y) = (%d,%d)\n", xsize, ysize);

	/* set the initial camera parameters */
	if (arParamLoad(cparam_name, 1, &wparam) < 0) {
		printf("Camera parameter load error !!\n");
		exit(0);
	}
	arParamChangeSize(&wparam, xsize, ysize, &cparam);
	arInitCparam(&cparam);
	printf("*** Camera Parameter ***\n");
	arParamDisp(&cparam);

	if ((patt_id = arLoadPatt(patt_name)) < 0) {
		printf("pattern load error !!\n");
		exit(0);
	}

	init_camera(&cparam, 1.0, 0, 0, 0, 0);

	arVideoCapStart();
}

void AttachNode(ISceneNode *thenode, ARUint8 *dataPtr) {
	ARMarkerInfo *marker_info;
	int marker_num;
	int j, k;
	double gl_para[16];
	float glf_para[16];
	int i;
	CMatrix4<float> mat;

	arDetectMarker(dataPtr, thresh, &marker_info, &marker_num);

	arVideoCapNext();

	/* check for object visibility */
	k = -1;
	for (j = 0; j < marker_num; j++) {
		if (patt_id == marker_info[j].id) {
			if (k == -1)
				k = j;
			else if (marker_info[k].cf < marker_info[j].cf)
				k = j;
		}
	}
	if (k == -1) {
		return;
	}

	/* get the transformation between the marker and the real camera */
	arGetTransMat(&marker_info[k], patt_center, patt_width, patt_trans);

	convert_trans_para(patt_trans, gl_para);
	for (i = 0; i < 16; i++)
		glf_para[i] = (float) gl_para[i];
	mat.setM(glf_para);

	vector3d<f32> scale_vec = mat.getScale();
	vector3d<f32> rot_vec = mat.getRotationDegrees();
	vector3d<f32> pos_vec = mat.getTranslation();

	pos_vec.X = -pos_vec.X;

	rot_vec.X += 90;
	rot_vec.Y = -rot_vec.Y;
	rot_vec.Z = -rot_vec.Z;

	printf("scale=<%f %f %f>\n", scale_vec.X, scale_vec.Y, scale_vec.Z);
	thenode->setScale(scale_vec);
	thenode->setRotation(rot_vec);
	thenode->setPosition(pos_vec + vector3df(0, -25, 0));

	//driver->setTransform(ETS_WORLD, mat);
}

void convert_trans_para(double para[3][4], double gl_para[16]) {
	int i, j;

	for (j = 0; j < 3; j++) {
		for (i = 0; i < 4; i++) {
			gl_para[i * 4 + j] = para[j][i];
		}
	}
	gl_para[0 * 4 + 3] = gl_para[1 * 4 + 3] = gl_para[2 * 4 + 3] = 0.0;
	gl_para[3 * 4 + 3] = 1.0;
}

void init_camera(ARParam *cparam, double zoom, int fullFlag, int xwin, int ywin,
		int hmd_flag) {
	int i;

	gl_hmd_flag = hmd_flag;
	gZoom = zoom;
	gImXsize = cparam->xsize;
	gImYsize = cparam->ysize;
	if (gl_hmd_flag == 0) {
		gXsize = (int) ((double) cparam->xsize * gZoom);
		gYsize = (int) ((double) cparam->ysize * gZoom);
	} else {
		gXsize = AR_HMD_XSIZE;
		gYsize = AR_HMD_YSIZE;
	}
	gMiniXsize = (int) ((double) cparam->xsize * gZoom / GMINI);
	gMiniYsize = (int) ((double) cparam->ysize * gZoom / GMINI);

	if (xwin * ywin > MINIWIN_MAX) {
		if (xwin > MINIWIN_MAX
		)
			xwin = MINIWIN_MAX;
		ywin = MINIWIN_MAX / xwin;
	}
	gMiniXnum = xwin;
	gMiniYnum = ywin;
	gWinXsize =
			(gMiniXsize * gMiniXnum > gXsize) ? gMiniXsize * gMiniXnum : gXsize;
	gWinYsize = gYsize + gMiniYsize * gMiniYnum;

	gCparam = *cparam;
	for (i = 0; i < 4; i++) {
		gCparam.mat[1][i] = (gCparam.ysize - 1) * (gCparam.mat[2][i])
				- gCparam.mat[1][i];
	}
	argConvGLcpara(&gCparam, AR_GL_CLIP_NEAR, AR_GL_CLIP_FAR, gl_cpara);

	//argInit2( fullFlag );
}

void argConvGLcpara(ARParam *param, double gnear, double gfar, float m[16]) {
	argConvGLcpara2(param->mat, param->xsize, param->ysize, gnear, gfar, m);
}

static void argConvGLcpara2(double cparam[3][4], int width, int height,
		double gnear, double gfar, float m[16]) {
	double icpara[3][4];
	double trans[3][4];
	double p[3][3], q[4][4];
	int i, j;

	if (arParamDecompMat(cparam, icpara, trans) < 0) {
		printf("gConvGLcpara: Parameter error!!\n");
		exit(0);
	}

	for (i = 0; i < 3; i++) {
		for (j = 0; j < 3; j++) {
			p[i][j] = icpara[i][j] / icpara[2][2];
		}
	}
	m[0] = q[0][0] = (2.0 * p[0][0] / width);
	m[1] = q[0][1] = (2.0 * p[0][1] / width);
	m[2] = q[0][2] = ((2.0 * p[0][2] / width) - 1.0);
	m[3] = q[0][3] = 0.0;

	m[4] = q[1][0] = 0.0;
	m[5] = q[1][1] = (2.0 * p[1][1] / height);
	m[6] = q[1][2] = ((2.0 * p[1][2] / height) - 1.0);
	m[7] = q[1][3] = 0.0;

	m[8] = q[2][0] = 0.0;
	m[9] = q[2][1] = 0.0;
	m[10] = q[2][2] = -(gfar + gnear) / (gfar - gnear);
	m[11] = q[2][3] = -2.0 * gfar * gnear / (gfar - gnear);

	m[12] = q[3][0] = 0.0;
	m[13] = q[3][1] = 0.0;
	m[14] = q[3][2] = -1.0;
	m[15] = q[3][3] = 0.0;

	for (i = 0; i < 4; i++) {
		for (j = 0; j < 3; j++) {
			m[i + j * 4] = q[i][0] * trans[0][j] + q[i][1] * trans[1][j]
					+ q[i][2] * trans[2][j];
		}
		m[i + 3 * 4] = q[i][0] * trans[0][3] + q[i][1] * trans[1][3]
				+ q[i][2] * trans[2][3] + q[i][3];
	}
}

#endif
