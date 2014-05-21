#pragma once

#include <Challenge/Challenge.h>
#include <Challenge/View/ActorParams.h>
#include <Challenge/Model/Model.h>
#include <Challenge/Network/Network.h>

namespace challenge
{

	class IActor
	{
	public:
		virtual ~IActor() { }

		virtual std::string GetType() = 0;

		virtual ActorParams* GetParams() = 0;

		virtual glm::mat4 GetTransform() = 0;
		virtual void SetTransform(glm::mat4 matrix) = 0;
	
		virtual ActorId GetId() = 0;
		virtual void SetId(ActorId id) = 0;

		virtual void OnUpdate(int deltaMillis) = 0;
		virtual void RotateY(float angle) = 0;

		virtual void SetPosition(glm::vec3 position) = 0;
		virtual glm::vec3 GetPosition() = 0;

		virtual void SetAngle(float angle) = 0;
		virtual float GetAngle() = 0;

		virtual void SetScale(float scale) = 0;
		virtual float GetScale() = 0;

		virtual Model *GetModel() = 0;
	};

	class Actor : public IActor, public INetworkObject
	{
	public:

		Actor();
		virtual ~Actor();

		virtual ActorParams* GetParams() { return mParams; }

		virtual std::string GetType() { return "Base"; }

		virtual glm::mat4 GetTransform() { return mTransform; }
		virtual void SetTransform(glm::mat4 matrix);

		virtual ActorId GetId() { return mId; }
		virtual void SetId(ActorId id) { mId = id; }

		virtual void OnUpdate(int deltaMillis);
		virtual void RotateY(float angle);

		void SetPosition(glm::vec3 position);
		glm::vec3 GetPosition() { return mPosition; }

		void SetAngle(float angle) { mXAngle = angle; }
		float GetAngle() { return mXAngle; }

		virtual void SetScale(float scale) { mScale = scale; }
		virtual float GetScale() { return mScale; };

		Model *GetModel() { return mModel; }

		/* INetworKObject methods */
		virtual void Serialize(std::stringstream &stream);
		virtual void Unserialize(std::stringstream &stream);

	protected:
		ActorId mId;
		std::string mNetworkId;
		ActorType mType;
		glm::mat4 mTransform;
		ActorParams* mParams;
		float mXAngle;
		float mYAngle;
		float mScale;
		glm::vec3 mPosition;
		Model *mModel;
	};
};