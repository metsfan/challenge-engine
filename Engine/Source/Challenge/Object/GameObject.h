#pragma once

#include <Challenge/Challenge.h>
#include <Challenge/Object/Component/Component.h>
#include <Challenge/Object/Transformable.h>

namespace challenge
{
	class GameObject : public Transformable
	{
	public:
		GameObject()
		{
		}

		virtual ~GameObject()
		{
		}

		template <typename T>
		std::vector<T *> FindComponents()
		{
			std::vector<T *> components;

			for (IComponent *component : mComponents) {
				auto casted = dynamic_cast<T *>(component);
				if (casted) {
					components.push_back(casted);
				}
			}

			return components;
		}

		void AddComponent(IComponent *component)
		{
			mComponents.push_back(component);
		}

		void Update(int deltaMillis);
		void Render(IGraphicsDevice *device, RenderState &state);

	private:
		std::vector<IComponent *> mComponents;
	};
};