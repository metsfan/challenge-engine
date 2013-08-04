#pragma once

#include <Engine/Challenge.h>
#include <Engine/Renderer/RenderState.h>
#include <Engine/Renderer/GraphicsDevice.h>
#include <Engine/Renderer/Shape.h>

namespace challenge
{
	struct HeightMapVertex
	{
		float position[3];
		float texCoord[2];
	};

	class HeightMapVertexBuffer
	{
	public:
		HeightMapVertexBuffer(IGraphicsDevice *device, Size size, float step) :
			mSize(size),
			mStep(step),
			mStepFactor(1.0 / mStep),
			mBuffer(NULL)
		{
			VERTEX_BUFFER_DESC desc;
			desc.Stride = sizeof(HeightMapVertex);
			desc.Usage = VertexBufferUsageStatic;
			desc.CPUAccess = 0;

			mBuffer = device->CreateVertexBuffer(desc);
			
			std::vector<HeightMapVertex> verts;

			for(float i = 0; i < size.height; i+=1) {
				for(float j = 0; j < size.width; j+=1) {
					float u1 = (i / (float)size.height);
					float v1 = (j / (float)size.width);
					float u2 = ((i+1) / (float)size.height);
					float v2 = ((j+1) / (float)size.width);

					HeightMapVertex v[4] = {
						{
							j, 0, i,
							u1, v1
						},
						{
							j + 1, 0, i,
							u2, v1
						},
						{
							j, 0, i + 1,
							u1, v2
						},
						{
							j + 1, 0, i + 1,
							u2, v2
						}
					};

					verts.push_back(v[0]);
					verts.push_back(v[1]);
					verts.push_back(v[2]);

					verts.push_back(v[1]);
					verts.push_back(v[2]);
					verts.push_back(v[3]);
				}
			}

			mBuffer->SetData(&verts[0], sizeof(HeightMapVertex) * verts.size());
		}

		~HeightMapVertexBuffer()
		{
			if(mBuffer) {
				delete mBuffer;
			}
		}

		void Activate()
		{
			if(mBuffer) {
				mBuffer->Activate();
			}
		}

		int GetNumVerts()
		{
			return (mSize.width * mStepFactor) * (mSize.height * mStepFactor) * 6;
		}

		bool MatchesSizeAndStep(Size size, float step)
		{
			return size == mSize && step == mStep;
		}

	private:
		float mStep;
		int mStepFactor;
		Size mSize;
		IVertexBuffer *mBuffer;
	};

	class HeightMapCache
	{
	public:
		HeightMapCache()
		{
		}

		~HeightMapCache()
		{
		}

		std::shared_ptr<HeightMapVertexBuffer> AddBuffer(IGraphicsDevice *device, Size size, float step)
		{
			std::shared_ptr<HeightMapVertexBuffer> buffer = std::shared_ptr<HeightMapVertexBuffer>(
				new HeightMapVertexBuffer(device, size, step)
			);

			mBuffers.push_back(buffer);

			return buffer;
		}

		std::shared_ptr<HeightMapVertexBuffer> GetBuffer(Size size, float step)
		{
			for(auto buffer : mBuffers) {
				if(buffer->MatchesSizeAndStep(size, step)) {
					return buffer;
				}
			}

			return NULL;
		}

	private:
		std::vector<std::shared_ptr<HeightMapVertexBuffer> > mBuffers;
	};

	class HeightMapShape : public Shape
	{
	public:
		HeightMapShape(IGraphicsDevice *device, Size size, float step);
		~HeightMapShape();

		void SetSize(Size size) { mSize = size; }
		void SetHeightData(float *data);

		void Draw(IGraphicsDevice *device, RenderState &state);

	private:
		float *mHeightData;
		Size mSize;
		ITexture *mHeightMapTexture;
		std::shared_ptr<HeightMapVertexBuffer> mBuffer;

		static HeightMapCache sHeightMapCache;
		static std::mutex sHeightMapCacheLock;
	};
};