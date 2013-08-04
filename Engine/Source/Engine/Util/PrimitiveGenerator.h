#pragma once

#include <Engine/Challenge.h>
#include <Engine/Model/Model.h>

namespace challenge
{
	class GameApplication;

	enum PrimitiveShape
	{
		PrimitiveShapeBox = 0,
		PrimitiveShapeSphere = 1,
		PrimitiveShapeCylinder = 2,
		PrimitiveShapeCone = 3,
		PrimitiveShapeTorus = 4
	};

	static const int kNumShapes = 5;

	static const std::string filenames[] = {
		"box.model",
		"sphere.model",
		"cylinder.model",
		"cone.model",
		"torus.model"
	};

	static const std::string kPrimitiveBasePath = "C:/gamedev/engine-dev/Engine/Engine/Source/Engine/Assets/Primitives/";

	class PrimitiveGenerator
	{
	public:
		PrimitiveGenerator(GameApplication *app);
		~PrimitiveGenerator();

		Model* CreatePrimitive(PrimitiveShape type);

	private:
		GameApplication *mApp;
	};
};