#include <Challenge/Challenge.h>
#include "Intersection.h"
#include <Challenge/Physics/Util/Math.h>
#include <Challenge/Util/Logger.h>
using namespace challenge;


/*bool IntersectionTests::SphereIntersectsSphere(const SphereShape *sphere1, const SphereShape *sphere2, CollisionData *collision)
{
	return false;
}

bool IntersectionTests::AABBIntersectsSphere(const AABBShape *aabb, const SphereShape *sphere, CollisionData *collision)
{
	return false;
}

bool IntersectionTests::AABBIntersectsAABB(const AABBShape *aabb1, const AABBShape *aabb2, CollisionData *collision)
{
	return false;
}

bool IntersectionTests::AABBIntersectsPlane(const AABBShape *aabb, const PlaneShape *plane, CollisionData *collision)
{
	glm::vec3 xAxis = glm::vec3(1.0, 0.0, 0.0);
	glm::vec3 yAxis = glm::vec3(0.0, 1.0, 0.0);
	glm::vec3 zAxis = glm::vec3(0.0, 0.0, 1.0);
	glm::vec3 normal = plane->GetNormal();

	/*float xLen = glm::length(xAxis * normal);
	float yLen = glm::length(yAxis * normal);
	float zLen = glm::length(zAxis * normal);

	float rEff = 0.5 * (xLen + yLen + zLen);
	
	PlaneShape plane1(glm::vec4(normal, plane->mComponents.w - rEff));

	glm::vec3 center = aabb->GetPosition();
	//center += glm::vec3(aabb->mHalfX, aabb->mHalfY, aabb->mHalfZ) * normal;
	float r = glm::dot(plane1.mComponents, glm::vec4(center, 1.0));
	bool intersects = abs(r) <= rEff;

	const glm::vec3 &center = aabb->GetCenter();
	const glm::vec3 &e = aabb->GetDimensions();

	glm::vec3 n = plane->GetNormal();
	float r = (e.x * abs(n.x)) + (e.y * abs(n.y)) + (e.z * abs(n.z));
	float s = glm::dot(n, center) - plane->GetD();

	bool intersects = abs(s) <= r;

	if (intersects && collision != NULL) {
		real xDotN = glm::dot(xAxis, normal);
		real yDotN = glm::dot(yAxis, normal);
		real zDotN = glm::dot(zAxis, normal);
		int numZero = 0;
		bool xAxisZero = false, yAxisZero = false, zAxisZero = false;

		if(xDotN == 0) {
			numZero++;
			xAxisZero = true;
		}

		if(yDotN == 0) {
			numZero++;
			yAxisZero = true;
		}

		if(zDotN == 0) {
			numZero++;
			zAxisZero = true;
		}


		if (numZero == 0) {
			Contact *contact = new Contact();
			glm::vec3 point = center - (0.5f * ((glm::sign(xDotN) * xAxis) + (glm::sign(yDotN) * yAxis) + (glm::sign(zDotN) * zAxis)));
			contact->mContactPoint = point;
			contact->mContactNormal = plane->GetNormal();
			contact->mPenetration = PhysicsMath::PointPlaneDistance(point, plane);
			collision->mContacts.push_back(contact);
		} else if(numZero == 1) {
			glm::vec3 zeroAxis, axis1, axis2, point;
			if(xAxisZero) {
				zeroAxis = xAxis;
				axis1 = yAxis;
				axis2 = zAxis;
			} else if(yAxisZero) {
				zeroAxis = yAxis;
				axis1 = xAxis;
				axis2 = zAxis;
			} else if(zAxisZero) {
				zeroAxis = zAxis;
				axis1 = xAxis;
				axis2 = yAxis;
			}

			glm::vec3 M = (glm::sign(xDotN) * axis1) + (glm::sign(yDotN) * axis1);

			Contact *contact = new Contact();
			point = center - (0.5f * (M + zeroAxis));
			contact->mContactPoint = point;
			contact->mContactNormal = plane->GetNormal();
			contact->mPenetration = PhysicsMath::PointPlaneDistance(point, plane);
			collision->mContacts.push_back(contact);

			contact = new Contact();
			point = center - (0.5f * (M - zeroAxis));
			contact->mContactPoint = point;
			contact->mContactNormal = plane->GetNormal();
			contact->mPenetration = PhysicsMath::PointPlaneDistance(point, plane);
			collision->mContacts.push_back(contact);
		} else if(numZero == 2) {
			glm::vec3 zeroAxis1, zeroAxis2, offAxis, point;
			bool zeroAxis1Set = false, zeroAxis2Set = false;

			if(xAxisZero) {
				zeroAxis1 = xAxis;
				zeroAxis1Set = true;
			} else {
				offAxis = xAxis;
			}

			if(yAxisZero) {
				if(!zeroAxis1Set) {
					zeroAxis1 = yAxis;
					zeroAxis1Set = true;
				} else {
					zeroAxis2 = yAxis;
					zeroAxis2Set = true;
				}
			} else {
				offAxis = yAxis;
			}

			if(zAxisZero) {
				if(!zeroAxis1Set) {
					zeroAxis1 = zAxis;
					zeroAxis1Set = true;
				} else if(!zeroAxis2Set) {
					zeroAxis2 = zAxis;
					zeroAxis2Set = true;
				} else {
					offAxis = zAxis;
				}
			} else {
				offAxis = zAxis;
			}

			glm::vec3 M = glm::sign(xDotN) * xAxis;

			Contact *contact = new Contact();
			point = center - (0.5f * (M + zeroAxis1 + zeroAxis2));
			contact->mContactPoint = point;
			contact->mContactNormal = plane->GetNormal();
			contact->mPenetration = PhysicsMath::PointPlaneDistance(point, plane);
			collision->mContacts.push_back(contact);

			contact = new Contact();
			point = center - (0.5f * (M + zeroAxis1 - zeroAxis2));
			contact->mContactPoint = point;
			contact->mContactNormal = plane->GetNormal();
			contact->mPenetration = PhysicsMath::PointPlaneDistance(point, plane);
			collision->mContacts.push_back(contact);

			contact = new Contact();
			point = center - (0.5f * (M - zeroAxis1 + zeroAxis2));
			contact->mContactPoint = point;
			contact->mContactNormal = plane->GetNormal();
			contact->mPenetration = PhysicsMath::PointPlaneDistance(point, plane);
			collision->mContacts.push_back(contact);

			contact = new Contact();
			point = center - (0.5f * (M - zeroAxis1 - zeroAxis2));
			contact->mContactPoint = point;
			contact->mContactNormal = plane->GetNormal();
			contact->mPenetration = PhysicsMath::PointPlaneDistance(point, plane);
			collision->mContacts.push_back(contact);
		}
	}

	return intersects;
}*/

