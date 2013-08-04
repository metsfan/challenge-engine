#include <Engine/Challenge.h>
#include <Engine/Util/Util.h>
#include "Octree.h"
using namespace challenge;

/*
 * OctreeNode Class Implementation
*/

OctreeNode::OctreeNode(float minx, float maxx, float miny, float maxy, float minz, float maxz)
{
	mBounds = BoundingBox(minx, miny, minz, maxx, maxy, maxz);
	mNodeId = Util::uuid_create();
	mHasChildren = false;
}

void OctreeNode::BuildChildren() 
{
	float midx = (mBounds.mMin.x + mBounds.mMax.x) / 2;
	float midy = (mBounds.mMin.y + mBounds.mMax.y) / 2;
	float midz = (mBounds.mMin.z + mBounds.mMax.z) / 2;
	
	mChildren[TOP_LEFT_NEAR] = new OctreeNode(mBounds.mMin.x, midx, midy, mBounds.mMax.y, mBounds.mMin.z, midz);
	mChildren[TOP_LEFT_FAR] = new OctreeNode(mBounds.mMin.x, midx, midy, mBounds.mMax.y, midz, mBounds.mMax.z);

	mChildren[TOP_RIGHT_NEAR] = new OctreeNode(midx, mBounds.mMax.x, midy, mBounds.mMax.y, mBounds.mMin.z, midz);
	mChildren[TOP_RIGHT_FAR] = new OctreeNode(midx, mBounds.mMax.x, midy, mBounds.mMax.y, midz, mBounds.mMax.z);

	mChildren[BOTTOM_LEFT_NEAR] = new OctreeNode(mBounds.mMin.x, midx, mBounds.mMin.y, midy, mBounds.mMin.z, midz);
	mChildren[BOTTOM_LEFT_FAR] = new OctreeNode(mBounds.mMin.x, midx, mBounds.mMin.y, midy, midz, mBounds.mMax.z);

	mChildren[BOTTOM_RIGHT_NEAR] = new OctreeNode(midx, mBounds.mMax.x, mBounds.mMin.y, midy, mBounds.mMin.z, midz);
	mChildren[BOTTOM_RIGHT_FAR] = new OctreeNode(midx, mBounds.mMax.x, mBounds.mMin.y, midy, midz, mBounds.mMax.z);

	mHasChildren = true;
}

bool OctreeNode::Contains(glm::vec3 point)  
{
	return mBounds.Contains(point);
}

bool OctreeNode::IntersectsShape(IPhysicsShape *shape)
{
	BoundingBox bbox = shape->GetBoundingBox();
	return mBounds.Intersects(bbox);
}

void OctreeNode::AddShape(IPhysicsShape *shape)
{
	mShapes.push_back(shape);	
}

/*
 * Octree Class Implementation
*/

Octree::Octree(int depth)
{
	mdepth = depth;
}

void Octree::BuildTree(TPhysicsShapeLinkedList shapes)
{
	float minx = kInfinity;
	float miny = kInfinity;
	float minz = kInfinity;
	float maxx = -kInfinity;
	float maxy = -kInfinity;
	float maxz = -kInfinity;
	int nShapes = shapes.size();

	TPhysicsShapeLinkedList::iterator iter = shapes.begin();
	while(iter != shapes.end()) {
		IPhysicsShape *shape = (*iter);
		BoundingBox bbox = shape->GetBoundingBox();
		if(bbox.mMin.x < minx) {
			minx = bbox.mMin.x;
		}
		if(bbox.mMax.x > maxx) {
			maxx = bbox.mMax.x;
		}
		if(bbox.mMin.y < miny) {
			miny = bbox.mMin.y;
		}
		if(bbox.mMax.y > maxy) {
			maxy = bbox.mMax.y;
		}
		if(bbox.mMin.z < minz) {
			minz = bbox.mMin.z;
		}
		if(bbox.mMax.z > maxz) {
			maxz = bbox.mMax.z;
		}
		iter++;
	}

	head = new OctreeNode(minx, maxx, miny, maxy, minz, maxz);
	SplitTree(head, 0);

	iter = shapes.begin();
	while(iter != shapes.end()) {
		IPhysicsShape *s = (*iter);
		
		TOctreeNodeList nodes;
		
		if(FindNearestNodesToShape(s, &nodes)) {
			for(int i = 0; i < nodes.size(); i++) {
				nodes[i]->AddShape(s);
			}
		}

		++iter;
	}
}

