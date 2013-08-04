#include <Engine/Challenge.h>
#include "ModelShape.h"
#include <Engine/Model/Model.h>
#include <Engine/Model/ModelMesh.h>
#include <Engine/Model/ModelBone.h>
#include <Engine/Renderer/Effect.h>

namespace challenge
{
	ModelShape::ModelShape(IGraphicsDevice *device, Model *model) :
		Shape(device, "model"),
		mModel(model)
	{
		TMeshList &meshes = model->GetMeshes();
		for(int i = 0; i < meshes.size(); i++) {
			ModelMesh *mesh = meshes[i];

			VERTEX_BUFFER_DESC desc;
			desc.Stride = sizeof(ModelVertex);
			IVertexBuffer *meshBuffer = device->CreateVertexBuffer(desc);
			meshBuffer->SetData(mesh->GetBuffer(), sizeof(ModelVertex) * mesh->GetTotalFaces());

			mMeshVertexBuffers.push_back(meshBuffer);
		}

		TMaterialList &materials = mModel->GetMaterials();
		for(int i = 0; i < materials.size(); i++) {
			ModelMaterial *material = materials[i];
			Image *image = material->GetImage(MaterialTextureDiffuse, 0);

			if(image) {
				TEXTURE_DESC desc;
				ITexture *texture = device->CreateTexture2D(desc);
				texture->Initialize(image->GetBits(), Size(image->GetWidth(), image->GetHeight()));

				mTextures.push_back(texture);
			}
			
		}
	}

	void ModelShape::Draw(IGraphicsDevice *device, RenderState &state)
	{
		IGraphicsContext *context = device->GetContext();
		int animationFrame = mModel->GetCurrentAnimationFrame();
		TMeshList &meshes = mModel->GetMeshes();

		glm::mat4 &wvp = state.GetWorldViewProjection();
		ShaderDataMatrix4 wvpData(&wvp, 1);
		state.SetShaderData("WORLDVIEWPROJ_MATRIX", &wvpData);

		glm::mat4 &transform = state.GetTransform();
		ShaderDataMatrix4 transformData(&transform, 1);
		state.SetShaderData("WORLD_MATRIX", &transformData);

		const std::vector<glm::mat4> &boneMatrices = mModel->GetBonesForKeyframe(animationFrame);
		ShaderDataMatrix4 boneData(&boneMatrices[0], boneMatrices.size());
		state.SetShaderData("BONE_MATRICES", &boneData);

		Effect *effect = context->GetEffect("Model");
		effect->SetActiveTechnique("BoneAnimation");

		for(int i = 0; i < meshes.size(); i++) {
			ModelMesh *mesh = meshes[i];
			
			ShaderDataTexture diffuseTex(mTextures[mesh->GetMaterial()]);
			state.SetShaderData("DIFFUSE_TEXTURE", &diffuseTex);

			Technique *technique = effect->GetActiveTechnique();
			technique->Begin();
			while(technique->HasNextPass()) {
				technique->ProcessNextPass(device, state);
				mMeshVertexBuffers[i]->Activate();
				device->Draw(PrimitiveTypeTriangleList, mesh->GetTotalFaces(), 0);
			}
		}
	}

	ModelShape::~ModelShape()
	{
	}
};