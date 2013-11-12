#pragma once

#include <Engine/Challenge.h>
#include <Engine/UI/Controls/FormElement.h>
#include <Engine/UI/Controls/PanelView.h>
#include <Engine/UI/Controls/ButtonView.h>

namespace challenge
{
	class Form;

	typedef std::function<void(Form *form, const std::string &action)> SubmitDelegate;

	class Form : public View
	{
	public:
		Form(Frame frame = Frame());
		~Form();

		void AddElement(FormElement *formElement);
		void AddMultiFormElement(MultiFormElement *formElement);
		void AddSubmitButton(ButtonView *button, const std::string &action);

		void SetSubmitDelegate(SubmitDelegate submitDelegate) { mSubmitDelegate = submitDelegate; }

		const std::map<std::string, std::string> GetValues();
		const std::map<std::string, std::vector<std::string>> GetMultiValues();

	protected:
		virtual void ParseFromXML(XMLNode &node);

	private:
		PanelView *mPanel;
		std::vector<FormElement *> mFormElements;
		std::vector<MultiFormElement *> mMultiFormElements;
		std::map<std::string, ButtonView *> mSubmitButtons;
		SubmitDelegate mSubmitDelegate;
	};
};