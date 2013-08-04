#pragma once

#include <Engine/Challenge.h>
#include <Engine/Renderer/Types.h>
#include <Engine/Renderer/Pass.h>
#include <Engine/Renderer/RenderState.h>
#include <Engine/Renderer/GraphicsDevice.h>

namespace challenge
{
	typedef std::vector<Pass *> TPassList;

	class Technique
	{
	public:
		Technique(std::string name);
		virtual ~Technique();

		void AddPass(Pass *pass) { mPasses.push_back(pass); }

		virtual bool HasNextPass();
		virtual void Begin();
		virtual void ProcessNextPass(IGraphicsDevice *device, RenderState &state);
		const std::string GetName() { return mName; }

	private:
		int mCurrentPass;
		int mNumPasses;
		TPassList mPasses;
		std::string mName;
	};
};