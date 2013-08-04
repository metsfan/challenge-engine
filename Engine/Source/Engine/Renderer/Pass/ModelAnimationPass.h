#pragma once

#include <Engine/Challenge.h>
#include <Engine/Renderer/Pass.h>
#include <Engine/Renderer/Material.h>
#include <Engine/Renderer/Attribute/TextureAttribute.h>
#include <Engine/Renderer/Attribute/BoneAnimationAttribute.h>
#include <Engine/Renderer/Attribute/ShadingAttribute.h>

namespace challenge
{
	template <typename Renderer>
	class ModelAnimationPass : public Pass {};

	typedef TextureAttribute<BoneAnimationAttribute<ShadingAttribute<MaterialProperties>>> ModelAnimationMaterialProperties;
};



#include <Engine/Renderer/Pass/DX11/ModelAnimationPassDX11.h>