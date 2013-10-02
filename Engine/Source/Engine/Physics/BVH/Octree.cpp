#include <Engine/Challenge.h>
#include <Engine/Util/Util.h>
#include "Octree.h"

namespace challenge
{
	/*
	 * OctreeNode Class Implementation
	*/

	OctreeNode::OctreeNode(float minx, float maxx, float miny, float maxy, float minz, float maxz) :
		mBounds(minx, miny, minz, maxx, maxy, maxz),
		mHasChildren(false),
		mNodeId(Util::uuid_create())
	{
		memset(mChildren, 0, sizeof(mChildren));
	}

	OctreeNode::OctreeNode(const BoundingBox &bounds) :
		mBounds(bounds),
		mHasChildren(false),
		mNodeId(Util::uuid_create())
	{
		memset(mChildren, 0, sizeof(mChildren));
	}

	void OctreeNode::BuildChildren() 
	{
		float midx = (mBounds.mMin.x + mBounds.mMax.x) / 2;
		float midy = (mBounds.mMin.y + mBounds.mMax.y) / 2;
		float midz = (mBounds.mMin.z + mBounds.mMax.z) / 2;

		mChildren[BottomLeftNear] = new OctreeNode(mBounds.mMin.x, midx, mBounds.mMin.y, midy, mBounds.mMin.z, midz);
		mChildren[BottomLeftFar] = new OctreeNode(mBounds.mMin.x, midx, mBounds.mMin.y, midy, midz, mBounds.mMax.z);
	
		mChildren[TopLeftNear] = new OctreeNode(mBounds.mMin.x, midx, midy, mBounds.mMax.y, mBounds.mMin.z, midz);
		mChildren[TopLeftFar] = new OctreeNode(mBounds.mMin.x, midx, midy, mBounds.mMax.y, midz, mBounds.mMax.z);

		mChildren[BottomRightNear] = new OctreeNode(midx, mBounds.mMax.x, mBounds.mMin.y, midy, mBounds.mMin.z, midz);
		mChildren[BottomRightFar] = new OctreeNode(midx, mBounds.mMax.x, mBounds.mMin.y, midy, midz, mBounds.mMax.z);

		mChildren[TopRightNear] = new OctreeNode(midx, mBounds.mMax.x, midy, mBounds.mMax.y, mBounds.mMin.z, midz);
		mChildren[TopRightFar] = new OctreeNode(midx, mBounds.mMax.x, midy, mBounds.mMax.y, midz, mBounds.mMax.z);

		mHasChildren = true;
	}

	bool OctreeNode::Contains(const glm::vec3 &point)  
	{
		return mBounds.Contains(point);
	}

	bool OctreeNode::IntersectsShape(IGeometricShape *shape)
	{
		return shape->Intersects(mBounds);
	}

	void OctreeNode::AddShape(IGeometricShape *shape, void *object)
	{
		OctreeObject obj = { shape, object };
		mShapes.push_back(obj);	
	}

	/*
	 * Octree Class Implementation
	*/

	Octree::Octree(const BoundingBox &maxBounds, int maxDepth, int flags) :
		mMaxDepth(maxDepth),
		mHead(new OctreeNode(maxBounds)),
		mFlags(flags),
		mMaxBounds(maxBounds)
	{
		mHead->BuildChildren();
	}

	Octree::~Octree(void)
	{
		delete mHead;
	}

	std::vector<OctreeObject> Octree::Query(IGeometricShape *shape)
	{
		std::list<OctreeObject> objects;
		this->FindObjects(mHead, shape, objects);

		std::vector<OctreeObject> finalList;
		for(auto &obj : objects) {
			if(obj.shape->Intersects(shape)) {
				finalList.push_back(obj);
			}
		}

		return finalList;
	}

	const OctreeObject* Octree::RayIntersection(Ray ray, int queryType)
	{
		glm::vec3 t0, t1;
		Ray original = ray;

		unsigned int offset = 0;
		glm::vec3 center = mMaxBounds.GetCenter();
		if(ray.GetDirectionX() < 0) {
			offset |= 4;
			real dist = -ray.GetOriginX() - center.x;
			ray.SetOriginX(ray.GetOriginX() + (dist * 2));
			ray.SetDirectionX(-ray.GetDirectionX());
		}

		if(ray.GetDirectionY() < 0) {
			offset |= 2;
			real dist = -ray.GetOriginY() - center.y;
			ray.SetOriginY(ray.GetOriginY() + (dist * 2));
			ray.SetDirectionY(-ray.GetDirectionY());
		}

		if(ray.GetDirectionZ() < 0) {
			offset |= 1;
			real dist = -ray.GetOriginZ() - center.z;
			ray.SetOriginZ(ray.GetOriginZ() + (dist * 2));
			ray.SetDirectionZ(-ray.GetDirectionZ());
		}

		t0 = (mMaxBounds.mMin - ray.GetOrigin()) / ray.GetDirection();
		t1 = (mMaxBounds.mMax - ray.GetOrigin()) / ray.GetDirection();

		if(std::max(t0.x, std::max(t0.y, t0.z)) < std::min(t1.x, std::min(t1.y, t1.z))) {
			real minT = INFINITY;
			return this->FindRayIntersection(mHead, ray, original, offset, t0.x, t0.y, t0.z, t1.x, t1.y, t1.z, minT);
		}

		return NULL;
	}

	void Octree::AddShape(IGeometricShape *shape, void *object)
	{
		if(!shape->ContainedWithin(mHead->mBounds)) {
			// Expand tree size
		}

		OctreeNode *node = this->FindContainingNode(mHead, shape);
		if(node) {
			node->AddShape(shape, object);
		}
	}

