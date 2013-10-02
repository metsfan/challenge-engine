#include <Engine/Challenge.h>
#include "Ray.h"
#include <Engine/Math/MathUtil.h>

namespace challenge
{
	//static const float EPSILON = 0.00001;
	bool Ray::GetIntersection(const BoundingBox &bounds, float &t) const
	{
		real tmin = 0;
		real tmax = INFINITY;

		for(int i = 0; i < 2; i++) {
			if(abs(mDirection[i]) < EPSILON) {
				if(mOrigin[i] < bounds.mMin[i] || mOrigin[i] > bounds.mMax[i]) {
					return false;
				}
			} else {
				real ood = 1.0 / mDirection[i];
				real t1 = (bounds.mMin[i] - mOrigin[i]) * ood;
				real t2 = (bounds.mMax[i] - mOrigin[i]) * ood;

				if(t1 > t2) {
					real tmp = t1;
					t1 = t2;
					t2 = tmp;
				}

				tmin = std::max(tmin, t1);
				tmax = std::min(tmax, t2);

				if(tmin > tmax) {
					return false;
				}
			}
		}

		t = tmin;
		if(t < 0) {
			return false;
		}

		return true;
	}

	bool Ray::GetIntersection(const Triangle &triangle, float &t) const
	{
		float u, v, w;

        glm::vec3 pa = triangle[0] - mOrigin;
        glm::vec3 pb = triangle[1] - mOrigin;
        glm::vec3 pc = triangle[2] - mOrigin;

		glm::vec3 m = glm::cross(mDirection, pc);
		u = glm::dot(pb, m);

		v = -glm::dot(pa, m);
		if(glm::sign(u) != glm::sign(v)) {
			return false;
		}

        w = MathUtil::ScalarTriple(mDirection, pb, pa);
		if(glm::sign(u) != glm::sign(w)) {
			return false;
		}

        float denom = 1.0f / (u + v + w);
        u *= denom;
        v *= denom;
        w *= denom;

        glm::vec3 point = triangle.BarycentricPoint(u, v, w);

		t = glm::dot((point - mOrigin), mDirection);

		if(t >= 0) {
			return true;
		}

        return false;
	}

	bool Ray::GetIntersection(const Plane &plane, float &t) const
	{
		real denom = glm::dot(plane.GetNormal(), mDirection);

		if(!denom) {
			return false;
		}

		real numer = -(glm::dot(plane.GetNormal(), mOrigin) + plane.GetD());

		t = numer / denom;

		if(t >= 0) {
			return true;
		}

		return false;
	}
};