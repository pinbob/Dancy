
/************************************************************************/
/*                        Author:liwenhaosuper
                          Date: 2011-07-19

						  SettingManager.h

	This class loads and writes the settings
	and manages the options.
    usage of this class can be as easy as the following:



	#include "SettingManager.h"

	int main()
	{
	SettingManager simple("asset/config/SettingManager.xml");
	if(simple.load())
	{
	simple.setSetting("vconf","../../bin/Data/WDM_camera_flipV.xml","params");
	simple.setSetting("cparam_name","../../bin/Data/camera_para.dat","params");
	simple.setSetting("patt_name","../../bin/Data/patt.hiro","params");
	simple.setSetting("patt_name1","../../bin/Data/patt.hiro","others");
	simple.setSetting("patt_name2","../../bin/Data/patt.hiro","images");
	simple.setSetting("patt_name3","../../bin/Data/patt.hiro","meshs");
	simple.setSetting("liwenhaosuper","../../bin/Data/patt.hiro");
	simple.save();
	}
	else printf("settingmanager.xml could not be open");
	//MainScene mainscene;
	return 0;
	}

*/
/************************************************************************/



#ifndef SETTINGMANAGER_H_
#define SETTINGMANAGER_H_




#include "irrlicht.h"

using namespace irr;
using namespace core;
using namespace scene;
using namespace video;
using namespace io;

#pragma comment(lib, "Irrlicht.lib")
#pragma once



class SettingManager
{
public:

	/**
	 *	Construct setting managers and set default settings
	 * default location to "asset/config/SettingManager.xml"
	 */
	SettingManager(const stringw& settings_file = L"asset/config/SettingManager.xml"): SettingsFile(settings_file), NullDevice(0)
	{
		// Irrlicht null device, we want to load settings before we actually created our device, therefore, nulldevice
		NullDevice = irr::createDevice(irr::video::EDT_NULL);

		// node tag used in the xml
		paramTag = L"params"; //constant for paramtag
	    paramInternalTag = L"param"; //we'll be looking for this tag in the xml

		imageTag = L"images"; //constant for imagetag
		imageInternalTag = L"image";

		meshTag = L"meshs";
		meshInternalTag = L"mesh";

		othersTag = L"others";
		othersInternalTag = L"other";

		resolutionTag = L"resolutionOption";
		resolutionInternalTag=L"resolution";
	}

	/**
	 *	Destructor, you could store settings automatically on exit of your application if you wanted to
	 *	in our case we simply drop the nulldevice
	 */
	~SettingManager()
	{
		if (NullDevice)
		{
			NullDevice->closeDevice();
			NullDevice->drop();
		}
	};
	/************************************************************************/
	/* load the content of the xml into the "ParamsMap"
	/* return false if fail to load to the content                             */
	/************************************************************************/
	bool load();

	/**
	 *	Save the xml to disk
	 *	We use the nulldevice
	 *  return false if fail to save the content
	 *  this function should be called after you do some changes to the xml file
	 */
	bool save();

	/**
	 *	Set setting in our manager
	 *  tag is either "params","images","meshs", or "others"
	 */
	void setSetting(const stringw& name, const stringw& value,const stringw& tag = L"others");

	/**
	 *	set setting overload to quickly assign integers to our setting map
	 *   tag is either "params","images","meshs", or "others"
	 */
	void setSetting(const stringw& name, s32 value,const stringw& tag = L"others");

	/**
	 *	Get setting as string
	 *	@param key Name of setting
	 *	@return	Empty string if the settings is not found, else value of the setting
	 */
	stringw getSetting(const stringw& key,const stringw& tag =L"others") const;

		/**
	 *	Get setting as dimension2d<u32>
	 *	@param key Name of setting
	 *	@return	Empty string if the settings is not found, else value of the setting
	 */
	dimension2d<s32> getDimension2dSetting(const stringw key);

	void setDimension2dSetting(const stringw key,dimension2d<s32> values);

	/**
	 *	Get setting as bool
	 *	@param key Name of setting
	 *	@return	False if the key cannot be found, else true if the setting == 1
	 */
	bool getSettingAsBoolean(const stringw& key,const stringw& tag = L"others" ) const
	{
		stringw s = getSetting(key,tag);
		if (s.size()==0)
			return false;
		return s.equals_ignore_case(L"1");
	}

	/**
	 *	Get setting as integer NOTE: function is not used in example but provided for completeness
	 *	@param	key	name of setting
	 *	@return	0 if the key cannot be found, else the setting converted to an integer
	 */
	s32 getSettingAsInteger(const stringw& key,const stringw& tag = L"others") const
	{
		//we implicitly cast to string instead of stringw because strtol10 does not accept wide strings
		const stringc s = getSetting(key,tag);
		if (s.size()==0)
			return 0;
		return strtol10(s.c_str());
	}

private:
	map<stringw, stringw> ParamsMap; //current config
	map<stringw, stringw> ImagesMap;
	map<stringw, stringw> MeshsMap;
	map<stringw, stringw> OthersMap;  
	map<stringw, dimension2d<s32>> ResolutionOptions;
	stringw SettingsFile; // location of the xml
	irr::IrrlichtDevice* NullDevice;

	// node tag used in the xml
	stringw paramTag; //constant for paramtag
	stringw paramInternalTag; //we'll be looking for this tag in the xml

	stringw imageTag; //constant for imagetag
	stringw imageInternalTag;

	stringw meshTag;
	stringw meshInternalTag;

	stringw othersTag;
	stringw othersInternalTag;

	stringw resolutionTag;
	stringw resolutionInternalTag;
};



#endif