#include <Challenge/Challenge.h>
#include "Intersection.h"
#include <Challenge/Physics/Util/Math.h>
#include <Challenge/Util/Logger.h>
#include "SphereShape.h"
#include "AABBShape.h"
#include "PlaneShape.h"
#include "TriangleShape.h"

#include <glm/gtx/norm.hpp>

namespace challenge
{
	/*bool IntersectionTests::SphereIntersectsSphere(const SphereShape *sphere1, const SphereShape *sphere2, CollisionData *collision)
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

	bool IntersectionTests::AABBIntersectsSphere(const AABBShape *aabb, const SphereShape *sphere, CollisionData *collision)
	{
		double sqDistance = glm::distance2(aabb->GetPosition(), sphere->GetPosition());
		double sqRadius = sphere->GetRadius() * sphere->GetRadius();

		return sqDistance <= sqRadius;
	}

	bool IntersectionTests::AABBIntersectsAABB(const AABBShape *aabb1, const AABBShape *aabb2, CollisionData *collision)
	{
		bool intersects = aabb1->GetBoundingBox().Intersects(aabb2->GetBoundingBox());

		if (collision) {
			BoundingBox intersection = aabb1->GetBoundingBox().Intersection(aabb2->GetBoundingBox());
			collision->penetrationDepth = intersection.GetHeight();
		}

		return intersects;
	}

	bool IntersectionTests::AABBIntersectsOBB(const AABBShape *aabb, const OBBShape *obb, CollisionData *collision)
	{
		glm::mat3 axes1;
		const glm::mat3 &axes2 = obb->GetAxes();

		const glm::vec3 &dims1 = aabb->GetDimensions();
		const glm::vec3 &dims2 = obb->GetDimensions();

		glm::vec3 t = obb->GetPosition() - aabb->GetPosition();

		bool intersects = IntersectionTests::BoxIntersect(axes1, dims1, axes2, dims2, t);

		return intersects;
	}

	bool IntersectionTests::AABBIntersectsTriangle(const AABBShape *aabb, const TriangleShape *triangle, CollisionData *collision)
	{
		glm::vec3 c = aabb->GetPosition();
		const glm::vec3 &tc = triangle->GetPosition();

		glm::vec3 v[3];
		v[0] = (triangle->GetPoint(0) + tc) - c;
		v[1] = (triangle->GetPoint(1) + tc) - c;
		v[2] = (triangle->GetPoint(2) + tc) - c;

		glm::vec3 f[3] = { v[1] - v[0], v[2] - v[1], v[0] - v[2] };
		glm::vec3 axes[3] = {
			glm::vec3(1.0, 0.0, 0.0),
			glm::vec3(0.0, 1.0, 0.0),
			glm::vec3(0.0, 0.0, 1.0)
		};

		float p0, p1, p2, r, min, max;
		glm::vec3 axis;

		glm::vec3 minAxis;
		real minDist = INFINITY;

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

				if (min > r || max < -r) {
					return false;
				}

				if (minDist > max - min) {
					minAxis = axis;
					minDist = max - min;
				}
			}
		}

		min = MIN(v[0].x, MIN(v[1].x, v[2].x));
		max = MAX(v[0].x, MAX(v[1].x, v[2].x));
		if (max < -aabb->GetHalfX() || min > aabb->GetHalfX()) {
			return false;
		}

		if (minDist > max - min) {
			minAxis = axis;
			minDist = max - min;
		}

		min = MIN(v[0].y, MIN(v[1].y, v[2].y));
		max = MAX(v[0].y, MAX(v[1].y, v[2].y));
		if (max < -aabb->GetHalfY() || min > aabb->GetHalfY()) {
			return false;
		}

		if (minDist > max - min) {
			minAxis = axis;
			minDist = max - min;
		}

		min = MIN(v[0].z, MIN(v[1].z, v[2].z));
		max = MAX(v[0].z, MAX(v[1].z, v[2].z));
		if (max < -aabb->GetHalfZ() || min > aabb->GetHalfZ()) {
			return false;
		}

		if (minDist > max - min) {
			minAxis = axis;
			minDist = max - min;
		}


		if (collision) {
			Logger::log(LogDebug, "Penetration Depth: %f", minDist);

			collision->penetrationDepth = PhysicsMath::PointPlaneDistance(c, triangle->GetPlane());
			collision->collisionNormal = glm::vec3(0, -1, 0);
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

	bool IntersectionTests::OBBIntersectsOBB(const OBBShape *obb1, const OBBShape *obb2, CollisionData *collision)
	{
		const glm::mat3 &axes1 = obb1->GetAxes();
		const glm::mat3 &axes2 = obb2->GetAxes();

		const glm::vec3 &dims1 = obb1->GetDimensions();
		const glm::vec3 &dims2 = obb2->GetDimensions();

		glm::vec3 t = obb2->GetPosition() - obb1->GetPosition();

		bool intersects = IntersectionTests::BoxIntersect(axes1, dims1, axes2, dims2, t);

		return intersects;
	}

	/* Private Helpers */

