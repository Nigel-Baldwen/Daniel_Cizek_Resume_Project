//
// VideoPlayback.xaml.h
// Declaration of the VideoPlayback class
//

#pragma once

#include "Core\VideoPlayback.g.h"
#include "DirectXPage.xaml.h"

using namespace Windows::Media::Playback;

namespace Simple3DGameXaml
{
	/// <summary>
	/// An empty page that can be used on its own or navigated to within a Frame.
	/// </summary>
	[Windows::Foundation::Metadata::WebHostHidden]
	public ref class VideoPlayback sealed
	{
	public:
		VideoPlayback();
		
	private:
		void _thankYouVideo_MediaEnded(MediaPlayer^ sender, Object^ e);
	};
}
