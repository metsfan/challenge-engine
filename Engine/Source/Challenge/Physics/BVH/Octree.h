#pragma once

#include <Challenge/Challenge.h>
#include <Challenge/Math/Ray.h>
#include <Challenge/Physics/Shapes/GeometricShape.h>
#include <Challenge/Physics/PhysicsCore.h>

namespace challenge
{
	static const int kMaxShapesPerNode = 10;

	/*static const int TOP_LEFT_NEAR = 0, 
					 TOP_LEFT_FAR = 1, 
					 TOP_RIGHT_NEAR = 2, 
					 TOP_RIGHT_FAR = 3, 
					 BOTTOM_LEFT_NEAR = 4, 
					 BOTTOM_LEFT_FAR = 5, 
					 BOTTOM_RIGHT_NEAR = 6, 
					 BOTTOM_RIGHT_FAR = 7;*/

	enum OctreeChildren
	{
		BottomLeftNear = 0,
		BottomLeftFar = 1,
		TopLeftNear = 2,
		TopLeftFar = 3,
		BottomRightNear = 4,
		BottomRightFar = 5,
		TopRightNear = 6,
		TopRightFar = 7
	};

	struct OctreeObject
	{
		OctreeObject() :
			shape(NULL),
			object(NULL)
		{
		}

		OctreeObject(const IGeometricShape *_shape, void *_object) :
			shape(_shape), object(_object)
		{
		}

		const IGeometricShape *shape;
		void *object;
	};

	class OctreeNode
	{
		friend class Octree;

	public:
		OctreeNode(float minx, float maxx, float miny, float maxy, float minz, float maxz);
		OctreeNode(const BoundingBox &bounds);
		void BuildChildren();
		bool Contains(const glm::vec3 &point);
		bool IntersectsShape(const IGeometricShape *shape);
		void AddShape(const IGeometricShape *shape, void *object);
		OctreeObject RemoveShape(const IGeometricShape *shape);

	private:
		BoundingBox mBounds;
		std::list<OctreeObject> mShapes;
		OctreeNode *mChildren[8];
		bool mHasChildren;
		UUID mNodeId;
	};

	enum OctreeFlags
	{
		OctreeLeafObjectsOnly = 0x1,
		OctreePreallocateDepth = 0x2,
		OctreeAutoExpandBredth = 0x4,
		OctreeAutoExtendDepth = 0x8
	};

	typedef std::vector<OctreeNode *> TOctreeNodeList;

	class Octree
	{
	public:
		Octree(const BoundingBox &maxBounds, int maxDepth, int flags = 0);
		~Octree();

		std::vector<OctreeObject> Query(const IGeometricShape *shape);
		const OctreeObject* RayIntersection(Ray ray, int queryType = RayCastClosest);
		void AddShape(const IGeometricShape *shape, void *object);

		void UpdateObject(const IGeometricShape *object);

	private:
		OctreeNode *mHead;
		int mMaxDepth;
		int mFlags;
		BoundingBox mMaxBounds;
		std::map<const IGeometricShape *, OctreeNode *> mObjectLookup;

		OctreeObject* FindRayIntersection(OctreeNode *node, const Ray &ray, const Ray &original, int offset,
			real t0x, real t0y, real t0z, real t1x, real t1y, real t1z, real &minT);
		OctreeNode* FindContainingNode(OctreeNode *node, const IGeometricShape *shape);
		void FindObjects(OctreeNode *node, const IGeometricShape *shape, std::vector<OctreeObject> &list);
		void SplitNode(OctreeNode *node);
	};
}


