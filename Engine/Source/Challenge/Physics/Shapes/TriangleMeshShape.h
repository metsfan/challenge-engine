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

		virtual bool Intersects(const IGeometricShape *other, CollisionData *collision = NULL) const;

		virtual bool Intersects(const AABBShape *aabb, CollisionData *collision = NULL) const;

		virtual bool Intersects(const OBBShape *obb, CollisionData *collision = NULL) const
		{
			return false;
		}

		virtual bool Intersects(const TriangleShape *triangle, CollisionData *collision = NULL) const
		{
			return false;
		}

		virtual bool Intersects(const TriangleMeshShape *mesh, CollisionData *collision = NULL) const
		{
			return false;
		}

		virtual bool RayIntersects(const Ray &ray, float &t) const;

		virtual void SetPosition(glm::vec3 position);

		virtual GeometricShapeType GetType() const { return kShapeTypeTriangleMesh; } 

		virtual void AddTriangle(const glm::vec3 &a, const glm::vec3 &b, const glm::vec3 &c);

		static IGeometricShape* CreateFromPointsList(const std::vector<glm::vec3> &points);

		void DrawDebug(IGraphicsDevice *device, RenderState &state);

		IGeometricShape* Clone();

	private:
		Octree *mDataTree;
		bool mTreeSet;
		std::vector<TriangleShape *> mTriangles;

		mutable TriangleShape *mDebugTriangle;
	};
};