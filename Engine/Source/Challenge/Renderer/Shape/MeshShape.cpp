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

		mWVPIndex = device->GetContext()->GetGlobalIndex("WORLDVIEWPROJ_MATRIX");
	}

	MeshShape::~MeshShape()
	{
	}

	void MeshShape::SetData(const void *data, size_t size, int numVerts, PrimitiveType primType)
	{
		int stride = size / numVerts;
		mBuffer->SetData(data, size, stride);
		mNumVerts = numVerts;
		mPrimType = primType;
	}

	void MeshShape::Draw(IGraphicsDevice *device, RenderState &state)
	{
		if(mEffect) {
			state.SetShaderData(mWVPIndex, &state.GetWorldViewProjection());

			auto tech = mEffect->GetActiveTechnique();

			tech->Begin();
			while(tech->HasNextPass()) {
				mBuffer->Activate();
				tech->ProcessNextPass(device, state);
				
				device->Draw(mPrimType, mNumVerts, 0);
			}
		}
	}
};