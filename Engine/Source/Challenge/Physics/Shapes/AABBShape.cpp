#include <Challenge/Challenge.h>
//#include <Challenge/Physics/Shapes/Intersection.h>
#include "AABBShape.h"

namespace challenge
{
	IGeometricShape* AABBShape::CreateFromPointsList(const std::vector<glm::vec3> &points, const glm::mat4 &transform)
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

		return new AABBShape(BoundingBox(min, max));
	}

	AABBShape::AABBShape(const glm::vec3 &center, const glm::vec3 &dimensions) :
		GeometricShape(),
		mCenter(center), 
		mDimensions(dimensions)
	{
	}

	AABBShape::AABBShape(AABBShape *other) :
		GeometricShape(other),
		mCenter(other->mCenter),
		mDimensions(other->mDimensions)
	{
	}

	AABBShape::AABBShape(const BoundingBox &box) :
		GeometricShape()
	{
		mDimensions = (box.mMax - box.mMin) * 0.5f;

		mCenter = (box.mMin + box.mMax) * 0.5f;
	}

	glm::mat3 AABBShape::CalculateInertiaTensor(float mass)
	{
		float a = (1.0f / 12.0f) * mass;

		float dx = mDimensions.x * 2;
		float dy = mDimensions.y * 2;
		float dz = mDimensions.z * 2;

		float dx2 = dx * dx;
		float dy2 = dy * dy;
		float dz2 = dz * dz;

		float x = a * (dy2 + dz2);
		float y = a * (dx2 + dz2);
		float z = a * (dx2 + dy2);

		return glm::mat3(
			x, 0.0f, 0.0f,
			0.0f, y, 0.0f,
			0.0f, 0.0f, z
			);                                                           
	}

	bool AABBShape::RayIntersects(const Ray &ray, float &t) const
	{
		return ray.GetIntersection(this->GetBoundingBox(), t);
	}

	//void AABBShape::CreateDebugShape(MeshShape *shape, RenderState &state)
	void AABBShape::DrawDebug(IGraphicsDevice *device, RenderState &state)
	{
		if(!mDebugShape) {
			mDebugShape = PrimitiveGenerator::CreatePrimitive(PrimitiveShapeBox);
		}

		/*glm::mat4 transform = glm::translate(glm::mat4(), this->GetPosition());
		transform = glm::scale(transform, mDimensions * 2.0f);
		state.PushTransform(transform);

		glm::vec4 color(1, 0, 0, 0.5);
		ShaderDataVector4 colorData(&color, 1);
		state.SetShaderData("COLOR", &colorData);
		state.SetShaderData("DIFFUSE_TEXTURE", NULL);
		device->EnableState(GraphicsState::AlphaBlending);

		mDebugShape->Render(device, state);

		glm::vec4 clearColor(0, 0, 0, 0);
		ShaderDataVector4 clearColorData(&clearColor, 1);
		state.SetShaderData("COLOR", &clearColorData);

		state.PopTransform();
		device->DisableState(GraphicsState::AlphaBlending);*/

		/*this->CalculateBoundingBox();
		//glm::vec3 transformedCenter = glm::vec3(mTransform * glm::vec4(mCenter, 1.0));
		glm::vec3 transformedCenter = mPosition;
		BoundingBox bbox(transformedCenter.x - mDimensions.x, transformedCenter.y, transformedCenter.z - mDimensions.z, 
			transformedCenter.x + mDimensions.x, transformedCenter.y + (mDimensions.y * 2), transformedCenter.z + mDimensions.z);
		glm::vec4 color(1, 0, 0, 1);
		DebugLinesVertex verts[] = {
			{ 
				bbox.mMin.x, bbox.mMin.y, bbox.mMin.z,
					color.x, color.y, color.z, color.w
			},
			{ 
				bbox.mMin.x, bbox.mMax.y, bbox.mMin.z,
					color.x, color.y, color.z, color.w
			},
			{ 
				bbox.mMin.x, bbox.mMax.y, bbox.mMin.z,
					color.x, color.y, color.z, color.w
			},
			{ 
				bbox.mMax.x, bbox.mMax.y, bbox.mMin.z,
					color.x, color.y, color.z, color.w
			},
			{ 
				bbox.mMax.x, bbox.mMax.y, bbox.mMin.z,
					color.x, color.y, color.z, color.w
			},
			{ 
				bbox.mMax.x, bbox.mMin.y, bbox.mMin.z,
					color.x, color.y, color.z, color.w
			},
			{ 
				bbox.mMax.x, bbox.mMin.y, bbox.mMin.z,
					color.x, color.y, color.z, color.w
			},
			{ 
				bbox.mMin.x, bbox.mMin.y, bbox.mMin.z,
					color.x, color.y, color.z, color.w
			},
			
			{ 
				bbox.mMin.x, bbox.mMin.y, bbox.mMax.z,
					color.x, color.y, color.z, color.w
			},
			{ 
				bbox.mMin.x, bbox.mMax.y, bbox.mMax.z,
					color.x, color.y, color.z, color.w
			},
			{ 
				bbox.mMin.x, bbox.mMax.y, bbox.mMax.z,
					color.x, color.y, color.z, color.w
			},
			{ 
				bbox.mMax.x, bbox.mMax.y, bbox.mMax.z,
					color.x, color.y, color.z, color.w
			},
			{ 
				bbox.mMax.x, bbox.mMax.y, bbox.mMax.z,
					color.x, color.y, color.z, color.w
			},
			{ 
				bbox.mMax.x, bbox.mMin.y, bbox.mMax.z,
					color.x, color.y, color.z, color.w
			},
			{ 
				bbox.mMax.x, bbox.mMin.y, bbox.mMax.z,
					color.x, color.y, color.z, color.w
			},
			{ 
				bbox.mMin.x, bbox.mMin.y, bbox.mMax.z,
					color.x, color.y, color.z, color.w
			},

			{ 
				bbox.mMin.x, bbox.mMin.y, bbox.mMin.z,
					color.x, color.y, color.z, color.w
			},
			{ 
				bbox.mMin.x, bbox.mMin.y, bbox.mMax.z,
					color.x, color.y, color.z, color.w
			},

			{ 
				bbox.mMin.x, bbox.mMax.y, bbox.mMin.z,
					color.x, color.y, color.z, color.w
			},
			{ 
				bbox.mMin.x, bbox.mMax.y, bbox.mMax.z,
					color.x, color.y, color.z, color.w
			},

			{ 
				bbox.mMax.x, bbox.mMax.y, bbox.mMin.z,
					color.x, color.y, color.z, color.w
			},
			{ 
				bbox.mMax.x, bbox.mMax.y, bbox.mMax.z,
					color.x, color.y, color.z, color.w
			},

			{ 
				bbox.mMax.x, bbox.mMin.y, bbox.mMin.z,
					color.x, color.y, color.z, color.w
			},
			{ 
				bbox.mMax.x, bbox.mMin.y, bbox.mMax.z,
					color.x, color.y, color.z, color.w
			},
		};

		shape->SetData(verts, sizeof(verts), sizeof(verts) / sizeof(DebugLinesVertex), PrimitiveTypeLineList);*/
	}
}