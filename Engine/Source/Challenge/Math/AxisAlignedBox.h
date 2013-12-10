#pragma once

#include <Challenge/Challenge.h>

namespace challenge
{
	class AxisAlignedBox
	{
	public:
		AxisAlignedBox()
		{
		}

		AxisAlignedBox(const glm::vec3 &min, const glm::vec3 &max) :
			mMin(min),
			mMax(max)
		{
		}

		~AxisAlignedBox()
		{
		}

		void SetMin(const glm::vec3 &min) { mMin = min; }
		void SetMax(const glm::vec3 &max) { mMin = max; }

		bool Intersects(const AxisAlignedBox &other)
		{
			return !(mMin.x > other.mMax.x ||
				mMin.y > other.mMax.y ||
				mMin.z > other.mMax.z ||
				mMax.x < other.mMin.x ||
				mMax.y < other.mMin.y ||
				mMax.z < other.mMin.z);
		}

		static AxisAlignedBox CreateFromPoints(const std::vector<glm::vec3> &points);

	private:
		glm::vec3 mMin;
		glm::vec3 mMax;
	};
};