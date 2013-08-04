#pragma once

#include <Engine/Challenge.h>
#include <Engine/Renderer/Texture.h>
#include <Engine/Input/InputManager.h>
#include <Engine/UI/Events/UIEventArgs.h>

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
	typedef std::vector<View *> TControlList;

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
		View();
		View(Frame frame);
		virtual ~View(void);

		void SetFrame(Frame frame) 
		{ 
			mFrame = frame; 
			UpdateAdjustedFrame();
		}
		const Frame& GetFrame() const { return mFrame; }
		void SetSize(Size size) { mFrame.size = size; }
		void SetPosition(Point point) { mFrame.origin = point; }

		void SetVisible(bool visible) { mVisible = visible; }
		bool IsVisible() { return mVisible; }

		void SetBackgroundColor(Color color) { mBackgroundColor = color; }
		const Color& GetBackgroundColor() const { return mBackgroundColor; }

		void SetBackgroundImage(std::string imageName);

		void AddSubcontrol(View *control);

		void SetZPosition(float zPosition) { mZPosition = zPosition; }
		float GetZPosition() { return mZPosition; }

		void SetParent(View *parent) 
		{ 
			mParent = parent; 
			UpdateAdjustedFrame();
		}
		View *GetParent() const { return mParent; }

		bool ContainsPoint(Point point) { return mAdjustedFrame.Contains(point); }

		/* Event Delegates */
		void AddMouseDownDelegate(MouseEventDelegate eventDelegate);
		void AddMouseUpDelegate(MouseEventDelegate eventDelegate);
		void AddMouseClickDelegate(MouseEventDelegate eventDelegate);
		void AddMouseMoveDelegate(MouseEventDelegate eventDelegate);
		void AddKeyDownDelegate(KeyboardEventDelegate eventDelegate);
		void AddKeyUpDelegate(KeyboardEventDelegate eventDelegate);

	private:
		Frame mFrame;
		Frame mAdjustedFrame;
		Color mBackgroundColor;
		ITexture *mBackgroundImage;
		ControlType mType;
		bool mVisible;
		TControlList mSubcontrols; 
		float mZPosition;
		View *mParent;

		TUIEventDelegateMap mDelegates;
		TMouseEventDelegateMap mMouseDelegates;
		TKeyboardEventDelegateMap mKeyboardDelegates;

		ControlMatrices mMatrices;
		ControlData mControlData;

		void UpdateAdjustedFrame() 
		{
			if(mParent) {
				Frame parentFrame = mParent->mAdjustedFrame;
				mAdjustedFrame = Frame(parentFrame.origin.x + mFrame.origin.x,
										parentFrame.origin.y + mFrame.origin.y,
										mFrame.size.width,
										mFrame.size.height);
			} else {
				mAdjustedFrame = mFrame; 
			}
		}

		void UpdateBase(int deltaMillis);
		virtual void Update(int deltaMillis) {}

		void RenderBase(UIManager *manager, Point origin);
		virtual void Render(UIManager *manager, Point origin) {}

		void OnKeyDown(const KeyboardEvent &e);
		void OnKeyUp(const KeyboardEvent &e);

		void OnMouseDown(const MouseEvent &e);
		void OnMouseMove(const MouseEvent &e);
		void OnMouseUp(const MouseEvent &e);
		void OnMouseClick(const MouseEvent &e);
		void OnMouseDblClick(const MouseEvent &e);

		bool OnMouseEvent(const MouseEvent &e);
		virtual bool ProcessMouseEvent(const MouseEvent &e);
		bool OnKeyboardEvent(const KeyboardEvent &e);
		virtual bool ProcessKeyboardEvent(const KeyboardEvent &e);
	};
};