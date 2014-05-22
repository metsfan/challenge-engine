#include <Challenge/Challenge.h>
#include <Challenge/Event/Types/KeyboardEventData.h>
#include <Challenge/Event/Types/MouseEventData.h>
#include <Challenge/GameApplication.h>
#include <Challenge/Event/EventManager.h>
#include <Challenge/Util/Logger.h>
#include "InputManager.h"

namespace challenge
{
	InputManager::InputManager()
	{
		mMouseDown = false;
		mKeyDown = false;
		mShiftDown = false;
		mCtrlDown = false;
		mAltDown = false;
	}

	void InputManager::AddKeyboardListener(std::shared_ptr<IKeyboardListener> listener)
	{
		if(listener != NULL) {
			mKeyboardListeners.push_back(listener);
		}
	}

	void InputManager::AddMouseListener(std::shared_ptr<IMouseListener> listener)
	{
		if (listener != NULL) {
			mMouseListeners.push_back(listener);
		}
	}

	void InputManager::ProcessKeyboardEvent(KeyboardEventType type, uint32_t keyCode, uint32_t virtualKeyCode)
	{
		if(keyCode == SpecialKeyShift) {
			mShiftDown = type == KeyboardEventKeyUp ? false : true;
		} else if(keyCode == SpecialKeyCtrl) {
			mCtrlDown = type == KeyboardEventKeyUp ? false : true;
		} else if(keyCode == SpecialKeyAlt) {
			mAltDown = type == KeyboardEventKeyUp ? false : true;
		} else {
			KeyboardEvent evt(type, keyCode, virtualKeyCode);

			bool found = false;
			auto key = std::find(mActiveKeys.begin(), mActiveKeys.end(), 
				std::pair<uint32_t, uint32_t>(keyCode, virtualKeyCode));

			switch (type)
			{
			case KeyboardEventKeyDown:
				if(key == mActiveKeys.end()) {
					mKeyboardEventQueue.push_back(evt);
				}
				break;

			case KeyboardEventKeyUp:
				if(key != mActiveKeys.end()) {
					mKeyboardEventQueue.push_back(evt);
				}

				break;
			}
		}
	}

	void InputManager::ProcessMouseEvent(MouseEventType type, unsigned int button, Point position)
	{
		MouseEvent evt(type, button, position);

		bool found = false;
		std::vector<unsigned int>::iterator it;

		switch (type)
		{
		case MouseEventMouseDown:
			//this->MouseDown(evt);
			mMouseDown = true;
		
			it = mActiveMouseButtons.begin();
			while (it != mActiveMouseButtons.end()) {
				if((*it) == button) {
					found = true;
				}
				++it;
			}

			if(!found) {
				mActiveMouseButtons.push_back(button);
				mMouseEventQueue.push_back(evt);
			}
			mMousePosition = position;

			break;

		case MouseEventMouseMove:
			mMousePosition = position;
			evt.mouseDown = mMouseDown;
			mMouseEventQueue.push_back(evt);
			break;

		case MouseEventMouseUp:
		
			it = mActiveMouseButtons.begin();
			while (it != mActiveMouseButtons.end()) {
				if((*it) == button) {
					mActiveMouseButtons.erase(it);
					mMouseEventQueue.push_back(evt);
					break;
				}
				++it;
			}

			if(mActiveMouseButtons.size() == 0) {
				mMouseDown = false;
			}
			mMousePosition = position;

			//this->MouseUp(evt);
			break;

		case MouseEventMouseClick:
			mMouseEventQueue.push_back(evt);
			break;

		case MouseEventMouseDblClick:
			mMouseEventQueue.push_back(evt);
			break;
		}
	}

	void InputManager::ProcessMouseWheelEvent(MouseEventType type, int delta)
	{
		MouseEvent evt;
		evt.type = type;
		evt.wheelDelta = delta;
		mMouseEventQueue.push_back(evt);
	}

	void InputManager::Update()
	{
		if(mKeyboardListeners.size() > 0) {
			// Process keyboard events in queue
			if(mKeyboardEventQueue.size()) {
				std::vector<KeyboardEvent> keyboardEvents(mKeyboardEventQueue.size());
				std::copy(mKeyboardEventQueue.begin(), mKeyboardEventQueue.end(), keyboardEvents.begin());
				mKeyboardEventQueue.clear();

				for(KeyboardEvent &evt : keyboardEvents) {
					auto key = std::find(mActiveKeys.begin(), mActiveKeys.end(), 
						std::pair<uint32_t, uint32_t>(evt.keyCode, evt.virtualKeyCode));
					evt.shiftDown = mShiftDown;
					evt.ctrlDown = mCtrlDown;
					evt.altDown = mAltDown;
					switch(evt.type) {
					case KeyboardEventKeyDown:
						if(key == mActiveKeys.end()) {
							mActiveKeys.push_back(std::pair<uint32_t, uint32_t>(evt.keyCode, evt.virtualKeyCode));
							this->PostKeyboardEvent(evt);
						}
				
						break;

					case KeyboardEventKeyUp:
						if(key != mActiveKeys.end()) {
							mActiveKeys.erase(key);
							this->PostKeyboardEvent(evt);
						}

						break;
					}
				}
			}

			// Send key press events for all active keys
			for(auto keys : mActiveKeys) {
				KeyboardEvent evt;
				evt.keyCode = keys.first;
				evt.virtualKeyCode = keys.second;
				evt.type = KeyboardEventKeyPress;
				evt.shiftDown = mShiftDown;
				evt.ctrlDown = mCtrlDown;
				evt.altDown = mAltDown;

				//Logger::Log(LogDebug, "Key Press: %c", key);

				this->PostKeyboardEvent(evt);
			}
		}

		if(mMouseListeners.size() > 0 &&mMouseEventQueue.size() > 0) {
			std::vector<MouseEvent> mouseEvents(mMouseEventQueue.size());
			std::copy(mMouseEventQueue.begin(), mMouseEventQueue.end(), mouseEvents.begin());
			mMouseEventQueue.clear();

			for(MouseEvent &evt : mouseEvents) {
				evt.shiftDown = mShiftDown;
				evt.ctrlDown = mCtrlDown;
				evt.altDown = mAltDown;
				this->PostMouseEvent(evt);
			}
		}
	}

	/* Keyboard Events */
	void InputManager::PostKeyboardEvent(const KeyboardEvent &e)
	{
		for (auto listener : mKeyboardListeners) {
			auto ptr = listener.lock();
			if (ptr && ptr->OnKeyboardEvent(e)) {
				return;
			}
		}
		
	}

	/* Mouse Events */
	void InputManager::PostMouseEvent(const MouseEvent &e)
	{
		for (auto listener : mMouseListeners) {
			auto ptr = listener.lock();
			if (ptr && ptr->OnMouseEvent(e)) {
				return;
			}
		}
	}
}