/************************************************************************/
/*                        Author:liwenhaosuper
                          Date: 2011-07-20
*/

#ifndef MAINSCENE_H_
#define MAINSCENE_H_

#pragma once

#include "irrlicht.h"
#include <iostream>
#include "SettingManager.h"
#ifdef WIN32
#include <windows.h>
#include <assert.h>
#include "MyEventReceiver.h"
#endif

using namespace irr;
using namespace core;

#pragma comment(lib,"irrlicht.lib")

class MainScene
{
public:
   MainScene(video::E_DRIVER_TYPE drivertype = video::EDT_OPENGL):driverType(drivertype),now(0),last(0),hitState(0){
 	   setting = new SettingManager();
 	   while(!setting->load())
 	   {
 		   printf(" MainScene: could not open settingManager.xml, waiting for opening...");
 		   Sleep(1000);
 	   }
       dimension2d<u32> windowsize = (dimension2d<u32>)setting->getDimension2dSetting("windowSize");

	   device = createDevice(drivertype, windowsize);

	   if(device==NULL)
	   {
		    std::cerr << "no device found\n";
			exit(1);
	   }
	   device->setWindowCaption(L"Dancy");

   }

   MainScene(IrrlichtDevice* newdevice):device(newdevice),now(0),last(0),hitState(0){
#ifdef WIN32
	   assert(device!=NULL);
#endif
   }

   ~MainScene(){
	   device->drop();
   }

   /*
   getter method of now and last and hitstate
   */
   u32 GetNow(){return now;}
   u32 GetLast(){ return last;}
   u8 GetHistState(){ return hitState;}

   /************************************************************************
   /* get the main device                                                  
   /************************************************************************/
   IrrlichtDevice* GetDevice(){  return device; }

   /************************************************************************
   /* get the current FPS                                                  *
   /************************************************************************/
   irr::s32 GetFPS()
   {
	   return device->getVideoDriver()->getFPS();
   }

   /************************************************************************
   /*   initialize the main scene                                          *
   /************************************************************************/
   bool InitializeMainScene();

   /************************************************************************
   /*       begin to draw main scene,this is a loop                          
   /************************************************************************/
   void run();

   //virtual function list
  
   /************************************************************************
   /* called when device is idle and device is on running state            
   /************************************************************************/
   virtual void OnWindowsIdle(){}
   /************************************************************************
   /* called when device has finish drawing during one loop                
   /************************************************************************/
   virtual void OnDrawFinish(){}
   /************************************************************************
   /* called when initializing the main scene                              
   /************************************************************************/
   virtual void OnSceneInit(){}
   /************************************************************************
   /*    call when key hit state changed                                                                  
   /************************************************************************/
   virtual void OnHitStateChange(){}

private:
	/************************************************************************
	/* load images for main scene                                         
	/************************************************************************/
	bool LoadImage();
	/************************************************************************
	/*  global device                                                        
	/************************************************************************/
   IrrlichtDevice *device;
   /************************************************************************
   /* event receiver                                                         
   /************************************************************************/
   MyEventReceiver eventReceiver;   //event listener 
   /************************************************************************
   /*  type of the driver,default for video::EDT_OPENGL                          
   /************************************************************************/ 
   video::E_DRIVER_TYPE driverType;
   /************************************************************************
   /* setting manager is a xml handler used for loading and saving configurations   
   /************************************************************************/
   SettingManager* setting; 
   /************************************************************************
   /*  	  @param last the last frame timestamp
   /*     @param now the current frame timestamp   
   /*     @param hitState is four key state corresponding to the four arrows
   /************************************************************************/
   u32 now;
   u32 last;
   u8 hitState;
};
#endif