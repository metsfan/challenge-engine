#pragma once

#include <Challenge/Challenge.h>
#include <Challenge/Model/Model.h>

namespace challenge
{
	enum PrimitiveShape
	{
		PrimitiveShapeBox = 0,
		PrimitiveShapeSphere = 1,
		PrimitiveShapeCylinder = 2,
		PrimitiveShapeCone = 3,
		PrimitiveShapeTorus = 4
	};

	static const int kNumShapes = 5;

	static const std::wstring filenames[] = {
		L"box.model",
		L"sphere.model",
		L"cylinder.model",
		L"cone.model",
		L"torus.model"
	};

	static const std::wstring kPrimitiveBasePath = L"Models/Primitives/";

	class PrimitiveGenerator
	{
	public:
		static Model* CreatePrimitive(PrimitiveShape type)
		{
			std::wstring filepath = kPrimitiveBasePath + filenames[type];
			return new Model(filepath);
		}
	};
};