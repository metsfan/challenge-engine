#pragma once

#include <Challenge/Challenge.h>
#include <Challenge/Renderer/Types.h>
#include <Challenge/Renderer/Shape.h>

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

		void SetColor(const glm::vec4 &color) { mColor = color; }

	private:
		ModelResource *mModel;
		int mCurrentAnimFrame;
		int mMaterialId;
		glm::vec4 mColor;
		std::vector<ITexture *> mTextures;
		std::vector<Material *> mMeshMaterials;
		std::vector<IVertexBuffer *> mMeshVertexBuffers;
	};
};