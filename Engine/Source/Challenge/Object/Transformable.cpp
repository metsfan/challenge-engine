#include <Challenge/Challenge.h>
#include <Challenge/Object/Transformable.h>

namespace challenge
{
	void Transformable::Update(int deltaMillis)
	{
		//if (mChanged) {
			mTransform = glm::translate(glm::mat4(), mPosition);

			mTransform = glm::rotate(mTransform, mRotation.z, glm::vec3(0, 0, 1));
			mTransform = glm::rotate(mTransform, mRotation.x, glm::vec3(1, 0, 0));
			mTransform = glm::rotate(mTransform, mRotation.y, glm::vec3(0, 1, 0));

			mTransform = glm::scale(mTransform, mScale);

			mChanged = false;
		//}
	}

	void Transformable::Serialize(ByteArrayOutputStream &stream)
	{
		stream << mPosition;
		stream << mRotation;
		stream << mScale;
	}

	void Transformable::Unserialize(ByteArrayInputStream &stream)
	{
		stream >> mPosition;
		stream >> mRotation;
		stream >> mScale;

		//Logger::Log(LogDebug, "Position: %f, %f, %f", mPosition.x, mPosition.y, mPosition.z);

		mChanged = true;
		mTestPos = mPosition;
	}
}
