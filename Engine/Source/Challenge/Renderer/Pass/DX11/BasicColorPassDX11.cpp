#include <Challenge/Core/Globals.h>
#include "BasicColorPassDX11.h"
#include <Challenge/Renderer/Shader/DX11/ShaderProgramDX11.h>
#include <Challenge/Renderer/Attribute/ColorAttribute.h>

namespace challenge
{
	BasicColorPass<RendererTypeDX11>::BasicColorPass() :
		Pass()
	{
		this->SetShaderProgram("model_anim");
	}

	BasicColorPass<RendererTypeDX11>::~BasicColorPass()
	{
	}

	void BasicColorPass<RendererTypeDX11>::Apply(IGraphicsDevice *device, RenderState &state)
	{
		/*IGraphicsContext *context = device->GetContext();
		ShaderProgramDX11 *shaderProgram = dynamic_cast<ShaderProgramDX11 *>(context->GetShaderProgram(this->GetShaderProgram()));
		if(shaderProgram) {
			shaderProgram->Use();
			const ColorAttribute *colorAttribute = state.GetAttribute<ColorAttribute>("color");
			if(colorAttribute) {
				const glm::vec4 &color = colorAttribute->GetColor();
				shaderProgram->SetConstantBuffer((void *)&color[0], sizeof(float) * 4, 0, ShaderTypePixelShader);
			}

			const TransformAttribute *transformAttribute = state.GetAttribute<TransformAttribute>("transform");
			const TransformAttribute *projectionAttribute = state.GetAttribute<TransformAttribute>("projection");
			if(transformAttribute && projectionAttribute) {
				const glm::mat4 &transform = transformAttribute->GetTransformMatrix();
				const glm::mat4 &projection = projectionAttribute->GetTransformMatrix();
				glm::mat4 mvp = transform * projection;
				shaderProgram->SetConstantBuffer((void *)&mvp[0][0], sizeof(float) * 16, 0, ShaderTypeVertexShader);
			}
		}*/
	}
};