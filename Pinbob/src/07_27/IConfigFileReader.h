/***********************************************************************
 * Module:  IConfigFileReader.h
 * Author:  liwenhaosuper
 * Modified: 2011Äê07ÔÂ21ÈÕ 21:25:53
 * Purpose: Declaration of the class IConfigFileReader
 * Comment: This interface must be implemented by all classes that read from the global config file
 ***********************************************************************/

#if !defined(__pibbob_logic_IConfigFileReader_h)
#define __pibbob_logic_IConfigFileReader_h

#include "irrlicht.h"

#ifdef WIN32
#pragma comment(lib,"irrlicht.lib")
#endif

using namespace irr;

using namespace core;
using namespace scene;
using namespace video;
using namespace io;
using namespace gui;

/**
 * This interface must be implemented by all classes that read from the global config file
 */
class IConfigFileReader
{
public:
   virtual void readConfig(IXMLReaderUTF8* pXml)=0;
};

#endif