#include <Challenge/Challenge.h>
#include <Challenge/Core/Cursor.h>

namespace challenge
{
	std::shared_ptr<Image> Cursor::sCursorImage = nullptr;
	bool Cursor::sCursorImageChanged = false;
	SpriteShape *Cursor::sCursorSprite = NULL;
	bool Cursor::sInitialized = Cursor::Initialize();
	bool Cursor::sVisible = false;
	bool Cursor::sPlatformVisible = true;
	Point Cursor::sPosition;

	void Cursor::SetCursor(std::shared_ptr<Image> image)
	{
		__CursorPlatform<>::HidePlatformCursor();

		if (image != sCursorImage) {
			sCursorImage = image;
			sCursorImageChanged = true;
		}

		sVisible = true;
		sPlatformVisible = false;
	}

	void Cursor::SetSystemCursor(const std::string &type)
	{
		__CursorPlatform<>::ShowPlatformCursor(type);
		sVisible = false;
		sPlatformVisible = true;
	}

	void Cursor::ShowCursor()
	{
		sVisible = true;
		sPlatformVisible = false;
	}

	void Cursor::HideCursor()
	{
		__CursorPlatform<>::HidePlatformCursor();
		sVisible = false;
		sPlatformVisible = false;
	}

	void Cursor::SetPosition(const Point &position)
	{
		sPosition = position;
	}

	bool Cursor::Initialize()
	{
		__CursorPlatform<>::ShowPlatformCursor("crosshair");
		//__CursorPlatform<>::HidePlatformCursor();

		return true;
	}

	void Cursor::Render(IGraphicsDevice *device, RenderState &state)
	{
		if (sVisible) {
			if (!sCursorSprite) {
				sCursorSprite = new SpriteShape(device, "sprite");
			}

			if (sCursorImageChanged) {
				sCursorSprite->SetBackgroundImage(sCursorImage.get());
				sCursorImageChanged = false;
			}

			sCursorSprite->SetPosition(sPosition.x, sPosition.y);
			sCursorSprite->Draw(device, state);
		}
	}
}