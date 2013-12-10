#include <Challenge/Challenge.h>
#include <Challenge/Physics/Shapes/OBBShape.h>

namespace challenge
{
	IGeometricShape* OBBShape::CreateFromPointsList(const std::vector<glm::vec3> &points, const glm::mat4 &transform)
	{
		glm::vec3 min(INFINITY);
		glm::vec3 max(-INFINITY);

		for(auto pt : points) {
			pt = glm::vec3(transform * glm::vec4(pt, 1.0f));
			min.x = glm::min(pt.x, min.x);
			min.y = glm::min(pt.y, min.y);
			min.z = glm::min(pt.z, min.z);

			max.x = glm::max(pt.x, max.x);
			max.y = glm::max(pt.y, max.y);
			max.z = glm::max(pt.z, max.z);
		}

		return new OBBShape(BoundingBox(min, max), glm::mat3());
	}

	OBBShape::OBBShape(const glm::vec3 &center, const glm::vec3 &dimensions, const glm::mat3 &axes) :
		GeometricShape(),
		mCenter(center),
		mBaseCenter(mCenter),
		mDimensions(dimensions),
		mBaseDimensions(mDimensions),
		mAxes(axes)
	{
	}

	OBBShape::OBBShape(const BoundingBox &box, const glm::mat3 &axes) :
		mCenter((box.mMin + box.mMax) * 0.5f),
		mBaseCenter(mCenter),
		mDimensions((box.mMax - box.mMin) * 0.5f),
		mBaseDimensions(mDimensions),
		mAxes(axes)
	{
	}

	OBBShape::OBBShape(OBBShape *other) :
		GeometricShape(other),
		mCenter(other->mCenter),
		mBaseCenter(mCenter),
		mDimensions(other->mDimensions),
		mBaseDimensions(mDimensions),
		mAxes(other->mAxes)
	{
	}

	bool OBBShape::Intersects(IGeometricShape *other, CollisionData *collision) const
	{
		return false;
	}

	bool OBBShape::RayIntersects(const Ray &ray, float &t) const
	{
		glm::vec3 tOrigin = mAxes * (ray.GetOrigin() - this->GetPosition());
		glm::vec3 tDirection = mAxes * ray.GetDirection();
		Ray translatedRay(tOrigin, tDirection);

		glm::vec3 min = mCenter - mDimensions;
		glm::vec3 max = mCenter + mDimensions;
		return translatedRay.GetIntersection(BoundingBox(-mDimensions, mDimensions), t);
	}

	void OBBShape::SetTransform(const glm::mat4 &transform)
	{
		GeometricShape::SetTransform(transform);

		glm::mat3 basis(transform);
		mAxes = glm::mat3(basis);

		mAxes = glm::transpose(mAxes);

		glm::vec3 scale(glm::length(mAxes[0]), glm::length(mAxes[1]), glm::length(mAxes[2]));

		mAxes[0] = glm::normalize(mAxes[0]);
		mAxes[1] = glm::normalize(mAxes[1]);
		mAxes[2] = glm::normalize(mAxes[2]);

		mAxes = glm::transpose(mAxes);

		mCenter = basis * mBaseCenter;
		mDimensions = mBaseDimensions * scale;		
	}

	void OBBShape::DrawDebug(IGraphicsDevice *device, RenderState &state)
	{
		if(!mDebugShape) {
			mDebugShape = PrimitiveGenerator::CreatePrimitive(PrimitiveShapeBox);
		}

		glm::mat4 transform = glm::translate(glm::mat4(), this->GetPosition());
		transform *= glm::mat4(mAxes);
		transform = glm::scale(transform, this->GetDimensions() * 2.0f);
		
		state.PushTransform(transform);

		glm::vec4 color(1, 0, 0, 0.5);
		ShaderDataVector4 colorData(&color, 1);
		state.SetShaderData("COLOR", &colorData);
		device->EnableState(GraphicsState::AlphaBlending);

		mDebugShape->Render(device, state);

		glm::vec4 clearColor(0, 0, 0, 0);
		ShaderDataVector4 clearColorData(&clearColor, 1);
		state.SetShaderData("COLOR", &clearColorData);

		state.PopTransform();
		device->DisableState(GraphicsState::AlphaBlending);
	}
};