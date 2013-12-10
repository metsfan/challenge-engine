#include <Challenge/Challenge.h>
#include <Challenge/Math/AxisAlignedBox.h>

namespace challenge
{
	AxisAlignedBox AxisAlignedBox::CreateFromPoints(const std::vector<glm::vec3> &points)
	{
		AxisAlignedBox outBox(glm::vec3(INFINITY), glm::vec3(-INFINITY));

		for(auto pt : points) {
			outBox.mMin.x = glm::min(pt.x, outBox.mMin.x);
			outBox.mMin.y = glm::min(pt.y, outBox.mMin.y);
			outBox.mMin.z = glm::min(pt.z, outBox.mMin.z);

			outBox.mMax.x = glm::max(pt.x, outBox.mMax.x);
			outBox.mMax.y = glm::max(pt.y, outBox.mMax.y);
			outBox.mMax.z = glm::max(pt.z, outBox.mMax.z);
		}

		return outBox;
	}
};


