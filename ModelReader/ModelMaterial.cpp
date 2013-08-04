#include "Globals.h"
#include "ModelMaterial.h"
#include <boost/algorithm/string.hpp>

namespace model
{
	ModelMaterial::ModelMaterial(aiMaterial *material) :
		mMaterial(material)
	{
		//aiString texFileName;
		//RendererType renderer = GameApplication::GetInstance()->GetRendererType();
		/*for(int j = aiTextureType_NONE; j <= aiTextureType_UNKNOWN; j++) {
			aiTextureType nType = static_cast<aiTextureType>(j);
			int count = baseMaterial->GetTextureCount(nType);
			if(count > 0) {
				baseMaterial->GetTexture(nType, 0, &texFileName);
				std::string texFilePath = basePath + std::string(texFileName.data);

				CImage *image = new CImage(texFilePath, true);

				//Texture *texture;
				/*if(renderer == RendererTypeDX11) {
					texture = new TextureDX11();
				}

				if(texture) {
					if(texture->Initialize(image->GetBits(), image->GetWidth(), image->GetHeight())) {
						mTextures[nType] = texture;
					} else {
						//delete texture;
						mTextures[nType] = NULL;
					}
				}
				//delete image;
			} else {
				mTextures[nType] = NULL;
			}
		}*/
	}

	ModelMaterial::~ModelMaterial()
	{
	}

	void ModelMaterial::Serialize(std::ostream &out)
	{
		for(int i = aiTextureType_NONE; i <= AI_TEXTURE_TYPE_MAX; i++) {
			aiTextureType nType = static_cast<aiTextureType>(i);
			int count = mMaterial->GetTextureCount(nType);

			// Write material type and count
			out.write((char *)&count, sizeof(int));

			for(int j = 0; j < count; j++) {
				aiString path;
				mMaterial->GetTexture(nType, j, &path);
				std::string pathStr(path.data);
				int pos = pathStr.rfind("/");
				std::string basename = pathStr.substr(pos+1);
				boost::to_lower(basename);
				// Write path
				int size = basename.size();
				out.write((char *)&size, sizeof(int));
				out.write((char *)&basename[0], size);
			}
		}
	}
};
