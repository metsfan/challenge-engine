#include <time.h>
#include <Engine/GameApplicationWindows.h>
#include <Engine/UI/UIManager.h>
#include <Engine/UI/Controls/ButtonView.h>
#include <Engine/Util/Timer.h>
#include <Engine/Util/Logger.h>
#include <Engine/Model/Model.h>
#include <Engine/Renderer/RenderState.h>
#include <Engine/Renderer/Shape/ModelShape.h>
#include <Engine/Renderer/Shape/BoxShape.h>
#include <Engine/Renderer/Shape/SkyboxShape.h>
#include <Engine/Renderer/Lights/DirectionalLightSource.h>
#include <d3dx9math.h>
#include "MovementController.h"
using namespace challenge;

int APIENTRY _tWinMain(_In_ HINSTANCE hInstance,
                     _In_opt_ HINSTANCE hPrevInstance,
                     _In_ LPTSTR    lpCmdLine,
                     _In_ int       nCmdShow)
{
	Size screenSize(1280, 1024);
	GameApplicationWindows *app = new GameApplicationWindows(screenSize, hInstance);
	if(!app->Initialize()) {
		exit(0);
	}

	// Main message loop:
	HACCEL hAccelTable = LoadAccelerators(hInstance, MAKEINTRESOURCE(1));
	MSG msg;

	int desiredFPS = 60;
	int frameTime = 1000000000 / desiredFPS;
	SYSTEMTIME systemTime;

	glm::mat4 projection = glm::perspective(45.0f, screenSize.width / screenSize.height, 0.1f, 1000.0f);
	//D3DXMATRIX view;
	//D3DXMatrixTranslation(&view, 0, 0, -10);
	//glm::mat4 projection = glm::perspective(45.0f, 1280.0f / 1024.0f, 0.1f, 1000.0f);
	glm::mat4 view;
	view = glm::translate(view, glm::vec3(0.0f, 0.0f, 0.0f));
	//view = glm::rotate(view, 180.0f, 0.0f, 0.0f, 1.0f);

	view = glm::inverse(view);
	//view = glm::transpose(view);
	glm::mat4 vp = view * projection;

	IGraphicsDevice *device = app->GetGraphicsDevice();
	IGraphicsContext *context = device->GetContext();

	RenderState state;

	//BoxShape *shape = new BoxShape(app->GetGraphicsDevice(), 1.0f);
	std::vector<Model *> testModels;
	std::vector<ModelShape *> shapes;

	MovementController mover;
	app->AddKeyboardListener(&mover);

	for(int i = 0; i < 200; i++) {
		Model *testModel = app->CreateModel("C:/gamedev/engine-dev/Engine/ModelReader/Assets/dark_mage.model");
		//Model *testModel = app->CreatePrimitive(PrimitiveShapeSphere);
		testModel->SetActiveAnimation("idle", true);
		//testModel->SetAnimFrame(i);
		testModels.push_back(testModel);

		ModelShape *shape = new ModelShape(device, testModel);
		shapes.push_back(shape);
	}
	
	std::shared_ptr<Image> skyboxImage = std::shared_ptr<Image>(new Image("C:/gamedev/engine-dev/EngineDev/Renderer/Assets/skybox.jpg", true));
	SkyboxShape *skybox = new SkyboxShape(device, skyboxImage, app->CreatePrimitive(PrimitiveShapeSphere));
	
	int frames = 0;

	CTimer *timer = new CTimer(1000, [&](void *obj) {
		Logger::log(LogDebug, "FPS: %d", frames);
		frames = 0;
	}, NULL, true);
	bool done = false;
	float angle = 0;
	state.SetProjection(projection);
	glm::mat4 model = glm::translate(glm::mat4(), 0.0f, -1.0f, -5.0f);
	//model = glm::rotate(model, 180.0f, 0.0f, 0.0f, 1.0f);

	app->RunMainLoop([&](int deltaMillis) {},
	[&](int deltaMillis) {
		for(Model *testModel : testModels) {
			testModel->SetNextFrame(16);
		}
		
		angle += 1;
		//model = glm::rotate(model, 1.0f, 0.0f, 1.0f, 0.0f);
		//model = glm::translate(model, glm::vec3(0.0f, 0.0f, -0.01f));
		//glm::mat4 nModel = glm::transpose(model);
		view = glm::rotate(glm::mat4(), mover.GetAngle(), 0.0f, 1.0f, 0.0f);
		//view = glm::translate(view, mover.GetPosition());
		
		DirectionalLightSource light;
		light.SetDirection(glm::vec3(0.5, 0.5, 0.0));
		state.AddLight(&light);

		state.PushTransform(view);
		skybox->Draw(device, state);
		state.PopTransform();

		view = glm::translate(view, mover.GetPosition());
		glm::mat4 mvp = view * model;

		float i = 0;
		for(ModelShape *shape : shapes) {
			//LARGE_INTEGER start, end, freq;
			//QueryPerformanceFrequency(&freq);
			//QueryPerformanceCounter(&start);

			glm::mat4 nModel = model;
			nModel = glm::translate(nModel, i, 0.0f, 0.0f);
			glm::mat4 mvp = view * nModel;

			state.PushTransform(mvp);
			//shape->Draw(device, state);
			state.PopTransform();

			i+=0.1;

			//QueryPerformanceCounter(&end);

			//Logger::log(LogDebug, "Time: %ld", ((end.QuadPart - start.QuadPart) * 1000000) / freq.QuadPart);
		}

		

		state.RemoveLight(&light);

		frames++;
	});

	return 0;
}