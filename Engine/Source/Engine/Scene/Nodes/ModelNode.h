#pragma once

#include <Engine/Challenge.h>
#include <Engine/Scene/SceneNode.h>
#include <Engine/Model/Model.h>
//#include <Engine/Renderer/Shader/DX11/HLSLProgram.h>
#include <Engine/Renderer/VertexBuffer.h>

namespace challenge
{
	static D3D11_INPUT_ELEMENT_DESC modelVertexDesc[3] = 
	{
		{ "POSITION", 0, DXGI_FORMAT_R32G32B32_FLOAT, 0, 0, D3D11_INPUT_PER_VERTEX_DATA, 0}, 
		{ "NORMAL", 0, DXGI_FORMAT_R32G32B32_FLOAT, 0, 12, D3D11_INPUT_PER_VERTEX_DATA, 0}, 
		{ "TEXCOORD", 0, DXGI_FORMAT_R32G32_FLOAT, 0, 24, D3D11_INPUT_PER_VERTEX_DATA, 0}
	};

	class ModelNode : public SceneNode
	{
	public:
		ModelNode(Model *model,
				  ActorId actorId,
				  std::string name,
				  RenderPass renderPass,
				  glm::mat4 *toWorld,
				  glm::mat4 *fromWorld);
		virtual ~ModelNode();

		virtual bool PreRender(Scene *pScene);
		virtual void Render(Scene *pScene);

		void SetBufferData();

	protected:
		glm::mat3 mNormalMatrix;
		Model *mModel;
		bool mUpdateNextRender;
		//HLSLProgram *mShader;
		IVertexBuffer *mVertexBuffer;

		static bool s_UniformsSet;

	private:
		bool vboSet;
	};
};