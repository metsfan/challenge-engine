#pragma once

#include <Challenge/Challenge.h>
#include <Challenge/Renderer/Pass.h>
#include <Challenge/Renderer/Material.h>
#include <Challenge/Renderer/Attribute/TextureAttribute.h>
#include <Challenge/Renderer/Attribute/BoneAnimationAttribute.h>
#include <Challenge/Renderer/Attribute/ShadingAttribute.h>

namespace challenge
{
	template <typename Renderer>
	class ModelAnimationPass : public Pass {};

	typedef TextureAttribute<BoneAnimationAttribute<ShadingAttribute<MaterialProperties>>> ModelAnimationMaterialProperties;
};



#include <Challenge/Renderer/Pass/DX11/ModelAnimationPassDX11.h>
