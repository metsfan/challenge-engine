#include <Challenge/Challenge.h>
#include <Challenge/Object/GameObject.h>

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

		std::vector<IRenderableComponent *> renderables = this->FindComponents<IRenderableComponent>();
		for (IRenderableComponent *renderable : renderables) {
			renderable->Render(device, state);
		}

		state.PopTransform();
	}
}