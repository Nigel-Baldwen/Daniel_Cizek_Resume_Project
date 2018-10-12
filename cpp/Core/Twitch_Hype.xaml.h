//
// Twitch_Hype.xaml.h
// Declaration of the Twitch_Hype class
//

#pragma once

#include "core\Twitch_Hype.g.h"
#include "DirectXPage.xaml.h"

namespace Simple3DGameXaml
{
	/// <summary>
	/// An empty page that can be used on its own or navigated to within a Frame.
	/// </summary>
	[Windows::Foundation::Metadata::WebHostHidden]
	public ref class Twitch_Hype sealed
	{
	public:
		Twitch_Hype();
		Twitch_Hype(DirectXPage^ mainMenu);
	private:
		void ReturnToMain_Click(Platform::Object^ sender, Windows::UI::Xaml::RoutedEventArgs^ e);
		DirectXPage^ MainMenu;
	};
}
