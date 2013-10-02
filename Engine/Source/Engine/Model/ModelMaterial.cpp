#include <Engine/Challenge.h>
#include <Engine/GameApplication.h>
#include <Engine/Renderer/Texture/Texture2DDX11.h>
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

	void ModelMaterial::Unserialize(std::istream &in, const std::string &basePath)
	{
		for(int i = MaterialTextureNone; i <= kMaterialTextureMax; i++) {
			MaterialTextureType nType = static_cast<MaterialTextureType>(i);
			
			// Read material count for this type
			int count;
			in.read((char *)&count, sizeof(int));

			for(int j = 0; j < count; j++) {
				// Read filename
				int filenameLength;
				in.read((char *)&filenameLength, sizeof(int));

				std::string filename;
				filename.resize(filenameLength);
				in.read(&filename[0], filenameLength);

				std::string texFilePath = basePath + filename;
				mMaterialImages[nType].push_back(new Image(texFilePath));
			}
		}
	}
};

