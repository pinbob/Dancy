/***********************************************************************
 * Module:  SettingHandler.h
 * Author:  liwenhaosuper
 * Modified: 2011Äê07ÔÂ21ÈÕ 21:05:10
 * Purpose: Declaration of the class SettingHandler
 ***********************************************************************/

#if !defined(__pibbob_logic_SettingHandler_h)
#define __pibbob_logic_SettingHandler_h

#include "irrlicht.h"
#ifdef WIN32
#pragma comment(lib,"irrlicht.lib")
#endif

using namespace irr;
using namespace core;
using namespace video;
using namespace io;

class SettingHandler
{
private:
	    /**
     * @class CSettings::_DRV
     * In this class the name and the ID of the available drivers are stored
     */
    class _DRV {
      public:
        stringw sName;    /**< name of the driver */
        E_DRIVER_TYPE iDriver;  /**< ID of the driver */
    };
	c8 m_sSettingsFile[1024]; /**< the settings file */ 
	IrrlichtDevice  *m_pDevice;       /**< the irrlicht device to be used */
	_DRV* m_aDrvs;       /**< list of the video drivers that are available only 1 currently*/
	bool m_bFullscreen;      /**< is fullscreen wanted? */
	E_DRIVER_TYPE m_iDriver;  /**< the driver */
	u32 m_iMinX,m_iMinY;
public:
    SettingHandler(const c8 * sSettingsFile);
	virtual ~SettingHandler();

	void save();
	void load();

	 /**
     * create a new device from the user's settings
     * @return the newly created IrrlichtDevice instance
     */
    IrrlichtDevice *createDeviceFromSettings();

};

#endif