#include <Engine/Challenge.h>
#include "Ray.h"
#include <Engine/Math/MathUtil.h>

namespace challenge
{
	static const float EPSILON = 0.00001;

	bool Ray::GetIntersection(const Triangle &triangle, float &t) const
	{
		/*glm::vec3 ab = triangle[1] - triangle[0];
		glm::vec3 ac = triangle[2] - triangle[0];
		const glm::vec3 normal = triangle.GetNormal();

		float d = glm::dot(mDirection, normal);
		if(d <= EPSILON) {
			return false;
		}

		glm::vec3 ap = mOrigin - triangle[0];
		t = glm::dot(ap, normal);
		if(t < 0) {
			return false;
		}

		glm::vec3 e = glm::cross(mDirection, ap);
		float v = glm::dot(ac, e);
		if(v < 0) {
			return false;
		}

		float w = glm::dot(ab, e) * -1;
		if(w < 0) {
			return false;
		}

		t /= d;

		return true;*/
		float u, v, w;

        glm::vec3 pa = triangle[0] - mOrigin;
        glm::vec3 pb = triangle[1] - mOrigin;
        glm::vec3 pc = triangle[2] - mOrigin;

		u = MathUtil::ScalarTriple(mDirection, pc, pb);
		if(u < 0) { return false; }
        v = MathUtil::ScalarTriple(mDirection, pa, pc);
		if(v < 0) { return false; }
        w = MathUtil::ScalarTriple(mDirection, pb, pa);
		if(w < 0) { return false; }

        int signU = MathUtil::Sign(u);
        int signV = MathUtil::Sign(v);
        int signW = MathUtil::Sign(w);

        //if (signU == signV && signU == signW)
        {
            float denom = 1.0f / (u + v + w);
            u *= denom;
            v *= denom;
            w *= denom;

            glm::vec3 point = triangle.BarycentricPoint(u, v, w);

            t = glm::distance(point, mOrigin);

			return true;
        }


        return false;
	}
};