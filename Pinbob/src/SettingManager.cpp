/************************************************************************/
/* SettingManager.cpp                                                                     */
/************************************************************************/

#include "SettingManager.h"
#include <wchar.h>
#include <cstdio>


bool SettingManager::load()
{
	//if not able to create device dont attempt to load
	if (!NullDevice)
		return false;

	irr::io::IXMLReader* xml = NullDevice->getFileSystem()->createXMLReader(SettingsFile);	//create xml reader
	if (!xml)
		return false;

	stringw currentSection; //keep track of our currentsection

	//while there is more to read
	while (xml->read())
	{
		//check the node type
		switch (xml->getNodeType())
		{
			//we found a new element
		case irr::io::EXN_ELEMENT:
			{
				//we currently are in the empty or dancy section and find the param tag so we set our current section to param
				if (currentSection.size()==0 && paramTag.equals_ignore_case(xml->getNodeName()))
				{
					currentSection = paramTag;
				}
				//we are in the param section and we find a paramInternal to parse
				else if (currentSection.equals_ignore_case(paramTag) && paramInternalTag.equals_ignore_case(xml->getNodeName() ))
				{
					//read in the key
					stringw key = xml->getAttributeValueSafe(L"name");
					//if there actually is a key to set
					if (key.size()!=0)
					{
						//set the setting in the map to the value,
						//the [] operator overrides values if they already exist or inserts a new key value
						//pair into the settings map if it was not defined yet
						ParamsMap[key] = xml->getAttributeValueSafe(L"value");
					}
				}
				//we currently are in the empty or dancy section and find the image tag so we set our current section to image
				else if(currentSection.size()==0&&imageTag.equals_ignore_case(xml->getNodeName()))
				{
					currentSection = imageTag;
				}
				//we are in the image section and we find a imageInternal to parse
				else if(currentSection.equals_ignore_case(imageTag)&&imageInternalTag.equals_ignore_case(xml->getNodeName()))
				{
					stringw key = xml->getAttributeValueSafe(L"name");
					//if there actually is a key to set
					if(key.size()!=0)
					{
						ImagesMap[key] = xml->getAttributeValueSafe(L"value");
					}
				}
				//mesh tag
				else if(currentSection.size()==0&&meshTag.equals_ignore_case(xml->getNodeName()))
				{
					currentSection = meshTag;
				}
				else if(currentSection.equals_ignore_case(meshTag)&&meshInternalTag.equals_ignore_case(xml->getNodeName()))
				{
					stringw key = xml->getAttributeValueSafe(L"name");
					if(key.size()!=0)
					{
						MeshsMap[key] = xml->getAttributeValueSafe(L"value");
					}
				}
				//others tag
				else if(currentSection.size()==0&&othersTag.equals_ignore_case(xml->getNodeName()))
				{
					currentSection = othersTag;
				}
				else if(currentSection.equals_ignore_case(othersTag)&&othersInternalTag.equals_ignore_case(xml->getNodeName()))
				{
					stringw key = xml->getAttributeValueSafe(L"name");
					if(key.size()!=0)
					{
						OthersMap[key] = xml->getAttributeValueSafe(L"value");
					}
				}
				//Resolution tag
				else if(currentSection.size()==0&&resolutionTag.equals_ignore_case(xml->getNodeName()))
				{
					currentSection = resolutionTag;
				}
				else if(currentSection.equals_ignore_case(resolutionTag)&&resolutionInternalTag.equals_ignore_case(xml->getNodeName()))
				{
					stringw key = xml->getAttributeValueSafe(L"name");
					if(key.size()!=0)
					{
						stringc width(xml->getAttributeValueSafe(L"width"));
						stringc height(xml->getAttributeValueSafe(L"height"));
						ResolutionOptions[key] = dimension2d<s32>(strtol10(width.c_str()),strtol10(height.c_str()));						
					}
				}

				//..
				// add more sections and tags to read in here
				//..
			}
			break;

			//we found the end of an element
		case irr::io::EXN_ELEMENT_END:
			//we were at the end of the param section so we reset our tag
			currentSection=L"";
			break;
		}
	}

	// don't forget to delete the xml reader
	xml->drop();

	return true;
}


