#include <Engine/Challenge.h>
#include <Engine/Physics/Shapes/Intersection.h>
#include "AABBShape.h"
using namespace challenge;

AABBShape::AABBShape(glm::vec3 center, real halfX, real halfY, real halfZ) :
	mCenter(center), mHalfX(halfX), mHalfY(halfY), mHalfZ(halfZ)
{
}

bool AABBShape::Intersects(IPhysicsShape *other, CollisionData *collision)
{
	PhysicsShapeType otherType = other->GetType();
	bool intersects = false;

	if(otherType == kShapeTypeAABB) {
		AABBShape *aabb = static_cast<AABBShape *>(other);
		intersects = IntersectionTests::AABBIntersectsAABB(aabb, this, collision);
	} else if(otherType == kShapeTypePlane) {
		PlaneShape *plane = static_cast<PlaneShape *>(other);
		intersects = IntersectionTests::AABBIntersectsPlane(this, plane, collision);
	}

	return intersects;
}

glm::mat3 AABBShape::CalculateInertiaTensor(float mass)
{
	float a = (1.0f / 12.0f) * mass;

	float dx = mHalfX * 2;
	float dy = mHalfY * 2;
	float dz = mHalfZ * 2;

	float dx2 = dx * dx;
	float dy2 = dy * dy;
	float dz2 = dz * dz;

	float x = a * (dy2 + dz2);
	float y = a * (dx2 + dz2);
	float z = a * (dx2 + dy2);

	return glm::mat3(
		x, 0.0f, 0.0f,
		0.0f, y, 0.0f,
		0.0f, 0.0f, z
		);                                                           
}

BoundingBox AABBShape::GetBoundingBox()
{
	glm::vec3 pos = this->GetPosition();
	return BoundingBox(pos.x - mHalfX, pos.y - mHalfY, pos.z - mHalfZ, pos.x + mHalfX, pos.y + mHalfY, pos.z + mHalfZ);
}

bool AABBShape::RayIntersects(Ray ray, glm::vec3 *outPoint)
{
	real tmin = 0;
	real tmax = kInfinity;

	BoundingBox bbox = GetBoundingBox();
	
	/*for(int i = 0; i < 3; i++) {
		if(abs(ray.direction[i]) < EPSILON) {
			if(ray.origin[i] < bbox.mMin[i] || ray.origin[i] > bbox.mMax[i]) {
				return false;
			}
		} else {
			real ood = 1.0 / ray.direction[i];
			real t1 = (bbox.mMin[i] - ray.origin[i]) * ood;
			real t2 = (bbox.mMax[i] - ray.origin[i]) * ood;

			/*if(t1 > t2) {
				real tmp = t1;
				t1 = t2;
				t2 = tmp;
			}

			tmin = MAX(tmin, t1);
			tmax = MIN(tmax, t2);

			if(tmin > tmax) {
				//return false;
			}
		}
	}

	outPoint[0] = ray.origin + (tmin * ray.direction);*/
	return true;
}

/*bool AABBShape::RayIntersects(Ray ray, glm::vec3 *outPoint)
{
	float t = kInfinity;

	real rx = mHalfX * 2;
	real ry = mHalfY * 2;
	real rz = mHalfZ * 2;

	glm::vec4 x0 = glm::vec4(1, 0, 0, mHalfX);
	glm::vec4 x1 = glm::vec4(1, 0, 0, -mHalfX);
	glm::vec4 y0 = glm::vec4(0, 1, 0, mHalfY);
	glm::vec4 y1 = glm::vec4(0, 1, 0, -mHalfY);
	glm::vec4 z0 = glm::vec4(0, 0, 1, mHalfZ);
	glm::vec4 z1 = glm::vec4(0, 0, 1, -mHalfZ);

	if(abs(ray.direction.x) > EPSILON) {
		if(ray.direction.x > 0) {
			t = (-ray.origin.x) / ray.direction.x;
			glm::vec3 p = ray.ValueAt(t);
			if(0 <= p.y && p.y <= ry && 
				0 <= p.z && p.z <= rz) {
				outPoint[0] = p + mPosition;
				return true;
			}
		} else if(ray.direction.x < 0) {
			t = (rx - ray.origin.x) / ray.direction.x;
			glm::vec3 p = ray.ValueAt(t);
			if(0 <= p.y && p.y <= ry && 
				0 <= p.z && p.z <= rz) {
				outPoint[0] = p + mPosition;
				return true;
			}
		}
	}

	if(abs(ray.direction.y) > EPSILON) {
		if(ray.direction.y > 0) {
			t = (-ray.origin.y) / ray.direction.y;
			glm::vec3 p = ray.ValueAt(t);
			if(0 <= p.x && p.x <= rx && 
				0 <= p.z && p.z <= rz) {
				outPoint[0] = p + mPosition;
				return true;
			}
		} else if(ray.direction.y < 0) {
			t = (ry - ray.origin.y) / ray.direction.y;
			glm::vec3 p = ray.ValueAt(t);
			if(0 <= p.x && p.x <= rx && 
				0 <= p.z && p.z <= rz) {
				outPoint[0] = p + mPosition;
				return true;
			}
		}
	}

	if(abs(ray.direction.z) > EPSILON) {
		if(ray.direction.z > 0) {
			t = (-ray.origin.z) / ray.direction.z;
			glm::vec3 p = ray.ValueAt(t);
			if(0 <= p.x && p.x <= rx && 
				0 <= p.y && p.y <= ry) {
				outPoint[0] = p + mPosition;
				return true;
			}
		} else if(ray.direction.x < 0) {
			t = (rz - ray.origin.z) / ray.direction.z;
			glm::vec3 p = ray.ValueAt(t);
			if(0 <= p.x && p.x <= rx && 
				0 <= p.y && p.y <= ry) {
				outPoint[0] = p + mPosition;
				return true;
			}
		}
	}

	return false;
}*/