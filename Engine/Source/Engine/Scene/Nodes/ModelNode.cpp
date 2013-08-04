#include <Engine/Challenge.h>
#include <Engine/Scene/Scene.h>
#include <Engine/Model/ModelMesh.h>
#include <Engine/Renderer/VertexBuffer/VertexBufferDX11.h>
#include <Engine/Renderer/Texture/Texture2DDX11.h>
#include <Engine/GameApplication.h>
#include "ModelNode.h"
using namespace challenge;

bool ModelNode::s_UniformsSet = false;

ModelNode::ModelNode(Model *model,
				  ActorId actorId,
				  std::string name,
				  RenderPass renderPass,
				  glm::mat4 *toWorld,
				  glm::mat4 *fromWorld) : SceneNode(actorId, name, renderPass, toWorld, fromWorld)
{
	mModel = model;
	vboSet = false;
	//mShader = new HLSLProgram();
	
	//mShader->AddShader("ModelBasicVertex", HLSLShaderTypeVertex);
	//mShader->AddShader("ModelBasicPixel", HLSLShaderTypePixel);
	//mShader->SetInputLayout(modelVertexDesc, 3);
	mVertexBuffer = NULL;
}

ModelNode::~ModelNode()
{
	
}

bool ModelNode::PreRender(Scene *pScene)
{
	SceneNode::PreRender(pScene);
	if(mModel->UpdateNextRender()) {
		vboSet = false;
	}

	return true;
}

void ModelNode::Render(Scene *pScene)
{
	//mShader->UseProgram();
	SetBufferData();

	glm::mat4 viewMatrix = pScene->GetCamera()->GetViewMatrix();
	glm::mat4 projectionMatrix = pScene->GetCamera()->GetProjectionMatrix();

	// TODO - Fix this hack
	//glm::mat4 modelTransform = glm::rotate(glm::mat4(1.0f),-90.0f, glm::vec3(1.0f, 0.0, 0.0f));
	glm::mat4 modelTransform = glm::rotate(glm::mat4(1.0f), 180.0f, glm::vec3(0.0f, 1.0, 0.0f));


	glm::mat4 modelViewMatrix = viewMatrix * mProps.ToWorld() * modelTransform;
	modelViewMatrix = glm::transpose(modelViewMatrix);

	glm::mat3 normalMatrix = glm::mat3(
		modelViewMatrix[0].x, modelViewMatrix[0].y, modelViewMatrix[0].z,
		modelViewMatrix[1].x, modelViewMatrix[1].y, modelViewMatrix[1].z,
		modelViewMatrix[2].x, modelViewMatrix[2].y, modelViewMatrix[2].z
	);
	
	mNormalMatrix = glm::transpose(glm::inverse(normalMatrix));
	
	glm::mat4 mvp = modelViewMatrix * projectionMatrix;

	/*Renderer *renderer = GameApplication::GetInstance()->GetWindow()->GetRenderer();

	RendererType type = renderer->GetType();
	if(type == RendererTypeDX11) {
		ModelCBMatrices matrices;
		matrices.gWVPMatrix = mvp;
		matrices.gNormalMatrix = normalMatrix;

		mShader->SetConstantBuffer(&matrices, sizeof(ModelCBMatrices), 0, HLSLShaderTypeVertex);

		TextureDX11 *texture = static_cast<TextureDX11 *>(mModel->GetTexture());
		if(texture != NULL) {
			ID3D11ShaderResourceView *resource = texture->GetTextureResource();
			mShader->SetResource(resource, 0, 1, HLSLShaderTypePixel);
		}
	}

	renderer->Draw(PrimitiveTypeTriangleList, 0, mModel->GetFaceCount());*/
}

void ModelNode::SetBufferData()
{
	if(!vboSet) {
		TMeshList meshes = mModel->GetMeshes();
		TMeshList::iterator it = meshes.begin();

		int nPoints = mModel->GetVertexCount();
		int size = nPoints * sizeof(ModelVertex);                                                                                                                                                           		
		ModelVertex *meshBuffer = new ModelVertex[nPoints];

		int n = 0;
		int i = 0;
		while (it != meshes.end()) {
			ModelMesh *mesh = (*it);
			int nVerts = mesh->GetTotalFaces();
			int meshSize = nVerts * sizeof(ModelVertex);

			memcpy(&meshBuffer[n], mesh->GetBuffer(), meshSize);

			n += nVerts;
			++it;
		};

		if(mVertexBuffer == NULL) {
			mVertexBuffer = GameApplication::GetInstance()->CreateVertexBuffer(meshBuffer, size);
		} else {
			mVertexBuffer->UpdateData(meshBuffer, size, 0);
		}

		vboSet = true;

		delete meshBuffer;
	}

	mVertexBuffer->Activate();
}