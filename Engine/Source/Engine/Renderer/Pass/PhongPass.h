#pragma once

#include <Engine/Core/Globals.h>
#include <Engine/Renderer/Pass.h>

namespace challenge
{
	template <typename Renderer>
	class PhongPass : public Pass {};
};

#include <Engine/Renderer/Pass/DX11/PhongPassDX11.h>