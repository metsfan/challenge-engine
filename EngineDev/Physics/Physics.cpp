// Physics.cpp : Defines the entry point for the application.
//

#include "stdafx.h"
#include "Physics.h"

#include <Challenge/Challenge.h>
#include <Challenge/Platform/Win32/CWindow.h>
#include <Challenge/Renderer/Shape/CubeShape.h>
#include <Challenge/Util/PrimitiveGenerator.h>

#include <Challenge/Physics/PhysicsWorld.h>

using namespace challenge;

class PhysicsTesting : public IApplicationListener
{

public:
	void PhysicsTesting::OnApplicationInitialized(GameApplication *app)
	{
		mEnvironment = new Model("molten_chasm.model");
		mCamera = new PerspectiveCamera(1.3, 45, 1.0, 1000.0, app->GetScreenSize());

		mCamera->MoveBy(glm::vec3(-390, -65, 80));
		//mCamera->Rotate(-90, glm::vec3(0, 1, 0));

		// The world.
		mPhysicsWorld = new PhysicsWorld();
		mPhysicsWorld->SetGravity(glm::vec3(0, -10, 0));

		TriangleMeshShape *mesh = dynamic_cast<TriangleMeshShape *>(mEnvironment->CreateBoundingVolume(kShapeTypeTriangleMesh, glm::mat4()));

		PhysicsObject *envObj = new PhysicsObject(mesh);
		mPhysicsWorld->AddObject(envObj);

		mBoxPosition = glm::vec3(-380, -20, 16);

		BoxShape *boxShape = new BoxShape(glm::vec3(5, 5, 5));
		mBoxBody = new PhysicsObject(boxShape);
		//mBoxBody->SetAcceleration(glm::vec3(10, 0, 0));
		mBoxBody->SetPosition(mBoxPosition);
		mBoxBody->SetMass(1);
		
		//mBoxBody->translate(btVector3(mBoxPosition.x, mBoxPosition.y, mBoxPosition.z));
		mPhysicsWorld->AddObject(mBoxBody);

		mBoxShape = NULL;
	}

	void PhysicsTesting::OnApplicationDestroyed(GameApplication *app)
	{

	}

	void PhysicsTesting::OnApplicationUpdate(GameApplication *app, uint32_t deltaMillis)
	{
		mCamera->Update();

		float step = (float)deltaMillis / 1000.0f;
		mPhysicsWorld->Update(step);

		mBoxPosition = mBoxBody->GetPosition();

		Logger::Log(LogDebug, "Position: %f, %f, %f", mBoxPosition.x, mBoxPosition.y, mBoxPosition.z);
	}

	void PhysicsTesting::OnApplicationRender(GameApplication *app, IGraphicsDevice *device)
	{
		if (!mBoxShape) {
			mBoxShape = PrimitiveGenerator::CreatePrimitive(PrimitiveShapeBox);

			mColorIndex = device->GetContext()->GetGlobalIndex("COLOR");
			mDiffuseTexIndex = device->GetContext()->GetGlobalIndex("DIFFUSE_TEXTURE");
		}

		RenderState state;

		device->EnableState(DepthTest);

		state.SetProjection(mCamera->GetProjectionMatrix());
		state.PushTransform(mCamera->GetInverseViewMatrix());

		mEnvironment->Render(device, state);

		glm::mat4 transform = glm::translate(glm::mat4(), mBoxPosition);
		transform = glm::scale(transform, glm::vec3(5.0) *2.0f);
		state.PushTransform(transform);

		glm::vec4 color(1, 0, 0, 1);
		state.SetShaderData(mColorIndex, &color);
		state.SetShaderData(mDiffuseTexIndex, NULL);
		device->EnableState(GraphicsState::AlphaBlending);

		mBoxShape->Render(device, state);

		glm::vec4 clearColor(0, 0, 0, 0);
		state.SetShaderData(mColorIndex, &clearColor);

		state.PopTransform();
	}

	Model *mEnvironment;
	PerspectiveCamera *mCamera;

	PhysicsObject *mBoxBody;
	Model *mBoxShape;
	glm::vec3 mBoxPosition;

	int mColorIndex;
	int mDiffuseTexIndex;

	PhysicsWorld *mPhysicsWorld;

};

int APIENTRY _tWinMain(_In_ HINSTANCE hInstance,
                     _In_opt_ HINSTANCE hPrevInstance,
                     _In_ LPTSTR    lpCmdLine,
                     _In_ int       nCmdShow)
{
	auto physics = std::make_shared<PhysicsTesting>();

	CWindow *window = new CWindow(hInstance, "Physics Testing", Size(1280, 1024), physics);
	if (!window->Initialize()) {
		return -1;
	}

	window->SetWindowVisibility(WindowVisible);
	return window->StartMainLoop();
}
