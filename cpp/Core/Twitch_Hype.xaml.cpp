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
}

// The alternative way to do this whole thing would be to just have two seperate panels with the different images and just
// transition between the two with an animation. I probably should switch to that method of doing things soon since the
// swap between images is somewhat jarring currently.

void Simple3DGameXaml::Twitch_Hype::UpperHalf_PointerEntered(Platform::Object^ sender, Windows::UI::Xaml::Input::PointerRoutedEventArgs^ e)
{
	Twitch_Button->Visibility = Windows::UI::Xaml::Visibility::Visible;

	auto bitmapImage = ref new Windows::UI::Xaml::Media::Imaging::BitmapImage();
	// Call BaseUri on the root Page element and combine it with a relative path
	// to consruct an absolute URI.
	bitmapImage->UriSource = ref new Windows::Foundation::Uri(BaseUri->AbsoluteUri, "../Assets/Images/Twitch_PoE_Still_Grey.png");
	PoE_Still->Source = bitmapImage;
	
	auto bitmapImage2 = ref new Windows::UI::Xaml::Media::Imaging::BitmapImage();
	bitmapImage2->UriSource = ref new Windows::Foundation::Uri(BaseUri->AbsoluteUri, "../Assets/Images/Twitch_DD_Still_Grey.png");
	DD_Still->Source = bitmapImage2;
}

void Simple3DGameXaml::Twitch_Hype::UpperHalf_PointerExited(Platform::Object^ sender, Windows::UI::Xaml::Input::PointerRoutedEventArgs^ e)
{
	Twitch_Button->Visibility = Windows::UI::Xaml::Visibility::Collapsed;
	
	auto bitmapImage = ref new Windows::UI::Xaml::Media::Imaging::BitmapImage();
	// Call BaseUri on the root Page element and combine it with a relative path
	// to consruct an absolute URI.
	bitmapImage->UriSource = ref new Windows::Foundation::Uri(BaseUri->AbsoluteUri, "../Assets/Images/Twitch_PoE_Still.png");
	PoE_Still->Source = bitmapImage;

	auto bitmapImage2 = ref new Windows::UI::Xaml::Media::Imaging::BitmapImage();
	bitmapImage2->UriSource = ref new Windows::Foundation::Uri(BaseUri->AbsoluteUri, "../Assets/Images/Twitch_DD_Still.png");
	DD_Still->Source = bitmapImage2;
}