#include <Engine/Challenge.h>
#include <Engine/Physics/Objects/PlaneObject.h>
#include "TriangleMeshShape.h"
#include <Engine/Physics/Shapes/PhysicsShape.h>
#include <Engine/Physics/Collision/CollisionData.h>
#include <Engine/Physics/Shapes/ConcaveTriangleMeshShape.h>
#include <minwindef.h>
using namespace challenge;

TriangleMeshShape::TriangleMeshShape() : PhysicsShape()
{
	mMeshChanged = false;
	mMinX = mMinY = mMinZ = kInfinity;
	mMaxX = mMaxY = mMaxZ = -kInfinity;
}

bool TriangleMeshShape::Intersects(IPhysicsShape *other, CollisionData *collision)
{
	PhysicsShapeType type = other->GetType();
	bool collides = false;

	if(type == kShapeTypePlane) {
		PlaneShape *plane = reinterpret_cast<PlaneShape *>(other);
		collides = mBoundingBox.Intersects(plane, collision);
	} else if(type == kShapeTypeConcaveTriangleMesh) {
		ConcaveTriangleMeshShape *shape = reinterpret_cast<ConcaveTriangleMeshShape *>(other);
		collides = shape->Intersects(&mBoundingBox, collision);
	}

	return collides;
}

void TriangleMeshShape::SetPosition(glm::vec3 position)
{
	mBoundingSphere.SetPosition(position);
	mBoundingBox.SetPosition(position);

	if(mMeshChanged) {
		CalculateBoundingSphere();
		CalculateBoundingBox();
		mMeshChanged = false;
	}
}

void TriangleMeshShape::AddTriangle(glm::vec3 a, glm::vec3 b, glm::vec3 c)
{
	TriangleShape *triangle = new TriangleShape(a, b, c);
	mTriangles.push_back(triangle);

	glm::vec3 points[3] = { a, b, c };

	for (int i = 0; i < 3; i++)
	{
		if(points[i].x < mMinX) mMinX = points[i].x;
		if(points[i].x > mMaxX) mMaxX = points[i].x;

		if(points[i].y < mMinY) mMinY = points[i].y;
		if(points[i].y > mMaxY) mMaxY = points[i].y;

		if(points[i].z < mMinZ) mMinZ = points[i].z;
		if(points[i].z > mMaxZ) mMaxZ = points[i].z;
	}

	mMeshChanged = true;
}

void TriangleMeshShape::CalculateDerivedData()
{
	if(mMeshChanged) {
		CalculateBoundingSphere();
		CalculateBoundingBox();
		mMeshChanged = false;
	}
}

void TriangleMeshShape::CalculateBoundingSphere()
{
	glm::vec3 xAxis = glm::vec3(1.0f, 0.0f, 0.0f);
	glm::vec3 yAxis = glm::vec3(0.0f, 1.0f, 0.0f);
	glm::vec3 zAxis = glm::vec3(0.0f, 0.0f, 1.0f);
	glm::vec3 mainAxis;

	real xDelta = mMaxX - mMinX;
	real yDelta = mMaxY - mMinY;
	real zDelta = mMaxZ - mMinZ;

	float maxDelta = MAX(xDelta, MAX(yDelta, zDelta)); 

	if(maxDelta == xDelta) {
		mainAxis = xAxis;
	} else if(maxDelta == yDelta) {
		mainAxis = yAxis;
	} else {
		mainAxis = zAxis;
	}

	glm::vec3 minP, maxP;
	real minDist = kInfinity, maxDist = -kInfinity;
	TTriangleList::iterator it = mTriangles.begin();

	while(it != mTriangles.end()) {
		TriangleShape *triangle = (*it);
		for(int i = 0; i < 3; i++) {
			real dist = glm::dot(triangle->mPoints[i], mainAxis);
			if(dist < minDist) {
				minDist = dist;
				minP = triangle->mPoints[i];
			}

			if(dist > maxDist) {
				maxDist = dist;
				maxP = triangle->mPoints[i];
			}
		}

		++it;
	}

	glm::vec3 center = (maxP + minP) / 2.0f;
	real r = glm::length(minP - center);
	real r2 = r * r;

	it = mTriangles.begin();
	while(it != mTriangles.end()) {
		TriangleShape *triangle = (*it);
		for(int i = 0; i < 3; i++) {
			glm::vec3 point = triangle->mPoints[i];
			glm::vec3 pMinusCenter = point - center;
			real pMinusCenterLen = glm::length(pMinusCenter);

			if((pMinusCenterLen * pMinusCenterLen) > r2) {
				glm::vec3 G = center - (r * (pMinusCenter / pMinusCenterLen));
				center = (G + point) / 2.0f;
				r = glm::length(point - center);
				r2 = r * r;
			}
		}

		++it;
	}

	mBoundingSphere = SphereShape(center, r);
}

void TriangleMeshShape::CalculateBoundingBox()
{
	glm::vec3 xAxis = glm::vec3(1.0f, 0.0f, 0.0f);
	glm::vec3 yAxis = glm::vec3(0.0f, 1.0f, 0.0f);
	glm::vec3 zAxis = glm::vec3(0.0f, 0.0f, 1.0f);

	real minDistX, maxDistX, minDistY, maxDistY, minDistZ, maxDistZ;
	minDistX = minDistY = minDistZ = kInfinity;
	maxDistX = maxDistY = maxDistZ = -kInfinity;

	glm::vec3 minX, minY, minZ, maxX, maxY, maxZ;

	TTriangleList::iterator it = mTriangles.begin();

	while(it != mTriangles.end()) {
		TriangleShape *triangle = (*it);
		for(int i = 0; i < 3; i++) {
			glm::vec3 point = triangle->mPoints[i];
			float pDotX = glm::dot(point, xAxis);
			float pDotY = glm::dot(point, yAxis);
			float pDotZ = glm::dot(point, zAxis);

			if(pDotX < minDistX) {
				minDistX = pDotX;
				minX = point;
			}
			if(pDotY < minDistY) {
				minDistY = pDotY;
				minY = point;
			}
			if(pDotZ < minDistZ) {
				minDistZ = pDotZ;
				minZ = point;
			}
			if(pDotX > maxDistX) {
				maxDistX = pDotX;
				maxX = point;
			}
			if(pDotY > maxDistY) {
				maxDistY = pDotY;
				maxY = point;
			}
			if(pDotZ > maxDistZ) {
				maxDistZ = pDotZ;
				maxZ = point;
			}
		}

		++it;
	}

	real a = (minDistX + maxDistX) / 2.0f;
	real b = (minDistY + maxDistY) / 2.0f;
	real c = (minDistZ + maxDistZ) / 2.0f;

	glm::vec3 center = (a * xAxis) + (b * yAxis) + (c * zAxis);

	real halfX = center.x - minX.x;
	real halfY = center.y - minY.y;
	real halfZ = center.z - minZ.z;

	mBoundingBox = AABBShape(center, halfX, halfY, halfZ);
}

glm::mat3 TriangleMeshShape::CalculateInertiaTensor(float mass)
{
	return mBoundingBox.CalculateInertiaTensor(mass);
}