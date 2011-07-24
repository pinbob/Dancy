/***********************************************************************
 * Module:  OptionsHandler.h
 * Author:  liwenhaosuper
 * Modified: 2011Äê07ÔÂ21ÈÕ 21:03:50
 * Purpose: Declaration of the class OptionsHandler. It handlers the options menu for the global system
 ***********************************************************************/

#if !defined(__pibbob_logic_OptionsHandler_h)
#define __pibbob_logic_OptionsHandler_h

#include "irrlicht.h"
#ifdef WIN32
#pragma comment(lib,"irrlicht.lib")
#endif
#include "StateMachine.h"

#include "IConfigFileReader.h"
#include "IConfigFileWriter.h"
#include "IState.h"
#include "ConfigFileManager.h"

class OptionsHandler : public IConfigFileReader, public IConfigFileWriter, public IEventReceiver, public IState
{
public:
protected:
private:

	virtual void readConfig( IXMLReaderUTF8* pXml );

	virtual void writeConfig( IXMLWriter* pXml );

	virtual u32 update( void );

	virtual void activate( IState* pPrevious );

	virtual void deactivate( IState* pNext );

};

#endif