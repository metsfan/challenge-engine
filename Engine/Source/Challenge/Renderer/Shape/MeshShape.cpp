#include <Challenge/Challenge.h>
#include <Challenge/Renderer/Shape/MeshShape.h>
#include <Challenge/Renderer/VertexBuffer.h>
#include <Challenge/Renderer/Effect.h>

namespace challenge
{
	MeshShape::MeshShape(IGraphicsDevice *device, const std::string &effect) :
		Shape(device, "mesh"),
		mNumVerts(0),
		mPrimType(PrimitiveTypeTriangleList)
	{
		mEffect = device->GetContext()->GetEffect(effect);

		VERTEX_BUFFER_DESC desc;
		ZeroMemory(&desc, sizeof(VERTEX_BUFFER_DESC));
		desc.Stride = sizeof(DebugLinesVertex);
		mBuffer = device->CreateVertexBuffer(desc);
	}

	MeshShape::~MeshShape()
	{
	}

	void MeshShape::SetData(const void *data, size_t size, int numVerts, PrimitiveType primType)
	{
		mBuffer->SetData(data, size);
		mNumVerts = numVerts;
		mPrimType = primType;
	}

	void MeshShape::Draw(IGraphicsDevice *device, RenderState &state)
	{
		if(mEffect) {
			

			ShaderDataMatrix4 wvpData(&state.GetWorldViewProjection(), 1);
			state.SetShaderData("WORLDVIEWPROJ_MATRIX", &wvpData);

			auto tech = mEffect->GetActiveTechnique();

			tech->Begin();
			while(tech->HasNextPass()) {
				tech->ProcessNextPass(device, state);
				mBuffer->Activate();
				device->Draw(mPrimType, mNumVerts, 0);
			}
		}
	}
};