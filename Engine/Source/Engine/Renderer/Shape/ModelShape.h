#pragma once

#include <Engine/Challenge.h>
#include <Engine/Renderer/Types.h>
#include <Engine/Renderer/Shape.h>

namespace challenge
{
	class Model;

	class ModelShape : public Shape
	{
	public:
		ModelShape(IGraphicsDevice *device, Model *model);
		~ModelShape();

		void Draw(IGraphicsDevice *device, RenderState &state);

	private:
		Model *mModel;
		std::vector<ITexture *> mTextures;
		std::vector<Material *> mMeshMaterials;
		std::vector<IVertexBuffer *> mMeshVertexBuffers;
	};
};