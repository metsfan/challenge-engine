#pragma once

#include <Engine/Challenge.h>
#include <Engine/Renderer/Types.h>
#include <Engine/Renderer/Shape.h>

namespace challenge
{
	class ModelResource;

	class ModelShape : public Shape
	{
	public:
		ModelShape(IGraphicsDevice *device, ModelResource *model);
		~ModelShape();

		void Draw(IGraphicsDevice *device, RenderState &state);

		void SetCurrentAnimFrame(int frame) { mCurrentAnimFrame = frame; }
		void SetMaterialId(int materialId) { mMaterialId = materialId; }

	private:
		ModelResource *mModel;
		int mCurrentAnimFrame;
		int mMaterialId;
		std::vector<ITexture *> mTextures;
		std::vector<Material *> mMeshMaterials;
		std::vector<IVertexBuffer *> mMeshVertexBuffers;
	};
};