	bool IntersectionTests::BoxIntersect(const glm::mat3 &axes1, const glm::vec3 &dims1,
		const glm::mat3 &axes2, const glm::vec3 &dims2,
		const glm::vec3 &t)
	{
		real ra, rb, tDotL;

		glm::mat3 r = axes1 * axes2;

		for (int i = 0; i < 3; i++) {
			ra = dims1[i];
			rb = (dims2[0] * abs(r[i][0])) + (dims2[1] * abs(r[i][1])) + (dims2[2] * abs(r[i][2]));
			tDotL = abs(t[i]);

			if (tDotL >(ra + rb)) {
				return false;
			}
		}

		for (int i = 0; i < 3; i++) {
			ra = (dims1[0] * abs(r[i][0])) + (dims1[1] * abs(r[i][1])) + (dims1[2] * abs(r[i][2]));
			rb = dims2[i];
			tDotL = abs((t.x * r[0][i]) + (t.y * r[1][i]) + (t.z * r[2][i]));

			if (tDotL >(ra + rb)) {
				return false;
			}
		}

		// axes1[0] X axes2[0]
		tDotL = abs((t.z * r[1][0]) - (t.y * r[2][0]));
		ra = (dims1.y * abs(r[2][0])) + (dims1.z * abs(r[1][0]));
		rb = (dims2.y * abs(r[0][2])) + (dims2.z * abs(r[0][1]));
		if (tDotL >(ra + rb)) {
			return false;
		}

		// axes1[0] X axes2[1]
		tDotL = abs((t.z * r[1][1]) - (t.y * r[2][1]));
		ra = (dims1.y * abs(r[2][1])) + (dims1.z * abs(r[1][1]));
		rb = (dims2.x * abs(r[0][2])) + (dims2.z * abs(r[0][0]));
		if (tDotL >(ra + rb)) {
			return false;
		}

		// axes1[0] X axes2[2]
		tDotL = abs((t.z * r[1][2]) - (t.y * r[2][2]));
		ra = (dims1.y * abs(r[2][2])) + (dims1.z * abs(r[1][2]));
		rb = (dims2.x * abs(r[0][1])) + (dims2.y * abs(r[0][0]));
		if (tDotL >(ra + rb)) {
			return false;
		}

		// axes1[1] X axes2[0]
		tDotL = abs((t.x * r[2][0]) - (t.z * r[0][0]));
		ra = (dims1.x * abs(r[2][0])) + (dims1.z * abs(r[0][0]));
		rb = (dims2.y * abs(r[1][2])) + (dims2.z * abs(r[1][1]));
		if (tDotL >(ra + rb)) {
			return false;
		}

		// axes1[1] X axes2[1]
		tDotL = abs((t.x * r[2][1]) - (t.z * r[0][1]));
		ra = (dims1.x * abs(r[2][1])) + (dims1.z * abs(r[0][1]));
		rb = (dims2.x * abs(r[1][2])) + (dims2.z * abs(r[1][0]));
		if (tDotL >(ra + rb)) {
			return false;
		}

		// axes1[1] X axes2[2]
		tDotL = abs((t.x * r[2][2]) - (t.z * r[0][2]));
		ra = (dims1.x * abs(r[2][2])) + (dims1.z * abs(r[0][2]));
		rb = (dims2.x * abs(r[1][1])) + (dims2.y * abs(r[1][0]));
		if (tDotL >(ra + rb)) {
			return false;
		}

		// axes1[2] X axes2[0]
		tDotL = abs((t.y * r[0][0]) - (t.x * r[1][0]));
		ra = (dims1.x * abs(r[1][0])) + (dims1.y * abs(r[0][0]));
		rb = (dims2.y * abs(r[2][2])) + (dims2.z * abs(r[2][1]));
		if (tDotL >(ra + rb)) {
			return false;
		}

		// axes1[2] X axes2[1]
		tDotL = abs((t.y * r[0][1]) - (t.x * r[1][1]));
		ra = (dims1.x * abs(r[1][1])) + (dims1.y * abs(r[0][1]));
		rb = (dims2.x * abs(r[2][2])) + (dims2.z * abs(r[2][0]));
		if (tDotL >(ra + rb)) {
			return false;
		}

		// axes1[2] X axes2[2]
		tDotL = abs((t.y * r[0][2]) - (t.x * r[1][2]));
		ra = (dims1.x * abs(r[1][2])) + (dims1.y * abs(r[0][2]));
		rb = (dims2.x * abs(r[2][1])) + (dims2.y * abs(r[2][0]));
		if (tDotL >(ra + rb)) {
			return false;
		}

		return true;
	}


	void IntersectionTests::UpdateSATPenetration(real min1, real max1,
		real min2, real max2,
		const glm::vec3 &axis, real &min, glm::vec3 &minAxis)
	{

	}
}