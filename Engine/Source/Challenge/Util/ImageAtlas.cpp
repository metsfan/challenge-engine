#include <Challenge/Challenge.h>
#include <Challenge/Util/ImageAtlas.h>

#include <Challenge/Util/XML/XML.h>

namespace challenge
{
	ImageAtlas::ImageAtlas(const std::string &name, float texelOffset) :
		mTexelOffset(texelOffset),
		mSizeOffset(0)
	{
		Asset file(name);
		if(file.ReadData()) {
			XMLDocument doc(file.GetData());

			XMLNode &rootNode = doc.GetRootNode();

			std::string filename = rootNode.GetAttributeString("filename");
			mImage = std::shared_ptr<Image>(new Image(filename));
			mSize.width = rootNode.GetAttributeFloat("width");
			mSize.height = rootNode.GetAttributeFloat("height");

			if (mImage) {
				auto &imageNodes = rootNode.GetChildrenByName("Image");
				for (auto &imageNode : imageNodes) {
					std::string name = imageNode.GetAttributeString("name");
					float x = imageNode.GetAttributeFloat("x_coord");
					float y = imageNode.GetAttributeFloat("y_coord");
					float width = imageNode.GetAttributeFloat("width");
					float height = imageNode.GetAttributeFloat("height");

					this->AddImage(name, Frame(x, y, width, height));
				}
			}
		}
	}

	ImageAtlas::ImageAtlas(const Size &size) :
		mSize(size),
		mTexelOffset(0),
		mSizeOffset(0)
	{
	}

	ImageAtlas::ImageAtlas() :
		mTexelOffset(0),
		mSizeOffset(0)
	{
	}

	ImageAtlas::~ImageAtlas()
	{
	}
};