bool IntersectionTests::AABBIntersectsTriangle(const AABBShape *aabb, const TriangleShape *triangle, CollisionData *collision)
{
	glm::vec3 c = aabb->GetPosition();

	glm::vec3 v[3];
	v[0] = triangle->GetPoint(0) - c;
	v[1] = triangle->GetPoint(1) - c;
	v[2] = triangle->GetPoint(2) - c;

	glm::vec3 f[3] = { v[1] - v[0], v[2] - v[1], v[0] - v[2] };
	glm::vec3 axes[3] = { 
		glm::vec3(1.0, 0.0, 0.0),
		glm::vec3(0.0, 1.0, 0.0),
		glm::vec3(0.0, 0.0, 1.0)
	};

	float p0, p1, p2, r, min, max;
	glm::vec3 axis;

	for (int i = 0; i < 3; i++) {
		for (int j = 0; j < 3; j++) {
			axis = glm::cross(axes[i], f[j]);
			
			p0 = glm::dot(v[0], axis);
			p1 = glm::dot(v[1], axis);
			p2 = glm::dot(v[2], axis);

			r = (aabb->GetHalfX() * abs(glm::dot(axes[0], axis))) + 
				(aabb->GetHalfY() * abs(glm::dot(axes[1], axis))) + 
				(aabb->GetHalfZ() * abs(glm::dot(axes[2], axis)));

			min = MIN(p0, MIN(p1, p2));
			max = MAX(p0, MAX(p1, p2));

			if(abs(min) < 100) {
				printf("stop");
			}

			if(min > r || max < -r) {
				return false;
			}
		}
	}

	min = MIN(v[0].x, MIN(v[1].x, v[2].x));
	max = MAX(v[0].x, MAX(v[1].x, v[2].x));
	if(max < -aabb->GetHalfX() || min > aabb->GetHalfX()) {
		return false;
	}

	min = MIN(v[0].y, MIN(v[1].y, v[2].y));
	max = MAX(v[0].y, MAX(v[1].y, v[2].y));
	if(max < -aabb->GetHalfY() || min > aabb->GetHalfY()) {
		return false;
	}
	
	min = MIN(v[0].z, MIN(v[1].z, v[2].z));
	max = MAX(v[0].z, MAX(v[1].z, v[2].z));
	if(max < -aabb->GetHalfZ() || min > aabb->GetHalfZ()) {
		return false;
	}

	if (collision) {
		collision->penetrationDepth = PhysicsMath::PointPlaneDistance(c, &triangle->GetPlane());
	}

	/*Contact *contact = new Contact();

	contact->mContactNormal = triangle->mNormalPlane.mNormal;
	//c.y += aabb->mHalfY;
	contact->mContactPoint = c;
	contact->mPenetration = PhysicsMath::PointPlaneDistance(c, &triangle->mNormalPlane);
	collision->mContacts.push_back(contact);

	//return true;
	bool intersects = IntersectionTests::AABBIntersectsPlane(aabb, &triangle->GetPlane(), NULL);

	if(intersects && collision != NULL) {
		contact->mContactNormal = triangle->GetPlane().GetNormal();

		glm::vec3 normal = contact->mContactNormal;

		//contact->mContactPoint = c;
		Ray r(c, triangle->GetPlane().GetNormal());

		glm::vec3 intPoint;
		if(!triangle->RayIntersects(r, &intPoint)) {
			return false;
		}
		
		contact->mContactPoint = intPoint;

		

		//r = Ray(intPoint, normal * -1.0f);
		//aabb->RayIntersects(r, &intPoint);

		glm::vec4 planes[6];
		planes[0] = glm::vec4(1, 0, 0, aabb->GetHalfX() + c.x);
		planes[1] = glm::vec4(1, 0, 0, -aabb->GetHalfX() + c.x);
		planes[2] = glm::vec4(0, 1, 0, aabb->GetHalfY() + c.y);
		planes[3] = glm::vec4(0, 1, 0, -aabb->GetHalfY() + c.y);
		planes[4] = glm::vec4(0, 0, 1, aabb->GetHalfZ() + c.z);
		planes[5] = glm::vec4(0, 0, 1, -aabb->GetHalfZ() + c.z);

		real minDist = FLT_MAX;
		for(int i = 0; i < 3; i++) {
			if(normal[i] < 0.00001) {
				continue;
			}
			if(normal[i] < 0) {
				PlaneShape plane(planes[i*2]);
				real dist = -PhysicsMath::PointPlaneDistance(intPoint, &plane);
				if(dist < minDist) {
					minDist = dist;
				}
			} else if(normal[i] > 0) {
				PlaneShape plane(planes[i*2+1]);
				real dist = -PhysicsMath::PointPlaneDistance(intPoint, &plane);
				if(dist < minDist) {
					minDist = dist;
				}
			}
		}

		//Logger::log(LogDebug, "%f", minDist);

		//contact->mPenetration = -minDist;
		c.y -= aabb->GetHalfY();
		contact->mPenetration = -PhysicsMath::PointPlaneDistance(c, &triangle->GetPlane());
		//contact->mPenetration = 0.01;
		collision->mContacts.push_back(contact);
	}*/

	return true;
}