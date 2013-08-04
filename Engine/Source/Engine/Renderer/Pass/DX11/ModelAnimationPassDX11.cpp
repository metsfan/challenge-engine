#include <Engine/Core/Globals.h>
#include "ModelAnimationPassDX11.h"
#include <Engine/Renderer/Texture/TextureDX11.h>

namespace challenge
{
	ModelAnimationPass<RendererTypeDX11>::ModelAnimationPass()
	{
		this->SetShaderProgram("model_anim");
		mShader = NULL;
	}

	ModelAnimationPass<RendererTypeDX11>::~ModelAnimationPass()
	{
	}
		
	void ModelAnimationPass<RendererTypeDX11>::Apply(IGraphicsDevice *device, RenderState &state)
	{
		IGraphicsContext *context = device->GetContext();
		if(!mShader) {
			mShader = dynamic_cast<ShaderProgramDX11 *>(context->GetShaderProgram(this->GetShaderProgram()));
		}
		
		if(mShader) {
			context->SetActiveShaderProgram(mShader);

			ModelMatricesCBuffer matrices;
			memset(&matrices, 0, sizeof(ModelMatricesCBuffer));

			glm::mat4 transform = state.GetTransform();
			glm::mat4 &projection = state.GetProjection();
			glm::mat4 &wvp = state.GetWorldViewProjection();

			memcpy(matrices.gWVPMatrix, &wvp[0][0], sizeof(glm::mat4));
			memcpy(matrices.gWorldMatrix, &transform[0][0], sizeof(glm::mat4));

			/*for(int i = 0; i < 4; i++) {
				for(int j = 0; j < 4; j++) {
					matrices.gWVPMatrix[i][j] = wvp[i][j];
					matrices.gWorldMatrix[i][j] = transform[i][j];
				}
			}*/

			/*glm::mat3 normalMatrix = glm::mat3(
				transform[0].x, transform[0].y, transform[0].z,
				transform[1].x, transform[1].y, transform[1].z,
				transform[2].x, transform[2].y, transform[2].z
			);
	
			//normalMatrix = glm::transpose(glm::inverse(normalMatrix));

			for(int i = 0; i < 3; i++) {
				for(int j = 0; j < 3; j++) {
					matrices.gNormalMatrix[i][j] = normalMatrix[i][j];
				}
			}*/
			mShader->SetConstantBuffer((void *)&matrices, sizeof(ModelMatricesCBuffer), 0, ShaderTypeVertexShader);
			
			Material *material = state.GetMaterial();
			ModelAnimationMaterialProperties *materialProperties = dynamic_cast<ModelAnimationMaterialProperties *>(
				material->GetProperties()
			);

			if(materialProperties) {
				Texture<RendererTypeDX11> *dxTexture = dynamic_cast<Texture<RendererTypeDX11> *>(
					materialProperties->GetTexture()
				);

				if(dxTexture) {
					ID3D11ShaderResourceView *resource = dxTexture->GetTextureResource();
					mShader->SetResources(&resource, 0, 1, ShaderTypePixelShader);
				}
				

				int numBones = materialProperties->GetNumBoneMatrices();

				BoneMatricesCBuffer boneMatrices;
				memset(&boneMatrices, 0, sizeof(BoneMatricesCBuffer));

				const glm::mat4 *matrices = materialProperties->GetBoneMatrices();
				memcpy(boneMatrices.gPositionMatrices, &matrices[0][0][0], sizeof(glm::mat4) * kMaxBones);

				mShader->SetConstantBuffer(&boneMatrices, sizeof(BoneMatricesCBuffer), 1, ShaderTypeVertexShader);
			}
		}
	}
};