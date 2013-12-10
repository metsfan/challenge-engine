#pragma once

#include <Challenge/Challenge.h>
#include <Challenge/Renderer/Texture.h>
#include <Challenge/Util/Image.h>

namespace challenge
{
	enum MaterialTextureType
	{
		MaterialTextureNone,
		MaterialTextureDiffuse,
		MaterialTextureSpecular,
		MaterialTextureAmbient,
		MaterialTextureEmissive,
		MaterialTextureHeightMap,
		MaterialTextureNormalMap,
		MaterialTextureShininess,
		MaterialTextureOpacity,
		MaterialTextureDisplacement,
		MaterialTextureLightMap,
		MaterialTextureReflection,
		MaterialTextureUnknown
	};

	static const int kMaterialTextureMax = MaterialTextureUnknown;
	static const int kNumMaterialTextureTypes = 13;

	class Image;

	//typedef std::map<aiTextureType, Texture*> TTextureMap;
	class ModelMaterial
	{
	public:
		ModelMaterial();
		~ModelMaterial();

		void Unserialize(std::istream &in, const std::string &basePath);

		Image* GetImage(MaterialTextureType type, int index) const 
		{ 
			const std::vector<Image *> &images = mMaterialImages[type];
			if(images.size() > index) {
				return images[index];
			}

			return NULL;
		}

	private:
		std::vector<std::vector<Image *> > mMaterialImages;
	};
};