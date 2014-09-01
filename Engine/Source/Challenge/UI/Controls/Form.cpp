#include <Challenge/Challenge.h>
#include "Form.h"
#include <Challenge/Input/InputManager.h>

namespace challenge
{
	Form::Form(Frame frame) :
		View(frame),
		mPanel(new PanelView(frame))
	{
		this->AddInternalSubview(mPanel);

		this->AddKeyboardEvent(KeyboardEventKeyDown, [this](View *sender, const KeyboardEvent &e) {
			if (e.keyCode == SpecialKeyTab) {
				auto &subviews = this->GetSubviews();
				bool focusNext = false;
				for (View *view : subviews) {
					if (focusNext) {
						FormElement *elem = dynamic_cast<FormElement *>(view);
						if (elem) {
							elem->SetFocused(true);
							break;
						}
					}

					if (view->IsFocused()) {
						focusNext = true;
					}
				}
			}
			else if (e.keyCode == SpecialKeyEnter) {
				if (mSubmitDelegate) {
					mSubmitDelegate(this, "submit");
				}
			}
		});
	}

	Form::~Form()
	{
	}

	void Form::AddElement(FormElement *formElement)
	{
		auto it = std::find(mFormElements.begin(), mFormElements.end(), formElement);
		if(it == mFormElements.end()) {
			mFormElements.push_back(formElement);
		}
		
	}

	void Form::AddMultiFormElement(MultiFormElement *formElement)
	{
		auto it = std::find(mMultiFormElements.begin(), mMultiFormElements.end(), formElement);
		if(it == mMultiFormElements.end()) {
			mMultiFormElements.push_back(formElement);
		}
	}

	void Form::AddSubmitButton(ButtonView *button, const std::string &action)
	{
		if (!mSubmitButtons.count(action)) {
			button->AddMouseEvent(MouseEventMouseDown, [this, action](View *sender, const MouseEvent &e) {
				if(mSubmitDelegate) {
					mSubmitDelegate(this, action);
				}
			});
			mSubmitButtons[action] = button;

			this->AddSubview(button);
		}

	}

	void Form::AddSubmitDelegate(const std::string &action, SubmitDelegate submitDelegate)
	{

	}

	TFormValuesList Form::GetValues()
	{
		TFormValuesList values;

		for(FormElement *element : mFormElements) {
			if (element->GetName().length() > 0) {
				values[element->GetName()].push_back(element->GetValue());
			}
		}

		for (MultiFormElement *element : mMultiFormElements) {
			for (int i = 0; i < element->GetNumValues(); i++) {
				if (element->GetName().length() > 0) {
					values[element->GetName()].push_back(element->GetValue(i));
				}
			}
		}

		return values;
	}

	void Form::ParseFromXML(XMLNode &node)
	{
		View::ParseFromXML(node);
	}

	void Form::OnXMLParseComplete()
	{

	}

	void Form::AddSubview(View *view)
	{
		View::AddSubview(view);

		this->FindFormElements(view);
	}

	void Form::Update(int deltaMillis)
	{
		if (this->IsLayoutInvalid()) {
			this->FindFormElements(this);
		}

		View::Update(deltaMillis);
	}

	void Form::Measure(const Size &parentSize)
	{
		View::Measure(parentSize);
	}

	void Form::FindFormElements(View *view)
	{
		FormElement *formElement = dynamic_cast<FormElement *>(view);
		if (formElement) {
			this->AddElement(formElement);
		}

		MultiFormElement *multiElement = dynamic_cast<MultiFormElement *>(view);
		if (multiElement) {
			this->AddMultiFormElement(multiElement);
		}

		ButtonView *button = dynamic_cast<ButtonView *>(view);
		if (button && button->GetAttribute("type") == "submit") {
			this->AddSubmitButton(button, button->GetAttribute("action"));
		}

		for (View *subview : view->GetSubviews()) {
			this->FindFormElements(subview);
		}
	}
};