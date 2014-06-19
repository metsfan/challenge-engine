#pragma once

#include <Challenge/Challenge.h>
#include <Challenge/Physics/Shapes/GeometricShape.h>


namespace challenge
{
	class Octree;
	class TriangleShape;

	class TriangleMeshShape : public GeometricShape
	{
	public:
		TriangleMeshShape();
		~TriangleMeshShape() {}

		virtual GeometricShapeType GetType() const { return kShapeTypeTriangleMesh; } 

		virtual void AddTriangle(const glm::vec3 &a, const glm::vec3 &b, const glm::vec3 &c);

		static IGeometricShape* CreateFromPointsList(const std::vector<glm::vec3> &points);

		void DrawDebug(IGraphicsDevice *device, RenderState &state);

		IGeometricShape* Clone();

	private:
		Octree *mDataTree;
		bool mTreeSet;

		btTriangleMesh mTriangles;

		mutable TriangleShape *mDebugTriangle;
	};
};