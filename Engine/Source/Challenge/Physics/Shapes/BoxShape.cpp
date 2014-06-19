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
	}

	BoxShape::BoxShape(BoxShape *other) :
		GeometricShape(other),
		mDimensions(other->mDimensions)
	{
	}

	BoxShape::BoxShape(const BoundingBox &box) :
		GeometricShape()
	{
		mDimensions = (box.mMax - box.mMin) * 0.5f;
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

		mCollisionShape = new btBoxShape(btVector3(mDimensions.x, mDimensions.y, mDimensions.z));
	}

	//void BoxShape::CreateDebugShape(MeshShape *shape, RenderState &state)
	void BoxShape::DrawDebug(IGraphicsDevice *device, RenderState &state)
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