#pragma once

#include <Challenge/Challenge.h>
#include <Challenge/Renderer/Pass.h>

namespace challenge
{
	template <typename Renderer>
	class BasicColorPass : public Pass {};
};

#include <Challenge/Renderer/Pass/DX11/BasicColorPassDX11.h>
