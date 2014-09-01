#pragma once

#include <Challenge/Challenge.h>
#include <Challenge/Physics/Shapes/GeometricShape.h>

namespace challenge
{
	enum CapsuleAxis
	{
		CapsuleAxisX,
		CapsuleAxisY,
		CapsuleAxisZ
	};

	class CapsuleShape : public GeometricShape
	{
	public:
		CapsuleShape(real radius, real height, CapsuleAxis axis = CapsuleAxisY);
		~CapsuleShape();

		GeometricShapeType GetType() const { return kShapeTypeCapsule; }

		static IGeometricShape* CreateFromPointsList(const std::vector<glm::vec3> & points);

		void SetPosition(glm::vec3 position);
		virtual glm::vec3 GetPosition() const;

		real GetRadius() { return mRadius; }
		real GetHeight() { return mHeight; }

		void DrawDebug(IGraphicsDevice *device, RenderState &state);

	private:
		real mRadius;
		real mHeight;
		CapsuleAxis mAxis;

		void UpdateShape();
		
	};
};