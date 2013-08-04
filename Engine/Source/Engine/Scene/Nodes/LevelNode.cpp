#include <Engine/Challenge.h>
#include <Engine/Scene/Scene.h>
#include <Engine/Model/ModelMesh.h>
#include <Engine/Renderer/VertexBuffer/VertexBufferDX11.h>
#include <Engine/Renderer/Texture/Texture2DDX11.h>
#include <Engine/GameApplication.h>
#include "LevelNode.h"
using namespace challenge;

LevelNode::LevelNode(Model *model,
				  ActorId actorId,
				  std::string name,
				  RenderPass renderPass,
				  glm::mat4 *toWorld,
				  glm::mat4 *fromWorld) :
				 ModelNode(model, actorId, name, renderPass, toWorld, fromWorld)
{
	int nMeshes = model->GetMeshes().size();
	mBuffers = new IVertexBuffer*[nMeshes];
	vboSet = new bool[nMeshes];
	for(int i = 0; i < nMeshes; i++) {
		vboSet[i] = false;
		mBuffers[i] = NULL;
	}


}

LevelNode::~LevelNode()
{
}


void LevelNode::Render(Scene *pScene)
{
	//mShader->UseProgram();

	glm::mat4 viewMatrix = pScene->GetCamera()->GetViewMatrix();
	glm::mat4 projectionMatrix = pScene->GetCamera()->GetProjectionMatrix();

 	glm::mat4 modelViewMatrix = viewMatrix * mProps.ToWorld();
	modelViewMatrix = glm::transpose(modelViewMatrix);

	glm::mat3 normalMatrix = glm::mat3(
		modelViewMatrix[0].x, modelViewMatrix[0].y, modelViewMatrix[0].z,
		modelViewMatrix[1].x, modelViewMatrix[1].y, modelViewMatrix[1].z,
		modelViewMatrix[2].x, modelViewMatrix[2].y, modelViewMatrix[2].z
	);
	
	mNormalMatrix = glm::transpose(glm::inverse(normalMatrix));

	glm::mat4 mvp = modelViewMatrix * projectionMatrix;
	//mvp *= -1.0f;

	TMeshList meshes = mModel->GetMeshes();
	TMeshList::iterator it = mModel->GetMeshes().begin();

	/*Renderer *renderer = GameApplication::GetInstance()->GetWindow()->GetRenderer();
	RendererType type = renderer->GetType();
	if(type == RendererTypeDX11) {
		ModelCBMatrices matrices;
		matrices.gWVPMatrix = mvp;
		matrices.gNormalMatrix = normalMatrix;
		mShader->SetConstantBuffer(&matrices, sizeof(ModelCBMatrices), 0, HLSLShaderTypeVertex);
	}

	
	for(int i = 0; i < meshes.size(); i++) {
		ModelMesh *nMesh = meshes[i];
		if(this->SetMeshTexture(nMesh)) {
			this->SetMeshBufferData(nMesh, i);
			renderer->Draw(PrimitiveTypeTriangleList, 0, nMesh->GetTotalFaces());
		}
	}*/
}

void LevelNode::SetMeshBufferData(ModelMesh *mesh, int index)
{
	/*int size = mesh->GetTotalFaces() * 3 * sizeof(float);
	mShader->setAttribData("VertexPosition", mesh->GetVertices(),  size, drawMode);
	mShader->setAttribData("VertexNormal", mesh->GetNormals(), size, drawMode);
	mShader->setAttribData("VertexTexCoord", mesh->GetTexels(), size, drawMode);

	int size = mesh->GetTotalFaces() * sizeof(ModelVertex);

	if(!vboSet[index]) {
		if(mBuffers[index] == NULL) {
			mBuffers[index] = new VertexBufferDX11(mesh->GetBuffer(), size, D3D11_USAGE_DEFAULT, sizeof(ModelVertex));
		} else {
			mBuffers[index]->SetData(mesh->GetBuffer(), size);
		}
		vboSet[index] = true;
	}

	mBuffers[index]->Activate();*/
}

bool LevelNode::SetMeshTexture(ModelMesh *mesh)
{
	/*Texture *texture = mesh->GetMaterial()->GetTexture(aiTextureType_DIFFUSE);
	if(texture != NULL) {
		TextureDX11 *textureDX = static_cast<TextureDX11 *>(texture);
		ID3D11ShaderResourceView *resource = textureDX->GetTextureResource();
		//mShader->SetResource(resource, 0, 1, HLSLShaderTypePixel);
		return true;
	}
	return false;*/
	return false;
}