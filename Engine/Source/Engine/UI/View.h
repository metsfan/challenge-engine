#pragma once

#include <Engine/Challenge.h>
#include <Engine/Renderer/Renderer.h>
#include <Engine/Input/InputManager.h>
#include <Engine/UI/Events/UIEventArgs.h>
#include <Engine/UI/Types.h>

namespace challenge
{
	class UIControlData
	{
	public:
		float *positionBuffer;
		float *colorBuffer;
		float *texCoordBuffer;
		int *hasTextBuffer;
		int *hasTextureBuffer;
		int current;

		UIControlData(int numControls) {
			positionBuffer = new float[numControls * 12];
			colorBuffer = new float[numControls * 16];
			texCoordBuffer = new float[numControls * 8];
			hasTextBuffer = new int[numControls * 4];
			hasTextureBuffer = new int[numControls * 4];
			current = 0;
		}

		~UIControlData() {
			delete positionBuffer;
			delete colorBuffer;
			delete texCoordBuffer;
			delete hasTextBuffer;
			delete hasTextureBuffer;
		}
	};

	typedef enum ControlType {
		ControlTypeButton,
		ControlTypePanel
	};

	class View;
	typedef std::vector<View *> TViewList;

	__declspec(align(16))
	struct ControlMatrices {
		glm::mat4 gWVPMatrix;
	};

	__declspec(align(16))
	struct ControlData {
		glm::vec4 gBackgroundColor;
		glm::vec4 gColor;
		int gHasTexture;
	};

	class View
	{
		friend class UIManager;

	public:
		View(Frame frame = Frame());
		virtual ~View(void);

		virtual void Update(int deltaMillis);
		virtual void Render(IGraphicsDevice *device, RenderState &state, const Frame &parentFrame);

		virtual void SetFrame(const Frame &frame) { mFrame = frame; }
		const Frame& GetAdjustedFrame() { return mAdjustedFrame; }
		const virtual Frame& GetFrame() const { return mFrame; }

		virtual void SetSize(Size size) { mFrame.size = size; }
		virtual void SetSize(int width, int height) 
		{
			mFrame.size.width = width;
			mFrame.size.height = height;
		}
		virtual void SetPosition(Point point) { mFrame.origin = point; }
		virtual void SetPosition(real x, real y)
		{
			mFrame.origin.x = x;
			mFrame.origin.y = y;
		}

		virtual void SetX(real x) { mFrame.origin.x = x; }
		virtual void SetY(real y) { mFrame.origin.y = y; }
		virtual void SetWidth(real width) { mFrame.size.width = width; }
		virtual void SetHeight(real height) { mFrame.size.height = height; }

		real GetX() { return mFrame.origin.x; }
		real GetY() { return mFrame.origin.y; }
		real GetWidth() { return mFrame.size.width; }
		real GetHeight() { return mFrame.size.height; }

		virtual void SetVisible(bool visible) { mVisible = visible; }
		virtual bool IsVisible() { return mVisible; }

		virtual void SetBackgroundColor(const glm::vec4 &color) { mBackgroundColor = color; }
		const virtual glm::vec4& GetBackgroundColor() const { return mBackgroundColor; }

		virtual void SetBackgroundImage(std::string imageName);
		virtual void SetBackgroundImage(std::shared_ptr<Image> image);

		virtual void AddSubview(View *view);
		const TViewList& GetSubviews() { return mSubviews; }

		virtual void SetZPosition(float zPosition) { mZPosition = zPosition; }
		virtual float GetZPosition() { return mZPosition; }

		virtual void SetParent(View *parent) { mParent = parent; }

		View *GetParent() const { return mParent; }

		bool ContainsPoint(Point point) { return mAdjustedFrame.Contains(point); }

		void SetTag(int tag) { mTag = tag; }
		int GetTag() { return mTag; }

		void SetFocused(bool focused);
		bool IsFocused() { return mFocused; }

		IWindow* GetWindow();

		/* Event Delegates */
		void AddMouseDownDelegate(MouseEventDelegate eventDelegate);
		void AddMouseUpDelegate(MouseEventDelegate eventDelegate);
		void AddMouseClickDelegate(MouseEventDelegate eventDelegate);
		void AddMouseMoveDelegate(MouseEventDelegate eventDelegate);
		void AddMouseWheelMoveDelegate(MouseEventDelegate eventDelegate);
		void AddKeyDownDelegate(KeyboardEventDelegate eventDelegate);
		void AddKeyUpDelegate(KeyboardEventDelegate eventDelegate);

	protected:
		SpriteShape* GetSprite() { return mSprite; }
		const Frame& GetTextureFrame() { return mTextureFrame; }
		void ClipSubviews(bool clip) { mClipSubviews = clip; }
		void AddInternalSubview(View *view);

	private:
		Frame mFrame;
		Frame mAdjustedFrame;
		Frame mTextureFrame;
		glm::vec4 mBackgroundColor;
		std::shared_ptr<Image> mBackgroundImage;
		bool mBackgroundImageChanged;
		ControlType mType;
		bool mVisible;
		TViewList mSubviews; 
		TViewList mInternalSubviews;
		float mZPosition;
		View *mParent;
		SpriteShape *mSprite;
		int mTag;
		bool mFocused;
		bool mClipSubviews;

		View *mRootView;
		UIManager *mUIManager;
		IWindow *mWindow;

		TUIEventDelegateMap mDelegates;
		TMouseEventDelegateMap mMouseDelegates;
		TKeyboardEventDelegateMap mKeyboardDelegates;

		ControlMatrices mMatrices;
		ControlData mControlData;

		void OnKeyDown(const KeyboardEvent &e);
		void OnKeyUp(const KeyboardEvent &e);

		void OnMouseDown(const MouseEvent &e);
		void OnMouseMove(const MouseEvent &e);
		void OnMouseUp(const MouseEvent &e);
		void OnMouseClick(const MouseEvent &e);
		void OnMouseDblClick(const MouseEvent &e);

		virtual bool ProcessMouseEvent(const MouseEvent &e);
		virtual bool ProcessKeyboardEvent(const KeyboardEvent &e);

		View* GetSelectedView(const Point &p);

		virtual Frame CalculateChildFrame() { return mAdjustedFrame; }
	};
};