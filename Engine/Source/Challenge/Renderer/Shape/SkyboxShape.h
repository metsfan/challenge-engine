#pragma once

#include <Challenge/Challenge.h>
#include <Challenge/Renderer/Shape.h>
#include <Challenge/Renderer/Texture.h>
#include <Challenge/Renderer/Material.h>
#include <Challenge/Renderer/Attribute/TextureAttribute.h>
#include <Challenge/Util/Image.h>
#include <Challenge/Model/Model.h>


namespace challenge
{
	struct SkyboxVertex
	{
		float position[3];
		float texCoord[2];
		float faceId;
	};

	class SkyboxMaterialProperties : 
		public MaterialProperties,
		public TextureAttribute
	{
	};

	class SkyboxShape : public Shape
	{
	public:
		SkyboxShape(IGraphicsDevice *device, std::shared_ptr<Image> cubeMap, Model *skyboxModel);
		~SkyboxShape();

		void SetImage(std::shared_ptr<Image> image);

		void Draw(IGraphicsDevice *device, RenderState &state);

	private:
		ITexture *mTexture;
		IVertexBuffer *mVertexBuffer;
		Material *mMaterial;
		Model *mSkyboxModel;
		int mNumVerts;
	};
};