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

		IGraphicsContext *context = device->GetContext();
		mWVPIndex = context->GetGlobalIndex("WORLDVIEWPROJ_MATRIX");
		mWorldIndex = context->GetGlobalIndex("WORLD_MATRIX");
		mBoneMatricesIndex = context->GetGlobalIndex("BONE_MATRICES");
		mDiffuseTextureIndex = context->GetGlobalIndex("DIFFUSE_TEXTURE");
		mColorIndex = context->GetGlobalIndex("COLOR");
	}

	void ModelShape::Draw(IGraphicsDevice *device, RenderState &state)
	{
		IGraphicsContext *context = device->GetContext();
		const TMeshList &meshes = mModel->GetMeshes();

		glm::mat4 &wvp = state.GetWorldViewProjection();
		state.SetShaderData(mWVPIndex, &wvp);

		glm::mat4 &transform = state.GetTransform();
		state.SetShaderData(mWorldIndex, &transform);

		Effect *effect = context->GetEffect("Model");

		if(mModel->IsAnimated()) {
			const std::vector<glm::mat4> &boneMatrices = mModel->GetBonesForKeyframe(mCurrentAnimFrame);
			state.SetShaderData(mBoneMatricesIndex, (void *)&boneMatrices[0], boneMatrices.size());
			effect->SetActiveTechnique("BoneAnimation");
		} else {
			state.SetShaderData(mBoneMatricesIndex, NULL);
			effect->SetActiveTechnique("Static");
		}

		/*if(mTextures.size() == 0) {
			ShaderDataVector4 colorData(&mColor, 1);
			state.SetShaderData("COLOR", &colorData);
		}*/

		for(int i = 0; i < meshes.size(); i++) {
			ModelMesh *mesh = meshes[i];

			glm::vec4 clearColor(0);

			if(mesh->GetMaterial() >= 0 &&
				mTextures[mesh->GetMaterial()]->IsLoaded()) {
				ITexture *diffuseTex = mTextures[mesh->GetMaterial()];
				state.SetShaderData(mDiffuseTextureIndex, diffuseTex);
				
			} else {
				state.SetShaderData(mDiffuseTextureIndex, NULL);
				//ShaderDataVector4 colorData(&mColor, 1);
				//state.SetShaderData("COLOR", NULL);
			}

			state.SetShaderData(mColorIndex, &mColor);

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