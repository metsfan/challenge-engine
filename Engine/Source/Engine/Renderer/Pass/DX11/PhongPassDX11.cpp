#include <Engine/Core/Globals.h>
#include "PhongPassDX11.h"
#include <Engine/Renderer/Shader/DX11/ShaderProgramDX11.h>
#include <Engine/Renderer/Attribute/ShadingAttribute.h>

namespace challenge
{
	PhongPass<RendererTypeDX11>::PhongPass() :
		Pass()
	{
		this->SetShaderProgram("phong");
	}

	PhongPass<RendererTypeDX11>::~PhongPass()
	{
	}

	void PhongPass<RendererTypeDX11>::Apply(IGraphicsDevice *device, RenderState &state)
	{
		/*IGraphicsContext *context = device->GetContext();
		ShaderProgramDX11 *shaderProgram = dynamic_cast<ShaderProgramDX11 *>(context->GetShaderProgram(this->GetShaderProgram()));
		if(shaderProgram) {
			shaderProgram->Use();
			const PointLightSourceAttribute *lightAttribute = state.GetAttribute<PointLightSourceAttribute>("light");
			LightCBuffer lightData;
			memset(&lightData, 0, sizeof(LightCBuffer));
			if(lightAttribute) {
				const glm::vec3& position = lightAttribute->GetPosition();
				lightData.lightSources[0].position[0] = position.x;
				lightData.lightSources[0].position[1] = position.y;
				lightData.lightSources[0].position[2] = position.z;
				lightData.lightSources[0].intensity = lightAttribute->GetIntensity();
			}

			const ShadingAttribute *shadingAttribute = state.GetAttribute<ShadingAttribute>("shading");
			if(shadingAttribute) {
				const glm::vec4& diffuse = shadingAttribute->GetDiffuseColor();
				const glm::vec4& specular = shadingAttribute->GetSpecularColor();
				const glm::vec4& ambient = shadingAttribute->GetAmbientColor();

				lightData.shadingParams.diffuse[0] = diffuse.r;
				lightData.shadingParams.diffuse[1] = diffuse.g;
				lightData.shadingParams.diffuse[2] = diffuse.b;
				lightData.shadingParams.diffuse[3] = diffuse.a;

				lightData.shadingParams.specular[0] = specular.r;
				lightData.shadingParams.specular[1] = specular.g;
				lightData.shadingParams.specular[2] = specular.b;
				lightData.shadingParams.specular[3] = specular.a;

				lightData.shadingParams.ambient[0] = ambient.r;
				lightData.shadingParams.ambient[1] = ambient.g;
				lightData.shadingParams.ambient[2] = ambient.b;
				lightData.shadingParams.ambient[3] = ambient.a;

				lightData.shadingParams.shininess = shadingAttribute->GetShininess();
			}

			shaderProgram->SetConstantBuffer((void *)&lightData, sizeof(LightCBuffer), 0, ShaderTypePixelShader);

			PhongMatricesCBuffer matrices;
			memset(&matrices, 0, sizeof(PhongMatricesCBuffer));

			const TransformAttribute *transformAttribute = state.GetAttribute<TransformAttribute>("transform");
			const TransformAttribute *projectionAttribute = state.GetAttribute<TransformAttribute>("projection");
			if(transformAttribute && projectionAttribute) {
				const glm::mat4 &transform = transformAttribute->GetTransformMatrix();
				const glm::mat4 &projection = projectionAttribute->GetTransformMatrix();

				glm::mat4 wvp = transform * projection;
				for(int i = 0; i < 4; i++) {
					for(int j = 0; j < 4; j++) {
						matrices.gWVPMatrix[i][j] = wvp[i][j];
						matrices.gWorldMatrix[i][j] = transform[i][j];
					}
				}

				glm::mat3 normalMatrix = glm::mat3(
					transform[0].x, transform[0].y, transform[0].z,
					transform[1].x, transform[1].y, transform[1].z,
					transform[2].x, transform[2].y, transform[2].z
				);
	
				normalMatrix = glm::inverse(normalMatrix);

				for(int i = 0; i < 3; i++) {
					for(int j = 0; j < 3; j++) {
						matrices.gNormalMatrix[i][j] = normalMatrix[i][j];
					}
				}

					
			}  
			shaderProgram->SetConstantBuffer((void *)&matrices, sizeof(PhongMatricesCBuffer), 0, ShaderTypeVertexShader);
		}*/
		
	}
};