	OctreeObject* Octree::FindRayIntersection(OctreeNode *node, const Ray &ray, const Ray &original, int offset,
		real t0x, real t0y, real t0z, real t1x, real t1y, real t1z, real &minT)
	{
		if(t1x < 0 || t1y < 0 || t1z < 0) {
			return NULL;
		}
		
		real t = INFINITY;
		OctreeObject *minObj = NULL;

		if(node->mShapes.size() > 0) {
			for(auto &nObj : node->mShapes) {
				if(nObj.shape->RayIntersects(original, t) &&
					t < minT) {
					minT = t;
					minObj = &nObj;
				}
			}
		}

		if(!node->mHasChildren) {
			return minObj;
		}

		real tmx = (t0x + t1x) * 0.5f;
		real tmy = (t0y + t1y) * 0.5f;
		real tmz = (t0z + t1z) * 0.5f;

		int currentNodeIndex = 0;

		/*if(node->Contains(ray.GetOrigin())) {
			for(int i = 0; i < 8; i++) {
				if(node->mChildren[i]->Contains(ray.GetOrigin())) {
					currentNodeIndex = i ^ offset;
					break;
				}
			}
		} else {*/
			if(tmx < t0z && tmy < t0z) {
				currentNodeIndex |= 1;
				currentNodeIndex |= 2;
			}
		
			if(tmx < t0y && tmz < t0y) {
				currentNodeIndex |= 1;
				currentNodeIndex |= 4;
			}
		
			if(tmy < t0x && tmz < t0x) {
				currentNodeIndex |= 2;
				currentNodeIndex |= 4;
			}
		//}
		

		auto findNextNode = [&](real tx, int xIndex, real ty, int yIndex, real tz, int zIndex) -> int {
			real min = std::min(tx, std::min(ty, tz));
			if(min == tx) {
				return xIndex;
			} else if(min == ty) {
				return yIndex;
			} else {
				return zIndex;
			}
		};

		OctreeObject *childObj = NULL;

		do {
			switch(currentNodeIndex)
			{
			case BottomLeftNear:
				childObj = this->FindRayIntersection(node->mChildren[BottomLeftNear ^ offset], ray, original, offset,
					t0x, t0y, t0z, tmx, tmy, tmz, minT);
				currentNodeIndex = findNextNode(tmx, 4, tmy, 2, tmz, 1);
				break;

			case BottomLeftFar:
				childObj = this->FindRayIntersection(node->mChildren[BottomLeftFar ^ offset], ray, original, offset, 
					t0x, t0y, tmz, tmx, tmy, t1z, minT);
				currentNodeIndex = findNextNode(tmx, 5, tmy, 3, t1z, -1);
				break;

			case TopLeftNear:
				childObj = this->FindRayIntersection(node->mChildren[TopLeftNear ^ offset], ray, original, offset, 
					t0x, tmy, t0z, tmx, t1y, tmz, minT);
				currentNodeIndex = findNextNode(tmx, 6, t1y, -1, tmz, 3);
				break;

			case TopLeftFar:
				childObj = this->FindRayIntersection(node->mChildren[TopLeftFar ^ offset], ray, original, offset, 
					t0x, tmy, tmz, tmx, t1y, t1z, minT);
				currentNodeIndex = findNextNode(tmx, 7, t1y, -1, t1z, -1);
				break;

			case BottomRightNear:
				childObj = this->FindRayIntersection(node->mChildren[BottomRightNear ^ offset], ray, original, offset, 
					tmx, t0y, t0z, t1x, tmy, tmz, minT);
				currentNodeIndex = findNextNode(t1x, -1, tmy, 6, tmz, 5);
				break;

			case BottomRightFar:
				childObj = this->FindRayIntersection(node->mChildren[BottomRightFar ^ offset], ray, original, offset, 
					tmx, t0y, tmz, t1x, tmy, t1z, minT);
				currentNodeIndex = findNextNode(t1x, -1, tmy, 7, t1z, -1);
				break;

			case TopRightNear:
				childObj = this->FindRayIntersection(node->mChildren[TopRightNear ^ offset], ray, original, offset, 
					tmx, tmy, t0z, t1x, t1y, tmz, minT);
				currentNodeIndex = findNextNode(t1x, -1, t1y, -1, tmz, 7);
				break;

			case TopRightFar:
				childObj = this->FindRayIntersection(node->mChildren[TopRightFar ^ offset], ray, original, offset, 
					tmx, tmy, tmz, t1x, t1y, t1z, minT);
				currentNodeIndex = findNextNode(t1x, -1, t1y, -1, t1z, -1);
				break;
			}

			if(childObj) {
				minObj = childObj;
			}

		} while(currentNodeIndex >= 0);

		return minObj;
	}

	OctreeNode* Octree::FindContainingNode(OctreeNode *node, IGeometricShape *shape)
	{
		if(node->mHasChildren) {
			bool contained = true;
			for(int i = 0; i < 8; i++) {
				if(shape->ContainedWithin(node->mChildren[i]->mBounds)) {
					return this->FindContainingNode(node->mChildren[i], shape);
				}
			}
		}

		return node;
	}

	void Octree::FindObjects(OctreeNode *node, IGeometricShape *shape, std::list<OctreeObject> &list)
	{
		if(!shape->ContainedWithin(node->mBounds)) {
			return;
		}

		std::copy(node->mShapes.begin(), node->mShapes.end(), list.begin());

		for(int i = 0; i < 8; i++) {
			this->FindObjects(node->mChildren[i], shape, list);
		}
	}

	void Octree::SplitNode(OctreeNode *node)
	{

	}
};

