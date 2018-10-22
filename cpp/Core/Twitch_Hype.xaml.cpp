//
// Twitch_Hype.xaml.cpp
// Implementation of the Twitch_Hype class
//

#include "pch.h"
#include "Twitch_Hype.xaml.h"

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
// The Blank Page item template is documented at https://go.microsoft.com/fwlink/?LinkId=234238

Twitch_Hype::Twitch_Hype()
{
	InitializeComponent();
}

Simple3DGameXaml::Twitch_Hype::Twitch_Hype(DirectXPage ^ mainMenu)
{
	throw ref new Platform::NotImplementedException();
}

void Simple3DGameXaml::Twitch_Hype::ReturnToMain_Click(Platform::Object ^ sender, Windows::UI::Xaml::RoutedEventArgs ^ e)
{
	// Switching pages requires a Xaml update, so it hase to be thread safe.
	Dispatcher->RunAsync(
		CoreDispatcherPriority::Normal,
		ref new DispatchedHandler([this]()
	{
		this->Frame->Navigate(Interop::TypeName(DirectXPage::typeid));
	})
	);
	//Window::Current->Content = ref new DirectXPage();
}
