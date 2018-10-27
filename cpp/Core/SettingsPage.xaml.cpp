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


void Simple3DGameXaml::SettingsPage::ForwardBox_TextChanged(Platform::Object^ sender, Windows::UI::Xaml::Controls::TextChangedEventArgs^ e)
{
	auto values = localSettings->Containers->Lookup("KeyBindings")->Values;
	values->Insert("forwardBinding", ForwardBox->Text);
}


void Simple3DGameXaml::SettingsPage::BackwardBox_TextChanged(Platform::Object^ sender, Windows::UI::Xaml::Controls::TextChangedEventArgs^ e)
{
	auto values = localSettings->Containers->Lookup("KeyBindings")->Values;
	values->Insert("backBinding", ForwardBox->Text);
}


void Simple3DGameXaml::SettingsPage::LeftBox_TextChanged(Platform::Object^ sender, Windows::UI::Xaml::Controls::TextChangedEventArgs^ e)
{
	auto values = localSettings->Containers->Lookup("KeyBindings")->Values;
	values->Insert("leftBinding", ForwardBox->Text);
}


void Simple3DGameXaml::SettingsPage::RightBox_TextChanged(Platform::Object^ sender, Windows::UI::Xaml::Controls::TextChangedEventArgs^ e)
{
	auto values = localSettings->Containers->Lookup("KeyBindings")->Values;
	values->Insert("rightBinding", ForwardBox->Text);
}


void Simple3DGameXaml::SettingsPage::UpBox_TextChanged(Platform::Object^ sender, Windows::UI::Xaml::Controls::TextChangedEventArgs^ e)
{
	auto values = localSettings->Containers->Lookup("KeyBindings")->Values;
	values->Insert("upBinding", ForwardBox->Text);
}


void Simple3DGameXaml::SettingsPage::DownBox_TextChanged(Platform::Object^ sender, Windows::UI::Xaml::Controls::TextChangedEventArgs^ e)
{
	auto values = localSettings->Containers->Lookup("KeyBindings")->Values;
	values->Insert("downBinding", ForwardBox->Text);
}


void Simple3DGameXaml::SettingsPage::PauseBox_TextChanged(Platform::Object^ sender, Windows::UI::Xaml::Controls::TextChangedEventArgs^ e)
{
	auto values = localSettings->Containers->Lookup("KeyBindings")->Values;
	values->Insert("pauseBinding", ForwardBox->Text);
}
