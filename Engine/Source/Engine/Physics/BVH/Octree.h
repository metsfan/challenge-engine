#pragma once

#include <Engine/Challenge.h>
#include <Engine/Physics/Shapes/PhysicsShape.h>
#include <Engine/Physics/PhysicsCore.h>

namespace challenge
{

	static const int TOP_LEFT_NEAR = 0, 
					 TOP_LEFT_FAR = 1, 
					 TOP_RIGHT_NEAR = 2, 
					 TOP_RIGHT_FAR = 3, 
					 BOTTOM_LEFT_NEAR = 4, 
					 BOTTOM_LEFT_FAR = 5, 
					 BOTTOM_RIGHT_NEAR = 6, 
					 BOTTOM_RIGHT_FAR = 7;

	class OctreeNode
	{
	public:
		OctreeNode(float minx, float maxx, float miny, float maxy, float minz, float maxz);
		void BuildChildren();
		bool Contains(glm::vec3 point);
		bool IntersectsShape(IPhysicsShape *shape);
		void AddShape(IPhysicsShape *shape);

		BoundingBox mBounds;
		TPhysicsShapeLinkedList mShapes;
		OctreeNode *mChildren[8];
		bool mHasChildren;
		std::string mNodeId;
	};

	typedef std::vector<OctreeNode *> TOctreeNodeList;

	class Octree
	{
	public:
		Octree(int depth);
		void BuildTree(TPhysicsShapeLinkedList shapes);
		TPhysicsShapeLinkedList FindNearestShapes(glm::vec3 point);
		TPhysicsShapeLinkedList FindNearestShapesToShape(IPhysicsShape *shape);
		//OctreeNode* FindNearestNode(glm::vec3 point);
		bool FindNearestNodesToShape(IPhysicsShape *shape, TOctreeNodeList *nodes, OctreeNode *node = NULL); 
		void AddShape(IPhysicsShape *shape);
		~Octree(void);

		OctreeNode *head;
	

	private:
		void SplitTree(OctreeNode *node, int depthLevel);

		int mdepth;

	};
}


