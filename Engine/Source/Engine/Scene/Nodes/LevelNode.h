#pragma once

#include <Engine/Challenge.h>
#include <Engine/Scene/Nodes/ModelNode.h>

namespace challenge
{
	class LevelNode : public ModelNode
	{
	public:
		LevelNode(Model *model,
				  ActorId actorId,
				  std::string name,
				  RenderPass renderPass,
				  glm::mat4 *toWorld,
				  glm::mat4 *fromWorld);
		virtual ~LevelNode();

		virtual void Render(Scene *pScene);

		void SetMeshBufferData(ModelMesh *mesh, int index);
		bool SetMeshTexture(ModelMesh *mesh);

	private:
		IVertexBuffer **mBuffers;
		bool *vboSet;
	};
};