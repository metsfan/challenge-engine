#pragma once

#include <Engine/Challenge.h>
#include <Engine/UI/Controls/FormElement.h>
#include <Engine/UI/Controls/PanelView.h>
#include <Engine/UI/Controls/ButtonView.h>

namespace challenge
{
	class Form;

	typedef std::function<void(Form *form, const std::string &action)> SubmitDelegate;
	typedef std::map<std::string, std::vector<std::string>> TFormValuesList;

	class Form : public View
	{
	public:
		Form(Frame frame = Frame());
		~Form();

		void AddSubmitButton(ButtonView *button, const std::string &action);

		void AddSubmitDelegate(const std::string &action, SubmitDelegate submitDelegate);

		void SetSubmitDelegate(SubmitDelegate submitDelegate) { mSubmitDelegate = submitDelegate; }

		const TFormValuesList GetValues();

	protected:
		virtual void ParseFromXML(XMLNode &node);
		virtual void OnXMLParseComplete();

		virtual void FindFormElements(View *view);

		virtual void PositionSubviews();

		void AddElement(FormElement *formElement);
		void AddMultiFormElement(MultiFormElement *formElement);

	private:
		PanelView *mPanel;
		std::vector<FormElement *> mFormElements;
		std::vector<MultiFormElement *> mMultiFormElements;
		std::map<std::string, ButtonView *> mSubmitButtons;
		SubmitDelegate mSubmitDelegate;
	};
};