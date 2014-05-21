#include <Challenge/Challenge.h>
#include <Challenge/Renderer/Shape/CircleShape.h>

namespace challenge
{
	MeshShape *CircleShape::sMesh = NULL;

	CircleShape::CircleShape(IGraphicsDevice *device) :
		Shape(device, "circle"),
		mRadius(0)
	{
	}

	CircleShape::~CircleShape()
	{
	}

	void CircleShape::Draw(IGraphicsDevice *device, RenderState &state)
	{
		if (!sMesh) {
			sMesh = new MeshShape(device, "Circle");

			float data[] = {
				-0.5, 0, -0.5, 0, 0,
				-0.5, 0, 0.5, 0, 1,
				0.5, 0, -0.5, 1, 0,
				0.5, 0, 0.5, 1, 1,
			};

			sMesh->SetData(&data[0], sizeof(data), 4, PrimitiveTypeTriangleStrip);
		}

		/*ShaderDataVector4 circleColor(&mColor, 1);
		state.SetShaderData("COLOR", &circleColor);

		glm::mat4 model = glm::translate(glm::mat4(), mPosition);
		model = glm::scale(model, glm::vec3(mRadius.x, 1.0f, mRadius.y));
		state.PushTransform(model);

		device->EnableState(AlphaBlending);
		sMesh->Draw(device, state);
		device->DisableState(AlphaBlending);

		state.PopTransform();*/
	}
}