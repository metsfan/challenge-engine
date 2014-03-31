#pragma once

#include <Challenge/Challenge.h>

namespace challenge
{
	class Cursor
	{
	public:
		static void SetCursor(std::shared_ptr<Image> image);
		static void SetSystemCursor(const std::string &type);
		static void ShowCursor();
		static void HideCursor();

		static void SetPosition(const Point &position);

		static void Render(IGraphicsDevice *device, RenderState &state);

	private:
		static std::shared_ptr<Image> sCursorImage;
		static bool sCursorImageChanged;
		static SpriteShape *sCursorSprite;
		static bool sInitialized;
		static bool sVisible;
		static bool sPlatformVisible;
		static Point sPosition;

		static bool Initialize();
	};

	template <typename Platform = CurrentPlatform>
	class __CursorPlatform
	{
		friend class Cursor;

		static void HidePlatformCursor();
		static void ShowPlatformCursor(const std::string &cursor);
	};
}