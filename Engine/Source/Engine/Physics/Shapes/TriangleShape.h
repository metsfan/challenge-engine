#pragma once

#include <Engine/Challenge.h>
#include "PhysicsShape.h"
#include "PlaneShape.h"
#include <Engine/Math/Ray.h>

namespace challenge
{
	class TriangleShape : public PhysicsShape
	{
	public:
		TriangleShape(glm::vec3 a, glm::vec3 b, glm::vec3 c);
		virtual bool Intersects(IPhysicsShape *other, CollisionData *collision = NULL);

		PhysicsShapeType GetType() { return kShapeTypeTriangle; }

		bool RayIntersects(Ray ray, glm::vec3 *outPoint = NULL);
		
		glm::vec3 mPoints[3];
		PlaneShape mNormalPlane;
	};

	typedef std::vector<TriangleShape *> TTriangleList;
};