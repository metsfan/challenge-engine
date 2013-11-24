#include <Engine/Challenge.h>
#include "Form.h"

namespace challenge
{
	Form::Form(Frame frame) :
		View(frame),
		mPanel(new PanelView(frame))
	{
		this->AddInternalSubview(mPanel);
	}

	Form::~Form()
	{
	}

	void Form::PositionSubviews()
	{
		View::PositionSubviews();

		this->FindFormElements(this);
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

	const std::map<std::string, std::vector<std::string>> Form::GetValues()
	{
		std::map<std::string, std::vector<std::string>> values;

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