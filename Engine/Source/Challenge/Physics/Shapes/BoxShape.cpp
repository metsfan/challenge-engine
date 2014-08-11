#include <Challenge/Challenge.h>
//#include <Challenge/Physics/Shapes/Intersection.h>
#include <Challenge/Physics/Shapes/BoxShape.h>

#include <btBulletDynamicsCommon.h>

namespace challenge
{
	IGeometricShape* BoxShape::CreateFromPointsList(const std::vector<glm::vec3> &points, const glm::mat4 &transform)
	{
		glm::vec3 min(INFINITY);
		glm::vec3 max(-INFINITY);

		glm::mat3 basis = glm::mat3(transform);
		glm::mat4 finalTransform = glm::mat4(basis);

		for(auto pt : points) {
			pt = glm::vec3(finalTransform * glm::vec4(pt, 1.0f));
			min.x = glm::min(pt.x, min.x);
			min.y = glm::min(pt.y, min.y);
			min.z = glm::min(pt.z, min.z);

			max.x = glm::max(pt.x, max.x);
			max.y = glm::max(pt.y, max.y);
			max.z = glm::max(pt.z, max.z);
		}

		return new BoxShape(BoundingBox(min, max));
	}

	BoxShape::BoxShape(const glm::vec3 &dimensions) :
		GeometricShape(),
		mDimensions(dimensions)
	{
		this->UpdateShape();
	}

	BoxShape::BoxShape(BoxShape *other) :
		GeometricShape(other),
		mDimensions(other->mDimensions)
	{
		this->UpdateShape();
	}

	BoxShape::BoxShape(const BoundingBox &box) :
		GeometricShape()
	{
		mDimensions = (box.mMax - box.mMin) * 0.5f;
		this->UpdateShape();
	}

	bool BoxShape::RayIntersects(const Ray &ray, float &t) const
	{
		return ray.GetIntersection(this->GetBoundingBox(), t);
	}

	void BoxShape::UpdateShape()
	{
		if (mCollisionShape != NULL) {
			delete mCollisionShape;
		}

		mCollisionShape = new btBoxShape(ToBullet(mDimensions));
		mCollisionShape->setMargin(0);
	}

	//void BoxShape::CreateDebugShape(MeshShape *shape, RenderState &state)
	void BoxShape::DrawDebug(IGraphicsDevice *device, RenderState &state)
	{
		if(!mDebugShape) {
			mDebugShape = PrimitiveGenerator::CreatePrimitive(PrimitiveShapeBox);
		}

		glm::mat4 transform = glm::translate(glm::mat4(), this->GetPosition());
		transform = glm::scale(transform, mDimensions * 2.0f);
		state.PushTransform(transform);

		glm::vec4 color(1, 0, 0, 0.5);
		state.SetShaderData(device->GetContext()->GetGlobalIndex("COLOR"), &color);
		state.SetShaderData(device->GetContext()->GetGlobalIndex("DIFFUSE_TEXTURE"), NULL);
		device->EnableState(GraphicsState::AlphaBlending);

		mDebugShape->Render(device, state);

		glm::vec4 clearColor(0, 0, 0, 0);
		state.SetShaderData(device->GetContext()->GetGlobalIndex("COLOR"), &clearColor);

		state.PopTransform();
		device->DisableState(GraphicsState::AlphaBlending);
	}
}