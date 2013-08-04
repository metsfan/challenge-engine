#include <Engine/Challenge.h>
#include "PrimitiveGenerator.h"
#include <Engine/GameApplication.h>

namespace challenge
{
	PrimitiveGenerator::PrimitiveGenerator(GameApplication *app) :
		mApp(app)
	{
		for(int i = 0; i < kNumShapes; i++) {
			std::string filepath = kPrimitiveBasePath + filenames[i];
			app->CreateModel(filepath);
		}
	}

	PrimitiveGenerator::~PrimitiveGenerator()
	{
	}

	Model* PrimitiveGenerator::CreatePrimitive(PrimitiveShape type)
	{
		std::string filepath = kPrimitiveBasePath + filenames[type];
		return mApp->CreateModel(filepath);
	}
};