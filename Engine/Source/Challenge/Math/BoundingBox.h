#pragma once

#include <Challenge/Challenge.h>

namespace challenge
{
	class BoundingBox
	{
	public:
		BoundingBox() {}
		BoundingBox(glm::vec3 min, glm::vec3 max) : mMin(min), mMax(max) {}
		BoundingBox(real minX, real minY, real minZ, real maxX, real maxY, real maxZ) 
		{
			mMin = glm::vec3(minX, minY, minZ);
			mMax = glm::vec3(maxX, maxY, maxZ);
		}

		real GetWidth() { return mMax.x - mMin.x; }
		real GetHeight() { return mMax.y - mMin.y; }
		real GetDepth() { return mMax.z - mMin.z; }

		glm::vec3 GetDimensions() 
		{ 
			return glm::vec3(this->GetWidth(), this->GetHeight(), this->GetDepth()); 
		}
		
		bool Contains(const BoundingBox &other) const
		{
			return !(mMin.x > other.mMin.x ||
				mMin.y > other.mMin.y ||
				mMin.z > other.mMin.z ||
				mMax.x < other.mMax.x ||
				mMax.y < other.mMax.y ||
				mMax.z < other.mMax.z);
		}

		bool Contains(const glm::vec3 &point) const
		{
			return (point.x >= this->mMin.x && 
					point.x <= this->mMax.x &&
					point.y >= this->mMin.y &&
					point.y <= this->mMax.y &&
					point.z >= this->mMin.z &&
					point.z <= this->mMax.z);
		}

		bool Intersects(const BoundingBox &other) const
		{
			return !(mMin.x > other.mMax.x ||
				mMin.y > other.mMax.y ||
				mMin.z > other.mMax.z ||
				mMax.x < other.mMin.x ||
				mMax.y < other.mMin.y ||
				mMax.z < other.mMin.z);
		}

		BoundingBox Intersection(const BoundingBox &other) const
		{
			BoundingBox inter;
			inter.mMin.x = glm::max(mMin.x, other.mMin.x);
			inter.mMin.y = glm::max(mMin.y, other.mMin.y);
			inter.mMin.z = glm::max(mMin.z, other.mMin.z);
			inter.mMax.x = glm::min(mMax.x, other.mMax.x);
			inter.mMax.y = glm::min(mMax.y, other.mMax.y);
			inter.mMax.z = glm::min(mMax.z, other.mMax.z);

			return inter;
		}

		glm::vec3 GetCenter() const { return (mMax + mMin) * 0.5f; }

		glm::vec3 mMin, mMax;
	};

};