#include <Challenge/Challenge.h>
#include <Challenge/Renderer/Shape/HeightMapShape.h>
#include <Challenge/Renderer/Effect.h>

namespace challenge
{
	HeightMapCache HeightMapShape::sHeightMapCache;
	std::mutex HeightMapShape::sHeightMapCacheLock;

	HeightMapShape::HeightMapShape(IGraphicsDevice *device, Size size, float step) :
		Shape(device, "heightmap"),
		mHeightData(NULL),
		mSize(size)
	{
		//mSize.width *= 10;
		//mSize.height *= 10;

		TEXTURE_DESC desc;
		desc.Format = TextureFormatFloat32;
		mHeightMapTexture = device->CreateTexture2D(desc);

		sHeightMapCacheLock.lock();
		mBuffer = sHeightMapCache.GetBuffer(size, 1);
		if(!mBuffer) {
			mBuffer = sHeightMapCache.AddBuffer(device, size, 1);
		}
		sHeightMapCacheLock.unlock();
	}

	HeightMapShape::~HeightMapShape()
	{
		if(mHeightData) {
			delete[] mHeightData;
		}

		delete mHeightMapTexture;
	}

	void HeightMapShape::SetHeightData(float *data)
	{
		if(mHeightData) {
			delete[] mHeightData;
		}

		mHeightData = new float[mSize.width * mSize.height];
		memcpy(mHeightData, data, mSize.width * mSize.height * sizeof(float));

		Size texSize(mSize.width, mSize.height);

		mHeightMapTexture->Initialize(reinterpret_cast<BYTE *>(mHeightData), texSize);
	}

	void HeightMapShape::Draw(IGraphicsDevice *device, RenderState &state)
	{
		/*ShaderDataMatrix4 wvpData(&state.GetWorldViewProjection(), 1);
		state.SetShaderData("WORLDVIEWPROJ_MATRIX", &wvpData);

		ShaderDataTexture texData(mHeightMapTexture);
		state.SetShaderData("HEIGHTMAP_TEXTURE", &texData);

		glm::vec2 size(50, 50);
		ShaderDataVector2 sizeData(&size, 1);
		state.SetShaderData("HEIGHTMAP_SIZE", &sizeData);

		Effect *effect = device->GetContext()->GetEffect("HeightMap");
		Technique *technique = effect->GetActiveTechnique();
		technique->Begin();
		while(technique->HasNextPass()) {
			mBuffer->Activate();
			technique->ProcessNextPass(device, state);
			device->Draw(PrimitiveTypeTriangleList, mBuffer->GetNumVerts(), 0);
		}*/
	}
};