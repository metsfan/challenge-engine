#include <Challenge/Challenge.h>
#include <Challenge/Object/GameObject.h>
#include <Challenge/Object/Component/PhysicsComponent.h>

namespace challenge
{
	void GameObject::Update(int deltaMillis)
	{
		Transformable::Update(deltaMillis);

		for (IComponent *component : mComponents) {
			component->Update(deltaMillis);
		}
	}

	void GameObject::Render(IGraphicsDevice *device, RenderState &state)
	{
		state.PushTransform(this->GetTransform());

		auto renderables = this->FindComponents<RenderableComponent>();
		for (RenderableComponent *renderable : renderables) {
			renderable->Render(device, state);
		}

		state.PopTransform();

		auto physicsComponent = this->FindComponent<PhysicsComponent>();
		if (physicsComponent) {
			physicsComponent->GetPhysicsObject()->DrawDebug(device, state);
		}
		
	}

	void GameObject::MoveBy(const glm::vec3 &position)
	{
		Transformable::MoveBy(position);

		auto physicsComponent = this->FindComponent<PhysicsComponent>();
		if (physicsComponent) {
			physicsComponent->GetPhysicsObject()->MoveBy(position);
		}
	}

	void GameObject::MoveTo(const glm::vec3 &position)
	{
		Transformable::MoveTo(position);

		auto physicsComponent = this->FindComponent<PhysicsComponent>();
		if (physicsComponent) {
			physicsComponent->GetPhysicsObject()->SetPosition(position);
		}
	}
}