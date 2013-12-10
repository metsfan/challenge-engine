#pragma once

#include <Challenge/Core/Globals.h>
#include <Challenge/Renderer/Pass.h>

namespace challenge
{
	template <typename Renderer>
	class PhongPass : public Pass {};
};

#include <Challenge/Renderer/Pass/DX11/PhongPassDX11.h>
