#include <Challenge/Challenge.h>
//#include <Challenge/Physics/Shapes/Intersection.h>
#include <Challenge/Physics/Shapes/TriangleShape.h>

#include <BulletCollision/CollisionShapes/btTriangleShape.h>

namespace challenge
{
	TriangleShape::TriangleShape(glm::vec3 a, glm::vec3 b, glm::vec3 c) :
		mTriangle(a, b, c)
	{
		//this->CalculateNormal();
		this->UpdateShape();
	}

	bool TriangleShape::Intersects(IGeometricShape *other, CollisionData *collision) const
	{
		return false;
	}

	bool TriangleShape::RayIntersects(const Ray &ray, float &t) const
	{
		Triangle translated;
		translated[0] = mTriangle[0] + this->GetPosition();
		translated[1] = mTriangle[1] + this->GetPosition();
		translated[2] = mTriangle[2] + this->GetPosition();

		return ray.GetIntersection(translated, t);
	}

	void TriangleShape::UpdateShape()
	{
		if (mCollisionShape) {
			delete mCollisionShape;
		}

		mCollisionShape = new btTriangleShape(ToBullet(mTriangle[0]), ToBullet(mTriangle[1]), ToBullet(mTriangle[2]));
	}
	
	void TriangleShape::DrawDebug(IGraphicsDevice *device, RenderState &state)
	{
		if (!mDebugShape) {
			std::vector<ModelVertex> verts;
			for (int i = 0; i < 3; i++) {
				ModelVertex vert;
				vert.position[0] = mTriangle.GetPoint(i).x;
				vert.position[1] = mTriangle.GetPoint(i).y;
				vert.position[2] = mTriangle.GetPoint(i).z;

				verts.push_back(vert);
			}

			mDebugShape = new Model(verts);
		}

		mDebugShape->SetBlendColor(glm::vec4(1, 0, 0, 1));
		mDebugShape->Render(device, state);
	}
};
