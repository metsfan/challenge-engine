#include <Engine/Challenge.h>
#include <Engine/Util/Util.h>
#include "Octree.h"
using namespace challenge;

/*
 * OctreeNode Class Implementation
*/

OctreeNode::OctreeNode(float minx, float maxx, float miny, float maxy, float minz, float maxz)
{
	mminx = minx;
	mmaxx = maxx;
	mminy = miny;
	mmaxy = maxy;
	mminz = minz;
	mmaxz = maxz;
	mhasChildren = false;
	mnodeId = Util::uuid_create();
}

void OctreeNode::BuildChildren() 
{
	float midx = (mminx + mmaxx) / 2;
	float midy = (mminy + mmaxy) / 2;
	float midz = (mminz + mmaxz) / 2;

	mbln = new OctreeNode(mminx, midx, mminy, midy, mminz, midz);
	mblf = new OctreeNode(mminx, midx, mminy, midy, midz, mmaxz);

	mbrn = new OctreeNode(midx, mmaxx, mminy, midy, mminz, midz);
	mbrf = new OctreeNode(midx, mmaxx, mminy, midy, midz, mmaxz);

	mtln = new OctreeNode(mminx, midx, midy, mmaxy, mminz, midz);
	mtlf = new OctreeNode(mminx, midx, midy, mmaxy, midz, mmaxz);

	mtrn = new OctreeNode(midx, mmaxx, midy, mmaxy, mminz, midz);
	mtrf = new OctreeNode(midx, mmaxx, midy, mmaxy, midz, mmaxz);

	mhasChildren = true;
}

bool OctreeNode::Contains(glm::vec3 point)  
{
	return (point.x >= mminx && point.x <= mmaxx &&
			point.y >= mminy && point.y <= mmaxy &&
			point.z >= mminz && point.z <= mmaxz);
}

void OctreeNode::AddShape(glm::mat3x4 shape)
{
	mshapes.push_back(shape);	
}

/*
 * Octree Class Implementation
*/

Octree::Octree(int depth)
{
	mdepth = depth;
}

void Octree::BuildTree(std::list<glm::mat3x4> shapes)
{
	float minx = kInfinity;
	float miny = kInfinity;
	float minz = kInfinity;
	float maxx = -kInfinity;
	float maxy = -kInfinity;
	float maxz = -kInfinity;
	int nShapes = shapes.size();

	std::list<glm::mat3x4>::iterator iter = shapes.begin();
	while(iter != shapes.end()) {
		for(int j = 0; j < 3; j++) {
			glm::vec4 p = (*iter)[j];
			if(p.x < minx) {
				minx = p.x;
			}
			if(p.x > maxx) {
				maxx = p.x;
			}
			if(p.y < miny) {
				miny = p.y;
			}
			if(p.y > maxy) {
				maxy = p.y;
			}
			if(p.z < minz) {
				minz = p.z;
			}
			if(p.z > maxz) {
				maxz = p.z;
			}
		}
		iter++;
	}

	head = new OctreeNode(minx, maxx, miny, maxy, minz, maxz);
	SplitTree(head, 0);

	std::map<std::string, bool> used;
	iter = shapes.begin();
	while(iter != shapes.end()) {
		glm::mat3x4 s = (*iter);
		
		OctreeNode *node = FindNearestNode(glm::vec3(s[0].x, s[0].y, s[0].z));

		if(node != NULL) {
			node->AddShape(s);
			used[node->getNodeId()] = true;
		}

		
		node = FindNearestNode(glm::vec3(s[1].x, s[1].y, s[1].z));
		if(node != NULL) {
			if(!used[node->getNodeId()]) {
				node->AddShape(s);
				used[node->getNodeId()] = true;
			}
		}

		node = FindNearestNode(glm::vec3(s[2].x, s[2].y, s[2].z));
		if(node != NULL) {
			if(!used[node->getNodeId()]) {
				node->AddShape(s);
				used[node->getNodeId()] = true;
			}
		}

		used.clear();

		++iter;
	}
}

OctreeNode* Octree::FindNearestNode(glm::vec3 point)
{
	OctreeNode *node = head;
	while(node->hasChildren()) {
		if(node->getBottomLeftNear()->Contains(point)) {
			node = node->getBottomLeftNear();
		} else if(node->getBottomLeftFar()->Contains(point)) {
			node = node->getBottomLeftFar();
		} else if(node->getBottomRightNear()->Contains(point)) {
			node = node->getBottomRightNear();
		} else if(node->getBottomRightFar()->Contains(point)) {
			node = node->getBottomRightFar();
		} else if(node->getTopLeftNear()->Contains(point)) {
			node = node->getTopLeftNear();
		} else if(node->getTopLeftFar()->Contains(point)) {
			node = node->getTopLeftFar();
		} else if(node->getTopRightNear()->Contains(point)) {
			node = node->getTopRightNear();
		} else if(node->getBottomRightFar()->Contains(point)) {
			node = node->getTopRightFar();
		} else {
			break;
		}
	}

	if(!node->hasChildren()) {
		return node;
	}

	return NULL;
}

void Octree::SplitTree(OctreeNode *node, int depthLevel)
{
	if(depthLevel >= mdepth) {
		return;
	}
	node->BuildChildren();
	depthLevel++;

	SplitTree(node->getBottomLeftNear(), depthLevel);
	SplitTree(node->getBottomLeftFar(), depthLevel);

	SplitTree(node->getBottomRightNear(), depthLevel);
	SplitTree(node->getBottomRightFar(), depthLevel);

	SplitTree(node->getTopLeftNear(), depthLevel);
	SplitTree(node->getTopLeftFar(), depthLevel);

	SplitTree(node->getTopRightNear(), depthLevel);
	SplitTree(node->getTopRightFar(), depthLevel);
}

std::list<glm::mat3x4> Octree::FindNearestShapes(glm::vec3 point)
{
	OctreeNode *node = FindNearestNode(point);
	std::list<glm::mat3x4> shapes = node->getShapes();
	return shapes;
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
}

Octree::~Octree(void)
{
}
