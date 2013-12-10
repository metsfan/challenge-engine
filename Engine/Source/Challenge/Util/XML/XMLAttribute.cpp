#include <Challenge/Challenge.h>
#include <Challenge/Util/XML/XMLAttribute.h>

namespace challenge
{
	XMLAttribute::XMLAttribute()
	{
	}

	XMLAttribute::XMLAttribute(const std::string &name, std::string &value) :
		mName(name),
		mValue(value)
	{
	}

	XMLAttribute::~XMLAttribute()
	{
	}
};