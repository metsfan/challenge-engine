#pragma once

#include <Engine/Challenge.h>

namespace challenge
{
	class OctreeNode
	{
	public:
		OctreeNode(float minx, float maxx, float miny, float maxy, float minz, float maxz);
		void BuildChildren();
		bool Contains(glm::vec3 point);
		void AddShape(glm::mat3x4 shape);

		float getMinX() { return mminx; }
		float getMaxX() { return mmaxx; }
		float getMinY() { return mminy; }
		float getMaxY() { return mmaxy; }
		float getMinZ() { return mminz; }
		float getMaxZ() { return mmaxz; }

		OctreeNode* getTopLeftNear() { return mtln; }
		OctreeNode* getTopLeftFar() { return mtlf; }
		OctreeNode* getBottomLeftNear() { return mbln; }
		OctreeNode* getBottomLeftFar() { return mblf; }
		OctreeNode* getTopRightNear() { return mtrn; }
		OctreeNode* getTopRightFar() { return mtrf; }
		OctreeNode* getBottomRightNear() { return mbrn; }
		OctreeNode* getBottomRightFar() { return mbrf; }

		std::list<glm::mat3x4> getShapes() { return mshapes; }

		bool hasChildren() { return mhasChildren; }
		std::string getNodeId() { return mnodeId; }

	private:
		float mminx, mmaxx, mminy, mmaxy, mminz, mmaxz;
		std::list<glm::mat3x4> mshapes;
		OctreeNode *mtln, *mtlf, *mbln, *mblf, *mtrn, *mtrf, *mbrn, *mbrf;
		bool mhasChildren;
		std::string mnodeId;
	};

	class Octree
	{
	public:
		Octree(int depth);
		void BuildTree(std::list<glm::mat3x4> shapes);
		std::list<glm::mat3x4> FindNearestShapes(glm::vec3 point);
		OctreeNode* FindNearestNode(glm::vec3 point);
		void AddTriangle(glm::mat3x4 verts);
		~Octree(void);

		OctreeNode *head;
	

	private:
		void SplitTree(OctreeNode *node, int depthLevel);

		int mdepth;

	};
}


