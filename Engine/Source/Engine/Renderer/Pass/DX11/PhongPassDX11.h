#pragma once

#include <Engine/Challenge.h>
#include <Engine/Renderer/Pass/PhongPass.h>

namespace challenge
{
	static const int kMaxLights = 1;

	struct ShadingParams
	{
		float diffuse[4];
		float specular[4];
		float ambient[4];
		float shininess; 
	};

	struct LightSourceParams
	{
		float intensity; 
		float direction[3];
		float position[4];
	};

	__declspec(align(16))
	struct LightCBuffer
	{
		LightSourceParams lightSources[kMaxLights];
		ShadingParams shadingParams;
		int numLights;
	};

	__declspec(align(16))
	struct PhongMatricesCBuffer
	{
		float gWVPMatrix[4][4];
		float gWorldMatrix[4][4];
		float gNormalMatrix[3][3];
	};

	template<>
	class PhongPass<RendererTypeDX11> : public Pass
	{
	public:
		PhongPass();
		~PhongPass();

		void Apply(IGraphicsDevice *device, RenderState &state);
	};
};