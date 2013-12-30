#include <Challenge/Challenge.h>
#include <Challenge/GameApplication.h>
#include <Challenge/Renderer/Texture/Texture2DDX11.h>
#include "ModelMaterial.h"

namespace challenge
{
	ModelMaterial::ModelMaterial() :
		mMaterialImages(kNumMaterialTextureTypes)
	{
	}

	ModelMaterial::~ModelMaterial()
	{
	}

	void ModelMaterial::Unserialize(FileInputStream &in, const std::wstring &basePath)
	{
		for(int i = MaterialTextureNone; i <= kMaterialTextureMax; i++) {
			MaterialTextureType nType = static_cast<MaterialTextureType>(i);
			
			// Read material count for this type
			int count = in.Read<int>();

			for(int j = 0; j < count; j++) {
				// Read filename
				int filenameLength = in.Read<int>();

				std::string filename;
				filename.resize(filenameLength);
				in.Read((char *)&filename[0], filenameLength);

				std::wstring texFilePath = basePath + StringUtil::ToWide(filename);
				Asset texAsset(texFilePath);

				if (texAsset.ReadData()) {
					mMaterialImages[nType].push_back(new Image(&texAsset));
				}
			}
		}
	}
};

