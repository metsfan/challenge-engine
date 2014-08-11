#include <Challenge/Challenge.h>
#include <Challenge/Physics/Shapes/CapsuleShape.h>

namespace challenge
{
	IGeometricShape* CapsuleShape::CreateFromPointsList(const std::vector<glm::vec3> & points)
	{
		glm::vec3 min(INFINITY);
		glm::vec3 max(-INFINITY);

		//glm::mat3 basis = glm::mat3(transform);
		//glm::mat4 finalTransform = glm::mat4(basis);

		for (auto pt : points) {
			//pt = glm::vec3(finalTransform * glm::vec4(pt, 1.0f));
			min.x = glm::min(pt.x, min.x);
			min.y = glm::min(pt.y, min.y);
			min.z = glm::min(pt.z, min.z);

			max.x = glm::max(pt.x, max.x);
			max.y = glm::max(pt.y, max.y);
			max.z = glm::max(pt.z, max.z);
		}

		glm::vec3 dims = (max - min);
		real radius = glm::min(dims.x, dims.z);
		real height = dims.y;
		return new CapsuleShape(radius, height);
	}

	CapsuleShape::CapsuleShape(real radius, real height, CapsuleAxis axis) :
		mRadius(radius),
		mHeight(height),
		mAxis(mAxis)
	{
		this->UpdateShape();
	}

	CapsuleShape::~CapsuleShape()
	{
	}

	void CapsuleShape::UpdateShape()
	{
		if (mCollisionShape) {
			delete mCollisionShape;
		}

		switch (mAxis)
		{
		case CapsuleAxisX:
			mCollisionShape = new btCapsuleShapeX(mRadius, mHeight);
			break;

		case CapsuleAxisZ:
			mCollisionShape = new btCapsuleShapeZ(mRadius, mHeight);
			break;

		default:
			mCollisionShape = new btCapsuleShape(mRadius, mHeight);
		}
		
		//mCollisionShape->setMargin(mHeight);
	}

	void CapsuleShape::DrawDebug(IGraphicsDevice *device, RenderState &state)
	{
		if (!mDebugShape) {
			mDebugShape = PrimitiveGenerator::CreatePrimitive(PrimitiveShapeBox);
		}

		glm::mat4 transform = glm::translate(glm::mat4(), mPosition);
		transform = glm::scale(transform, glm::vec3(mRadius, mHeight, mRadius));
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

	void CapsuleShape::SetPosition(glm::vec3 position)
	{
		//position.y -= mHeight * 0.5;
		mPosition = position;
	}

	glm::vec3 CapsuleShape::GetPosition() const
	{
		glm::vec3 position = mPosition;
		//position.y -= mHeight;

		return position;
	}

}