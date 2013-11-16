#pragma once

#include <Engine/Challenge.h>
#include <Engine/Renderer/Renderer.h>
#include <Engine/UI/Events/UIEventArgs.h>
#include <Engine/UI/Types.h>
#include <Engine/Util/XML/XML.h>

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

	enum ControlType 
	{
		ControlTypeButton,
		ControlTypePanel
	};

	enum LayoutType
	{
		LayoutTypeAbsolute,
		LayoutTypeLinear,
		LayoutTypeGrid
	};

	class ILayout;
	class View;

	typedef std::shared_ptr<View> ViewPtr;
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

	typedef std::function<View * (Frame)> TViewCreatorFunction;

	class View
	{
		friend class Window;
		friend class ViewManager;
		friend class ViewXMLParser;

	public:
		View(Frame frame = Frame(), LayoutType layout = LayoutTypeAbsolute);
		virtual ~View(void);

		virtual void Update(int deltaMillis);
		virtual void Render(IGraphicsDevice *device, RenderState &state, const Frame &parentFrame);

		void SetId(const std::string &id) { mId = id; }
		const std::string& GetId() { return mId; }

		View * FindViewById(const std::string &id);

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

		const Size& GetSize() { return mFrame.size;  }
		const Point& GetPosition() { return mFrame.origin;  }

		virtual Point GetPositionInView(const Point &position, View *other);

		virtual void SetPadding(const Rect &padding) { mPadding = padding; }
		virtual void SetLeftPadding(real padding) { mPadding.left = padding; }
		virtual void SetBottomPadding(real padding) { mPadding.bottom = padding; }
		virtual void SetRightPadding(real padding) { mPadding.right = padding; }
		virtual void SetTopPadding(real padding) { mPadding.top = padding; }

		const Rect& GetPadding() { return mPadding; }
		virtual real GetLeftPadding() { return mPadding.left; }
		virtual real GetBottomPadding() { return mPadding.bottom; }
		virtual real GetRightPadding() { return mPadding.right; }
		virtual real GetTopPadding() { return mPadding.top; }

		virtual void SetVisible(bool visible) { mVisible = visible; }
		virtual bool IsVisible() { return mVisible; }

		virtual void SetBackgroundColor(const Color &color) { mBackgroundColor = color; }
		const virtual Color& GetBackgroundColor() const { return mBackgroundColor; }

		void SetBorderColor(const Color &color) { mBorderColor = color; }
		void SetBorderWidth(float width) { mBorderWidth = width; }

		virtual void SetBackgroundImage(std::string imageName);
		virtual void SetBackgroundImage(std::shared_ptr<Image> image);

		virtual void AddSubview(View *view);
		virtual void RemoveSubview(View *view);
		virtual void RemoveFromSuperview();
		const TViewList& GetSubviews() { return mSubviews; }

		virtual void SetZPosition(float zPosition) { mZPosition = zPosition; }
		virtual float GetZPosition() { return mZPosition; }

		virtual void SetParent(View *parent) { mParent = parent; }

		View * GetParent() const { return mParent; }

		virtual bool ContainsPoint(const Point &point) { return mAdjustedFrame.Contains(point); }

		void SetTag(int tag) { mTag = tag; }
		int GetTag() { return mTag; }

		void SetFocused(bool focused);
		bool IsFocused();

		Window* GetWindow();
		void SetWindow(Window *window) { mWindow = window; }

		void SetLayoutType(LayoutType layout);

		/* Event Delegates */
		void AddMouseEvent(MouseEventType type, MouseEventDelegate eventDelegate);
		void AddKeyboardEvent(KeyboardEventType type, KeyboardEventDelegate eventDelegate);

		static View * CreateFromResource(const std::string &resource);
		static void RegisterViewClass(const std::string &name, TViewCreatorFunction creator);


	protected:
		SpriteShape* GetSprite() { return mSprite; }
		const Frame& GetTextureFrame() { return mTextureFrame; }
		void ClipSubviews(bool clip);
		void AddInternalSubview(View *view);
		virtual void ParseFromXML(XMLNode &node);
		virtual void CalculateChildFrames() {}
		virtual void OnLoadComplete() {}

		void SetFocusedInternal(bool focused) { mFocused = focused; }

	private:
		Frame mFrame;
		Frame mAdjustedFrame;
		Frame mTextureFrame;
		Rect mPadding;
		Color mBackgroundColor;
		std::shared_ptr<Image> mBackgroundImage;
		bool mBackgroundImageChanged;
		ControlType mType;
		bool mVisible;
		TViewList mSubviews; 
		TViewList mInternalSubviews;
		float mZPosition;
		View * mParent;
		SpriteShape *mSprite;
		std::string mId;
		int mTag;
		bool mFocused;
		bool mClipSubviews;
		Frame mClipRegion;
		bool mFrameSet;
		Color mBorderColor;
		float mBorderWidth;

		Window *mWindow;

		std::unique_ptr<ILayout> mLayoutEngine;

		TUIEventDelegateMap mDelegates;
		TMouseEventDelegateMap mMouseDelegates;
		TKeyboardEventDelegateMap mKeyboardDelegates;

		ControlMatrices mMatrices;
		ControlData mControlData;

		static std::map<std::string, TViewCreatorFunction> sViewCreatorRegistry;

		void OnKeyDown(const KeyboardEvent &e);
		void OnKeyUp(const KeyboardEvent &e);

		void OnMouseDown(const MouseEvent &e);
		void OnMouseMove(const MouseEvent &e);
		void OnMouseUp(const MouseEvent &e);
		void OnMouseClick(const MouseEvent &e);
		void OnMouseDblClick(const MouseEvent &e);

		virtual bool ProcessMouseEvent(const MouseEvent &e);
		virtual bool ProcessKeyboardEvent(const KeyboardEvent &e);

		View * GetSelectedView(const Point &p);

		virtual Frame CalculateChildFrame() { return mAdjustedFrame; }
		virtual void PositionSubviews();
	};
};