//
// DesignDocs.xaml.h
// Declaration of the DesignDocs class
//

#pragma once

#include "Core\DesignDocs.g.h"
#include "DirectXPage.xaml.h"

namespace Simple3DGameXaml
{
	/// <summary>
	/// An empty page that can be used on its own or navigated to within a Frame.
	/// </summary>
	[Windows::Foundation::Metadata::WebHostHidden]
	public ref class DesignDocs sealed
	{
	public:
		DesignDocs();

	private:
		void ReturnToMain_Click(Platform::Object^ sender, Windows::UI::Xaml::RoutedEventArgs^ e);
	};
}
