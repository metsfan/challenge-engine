#pragma once

#include <Challenge/Challenge.h>
#include <Challenge/Renderer/Renderer.h>
#include <Challenge/UI/Events/UIEventArgs.h>
#include <Challenge/UI/Types.h>
#include <Challenge/Util/XML/XML.h>
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

	enum ViewVisibility
	{
		ViewVisible,
		ViewInvisible,
		ViewGone
	};

	enum ViewAlignment
	{
		AlignmentInherit = 0,
		AlignmentLeft = (1 << 1),
		AlignmentRight = (1 << 2),
		AlignmentBottom = (1 << 3),
		AlignmentTop = (1 << 4),
		AlignmentCenterHorizontal = (1 << 5),
		AlignmentCenterVertical = (1 << 6),
		AlignmentCenter = AlignmentCenterVertical | AlignmentCenterHorizontal
	};

	struct LayoutParams
	{
		Size size;
		Rect measureBounds;
		Size measureSize;

		/* Relative Layout params */
		bool alignParentTop = false;
		bool alignParentBottom = false;
		bool alignParentLeft = false;
		bool alignParentRight = false;

		View *leftOfView = NULL;
		View *rightOfView = NULL;
		View *aboveView = NULL;
		View *belowView = NULL;

		std::string leftOfViewId;
		std::string rightOfViewId;
		std::string aboveViewId;
		std::string belowViewId;

		/* Linear Layout params*/
		uint32_t layoutWeight = 0;
		ViewAlignment alignment = AlignmentInherit;
		ViewAlignment subviewAlignment = AlignmentInherit;
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

	static int MATCH_PARENT = 0xFF00;
	static int WRAP_CONTENT = 0xFF01;

	class View
	{
		friend class Window;
		friend class ViewManager;
		friend class ViewXMLParser;

	public:
		View(const Frame &frame = Frame());
		View(real x, real y, real width, real height) :
			View(Frame(x, y, width, height))
		{
		}

		View(const Size &size = Size()) :
			View(Frame(0, 0, size.width, size.height))
		{
		}

		View(real width, real height) :
			View(Size(width, height))
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

		virtual void SetSize(Size size)
		{
			mFrame.size = size; this->InvalidateLayout();
			mLayoutParams.size = size;
		}
		virtual void SetSize(int width, int height)
		{
			mFrame.size.width = width;
			mFrame.size.height = height;
			mLayoutParams.size = Size(width, height);
			this->InvalidateLayout();
		}
		virtual void SetPosition(Point point) { mFrame.origin = point; this->InvalidateLayout(); }
		virtual void SetPosition(real x, real y)
		{
			mFrame.origin.x = x;
			mFrame.origin.y = y;
			this->InvalidateLayout();
		}

		virtual void SetX(real x) { mFrame.origin.x = x; this->InvalidateLayout(); }
		virtual void SetY(real y) { mFrame.origin.y = y; this->InvalidateLayout(); }

		virtual void SetWidth(real width)
		{
			mFrame.size.width = width;
			mLayoutParams.size.width = width;
			this->InvalidateLayout();
		}
		virtual void SetHeight(real height)
		{
			mFrame.size.height = height;
			mLayoutParams.size.height = height;
			this->InvalidateLayout();
		}

		real GetX() { return mFrame.origin.x; }
		real GetY() { return mFrame.origin.y; }
		real GetWidth() { return mFrame.size.width; }
		real GetHeight() { return mFrame.size.height; }

		const Size& GetSize() { return mFrame.size; }
		const Point& GetPosition() { return mFrame.origin; }

		virtual Point GetPositionInView(const Point &position, View *other);

		virtual void SetPadding(const Rect &padding) { mPadding = padding; this->InvalidateLayout(); }
		virtual void SetLeftPadding(real padding) { mPadding.left = padding; this->InvalidateLayout(); }
		virtual void SetBottomPadding(real padding) { mPadding.bottom = padding; this->InvalidateLayout(); }
		virtual void SetRightPadding(real padding) { mPadding.right = padding; this->InvalidateLayout(); }
		virtual void SetTopPadding(real padding) { mPadding.top = padding; this->InvalidateLayout(); }

		const Rect& GetPadding() { return mPadding; }
		virtual real GetLeftPadding() { return mPadding.left; }
		virtual real GetBottomPadding() { return mPadding.bottom; }
		virtual real GetRightPadding() { return mPadding.right; }
		virtual real GetTopPadding() { return mPadding.top; }

		virtual void SetMargin(const Rect &margin) { mMargin = margin; this->InvalidateLayout(); }
		virtual void SetLeftMargin(real margin) { mMargin.left = margin; this->InvalidateLayout(); }
		virtual void SetBottomMargin(real margin) { mMargin.bottom = margin; this->InvalidateLayout(); }
		virtual void SetRightMargin(real margin) { mMargin.right = margin; this->InvalidateLayout(); }
		virtual void SetTopMargin(real margin) { mMargin.top = margin; this->InvalidateLayout(); }

		const Rect& GetMargin() { return mMargin; }
		virtual real GetLeftMargin() { return mMargin.left; }
		virtual real GetBottomMargin() { return mMargin.bottom; }
		virtual real GetRightMargin() { return mMargin.right; }
		virtual real GetTopMargin() { return mMargin.top; }

		HorizontalAlignment GetHorizontalAlignment() { return mHoriAlign; }
		VerticalAlignment GetVerticalAlignment() { return mVertAlign; }

		void SetHorizontalAlignment(HorizontalAlignment halign) { mHoriAlign = halign; }
		void SetVerticalAlignment(VerticalAlignment valign) { mVertAlign = valign; }

		virtual void SetVisibility(ViewVisibility visibility);
		virtual ViewVisibility GetVisibility() { return mVisibility; }

		virtual void SetBackgroundColor(const Color &color) { mBackgroundColor = color; this->InvalidateLayout(); }
		const virtual Color& GetBackgroundColor() const { return mBackgroundColor; }

		void SetBorderColor(const Color &color) { mBorderColor = color; this->InvalidateLayout(); }
		void SetBorderWidth(float width) { mBorderWidth = width; this->InvalidateLayout(); }

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

		virtual void SetParent(View *parent) { mParent = parent; this->InvalidateLayout(); }

		View * GetParent() const { return mParent; }

		virtual bool ContainsPoint(const Point &point) { return mAdjustedFrame.Contains(point); }

		void SetTag(int tag) { mTag = tag; }
		int GetTag() { return mTag; }

		void SetFocused(bool focused);
		bool IsFocused();

		void SetAlpha(real alpha) { mAlpha = alpha; }
		real GetAlpha() { return mAlpha; }

		Window* GetWindow();
		void SetWindow(Window *window) { mWindow = window; this->InvalidateLayout(); }

		void SetAttribute(const std::string &name, const std::string &value);
		std::string GetAttribute(const std::string &name);

		void ClipSubviews(bool clip);

		virtual void SetRotation(real rotation)
		{
			mRotation = rotation;
		}

		virtual real GetRotation() { return mRotation; }

		void SetLayoutParams(const LayoutParams &params) { mLayoutParams = params; this->InvalidateLayout(); }
		const LayoutParams& GetLayoutParams() { return mLayoutParams; }

		/* Relative Layout methods */
		void SetAlignParentLeft(bool align) { mLayoutParams.alignParentLeft = align; this->InvalidateLayout(); }
		void SetAlignParentRight(bool align) { mLayoutParams.alignParentRight = align; this->InvalidateLayout(); }
		void SetAlignParentBottom(bool align) { mLayoutParams.alignParentBottom = align; this->InvalidateLayout(); }
		void SetAlignParentTop(bool align) { mLayoutParams.alignParentTop = align; this->InvalidateLayout(); }

		void SetLeftOf(View *view) { mLayoutParams.leftOfView = view; this->InvalidateLayout(); }
		void SetRightOf(View *view) { mLayoutParams.rightOfView = view; this->InvalidateLayout(); }
		void SetAbove(View *view) { mLayoutParams.aboveView = view; this->InvalidateLayout(); }
		void SetBelow(View *view) { mLayoutParams.belowView = view; this->InvalidateLayout(); }

		/* Linear Layout methods */
		void SetLayoutWeight(uint32_t weight) { mLayoutParams.layoutWeight = weight; this->InvalidateLayout(); }
		void SetAlignment(ViewAlignment align) { mLayoutParams.alignment = align; this->InvalidateLayout(); }
		void SetSubviewAlignment(ViewAlignment align) { mLayoutParams.subviewAlignment = align; this->InvalidateLayout(); }

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

		virtual void Measure(const Size &parentSize);

		void InvalidateLayout();
		bool IsLayoutInvalid() { return mLayoutInvalid; }
		void WrapToSubviews();

	private:
		Frame mFrame;
		Frame mAdjustedFrame;
		Frame mTextureFrame;
		Rect mPadding;
		Rect mMargin;
		real mAlpha;
		Color mBackgroundColor;
		std::shared_ptr<Image> mBackgroundImage;
		std::shared_ptr<ImageAtlas> mBackgroundImageAtlas;
		std::string mBackgroundImageKey;
		bool mBackgroundImageChanged;
		ControlType mType;
		ViewVisibility mVisibility;
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

		LayoutParams mLayoutParams;
		bool mLayoutInvalid;

		Window *mWindow;

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