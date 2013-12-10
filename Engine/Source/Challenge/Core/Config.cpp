#include <Challenge/Challenge.h>
#include "Config.h"
#include <Challenge/Util/XML/XMLDocument.h>

namespace challenge
{
	std::map<std::string, std::string> Config::mConfigValues;

	void Config::LoadFile(const std::string &file)
	{
		Asset configFile(file);
		if(configFile.ReadData()) {
			XMLDocument doc(&configFile);

			TXMLNodeList objects = doc.GetRootNode().GetChildrenByName("object");
			for(XMLNode &node : objects) {
				const std::string key = node.GetChildrenByName("key")[0].GetValue();
				const std::string value = node.GetChildrenByName("value")[0].GetValue();

				mConfigValues[key] = value;
			}
		}
	}
};