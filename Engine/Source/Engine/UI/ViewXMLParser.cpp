#include <Engine/Challenge.h>
#include <Engine/UI/ViewXMLParser.h>
#include <Engine/UI/UI.h>
#include <Engine/Util/StringUtil.h>

namespace challenge
{
	View * ViewXMLParser::Parse(File *file)
	{
		if(file && file->ReadData()) {
			XMLDocument doc(file);
			XMLNode &rootNode = doc.GetRootNode();

			return ParseView(rootNode);
		}
		return NULL;
	}

	Frame ViewXMLParser::ParseFrame(const std::string &frameStr)
	{
		auto tokens = StringUtil::SplitString(frameStr, ',');
		
		Frame frame;
		if(tokens.size() == 4) {
			frame.origin.x = atoi(tokens[0].c_str());
			frame.origin.y = atoi(tokens[1].c_str());
			frame.size.width = atoi(tokens[2].c_str());
			frame.size.height = atoi(tokens[3].c_str());
		}

		return frame;
	}

	Rect ViewXMLParser::ParseRect(const std::string &rectStr)
	{
		auto tokens = StringUtil::SplitString(rectStr, ',');
		
		Rect rect;
		if(tokens.size() == 4) {
			rect.left = atoi(tokens[0].c_str());
			rect.bottom = atoi(tokens[1].c_str());
			rect.right = atoi(tokens[2].c_str());
			rect.top = atoi(tokens[3].c_str());
		}

		return rect;
	}

	View * ViewXMLParser::ParseView(XMLNode &node)
	{
		const std::string &name = node.GetName();
		View *view = CreateViewForName(name);
		if(view) {
			view->ParseFromXML(node);
		
			TXMLNodeList &children = node.GetChildren();
			for(XMLNode &childNode : children) {
				View *child = ParseView(childNode);
				if(child) {
					view->AddSubview(child);
				}
			}
		}

		return view;
	}

	View * ViewXMLParser::CreateViewForName(const std::string &name)
	{
		auto it = View::sViewCreatorRegistry.find(name);
		if(it != View::sViewCreatorRegistry.end()) {
			return it->second(Frame());
		}

		return NULL;
	}
};