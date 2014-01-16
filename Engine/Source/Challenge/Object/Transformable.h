#pragma once

#include <Challenge/Challenge.h>

namespace challenge
{
	class Transformable;

	class ITransformableListener
	{
	public:
		virtual void OnTransformChanged(Transformable *transformable) = 0;
	};

	class Transformable
	{
	public:
		Transformable() :
			mChanged(true),
			mScale(1)
		{
		}

		~Transformable()
		{
		}

		std::string GetType()
		{
			return "transform"; 
		}

		virtual void MoveBy(const glm::vec3 &position)
		{
			mPosition += position;
			mChanged = true;
		}

		virtual void MoveTo(const glm::vec3 &position)
		{
			mPosition = position;
			mChanged = true;
		}

		virtual void RotateBy(const glm::vec3 &rotate)
		{
			mRotation += rotate;
			mChanged = true;
		}

		virtual void RotateTo(const glm::vec3 &rotate)
		{
			mRotation = rotate;
			mChanged = true;
		}

		virtual void ScaleBy(const glm::vec3 &scale)
		{
			mScale *= scale;
			mChanged = true;
		}

		virtual void ScaleTo(const glm::vec3 &scale)
		{
			mScale = scale;
			mChanged = true;
		}

		const glm::vec3& GetPosition() { return mPosition; }
		const glm::vec3& GetRotation() { return mRotation; }
		const glm::vec3& GetScale() { return mScale; }
		const glm::mat4& GetTransform() { return mTransform; }

	protected:
		void Update(int deltaMillis);

	private:
		glm::vec3 mPosition;
		glm::vec3 mRotation;
		glm::vec3 mScale;

		bool mChanged;

		glm::mat4 mTransform;
	};
};