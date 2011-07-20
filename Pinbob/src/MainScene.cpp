
#include "MainScene.h"


bool MainScene::InitializeMainScene()
{
    setting = new SettingManager();
    while(!setting->load())
	{
		printf("failed to load settingManager.xml,waiting for loading...\n");
		Sleep(1000);
	}
	irr::io::path meshfile = setting->getSetting(L"turtle",L"meshs");
	device->getFileSystem()->addZipFileArchive("asset/models/map-20kdm2.pk3");
 	irr::scene::IAnimatedMesh* mesh = device->getSceneManager()->getMesh("asset/models/20kdm2.bsp");//device->getSceneManager()->getMesh(meshfile);
 	if(mesh)
 	{
 		scene::ISceneNode* node = device->getSceneManager()->addOctreeSceneNode(mesh->getMesh(0), 0, -1, 1024);
 		if(node)
 			node->setPosition(core::vector3df(-1390,-100,-1249));
 		//device->getSceneManager()->addCameraSceneNodeFPS();
		vector3df camera_pos = vector3df(10, 70, -55);
		vector3df camera_target = vector3df(10, 70, -50);
		ICameraSceneNode* camera = device->getSceneManager()->addCameraSceneNode(0, camera_pos,
			camera_target);
 		device->getCursorControl()->setVisible(true);
		//virtual function
		OnSceneInit();
 		return true;
 	}
 	return false;

}

bool MainScene::LoadImage()
{
	return false;
}

void MainScene::run()
{
	while(device->run())
	{
		if(device->isWindowActive())
		{
			last = now;
			now = device->getTimer()->getTime();
			device->getVideoDriver()->beginScene(true, true, video::SColor(255,200,200,200));
			device->getSceneManager()->drawAll();
			device->getVideoDriver()->endScene();
			OnDrawFinish();
			//key event listener
			hitState = 0;
			//W
			if(eventReceiver.IsKeyDown(irr::KEY_KEY_W))
			{
				hitState = hitState | 1;
			}
			//A
			if(eventReceiver.IsKeyDown(irr::KEY_KEY_A))
			{
				hitState = hitState | 2;
			}
			//S
			if(eventReceiver.IsKeyDown(KEY_KEY_S))
			{
				hitState = hitState | 4;
			}
			//D
			if(eventReceiver.IsKeyDown(KEY_KEY_D))
			{
				hitState = hitState | 8;
			}
			// virtual function called
			OnHitStateChange();

		}
		else {
			device->yield();
			OnWindowsIdle();
		}
	}


}
