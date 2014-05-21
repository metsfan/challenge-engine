#include "GUITesting.h"
#include <Challenge/UI/Controls/TextFieldView.h>

void GUITesting::OnApplicationInitialized(GameApplication *app)
{
	auto window = app->GetWindow();

	/*TextFieldView *textField = new TextFieldView(Frame(100, 100, 75, 30));
	textField->SetBorderWidth(1);
	textField->SetBorderColor(Color::Black());
	window->AddSubview(textField);*/

	LabelView *label = new LabelView(Frame(100, 100, 75, 30));
	label->SetText("Hello");
	label->SetTextColor(Color::Red());
	label->SetBackgroundColor(Color::Clear());
	window->AddSubview(label);
}

void GUITesting::OnApplicationDestroyed(GameApplication *app)
{

}

void GUITesting::OnApplicationUpdate(GameApplication *app, uint32_t deltaMillis)
{

}

void GUITesting::OnApplicationRender(GameApplication *app, IGraphicsDevice *device)
{

}