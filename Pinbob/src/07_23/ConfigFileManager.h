/***********************************************************************
 * Module:  ConfigFileManager.h
 * Author:  liwenhaosuper
 * Modified: 2011Äê07ÔÂ21ÈÕ 21:27:10
 * Purpose: Declaration of the class ConfigFileManager
 * Comment: The CConfigFileManager manages reading and writing of the global configuration file
 ***********************************************************************/

#if !defined(__pibbob_logic_ConfigFileManager_h)
#define __pibbob_logic_ConfigFileManager_h

#include "irrlicht.h"
#include "IConfigFileReader.h"
#include "IConfigFileWriter.h"

#ifdef WIN32
#pragma comment(lib,"irrlicht.lib")
#endif

using namespace irr;
using namespace core;
using namespace scene;
using namespace video;
using namespace io;
using namespace gui;



class ConfigFileManager
{
public:
   /*  Get the singleton instance of the manager
    *  @return the shared instance of the manager */
   static ConfigFileManager * getSharedInstance(void);
   void addReader(IConfigFileReader* pReader);
   void addWriter(IConfigFileWriter* pWriter);
   void removeReader(IConfigFileReader* pReader);
   void removeWriter(IConfigFileWriter* pWriter);
   void clearReadersWriters(void);
   void loadConfig(IrrlichtDevice* pDevice, const c8 * sFileName);
   void writeConfig(IrrlichtDevice* pDevice, const c8 * sFileName);

protected:
   list<IConfigFileReader *> m_lReaders;
   list<IConfigFileWriter *> m_lWriters;

private:

};

#endif