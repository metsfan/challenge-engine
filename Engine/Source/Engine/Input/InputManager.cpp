#include <Engine/Challenge.h>
#include <Engine/Event/Types/KeyboardEventData.h>
#include <Engine/Event/Types/MouseEventData.h>
#include <Engine/GameApplication.h>
#include <Engine/Event/EventManager.h>
#include <Engine/Util/Logger.h>
#include "InputManager.h"
using namespace challenge;

InputManager::InputManager()
{
	mMouseDown = false;
	mKeyDown = false;
}

void InputManager::AddKeyboardListener(IKeyboardListener *pListener)
{
	if(pListener != NULL) {
		mKeyboardListeners.push_back(pListener);
	}
}

void InputManager::AddMouseListener(IMouseListener *pListener)
{
	if(pListener != NULL) {
		mMouseListeners.push_back(pListener);
	}
}

void InputManager::ProcessKeyboardEvent(KeyboardEventType type, unsigned int keyCode)
{
	KeyboardEvent evt(type, keyCode);

	bool found = false;
	auto key = std::find(mActiveKeys.begin(), mActiveKeys.end(), keyCode);

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

void InputManager::Update()
{
	if(mKeyboardListeners.size() > 0) {
		// Process keyboard events in queue
		if(mKeyboardEventQueue.size()) {
			std::vector<KeyboardEvent> keyboardEvents(mKeyboardEventQueue.size());
			std::copy(mKeyboardEventQueue.begin(), mKeyboardEventQueue.end(), keyboardEvents.begin());
			mKeyboardEventQueue.clear();

			for(KeyboardEvent &evt : keyboardEvents) {
				auto key = std::find(mActiveKeys.begin(), mActiveKeys.end(), evt.keyCode);
				switch(evt.type) {
				case KeyboardEventKeyDown:
					if(key == mActiveKeys.end()) {
						mActiveKeys.push_back(evt.keyCode);
						this->KeyDown(evt);
					}
				
					break;

				case KeyboardEventKeyUp:
					if(key != mActiveKeys.end()) {
						mActiveKeys.erase(key);
						this->KeyUp(evt);
					}

					break;
				}
			}
		}

		// Send key press events for all active keys
		for(unsigned int key : mActiveKeys) {
			KeyboardEvent evt;
			evt.keyCode = key;
			evt.type = KeyboardEventKeyPress;

			//Logger::log(LogDebug, "Key Press: %c", key);

			this->KeyPress(evt);
		}
	}

	if(mMouseListeners.size() > 0 &&mMouseEventQueue.size() > 0) {
		std::vector<MouseEvent> mouseEvents(mMouseEventQueue.size());
		std::copy(mMouseEventQueue.begin(), mMouseEventQueue.end(), mouseEvents.begin());
		mMouseEventQueue.clear();

		std::vector<MouseEvent>::iterator mouseIt =  mouseEvents.begin();
		while(mouseIt != mouseEvents.end()) {
			switch((*mouseIt).type) {
			case MouseEventMouseDown:
				MouseDown((*mouseIt));
				break;

			case MouseEventMouseMove:
				MouseMove((*mouseIt));
				break;

			case MouseEventMouseUp:
				MouseUp((*mouseIt));
				break;

			case MouseEventMouseClick:
				MouseClick((*mouseIt));
				break;

			case MouseEventMouseDblClick:
				MouseDblClick((*mouseIt));
				break;
			}
			mouseIt++;
		}
	}
}

/* Keyboard Events */

void InputManager::KeyDown(const KeyboardEvent &e)
{
	for(IKeyboardListener *listener : mKeyboardListeners) {
		listener->OnKeyDown(e);
	}
}

void InputManager::KeyUp(const KeyboardEvent &e)
{
	for(IKeyboardListener *listener : mKeyboardListeners) {
		listener->OnKeyUp(e);
	}
}

void InputManager::KeyPress(const KeyboardEvent &e)
{
	for(IKeyboardListener *listener : mKeyboardListeners) {
		listener->OnKeyPress(e);
	}
}

/* Mouse Events */

void InputManager::MouseDown(const MouseEvent &e)
{
	TMouseListenerList::iterator it = mMouseListeners.begin();
	while(it != mMouseListeners.end()) {
		(*it)->OnMouseDown(e);
		it++;
	}
}

void InputManager::MouseUp(const MouseEvent &e)
{
	TMouseListenerList::iterator it = mMouseListeners.begin();
	while(it != mMouseListeners.end()) {
		(*it)->OnMouseUp(e);
		it++;
	}
}

void InputManager::MouseMove(const MouseEvent &e)
{
	TMouseListenerList::iterator it = mMouseListeners.begin();
	while(it != mMouseListeners.end()) {
		(*it)->OnMouseMove(e);
		it++;
	}
}

void InputManager::MouseClick(const MouseEvent &e)
{
	TMouseListenerList::iterator it = mMouseListeners.begin();
	while(it != mMouseListeners.end()) {
		(*it)->OnMouseClick(e);
		it++;
	}
}

void InputManager::MouseDblClick(const MouseEvent &e)
{
	TMouseListenerList::iterator it = mMouseListeners.begin();
	while(it != mMouseListeners.end()) {
		(*it)->OnMouseDblClick(e);
		it++;
	}
}