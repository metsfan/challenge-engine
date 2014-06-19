// Physics.cpp : Defines the entry point for the application.
//

#include "stdafx.h"
#include "Physics.h"

#include <Challenge/Challenge.h>
#include <Challenge/Platform/Win32/CWindow.h>
#include <Challenge/Renderer/Shape/BoxShape.h>
#include <Challenge/Util/PrimitiveGenerator.h>

#include <btBulletDynamicsCommon.h>

using namespace challenge;

class PhysicsTesting : public IApplicationListener
{

public:
	void PhysicsTesting::OnApplicationInitialized(GameApplication *app)
	{
		mEnvironment = new Model("molten_chasm.model");
		mCamera = new PerspectiveCamera(1.3, 45, 1.0, 1000.0, app->GetScreenSize());

		mCamera->MoveTo(glm::vec3(-380, -45, 120));

		// Build the broadphase
		btBroadphaseInterface* broadphase = new btDbvtBroadphase();

		// Set up the collision configuration and dispatcher
		btDefaultCollisionConfiguration* collisionConfiguration = new btDefaultCollisionConfiguration();
		btCollisionDispatcher* dispatcher = new btCollisionDispatcher(collisionConfiguration);

		// The actual physics solver
		btSequentialImpulseConstraintSolver* solver = new btSequentialImpulseConstraintSolver;

		// The world.
		mPhysicsWorld = new btDiscreteDynamicsWorld(dispatcher, broadphase, solver, collisionConfiguration);
		mPhysicsWorld->setGravity(btVector3(0, -10, 0));

		TriangleMeshShape *mesh = dynamic_cast<TriangleMeshShape *>(mEnvironment->CreateBoundingVolume(kShapeTypeTriangleMesh, glm::mat4()));

		
		btTriangleMesh *envMesh = new btTriangleMesh();
		auto &tris = mesh->GetTriangles();

		for (auto tri : tris) {
			const Triangle &shape = tri->GetTriangle();
			btVector3 v1(shape[0].x, shape[0].y, shape[0].z);
			btVector3 v2(shape[1].x, shape[1].y, shape[1].z);
			btVector3 v3(shape[2].x, shape[2].y, shape[2].z);
			envMesh->addTriangle(v1, v2, v3);
		}

		btBvhTriangleMeshShape *environmentShape = new btBvhTriangleMeshShape(envMesh, true);

		btDefaultMotionState *envMotionState = new btDefaultMotionState();
		
		btRigidBody::btRigidBodyConstructionInfo envObjInfo(0, envMotionState, environmentShape);
		btRigidBody *envObj = new btRigidBody(envObjInfo);
		mPhysicsWorld->addRigidBody(envObj);

		mBoxPosition = glm::vec3(-380, -20, 16);

		btBoxShape *boxShape = new btBoxShape(btVector3(5, 5, 5));
		boxShape->calculateLocalInertia(1, btVector3(0, 0, 0));
		btTransform transform(btTransform(btQuaternion(0, 0, 0, 1), btVector3(mBoxPosition.x, mBoxPosition.y, mBoxPosition.z)));
		btDefaultMotionState *boxMotionState = new btDefaultMotionState(transform);
		btRigidBody::btRigidBodyConstructionInfo boxObjInfo(1, boxMotionState, boxShape);
		mBoxBody = new btRigidBody(boxObjInfo);
		//mBoxBody->translate(btVector3(mBoxPosition.x, mBoxPosition.y, mBoxPosition.z));
		mPhysicsWorld->addRigidBody(mBoxBody);

		mBoxShape = NULL;
	}

	void PhysicsTesting::OnApplicationDestroyed(GameApplication *app)
	{

	}

	void PhysicsTesting::OnApplicationUpdate(GameApplication *app, uint32_t deltaMillis)
	{
		mCamera->Update();

		float step = (float)deltaMillis / 1000.0f;
		mPhysicsWorld->stepSimulation(1 / 60.f, 10);

		btTransform trans;
		mBoxBody->getMotionState()->getWorldTransform(trans);
		btVector3 position = trans.getOrigin();
		mBoxPosition = glm::vec3(position.x(), position.y(), position.z());

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

	btRigidBody *mBoxBody;
	Model *mBoxShape;
	glm::vec3 mBoxPosition;

	int mColorIndex;
	int mDiffuseTexIndex;

	btDiscreteDynamicsWorld *mPhysicsWorld;

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
