#pragma once

#include <Challenge/Challenge.h>
#include <Challenge/Renderer/Types.h>
#include <Challenge/Renderer/Technique.h>

namespace challenge
{
	class Effect
	{
	public:
		Effect(std::string name);
		~Effect();

		void AddTechnique(Technique *technique);

		void SetActiveTechnique(std::string name);
		Technique *GetActiveTechnique() { return mActiveTechnique; }

		const std::string& GetName() { return mName; }

	private:
		std::string mName;
		std::unordered_map<std::string, Technique *> mTechniques;
		Technique *mActiveTechnique;
	};
};