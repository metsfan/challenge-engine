#pragma once

#include <Engine/Challenge.h>
#include <Engine/Renderer/Pass/ModelAnimationPass.h>
#include <Engine/Renderer/Shader/DX11/ShaderProgramDX11.h>

namespace challenge
{
	__declspec(align(16))
	struct ModelMatricesCBuffer
	{
		float gWVPMatrix[4][4];
		float gWorldMatrix[4][4];
		float gNormalMatrix[3][3];
	};

	static const int kMaxBones = 64;

	__declspec(align(16))
	struct BoneMatricesCBuffer
	{
		float gPositionMatrices[kMaxBones][4][4];
	}; 

	template<>
	class ModelAnimationPass<RendererTypeDX11> : public Pass
	{
	public:
		ModelAnimationPass();
		~ModelAnimationPass();
		
		void Apply(IGraphicsDevice *device, RenderState &state);

	private:
		ShaderProgramDX11 *mShader;
	};
};