/**
	 *	Save the xml to disk
	 *	We use the nulldevice
	 */
	bool SettingManager::save()
	{

		//if not able to create device don't attempt to save
		if (!NullDevice)
			return false;

		//create xml writer
		irr::io::IXMLWriter* xwriter = NullDevice->getFileSystem()->createXMLWriter(SettingsFile );
		if (!xwriter)
			return false;

		//write out the obligatory xml header. Each xml-file needs to have exactly one of those.
		xwriter->writeXMLHeader();
		//start element	dancy, you replace the label "dancy" with anything you want
		xwriter->writeElement(L"dancy");
		xwriter->writeLineBreak();					//new line

		//start section with param settings
		xwriter->writeElement(L"params");
		xwriter->writeLineBreak();					//new line

		// getIterator gets us a pointer to the first node of the settings map
		// every iteration we increase the iterator which gives us the next map node
		// until we reach the end we write settings one by one by using the nodes key and value functions
		map<stringw, stringw>::Iterator i = ParamsMap.getIterator();
		for(; !i.atEnd(); i++)
		{
			//write element as <setting name="key" value="x" />
			//the second parameter indicates this is an empty element with no children, just attributes
			xwriter->writeElement(L"param",true, L"name", i->getKey().c_str(), L"value",i->getValue().c_str() );
			xwriter->writeLineBreak();
		}
		//close param section
		xwriter->writeClosingTag(L"params");
		xwriter->writeLineBreak();


		//start section with image settings
		xwriter->writeElement(L"images");
		xwriter->writeLineBreak();					//new line
		// getIterator gets us a pointer to the first node of the settings map
		// every iteration we increase the iterator which gives us the next map node
		// until we reach the end we write settings one by one by using the nodes key and value functions
		i = ImagesMap.getIterator();
		for(; !i.atEnd(); i++)
		{
			//write element as <setting name="key" value="x" />
			//the second parameter indicates this is an empty element with no children, just attributes
			xwriter->writeElement(L"image",true, L"name", i->getKey().c_str(), L"value",i->getValue().c_str() );
			xwriter->writeLineBreak();
		}
		//close param section
		xwriter->writeClosingTag(L"images");
		xwriter->writeLineBreak();


		//start section with mesh settings
		xwriter->writeElement(L"meshs");
		xwriter->writeLineBreak();					//new line
		// getIterator gets us a pointer to the first node of the settings map
		// every iteration we increase the iterator which gives us the next map node
		// until we reach the end we write settings one by one by using the nodes key and value functions
		i = MeshsMap.getIterator();
		for(; !i.atEnd(); i++)
		{
			//write element as <setting name="key" value="x" />
			//the second parameter indicates this is an empty element with no children, just attributes
			xwriter->writeElement(L"mesh",true, L"name", i->getKey().c_str(), L"value",i->getValue().c_str() );
			xwriter->writeLineBreak();
		}
		//close param section
		xwriter->writeClosingTag(L"meshs");
		xwriter->writeLineBreak();


		//start section with others settings
		xwriter->writeElement(L"others");
		xwriter->writeLineBreak();					//new line
		// getIterator gets us a pointer to the first node of the settings map
		// every iteration we increase the iterator which gives us the next map node
		// until we reach the end we write settings one by one by using the nodes key and value functions
		i = OthersMap.getIterator();
		for(; !i.atEnd(); i++)
		{
			//write element as <setting name="key" value="x" />
			//the second parameter indicates this is an empty element with no children, just attributes
			xwriter->writeElement(L"other",true, L"name", i->getKey().c_str(), L"value",i->getValue().c_str() );
			xwriter->writeLineBreak();
		}
		//close param section
		xwriter->writeClosingTag(L"others");
		xwriter->writeLineBreak();

		//start section with others settings
		xwriter->writeElement(L"resolutionOption");
		xwriter->writeLineBreak();					//new line
		// getIterator gets us a pointer to the first node of the settings map
		// every iteration we increase the iterator which gives us the next map node
		// until we reach the end we write settings one by one by using the nodes key and value functions
		irr::core::map<stringw,dimension2d<s32>>::Iterator it= ResolutionOptions.getIterator();
		for(; !it.atEnd(); it++)
		{
			xwriter->writeElement(L"resolution",true, L"name", it->getKey().c_str(), L"width",stringw(it->getValue().Width).c_str(),L"height",stringw(it->getValue().Height).c_str() );
			xwriter->writeLineBreak();
		}
		//close param section
		xwriter->writeClosingTag(L"resolutionOption");
		xwriter->writeLineBreak();


		//close dancy section
		xwriter->writeClosingTag(L"dancy");

		//delete xml writer
		xwriter->drop();

		return true;
	}



		/**
	 *	Set setting in our manager
	 *  tag is either "params","images","meshs", or "others"
	 */
	void SettingManager::setSetting(const stringw& name, const stringw& value,const stringw& tag)
	{
		if(tag == paramTag)
		{
			ParamsMap[name]=value;
		}
		else if(tag == imageTag)
		{
			ImagesMap[name] = value;
		}
		else if(tag == meshTag)
		{
			MeshsMap[name] = value;
		}
		else
		{
			OthersMap[name] = value;
		}
	}

		/**
	 *	set setting overload to quickly assign integers to our setting map
	 *   tag is either "params","images","meshs", or "others"
	 */
	void SettingManager::setSetting(const stringw& name, s32 value,const stringw& tag)
	{
		if(tag == paramTag)
		{
			ParamsMap[name]=stringw(value);
		}
		else if(tag == imageTag)
		{
			ImagesMap[name] = stringw(value);
		}
		else if(tag == meshTag)
		{
			MeshsMap[name] = stringw(value);
		}
		else
		{
			OthersMap[name] = stringw(value);
		}
	}


		/**
	 *	Get setting as string
	 *	@param key Name of setting
	 *	@return	Empty string if the settings is not found, else value of the setting
	 */
	stringw SettingManager::getSetting(const stringw& key,const stringw& tag) const
	{
		//the find function or irrmap returns a pointer to a map Node
		//if the key can be found, otherwise it returns null
		//the map node has the function getValue and getKey, as we already know the key, we return node->getValue()
		if(tag == paramTag)
		{
			map<stringw, stringw>::Node* n = ParamsMap.find(key);
			if (n)
				return n->getValue();
			else
				return L"";
		}
		else if(tag == imageTag)
		{
			map<stringw, stringw>::Node* n = ImagesMap.find(key);
			if (n)
				return n->getValue();
			else
				return L"";
		}
		else if(tag == meshTag)
		{
			map<stringw, stringw>::Node* n = MeshsMap.find(key);
			if (n)
				return n->getValue();
			else
				return L"";
		}
		else {
			map<stringw, stringw>::Node* n = OthersMap.find(key);
			if (n)
				return n->getValue();
			else
				return L"";
		}

	}

	dimension2d<s32> SettingManager::getDimension2dSetting( const stringw key )
	{
       map<stringw,dimension2d<s32>>::Node* n = ResolutionOptions.find(key);
	   if(n)
		   return n->getValue();
	   else return dimension2d<s32>(0,0);
	}

	void SettingManager::setDimension2dSetting( const stringw key,dimension2d<s32> d2d)
	{
		ResolutionOptions[key] = d2d;
	}
