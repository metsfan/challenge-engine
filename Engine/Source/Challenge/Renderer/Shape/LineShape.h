#pragma once

#include <Challenge/Challenge.h>
#include <Challenge/Renderer/Shape/MeshShape.h>

namespace challenge
{
	class LineShape : public Shape
	{
	public:
		LineShape(IGraphicsDevice *device);
		~LineShape();

		void SetWidth(float width)
		{
			mWidth = width;
		}

		void SetColor(const Color &color)
		{
			mColor.r = color.red / 255.0f;
			mColor.g = color.green / 255.0f;
			mColor.b = color.blue / 255.0f;
			mColor.a = color.alpha / 255.0f;
		}

		void AddPoint(const glm::vec3 &point)
		{
			mPoints.push_back(point);
			mReloadPoints = true;
		}

		void RemovePoint(int index)
		{
			mPoints.erase(mPoints.begin() + index);
			mReloadPoints = true;
		}

		int GetNumPoints()
		{
			return mPoints.size();
		}

		void ClearPoints()
		{
			mPoints.clear();
		}

		void Draw(IGraphicsDevice *device, RenderState &state);

	private:
		float mWidth;
		glm::vec4 mColor;
		std::vector<glm::vec3> mPoints;
		bool mReloadPoints;

		MeshShape *mMesh;
	};
};