#pragma once

#include <Engine/Challenge.h>
#include <Engine/Renderer/Pass.h>

namespace challenge
{
	template <typename Renderer>
	class BasicColorPass : public Pass {};
};

#include <Engine/Renderer/Pass/DX11/BasicColorPassDX11.h>