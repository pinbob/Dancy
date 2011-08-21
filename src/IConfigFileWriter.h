/***********************************************************************
 * Module:  IConfigFileWriter.h
 * Author:  Administrator
 * Modified: 2011Äê07ÔÂ21ÈÕ 21:26:31
 * Purpose: Declaration of the class IConfigFileWriter
 ***********************************************************************/

#if !defined(__pibbob_logic_IConfigFileWriter_h)
#define __pibbob_logic_IConfigFileWriter_h


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


class IConfigFileWriter
{
public:
   virtual void writeConfig(IXMLWriter* pXml)=0;
};

#endif