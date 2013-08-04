#pragma once

#include <Engine/Challenge.h>
#include <Engine/Renderer/Technique.h>
#include <Engine/Renderer/Attribute.h>
#include <Engine/Renderer/GraphicsDevice.h>

namespace challenge
{
	typedef std::vector<ITechnique *> TTechniqueList;

	class MaterialProperties
	{
	public:
		MaterialProperties()
		{
		};

		virtual ~MaterialProperties()
		{
		}
	};

	class Material
	{
	public:
		Material(IGraphicsDevice *device, MaterialProperties *properties);
		virtual ~Material();

		ITechnique* GetTechnique(int index) { return mTechniques[index]; }

		MaterialProperties* GetProperties() { return mProperties; }

	protected:
		void AddTechnique(ITechnique *technique) { mTechniques.push_back(technique); }

	private:
		TTechniqueList mTechniques;
		IGraphicsDevice *mDevice;
		MaterialProperties *mProperties;
	};
};