#include <Challenge/Challenge.h>
#include "SkyboxShape.h"
#include <Challenge/Model/ModelMesh.h>
#include <Challenge/Util/CubeMapReader.h>
#include <Challenge/Renderer/Shader/ShaderProgram.h>
#include <Challenge/Renderer/Texture.h>
#include <Challenge/Renderer/ShaderData.h>
#include <Challenge/Renderer/Effect.h>

namespace challenge
{
	SkyboxShape::SkyboxShape(IGraphicsDevice *device, std::shared_ptr<Image> cubeMap, Model *skyboxModel) :
		Shape(device, "skybox"),
		mSkyboxModel(skyboxModel)
	{
		CubeMapReader cubeReader(cubeMap);

		TEXTURE_DESC desc;
		mTexture = device->CreateTextureCube(desc);
		mTexture->Initialize(cubeReader.GetBuffer(), cubeReader.GetFaceSize());

		int size = 5;

		/*SkyboxVertex vertex_data[] = {
			-size,  size,  size, 1.0f, 1.0f, 0,
			-size,  size, -size, 0.0f, 1.0f, 0,
			-size, -size, -size, 0.0f, 0.0f, 0,
			-size,  size,  size, 1.0f, 1.0f, 0,
			-size, -size, -size, 0.0f, 0.0f, 0,
			-size, -size,  size, 0.0f, 1.0f, 0,

			 size,  size,  size, 1.0f, 1.0f, 1,
			-size,  size,  size, 0.0f, 1.0f, 1,
			-size, -size,  size, 0.0f, 0.0f, 1,
			 size,  size,  size, 1.0f, 1.0f, 1,
			-size, -size,  size, 0.0f, 0.0f, 1,
			 size, -size,  size, 1.0f, 0.0f, 1,

			 size,  size, -size, 1.0f, 0.0f, 2,
			 size,  size,  size, 1.0f, 1.0f, 2,
			 size, -size,  size, 0.0f, 1.0f, 2,
			 size,  size, -size, 1.0f, 0.0f, 2,
			 size, -size,  size, 0.0f, 1.0f, 2,
			 size, -size, -size, 0.0f, 0.0f, 2,

			-size,  size, -size, 0.0f, 1.0f, 3,
			 size,  size, -size, 1.0f, 1.0f, 3,
			 size, -size, -size, 1.0f, 0.0f, 3,
			-size,  size, -size, 0.0f, 1.0f, 3,
			 size, -size, -size, 1.0f, 0.0f, 3,
			-size, -size, -size, 0.0f, 0.0f, 3,

			-size,  size,  size, 0.0f, 1.0f, 4,
			 size,  size, -size, 1.0f, 0.0f, 4,
			-size,  size, -size, 0.0f, 0.0f, 4,
			-size,  size,  size, 0.0f, 1.0f, 4,
			 size,  size,  size, 1.0f, 1.0f, 4,
			 size,  size, -size, 1.0f, 0.0f, 4,

			 size, -size, -size, 1.0f, 0.0f, 5,
			 size, -size,  size, 1.0f, 1.0f, 5,
			-size, -size,  size, 0.0f, 1.0f, 5,
			 size, -size, -size, 1.0f, 0.0f, 5,
			-size, -size,  size, 0.0f, 1.0f, 5,
			-size, -size, -size, 0.0f, 0.0f, 5,
		};*/

		/*ModelMesh *mesh = mSkyboxModel->GetMeshes()[0];

		VERTEX_BUFFER_DESC vbDesc;
		vbDesc.Usage = VertexBufferUsageStatic;
		vbDesc.CPUAccess = 0;
		vbDesc.Stride = sizeof(ModelVertex);
		mVertexBuffer = device->CreateVertexBuffer(vbDesc);
		mVertexBuffer->SetData(mesh->GetBuffer(), sizeof(ModelVertex) * mesh->GetTotalFaces());
		mNumVerts = mesh->GetTotalFaces();

		SkyboxMaterialProperties *props = new SkyboxMaterialProperties();
		props->SetTexture(mTexture);

		mMaterial = new Material(device, props);*/
	}

	void SkyboxShape::SetImage(std::shared_ptr<Image> image)
	{
		CubeMapReader cubeReader(image);
		mTexture->Initialize(cubeReader.GetBuffer(), cubeReader.GetFaceSize());
	}

	void SkyboxShape::Draw(IGraphicsDevice *device, RenderState &state)
	{
		/*IGraphicsContext *context = device->GetContext();

		glm::mat4 transform = state.GetTransform();
		glm::mat4 projection = state.GetProjection();

		transform = glm::scale(transform, glm::vec3(100));

		glm::mat4 wvp = projection * transform;

		ShaderDataMatrix4 wvpData(&wvp, 1);
		state.SetShaderData("WORLDVIEWPROJ_MATRIX", &wvpData);

		//ShaderDataTexture texData(mTexture);
		//state.SetShaderData("SKYBOX_TEXTURE", &texData);

		Effect *effect = context->GetEffect("Skybox");
		Technique *technique = effect->GetActiveTechnique();

		technique->Begin();

		while(technique->HasNextPass()) {
			mVertexBuffer->Activate();
			technique->ProcessNextPass(device, state);
			device->Draw(PrimitiveTypeTriangleList, mNumVerts, 0);
		}*/
	}

	SkyboxShape::~SkyboxShape()
	{
	}
};