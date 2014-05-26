#pragma once

#include <Challenge/Challenge.h>
#include <Challenge/Object/Component/Component.h>
#include <Challenge/Object/Transformable.h>

namespace challenge
{
	class GameObject : public Transformable,
					   public ISerializable
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

		template <typename T>
		T * FindComponent()
		{
			for (IComponent *component : mComponents) {
				auto casted = dynamic_cast<T *>(component);
				if (casted) {
					return casted;
				}
			}

			return NULL;
		}

		void AddComponent(IComponent *component)
		{
			mComponents.push_back(component);
		}

		virtual void MoveBy(const glm::vec3 &position);
		virtual void MoveTo(const glm::vec3 &position);

		virtual void Serialize(ByteArrayOutputStream &stream);
		virtual void Unserialize(ByteArrayInputStream &stream);

		void Update(int deltaMillis);
		void Render(IGraphicsDevice *device, RenderState &state);

	private:
		std::vector<IComponent *> mComponents;
	};
};