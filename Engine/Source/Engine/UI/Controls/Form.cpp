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

	void Form::AddElement(FormElement *formElement)
	{
		auto it = std::find(mFormElements.begin(), mFormElements.end(), formElement);
		if(it != mFormElements.end()) {
			mPanel->AddSubview(formElement);
			mFormElements.push_back(formElement);
		}
		
	}

	void Form::AddMultiFormElement(MultiFormElement *formElement)
	{
		auto it = std::find(mMultiFormElements.begin(), mMultiFormElements.end(), formElement);
		if(it != mMultiFormElements.end()) {
			mPanel->AddSubview(formElement);
			mMultiFormElements.push_back(formElement);
		}
	}

	void Form::AddSubmitButton(ButtonView *button, const std::string &action)
	{
		if(!mSubmitButtons.count(action)) {
			button->AddMouseDownDelegate([this, action](View *sender, const MouseEvent &e) {
				if(mSubmitDelegate) {
					mSubmitDelegate(this, action);
				}
			});
			mSubmitButtons[action] = button;

			this->AddSubview(button);
		}

	}

	const std::map<std::string, std::string> Form::GetValues()
	{
		std::map<std::string, std::string> values;

		for(FormElement *element : mFormElements) {
			values[element->GetName()] = element->GetValue();
		}

		return values;
	}

	const std::map<std::string, std::vector<std::string>> Form::GetMultiValues()
	{
		std::map<std::string, std::vector<std::string>> values;

		for(MultiFormElement *element : mMultiFormElements) {
			for(int i = 0; i < element->GetNumValues(); i++) {
				values[element->GetName()].push_back(element->GetValue(i));
			}
		}

		return values;
	}

	void Form::ParseFromXML(XMLNode &node)
	{
		View::ParseFromXML(node);
	}
};