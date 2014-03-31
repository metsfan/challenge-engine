#pragma once

#include <Challenge/Challenge.h>

namespace challenge
{
	class GameObject;

	class IComponent
	{
	public:
		virtual std::string GetType() = 0;

		virtual void Update(int deltaMillis) = 0;
	};

	class BaseComponent : public IComponent
	{
	public:
		BaseComponent(GameObject *owner) :
			mOwner(owner)
		{
		}

		virtual void Update(int deltaMillis)
		{
		}

		GameObject * GetOwner() { return mOwner; }

	private:
		GameObject *mOwner;
	};

	class RenderableComponent : public BaseComponent
	{
	public:
		RenderableComponent(GameObject *owner) :
			BaseComponent(owner)
		{
		}

		virtual void Render(IGraphicsDevice *device, RenderState &state) = 0;
	};
};