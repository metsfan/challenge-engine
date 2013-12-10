#pragma once

#include <Challenge/Challenge.h>
#include <Challenge/Renderer/Types.h>
#include <Challenge/Renderer/Pass.h>
#include <Challenge/Renderer/RenderState.h>
#include <Challenge/Renderer/GraphicsDevice.h>

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