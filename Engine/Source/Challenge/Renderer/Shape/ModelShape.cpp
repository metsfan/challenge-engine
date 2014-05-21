#include <Challenge/Challenge.h>
#include "ModelShape.h"
#include <Challenge/Model/ModelResource.h>
#include <Challenge/Model/ModelMesh.h>
#include <Challenge/Model/ModelBone.h>
#include <Challenge/Renderer/Effect.h>

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
			meshBuffer->SetData(mesh->GetBuffer(), sizeof(ModelVertex) * mesh->GetTotalFaces(), sizeof(ModelVertex));

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
				Logger::Log(LogDebug, "Image not found");
			}

			mTextures.push_back(texture);
		}
	}

	void ModelShape::Draw(IGraphicsDevice *device, RenderState &state)
	{
		/*IGraphicsContext *context = device->GetContext();
		const TMeshList &meshes = mModel->GetMeshes();

		glm::mat4 &wvp = state.GetWorldViewProjection();
		ShaderDataMatrix4 wvpData(&wvp, 1);
		state.SetShaderData("WORLDVIEWPROJ_MATRIX", &wvpData);

		glm::mat4 &transform = state.GetTransform();
		ShaderDataMatrix4 transformData(&transform, 1);
		state.SetShaderData("WORLD_MATRIX", &transformData);

		Effect *effect = context->GetEffect("Model");
		ShaderDataMatrix4 boneData;

		if(mModel->IsAnimated()) {
			const std::vector<glm::mat4> &boneMatrices = mModel->GetBonesForKeyframe(mCurrentAnimFrame);
			boneData.SetData(&boneMatrices[0], boneMatrices.size());
			state.SetShaderData("BONE_MATRICES", &boneData);
			effect->SetActiveTechnique("BoneAnimation");
		} else {
			state.SetShaderData("BONE_MATRICES", NULL);
			effect->SetActiveTechnique("Static");
		}

		/*if(mTextures.size() == 0) {
			ShaderDataVector4 colorData(&mColor, 1);
			state.SetShaderData("COLOR", &colorData);
		}*

		for(int i = 0; i < meshes.size(); i++) {
			ModelMesh *mesh = meshes[i];

			ShaderDataTexture diffuseTex;
			ShaderDataVector4 colorData;
			glm::vec4 clearColor(0);

			if(mesh->GetMaterial() >= 0 &&
				mTextures[mesh->GetMaterial()]->IsLoaded()) {
				diffuseTex = ShaderDataTexture(mTextures[mesh->GetMaterial()]);
				state.SetShaderData("DIFFUSE_TEXTURE", &diffuseTex);
				
			} else {
				state.SetShaderData("DIFFUSE_TEXTURE", NULL);
				//ShaderDataVector4 colorData(&mColor, 1);
				//state.SetShaderData("COLOR", NULL);
			}

			colorData = ShaderDataVector4(&mColor, 1);
			state.SetShaderData("COLOR", &colorData);

			Technique *technique = effect->GetActiveTechnique();
			technique->Begin();
			while(technique->HasNextPass()) {
				technique->ProcessNextPass(device, state);
				mMeshVertexBuffers[i]->Activate();
				device->Draw(PrimitiveTypeTriangleList, mesh->GetTotalFaces(), 0);
			}
		}*/
	}

	ModelShape::~ModelShape()
	{
	}
};