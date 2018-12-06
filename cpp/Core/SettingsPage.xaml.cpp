//
// SettingsPage.xaml.cpp
// Implementation of the SettingsPage class
//

#include "pch.h"
#include "SettingsPage.xaml.h"

using namespace Simple3DGameXaml;

using namespace Platform;
using namespace Windows::Foundation;
using namespace Windows::Foundation::Collections;
using namespace Windows::UI::Xaml;
using namespace Windows::UI::Xaml::Controls;
using namespace Windows::UI::Xaml::Controls::Primitives;
using namespace Windows::UI::Xaml::Data;
using namespace Windows::UI::Xaml::Input;
using namespace Windows::UI::Xaml::Media;
using namespace Windows::UI::Xaml::Navigation;
using namespace Windows::UI::Core;
using namespace Windows::UI::Xaml::Interop;

// The Blank Page item template is documented at https://go.microsoft.com/fwlink/?LinkId=234238

SettingsPage::SettingsPage()
{
	InitializeComponent();
	this->NavigationCacheMode = Windows::UI::Xaml::Navigation::NavigationCacheMode::Enabled;
	localSettings = Windows::Storage::ApplicationData::Current->LocalSettings;
	keyBindingsList = localSettings->Containers->Lookup("KeyBindings")->Values;

	// TODO :: We properly save keybinding state between runs, but it isn't reflected
	// when you revisit the page since the value of the text box reverts to the placeholder
	// text every reload. It ought to be the case that after setting a bind, the user sees
	// the custom binding in place when they revisit the menu. This is more than just QOL,
	// but at the end of the day, there are more pressing matters currently.
}


void Simple3DGameXaml::SettingsPage::BackButton_Click(Platform::Object^ sender, Windows::UI::Xaml::RoutedEventArgs^ e)
{
	// Switching pages requires a Xaml update, so it has to be thread safe.
	Dispatcher->RunAsync(
		CoreDispatcherPriority::Normal,
		ref new DispatchedHandler([this]()
	{
		this->Frame->Navigate(TypeName(DirectXPage::typeid));
	})
	);
}

//void Simple3DGameXaml::SettingsPage::ForwardBox_TextChanged(Platform::Object^ sender, Windows::UI::Xaml::Controls::TextChangedEventArgs^ e)
//{
//	keyBindingsList->Insert("forwardBinding", ProcessTextBoxText(ForwardBox->Text));
//}

void Simple3DGameXaml::SettingsPage::ForwardBox_KeyDown(Platform::Object^ sender, Windows::UI::Xaml::Input::KeyRoutedEventArgs^ e)
{
	auto textBox = safe_cast<TextBox^>(sender);
	textBox->Text = virtualKey_IndexToString[(int)e->Key];
	keyBindingsList->Insert("forwardBinding", textBox->Text);
}


void Simple3DGameXaml::SettingsPage::BackwardBox_KeyDown(Platform::Object^ sender, Windows::UI::Xaml::Input::KeyRoutedEventArgs^ e)
{
	auto textBox = safe_cast<TextBox^>(sender);
	textBox->Text = virtualKey_IndexToString[(int)e->Key];
	keyBindingsList->Insert("backBinding", textBox->Text);
}


void Simple3DGameXaml::SettingsPage::LeftBox_KeyDown(Platform::Object^ sender, Windows::UI::Xaml::Input::KeyRoutedEventArgs^ e)
{
	auto textBox = safe_cast<TextBox^>(sender);
	textBox->Text = virtualKey_IndexToString[(int)e->Key];
	keyBindingsList->Insert("leftBinding", textBox->Text);
}


void Simple3DGameXaml::SettingsPage::RightBox_KeyDown(Platform::Object^ sender, Windows::UI::Xaml::Input::KeyRoutedEventArgs^ e)
{
	auto textBox = safe_cast<TextBox^>(sender);
	textBox->Text = virtualKey_IndexToString[(int)e->Key];
	keyBindingsList->Insert("rightBinding", textBox->Text);
}


void Simple3DGameXaml::SettingsPage::UpBox_KeyDown(Platform::Object^ sender, Windows::UI::Xaml::Input::KeyRoutedEventArgs^ e)
{
	auto textBox = safe_cast<TextBox^>(sender);
	textBox->Text = virtualKey_IndexToString[(int)e->Key];
	keyBindingsList->Insert("upBinding", textBox->Text);
}


void Simple3DGameXaml::SettingsPage::DownBox_KeyDown(Platform::Object^ sender, Windows::UI::Xaml::Input::KeyRoutedEventArgs^ e)
{
	auto textBox = safe_cast<TextBox^>(sender);
	textBox->Text = virtualKey_IndexToString[(int)e->Key];
	keyBindingsList->Insert("downBinding", textBox->Text);
}


void Simple3DGameXaml::SettingsPage::PauseBox_KeyDown(Platform::Object^ sender, Windows::UI::Xaml::Input::KeyRoutedEventArgs^ e)
{
	auto textBox = safe_cast<TextBox^>(sender);
	textBox->Text = virtualKey_IndexToString[(int)e->Key];
	keyBindingsList->Insert("pauseBinding", textBox->Text);
}


void Simple3DGameXaml::SettingsPage::BindingBox_PointerPressed(Platform::Object^ sender, Windows::UI::Xaml::Input::PointerRoutedEventArgs^ e)
{
	auto textBox = safe_cast<TextBox^>(sender);
	textBox->PlaceholderText = "";
}
