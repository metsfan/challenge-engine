#include <Engine/Challenge.h>
#include "BoxShape.h"

namespace challenge
{
	BoxShape::BoxShape(IGraphicsDevice *device, int size) :
		Shape(device, "box"),
		mSize(size),
		mBuffer(NULL)
	{
		std::vector<BasicVertex> verts;

		BoxVertex vertex_data[] = {
			-size,  size, -size, 1.0f, 0.0f, 0.0f, -1.0f,
			 size,  size, -size, 1.0f, 0.0f, 0.0f, -1.0f,
			 size, -size, -size, 1.0f, 0.0f, 0.0f, -1.0f,
			-size,  size, -size, 1.0f, 0.0f, 0.0f, -1.0f,
			 size, -size, -size, 1.0f, 0.0f, 0.0f, -1.0f,
			-size, -size, -size, 1.0f, 0.0f, 0.0f, -1.0f,

			 size,  size,  size, 1.0f, 0.0f, 0.0f, 1.0f,
			-size,  size,  size, 1.0f, 0.0f, 0.0f, 1.0f,
			-size, -size,  size, 1.0f, 0.0f, 0.0f, 1.0f,
			 size,  size,  size, 1.0f, 0.0f, 0.0f, 1.0f,
			-size, -size,  size, 1.0f, 0.0f, 0.0f, 1.0f,
			 size, -size,  size, 1.0f, 0.0f, 0.0f, 1.0f,

			 size,  size, -size, 1.0f, 1.0f, 0.0f, 0.0f,
			 size,  size,  size, 1.0f, 1.0f, 0.0f, 0.0f,
			 size, -size,  size, 1.0f, 1.0f, 0.0f, 0.0f,
			 size,  size, -size, 1.0f, 1.0f, 0.0f, 0.0f,
			 size, -size,  size, 1.0f, 1.0f, 0.0f, 0.0f,
			 size, -size, -size, 1.0f, 1.0f, 0.0f, 0.0f,

			-size,  size,  size, 1.0f, -1.0f, 0.0f, 0.0f,
			-size,  size, -size, 1.0f, -1.0f, 0.0f, 0.0f,
			-size, -size, -size, 1.0f, -1.0f, 0.0f, 0.0f,
			-size,  size,  size, 1.0f, -1.0f, 0.0f, 0.0f,
			-size, -size, -size, 1.0f, -1.0f, 0.0f, 0.0f,
			-size, -size,  size, 1.0f, -1.0f, 0.0f, 0.0f,

			-size,  size,  size, 1.0f, 0.0f, 1.0f, 0.0f,
			 size,  size, -size, 1.0f, 0.0f, 1.0f, 0.0f,
			-size,  size, -size, 1.0f, 0.0f, 1.0f, 0.0f,
			-size,  size,  size, 1.0f, 0.0f, 1.0f, 0.0f,
			 size,  size,  size, 1.0f, 0.0f, 1.0f, 0.0f,
			 size,  size, -size, 1.0f, 0.0f, 1.0f, 0.0f,

			 size, -size, -size, 1.0f, 0.0f, -1.0f, 0.0f,
			 size, -size,  size, 1.0f, 0.0f, -1.0f, 0.0f,
			-size, -size,  size, 1.0f, 0.0f, -1.0f, 0.0f,
			 size, -size, -size, 1.0f, 0.0f, -1.0f, 0.0f,
			-size, -size,  size, 1.0f, 0.0f, -1.0f, 0.0f,
			-size, -size, -size, 1.0f, 0.0f, -1.0f, 0.0f,
		};
		
		/*BoxVertex vertex_data[] = {
			-size,-size,-size, 1.0, 0.0, 0.0, 0.0,
			-size,-size, size, 1.0, 0.0, 0.0, 0.0,
			-size, size, size, 1.0, 0.0, 0.0, 0.0,
			size, size,-size, 1.0, 0.0, 0.0, 0.0,
			-size,-size,-size, 1.0, 0.0, 0.0, 0.0,
			-size, size,-size, 1.0, 0.0, 0.0, 0.0,
			size,-size, size, 1.0, 0.0, 0.0, 0.0,
			-size,-size,-size, 1.0, 0.0, 0.0, 0.0,
			size,-size,-size, 1.0, 0.0, 0.0, 0.0,
			size, size,-size, 1.0, 0.0, 0.0, 0.0,
			size,-size,-size, 1.0, 0.0, 0.0, 0.0,
			-size,-size,-size, 1.0, 0.0, 0.0, 0.0,
			-size,-size,-size, 1.0, 0.0, 0.0, 0.0,
			-size, size, size, 1.0, 0.0, 0.0, 0.0,
			-size, size,-size, 1.0, 0.0, 0.0, 0.0,
			size,-size, size, 1.0, 0.0, 0.0, 0.0,
			-size,-size, size, 1.0, 0.0, 0.0, 0.0,
			-size,-size,-size, 1.0, 0.0, 0.0, 0.0,
			-size, size, size, 1.0, 0.0, 0.0, 0.0,
			-size,-size, size, 1.0, 0.0, 0.0, 0.0,
			size,-size, size, 1.0, 0.0, 0.0, 0.0,
			size, size, size, 1.0, 0.0, 0.0, 0.0,
			size,-size,-size, 1.0, 0.0, 0.0, 0.0,
			size, size,-size, 1.0, 0.0, 0.0, 0.0,
			size,-size,-size, 1.0, 0.0, 0.0, 0.0,
			size, size, size, 1.0, 0.0, 0.0, 0.0,
			size,-size, size, 1.0, 0.0, 0.0, 0.0,
			size, size, size, 1.0, 0.0, 0.0, 0.0,
			size, size,-size, 1.0, 0.0, 0.0, 0.0,
			-size, size,-size, 1.0, 0.0, 0.0, 0.0,
			size, size, size, 1.0, 0.0, 0.0, 0.0,
			-size, size,-size, 1.0, 0.0, 0.0, 0.0,
			-size, size, size, 1.0, 0.0, 0.0, 0.0,
			size, size, size, 1.0, 0.0, 0.0, 0.0,
			-size, size, size, 1.0, 0.0, 0.0, 0.0,
			size,-size, size, 1.0, 0.0, 0.0, 0.0,
		};

		for(int i = 0; i < 36; i+=3) {
			BoxVertex *v1 = &vertex_data[i];
			BoxVertex *v2 = &vertex_data[i+1];
			BoxVertex *v3 = &vertex_data[i+2];

			glm::vec3 u = glm::vec3(v2->position[0] - v1->position[0], 
									v2->position[1] - v1->position[1], 
									v2->position[2] - v1->position[2]);

			glm::vec3 v = glm::vec3(v3->position[0] - v1->position[0], 
									v3->position[1] - v1->position[1], 
									v3->position[2] - v1->position[2]);

			glm::vec3 normal = glm::normalize(glm::cross(u, v));
			v1->normal[0] = v2->normal[0] = v3->normal[0] = normal.x;
			v1->normal[1] = v2->normal[1] = v3->normal[1] = normal.y;
			v1->normal[2] = v2->normal[2] = v3->normal[2] = normal.z;
		}*/

		/*static const float vertex_data[] = {
			0.0, 0.0, -50.0,
			1.0, 0.0, -50.0,
			0.0, 1.0, -50.0
		};*/

		/*mMaterial = new Material(device, NULL);

		VERTEX_BUFFER_DESC desc;
		memset(&desc, 0, sizeof(VERTEX_BUFFER_DESC));
		desc.Stride = sizeof(BoxVertex);
		mBuffer = device->CreateVertexBuffer(desc);
		mBuffer->SetData((void *)vertex_data, sizeof(vertex_data));*/
	}

	void BoxShape::Draw(IGraphicsDevice *device, RenderState &state)
	{
		/*ITechnique *technique = mMaterial->GetTechnique(1);
		technique->Begin();
		while(technique->HasNextPass()) {
			mBuffer->Activate();
			technique->ProcessNextPass(device, state);
			device->Draw(PrimitiveTypeTriangleList, 36, 0);
		}*/
		
	}

	BoxShape::~BoxShape()
	{
		if (mBuffer) {
			delete mBuffer;
		}
	}
};