//
// DesignDocs.xaml.cpp
// Implementation of the DesignDocs class
//

#include "pch.h"
#include "DesignDocs.xaml.h"

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

DesignDocs::DesignDocs()
{
	InitializeComponent();
}

void Simple3DGameXaml::DesignDocs::ReturnToMain_Click(Platform::Object ^ sender, Windows::UI::Xaml::RoutedEventArgs ^ e)
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
