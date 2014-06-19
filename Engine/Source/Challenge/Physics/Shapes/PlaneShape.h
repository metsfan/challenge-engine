#pragma once

#include <Challenge/Challenge.h>
#include <Challenge/Physics/Shapes/GeometricShape.h>

namespace challenge
{
	class PlaneShape : public GeometricShape
	{
	public:
		PlaneShape() : GeometricShape() {}
		PlaneShape(glm::vec4 components);
		virtual bool Intersects(IGeometricShape *other, CollisionData *collision = NULL) const;

		GeometricShapeType GetType() const { return kShapeTypePlane; }

		void SetNormal(const glm::vec3 &normal)
		{
			mNormal = normal;
			mComponents = glm::vec4(normal, mComponents.w);

			this->UpdateShape();
		}

		const glm::vec3& GetNormal() const { return mNormal; }

		void SetD(real D)
		{
			mComponents.w = D;

			this->UpdateShape();
		}

		real GetD() const { return mComponents.w; }

		void SetPlane(const glm::vec4 &plane)
		{
			mComponents = plane;
			mNormal = glm::vec3(plane);

			this->UpdateShape();
		}

		const glm::vec4& GetPlane() const { return mComponents; }

	private:
		glm::vec4 mComponents;
		glm::vec3 mNormal;

		void UpdateShape();
	};
};