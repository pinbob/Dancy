/***********************************************************************
 * Module:  ConfigFileManager.cpp
 * Author:  liwenhaosuper
 * Modified: 2011Äê07ÔÂ21ÈÕ 21:27:10
 * Purpose: Implementation of the class ConfigFileManager
 * Comment: The CConfigFileManager manages reading and writing of the global configuration file
 ***********************************************************************/

#include "ConfigFileManager.h"

////////////////////////////////////////////////////////////////////////
// Name:       ConfigFileManager::getSharedInstance()
// Purpose:    Implementation of ConfigFileManager::getSharedInstance()
// Comment:     Get the singleton instance of the manager
//              @return the shared instance of the manager
// Return:     CConfigFileManager *
////////////////////////////////////////////////////////////////////////

ConfigFileManager * ConfigFileManager::getSharedInstance(void)
{
   // TODO : implement
	static ConfigFileManager configManager;
	return &configManager;
}

////////////////////////////////////////////////////////////////////////
// Name:       ConfigFileManager::addReader(IConfigFileReader* pReader)
// Purpose:    Implementation of ConfigFileManager::addReader()
// Parameters:
// - pReader
// Return:     void
////////////////////////////////////////////////////////////////////////

void ConfigFileManager::addReader(IConfigFileReader* pReader)
{
   // TODO : implement
	m_lReaders.push_back(pReader);
}

////////////////////////////////////////////////////////////////////////
// Name:       ConfigFileManager::addWriter(IConfigFileWriter* pWriter)
// Purpose:    Implementation of ConfigFileManager::addWriter()
// Parameters:
// - pWriter
// Return:     void
////////////////////////////////////////////////////////////////////////

void ConfigFileManager::addWriter(IConfigFileWriter* pWriter)
{
   // TODO : implement
	m_lWriters.push_back(pWriter);
}

////////////////////////////////////////////////////////////////////////
// Name:       ConfigFileManager::removeReader(IConfigFileReader* pReader)
// Purpose:    Implementation of ConfigFileManager::removeReader()
// Parameters:
// - pReader
// Return:     void
////////////////////////////////////////////////////////////////////////

void ConfigFileManager::removeReader(IConfigFileReader* pReader)
{
   // TODO : implement
	list<IConfigFileReader *>::Iterator it;
	for (it=m_lReaders.begin(); it!=m_lReaders.end(); it++) 
	{
		if ((*it)==pReader) 
		{ 
			m_lReaders.erase(it); 
			return;
		}
	}
}

////////////////////////////////////////////////////////////////////////
// Name:       ConfigFileManager::removeWriter(IConfigFileWriter pWriter)
// Purpose:    Implementation of ConfigFileManager::removeWriter()
// Parameters:
// - pWriter
// Return:     void
////////////////////////////////////////////////////////////////////////

void ConfigFileManager::removeWriter(IConfigFileWriter* pWriter)
{
   // TODO : implement
	list<IConfigFileWriter *>::Iterator it;
	for (it=m_lWriters.begin(); it!=m_lWriters.end(); it++)
	{
		if ((*it)==pWriter)
		{ 
			m_lWriters.erase(it); 
			return; 
		}
	}
}

////////////////////////////////////////////////////////////////////////
// Name:       ConfigFileManager::clearReadersWriters()
// Purpose:    Implementation of ConfigFileManager::clearReadersWriters()
// Return:     void
////////////////////////////////////////////////////////////////////////

void ConfigFileManager::clearReadersWriters(void)
{
   // TODO : implement
	m_lReaders.clear();
	m_lWriters.clear();
}

////////////////////////////////////////////////////////////////////////
// Name:       ConfigFileManager::loadConfig(IrrlichtDevice* pDevice, const c8 * sFileName)
// Purpose:    Implementation of ConfigFileManager::loadConfig()
// Parameters:
// - pDevice
// - sFileName
// Return:     void
////////////////////////////////////////////////////////////////////////

void ConfigFileManager::loadConfig(IrrlichtDevice* pDevice, const c8 * sFileName)
{
   // TODO : implement
	IXMLReaderUTF8 *pXml=pDevice->getFileSystem()->createXMLReaderUTF8(sFileName);
	bool bSettings=false;

	if (pXml) {
		while (pXml->read()) {
			bSettings=bSettings || (!strcmp(pXml->getNodeName(),"settings") && pXml->getNodeType()==EXN_ELEMENT);
			if (bSettings) {
				list<IConfigFileReader *>::Iterator it;
				for (it=m_lReaders.begin(); it!=m_lReaders.end(); it++) {
					(*it)->readConfig(pXml);
				}
			}
		}
		pXml->drop();
	}
}

////////////////////////////////////////////////////////////////////////
// Name:       ConfigFileManager::writeConfig(IrrlichtDevice* pDevice, const c8 * sFileName)
// Purpose:    Implementation of ConfigFileManager::writeConfig()
// Parameters:
// - pDevice
// - sFileName
// Return:     void
////////////////////////////////////////////////////////////////////////

void ConfigFileManager::writeConfig(IrrlichtDevice* pDevice, const c8 * sFileName)
{
   // TODO : implement
	IXMLWriter *pXml=pDevice->getFileSystem()->createXMLWriter(sFileName);

	if (pXml) {
		pXml->writeXMLHeader();
		pXml->writeElement(L"settings");
		pXml->writeLineBreak();

		list<IConfigFileWriter *>::Iterator it;
		for (it=m_lWriters.begin(); it!=m_lWriters.end(); it++) {
			(*it)->writeConfig(pXml);
		}
		pXml->writeClosingTag(L"settings");
		pXml->writeLineBreak();
		pXml->drop();
	}
}