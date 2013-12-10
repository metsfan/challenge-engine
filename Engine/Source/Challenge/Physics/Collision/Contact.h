#pragma once

#include <Challenge/Challenge.h>

namespace challenge
{
	typedef std::vector<glm::vec3> TCollisionPointsList;
	class RigidBody;

	class Contact
	{
	public:
		Contact();
		void CalculateInternals(real duration);

		RigidBody *mObjects[2];
		glm::vec3 mContactPoint;
		glm::vec3 mRelativePositions[2];
		glm::vec3 mContactVelocity;
		real mDesiredDeltaVelocity;
		real mVelocityPerUnitImpulse;
		real mPenetration;
		glm::vec3 mImpulse;
		glm::vec3 mContactNormal;
		glm::mat3 mContactToWorld, mWorldToContact;

	private:
		void MakeOrthonormalBasis(glm::vec3 *x, glm::vec3 *y, glm::vec3 *z);
		real CalculateImplusePerUnit(real duration);
		real CalculateDesiredVelocity(real duration);
		glm::vec3 CalculateLocalVelocity(int index, real duration);
		void SwapBodies();
	};
};