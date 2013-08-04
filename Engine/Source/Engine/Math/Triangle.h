#pragma once

#include <Engine/Challenge.h>

namespace challenge
{
	class Triangle
	{
	public:
		Triangle();
		Triangle(glm::vec3 p1, glm::vec3 p2, glm::vec3 p3);
		~Triangle();

		const glm::vec3& GetPoint(int index) const { return mPoints[index]; }
		const glm::vec3& operator[](int index) const { return mPoints[index]; }
		glm::vec3& operator[](int index) { return mPoints[index]; }

		const glm::vec3 GetNormal() const 
		{
			return glm::normalize(glm::cross(mPoints[1] - mPoints[0], mPoints[2] - mPoints[0])); 
		}

		const glm::vec3 BarycentricPoint(float u, float v, float w) const
		{
			return (mPoints[0] * u) + (mPoints[1] * v) + (mPoints[2] * w);
		}

	private:
		glm::vec3 mPoints[3];
		glm::vec3 mNormal;
	};
};