
#include "SettingHandler.h"


SettingHandler::SettingHandler(const c8 * sSettingsFile )
{
	if (sSettingsFile) strcpy(m_sSettingsFile,sSettingsFile); else m_sSettingsFile[0]='\0';
	m_iDriver = EDT_NULL;
	m_bFullscreen=false;
	m_iMinX=0;
	m_iMinY=0;
	m_pDevice = irr::createDevice(irr::video::EDT_NULL);
	m_aDrvs = new _DRV();
	load();
}

SettingHandler::~SettingHandler()
{

}

void SettingHandler::save()
{
	//Write settings to the settings file
    // not necessary currently
}

void SettingHandler::load()
{
	IXMLReaderUTF8 *pXml=m_pDevice->getFileSystem()->createXMLReaderUTF8(m_sSettingsFile);
	if (pXml) {
		while (pXml->read()) {
			//video driver parameter
			if (!strcmp(pXml->getNodeName(),"videodriver")) {
				m_aDrvs->sName = pXml->getAttributeValue("name");;
				m_aDrvs->iDriver=(E_DRIVER_TYPE)atoi(pXml->getAttributeValue("id"  ));
			}
			//resolution parameter
			if (!strcmp(pXml->getNodeName(),"resolution")) {
				if (pXml->getAttributeValue("minx")) m_iMinX=atoi(pXml->getAttributeValue("minx"));
				if (pXml->getAttributeValue("miny")) m_iMinY=atoi(pXml->getAttributeValue("miny"));
			}
			if (!strcmp(pXml->getNodeName(),"fullscreen")) m_bFullscreen=atoi(pXml->getAttributeValue("value"))!=0;
			if (!strcmp(pXml->getNodeName(),"driver"    )) m_iDriver    =(E_DRIVER_TYPE)atoi(pXml->getAttributeValue("value"));
		}

		pXml->drop();
	}
}

IrrlichtDevice * SettingHandler::createDeviceFromSettings()
{
	if (m_pDevice) {
		m_pDevice->closeDevice();
		m_pDevice->run();
		m_pDevice->drop();
		m_pDevice=NULL;
	}
	m_pDevice=createDevice(m_aDrvs->iDriver,dimension2du(m_iMinX,m_iMinY),16,m_bFullscreen,false,false,0);
	return m_pDevice;
}
