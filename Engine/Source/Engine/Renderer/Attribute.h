#pragma once

#include <Engine/Challenge.h>

namespace challenge
{
	template <typename T>
	class Attribute : public T
	{
	public:
		Attribute(std::string name) :
			mName(name) {}

		virtual ~Attribute() {}

		const std::string& GetName() const { return mName; }

	private:
		std::string mName;
	};
};