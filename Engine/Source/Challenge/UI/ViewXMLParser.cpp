#include <Challenge/Challenge.h>
#include <Challenge/UI/ViewXMLParser.h>
#include <Challenge/UI/UI.h>
#include <Challenge/Util/StringUtil.h>

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
		auto tokens = StringUtil::SplitString(frameStr, std::string(","));
		
		Frame frame;
		if(tokens.size() == 4) {
			frame.origin = ParsePoint(tokens[0] + "," + tokens[1]);
			frame.size = ParseSize(tokens[2] + "," + tokens[3]);
		}

		return frame;
	}

	Rect ViewXMLParser::ParseRect(const std::string &rectStr)
	{
		auto tokens = StringUtil::SplitString(rectStr, std::string(","));
		
		Rect rect;
		if(tokens.size() == 4) {
			rect.left = atoi(tokens[0].c_str());
			rect.bottom = atoi(tokens[1].c_str());
			rect.right = atoi(tokens[2].c_str());
			rect.top = atoi(tokens[3].c_str());
		}

		return rect;
	}

	Size ViewXMLParser::ParseSize(const std::string &sizeStr)
	{
		auto tokens = StringUtil::SplitString(sizeStr, std::string(","));

		Size size;
		if (tokens.size() == 2) {
			if (tokens[0] == "match_parent") {
				size.width = MATCH_PARENT;
			}
			else if (tokens[0] == "wrap_content") {
				size.width = WRAP_CONTENT;
			}
			else {
				size.width = atof(tokens[0].c_str());
			}

			if (tokens[1] == "match_parent") {
				size.height = MATCH_PARENT;
			}
			else if (tokens[1] == "wrap_content") {
				size.height = WRAP_CONTENT;
			}
			else {
				size.height = atof(tokens[1].c_str());
			}
		}

		return size;
	}

	Point ViewXMLParser::ParsePoint(const std::string &pointStr)
	{
		auto tokens = StringUtil::SplitString(pointStr, std::string(","));

		Point point;
		if (tokens.size() == 2) {
			point.x = atoi(tokens[0].c_str());
			point.y = atoi(tokens[1].c_str());
		}

		return point;
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

			view->OnXMLParseComplete();
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