#include <Challenge/Challenge.h>
#include "Material.h"

namespace challenge
{
	Material::Material(IGraphicsDevice *device, MaterialProperties *properties) :
		mDevice(device),
		mProperties(properties)
	{
	}

	Material::~Material()
	{
	}
};