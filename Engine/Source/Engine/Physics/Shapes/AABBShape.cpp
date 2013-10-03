#include <Engine/Challenge.h>
#include <Engine/Physics/Shapes/Intersection.h>
#include "AABBShape.h"

namespace challenge
{
	IGeometricShape* AABBShape::CreateFromPointsList(const std::vector<glm::vec3> &points, const glm::mat4 &transform)
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

		return new AABBShape(min, max);
	}

	AABBShape::AABBShape(const glm::vec3 &center, real halfX, real halfY, real halfZ) :
		GeometricShape(),
		mCenter(center), 
		mDimensions(halfX, halfY, halfZ)
	{
	}

	AABBShape::AABBShape(AABBShape *other) :
		GeometricShape(other),
		mCenter(other->mCenter),
		mDimensions(other->mDimensions)
	{
	}

	AABBShape::AABBShape(const glm::vec3 &min, const glm::vec3 &max) :
		GeometricShape()
	{
		mDimensions = (max - min) * 0.5f;

		mCenter = (min + max) * 0.5f;
	}

	IGeometricShape* AABBShape::Clone()
	{
		return new AABBShape(*this);
	}

	bool AABBShape::Intersects(IGeometricShape *other, CollisionData *collision) const
	{
		GeometricShapeType otherType = other->GetType();
		bool intersects = false;

		if(otherType == kShapeTypeAABB) {
			AABBShape *aabb = static_cast<AABBShape *>(other);
			intersects = IntersectionTests::AABBIntersectsAABB(aabb, this, collision);
		} else if(otherType == kShapeTypePlane) {
			PlaneShape *plane = static_cast<PlaneShape *>(other);
			intersects = IntersectionTests::AABBIntersectsPlane(this, plane, collision);
		}

		return intersects;
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
		//BoundingBox bbox = GetBoundingBox();
		//glm::vec3 transformedCenter = glm::vec3(mTransform * glm::vec4(mCenter, 1.0));
		glm::vec3 transformedCenter = mPosition;
		BoundingBox bbox(transformedCenter.x - mDimensions.x, transformedCenter.y, transformedCenter.z - mDimensions.z, 
			transformedCenter.x + mDimensions.x, transformedCenter.y + (mDimensions.y * 2), transformedCenter.z + mDimensions.z);

		return ray.GetIntersection(bbox, t);
	}

	void AABBShape::CreateDebugShape(MeshShape *shape)
	{
		this->CalculateBoundingBox();
		/*BoundingBox bbox(mBoundingBox.mMin.x - mPosition.x, mBoundingBox.mMin.y - mPosition.y, mBoundingBox.mMin.z - mPosition.z,
			mBoundingBox.mMin.x + mPosition.x, mBoundingBox.mMin.y + mPosition.y, mBoundingBox.mMin.z + mPosition.z);*/
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
				bbox.mMin.x, bbox.mMin.y, bbox.mMax.z,
					color.x, color.y, color.z, color.w
			},
			{ 
				bbox.mMax.x, bbox.mMin.y, bbox.mMax.z,
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
				bbox.mMin.x, bbox.mMax.y, bbox.mMin.z,
					color.x, color.y, color.z, color.w
			},
			{ 
				bbox.mMin.x, bbox.mMax.y, bbox.mMin.z,
					color.x, color.y, color.z, color.w
			},
			{ 
				bbox.mMin.x, bbox.mMin.y, bbox.mMin.z,
					color.x, color.y, color.z, color.w
			},
			{ 
				bbox.mMin.x, bbox.mMin.y, bbox.mMin.z,
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
				bbox.mMin.x, bbox.mMax.y, bbox.mMin.z,
					color.x, color.y, color.z, color.w
			},
			{ 
				bbox.mMin.x, bbox.mMin.y, bbox.mMin.z,
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
			{ 
				bbox.mMax.x, bbox.mMax.y, bbox.mMax.z,
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

			
		};

		shape->SetData(verts, sizeof(verts), sizeof(verts) / sizeof(DebugLinesVertex), PrimitiveTypeLineStrip);
	}
}