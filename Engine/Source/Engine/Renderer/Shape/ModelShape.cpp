#include <Engine/Challenge.h>
#include "ModelShape.h"
#include <Engine/Model/ModelResource.h>
#include <Engine/Model/ModelMesh.h>
#include <Engine/Model/ModelBone.h>
#include <Engine/Renderer/Effect.h>

namespace challenge
{
	ModelShape::ModelShape(IGraphicsDevice *device, ModelResource *model) :
		Shape(device, "model"),
		mModel(model),
		mCurrentAnimFrame(0),
		mMaterialId(0)
	{
		const TMeshList &meshes = model->GetMeshes();
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
	
			TEXTURE_DESC desc;
			ITexture *texture = device->CreateTexture2D(desc);

			if(image) {
				const TByteArray &bits = image->GetBits();
				texture->Initialize(&bits[0], Size(image->GetWidth(), image->GetHeight()));
			} else {
				Logger::log(LogDebug, "Image not found");
			}

			mTextures.push_back(texture);
		}
	}

	void ModelShape::Draw(IGraphicsDevice *device, RenderState &state)
	{
		IGraphicsContext *context = device->GetContext();
		const TMeshList &meshes = mModel->GetMeshes();

		glm::mat4 &wvp = state.GetWorldViewProjection();
		ShaderDataMatrix4 wvpData(&wvp, 1);
		state.SetShaderData("WORLDVIEWPROJ_MATRIX", &wvpData);

		glm::mat4 &transform = state.GetTransform();
		ShaderDataMatrix4 transformData(&transform, 1);
		state.SetShaderData("WORLD_MATRIX", &transformData);

		Effect *effect = context->GetEffect("Model");
		ShaderDataMatrix4 boneData;

		if(mModel->IsAnimated() && false) {
			const std::vector<glm::mat4> &boneMatrices = mModel->GetBonesForKeyframe(mCurrentAnimFrame);
			boneData.SetData(&boneMatrices[0], boneMatrices.size());
			state.SetShaderData("BONE_MATRICES", &boneData);
			effect->SetActiveTechnique("BoneAnimation");
		} else {
			state.SetShaderData("BONE_MATRICES", NULL);
			effect->SetActiveTechnique("Static");
		}

		for(int i = 0; i < meshes.size(); i++) {
			ModelMesh *mesh = meshes[i];

			if(mTextures[mesh->GetMaterial()]->IsLoaded()) {
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
	}

	ModelShape::~ModelShape()
	{
	}
};