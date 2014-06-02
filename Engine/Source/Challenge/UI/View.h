#pragma once

#include <Challenge/Challenge.h>
#include <Challenge/Renderer/Renderer.h>
#include <Challenge/UI/Events/UIEventArgs.h>
#include <Challenge/UI/Types.h>
#include <Challenge/Util/XML/XML.h>
#include <Challenge/UI/Layout/Layout.h>
#include <Challenge/Util/ImageAtlas.h>

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

	enum HorizontalAlignment
	{
		HorizontalAlignLeft,
		HorizontalAlignRight,
		HorizontalAlignCenter
	};

	enum VerticalAlignment
	{
		VerticalAlignTop,
		VerticalAlignMiddle,
		VerticalAlignBottom
	};

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
		View(real x, real y, real width, real height, LayoutType layout = LayoutTypeAbsolute) :
			View(Frame(x, y, width, height), layout)
		{
		}
		virtual ~View(void);

		void SafeDelete();

		virtual void Update(int deltaMillis);
		virtual void Render(IGraphicsDevice *device, RenderState &state, const Frame &parentFrame);

		void SetId(const std::string &id) { mId = id; }
		const std::string& GetId() { return mId; }

		View * FindViewById(const std::string &id);
		
		template <typename T>
		T * FindViewById(const std::string &id)
		{
			return dynamic_cast<T *>(this->FindViewById(id));
		}

		View * FindView(View *view);

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

		HorizontalAlignment GetHorizontalAlignment() { return mHoriAlign; }
		VerticalAlignment GetVerticalAlignment() { return mVertAlign; }

		void SetHorizontalAlignment(HorizontalAlignment halign) { mHoriAlign = halign; }
		void SetVerticalAlignment(VerticalAlignment valign) { mVertAlign = valign; }

		virtual void SetVisible(bool visible);
		virtual bool IsVisible() { return mVisible; }

		virtual void SetBackgroundColor(const Color &color) { mBackgroundColor = color; }
		const virtual Color& GetBackgroundColor() const { return mBackgroundColor; }

		void SetBorderColor(const Color &color) { mBorderColor = color; }
		void SetBorderWidth(float width) { mBorderWidth = width; }

		virtual void SetBackgroundImage(std::wstring imageName);
		virtual void SetBackgroundImage(std::string imageName)
		{
			this->SetBackgroundImage(StringUtil::ToWide(imageName));
		}

		virtual void SetBackgroundImage(std::shared_ptr<Image> image);
		virtual void SetBackgroundImage(std::shared_ptr<ImageAtlas> atlas, const std::string &key);

		virtual void AddSubview(View *view);
		virtual View * RemoveSubview(View *view);
		virtual TViewList RemoveAllSubviews();
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

		void SetAlpha(real alpha) { mAlpha = alpha; }
		real GetAlpha() { return mAlpha; }

		Window* GetWindow();
		void SetWindow(Window *window) { mWindow = window; }

		void SetLayoutType(LayoutType layout);
		void SetLayoutEngine(ILayout *layout)
		{
			mLayoutEngine = std::unique_ptr<ILayout>(layout);
		}

		void SetAttribute(const std::string &name, const std::string &value);
		std::string GetAttribute(const std::string &name);

		void ClipSubviews(bool clip);

		virtual void SetRotation(real rotation)
		{
			mRotation = rotation;
		}

		virtual real GetRotation() { return mRotation; }

		/* Event Delegates */
		void AddMouseEvent(MouseEventType type, MouseEventDelegate eventDelegate);
		void AddKeyboardEvent(KeyboardEventType type, KeyboardEventDelegate eventDelegate);

		static View * CreateFromResource(const std::wstring &resource);

		static View * CreateFromResource(const std::string &resource)
		{
			return View::CreateFromResource(StringUtil::ToWide(resource));
		}

		template <typename T>
		static T * CreateFromResource(const std::wstring &resource)
		{
			return dynamic_cast<T *>(View::CreateFromResource(resource));
		}

		template <typename T>
		static T * CreateFromResource(const std::string &resource)
		{
			return View::CreateFromResource<T>(StringUtil::ToWide(resource));
		}

		static void RegisterViewClass(const std::string &name, TViewCreatorFunction creator);

		virtual bool OnKeyboardEvent(const KeyboardEvent &e);
		virtual bool OnMouseEvent(const MouseEvent &e);


	protected:
		SpriteShape* GetSprite() { return mSprite; }
		const Frame& GetTextureFrame() { return mTextureFrame; }
		void AddInternalSubview(View *view);

		virtual void ParseFromXML(XMLNode &node);
		virtual void OnXMLParseComplete();

		virtual void CalculateChildFrames() {}
		virtual void OnLoadComplete() {}

		void SetFocusedInternal(bool focused) { mFocused = focused; }

		virtual void PositionSubviews();


	private:
		Frame mFrame;
		Frame mAdjustedFrame;
		Frame mTextureFrame;
		Rect mPadding;
		real mAlpha;
		Color mBackgroundColor;
		std::shared_ptr<Image> mBackgroundImage;
		std::shared_ptr<ImageAtlas> mBackgroundImageAtlas;
		std::string mBackgroundImageKey;
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
		real mRotation;
		HorizontalAlignment mHoriAlign;
		VerticalAlignment mVertAlign;
		std::map<std::string, std::string> mAttributes;

		Window *mWindow;

		std::unique_ptr<ILayout> mLayoutEngine;

		TUIEventDelegateMap mDelegates;
		TMouseEventDelegateMap mMouseDelegates;
		TKeyboardEventDelegateMap mKeyboardDelegates;

		ControlMatrices mMatrices;
		ControlData mControlData;

		static std::map<std::string, TViewCreatorFunction> sViewCreatorRegistry;

		virtual bool ProcessMouseEvent(const MouseEvent &e);
		virtual bool ProcessKeyboardEvent(const KeyboardEvent &e);

		View * GetSelectedView(const Point &p);

		virtual Frame CalculateChildFrame() { return mAdjustedFrame; }
	};
};