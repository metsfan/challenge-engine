#pragma once

#include <Engine/Challenge.h>
#include <Engine/Renderer/Shape.h>
#include <Engine/Renderer/Texture.h>
#include <Engine/Renderer/Material.h>
#include <Engine/Renderer/Attribute/TextureAttribute.h>
#include <Engine/Util/Image.h>
#include <Engine/Model/Model.h>


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