void Octree::AddShape(IPhysicsShape *shape)
{

}

/*OctreeNode* Octree::FindNearestNode(glm::vec3 point)
{
	OctreeNode *node = head;
	while(node->mHasChildren) {
		if(node->mBottomLeftNear->Contains(point)) {
			node = node->mBottomLeftNear;
		} else if(node->mBottomLeftFar->Contains(point)) {
			node = node->mBottomLeftFar;
		} else if(node->mBottomRightNear->Contains(point)) {
			node = node->mBottomRightNear;
		} else if(node->mBottomRightFar->Contains(point)) {
			node = node->mBottomRightFar;
		} else if(node->mTopLeftNear->Contains(point)) {
			node = node->mTopLeftNear;
		} else if(node->mTopLeftFar->Contains(point)) {
			node = node->mTopLeftFar;
		} else if(node->mTopRightNear->Contains(point)) {
			node = node->mTopRightNear;
		} else if(node->mBottomRightFar->Contains(point)) {
			node = node->mTopRightFar;
		} else {
			break;
		}
	}

	if(!node->mHasChildren) {
		return node;
	}

	return NULL;
}*/

bool Octree::FindNearestNodesToShape(IPhysicsShape *shape, TOctreeNodeList *nodes,  OctreeNode *node)
{
	if(node == NULL) {
		node = head;
	}

	if(node->mHasChildren) {
		for(int i = 0; i < 8; i++) {
			if(node->mChildren[i]->IntersectsShape(shape)) {
				FindNearestNodesToShape(shape, nodes, node->mChildren[i]);
			}
		}
	} else {
		nodes->push_back(node);
	}

	if(nodes->size() > 0) {
		return true;
	}

	return false;
}

TPhysicsShapeLinkedList Octree::FindNearestShapesToShape(IPhysicsShape *shape)
{
	TPhysicsShapeLinkedList shapesList;
	TOctreeNodeList nodes;
	if(FindNearestNodesToShape(shape, &nodes)) {
		for(int i = 0; i < nodes.size(); i++) {
			OctreeNode *node = nodes[i];
			TPhysicsShapeLinkedList::iterator shapes = node->mShapes.begin();
			TPhysicsShapeLinkedList::iterator end = node->mShapes.end();

			while(shapes != end) {
				IPhysicsShape *shape = (*shapes);
				shapesList.push_back(shape);
				++shapes;
			}
		}
	}

	return shapesList;
}

void Octree::SplitTree(OctreeNode *node, int depthLevel)
{
	if(depthLevel >= mdepth) {
		return;
	}
	node->BuildChildren();
	depthLevel++;

	for(int i = 0; i < 8; i++) {
		SplitTree(node->mChildren[i], depthLevel);
	}
}

TPhysicsShapeLinkedList Octree::FindNearestShapes(glm::vec3 point)
{
	/*int nShapes = shapes.size();
	glm::mat3x4 nearest;
	float nearx = kInfinity;
	float neary = kInfinity;
	float nearz = kInfinity;
	std::list<glm::mat3x4> foundShapes;
	for(int i = 0; i < nShapes; i++) {
		glm::mat3x4 s = shapes[i];
		float minx = kInfinity;
		float miny = kInfinity;
		float minz = kInfinity;
		float maxx = -kInfinity;
		float maxy = -kInfinity;
		float maxz = -kInfinity;
		for(int j = 0; j < 3; j++) {
			glm::vec4 p = shapes[i][j];
			if(p.x <= minx) {
				minx = p.x;
			}
			if(p.x >= maxx) {
				maxx = p.x;
			}
			if(p.y <= miny) {
				miny = p.y;
			}
			if(p.y >= maxy) {
				maxy = p.y;
			}
			if(p.z <= minz) {
				minz = p.z;
			}
			if(p.z >= maxz) {
				maxz = p.z;
			}
		}
		if(point.x >= minx && point.x <= maxx &&
			point.y >= miny && point.y <= maxy &&
			point.z >= minz && point.z <= maxz) {
				foundShapes.push_back(s);
		} else {
			float dx = abs(point.x - s[0].x);
			float dy = abs(point.y - s[0].y);
			float dz = abs(point.z - s[0].z);
			if(dx < nearx && dy < neary && dz < nearz) {
				nearx = dx;
				neary = dy;
				nearz = dz;
				nearest = s;
			}
		}

	}
	//return nearest;
	return foundShapes;*/
	return TPhysicsShapeLinkedList();
}

Octree::~Octree(void)
{
}
