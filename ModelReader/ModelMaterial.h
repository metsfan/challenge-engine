#pragma once

#include "Globals.h"
#include <aiScene.h>

namespace model
{
	class ModelMaterial
	{
	public:
		ModelMaterial(aiMaterial *material);
		~ModelMaterial();

		void Serialize(std::ostream &out);

	private:
		aiMaterial *mMaterial;
	};
};