#include "pch.h"
#include "App.xaml.h"

using namespace Platform;
using namespace Simple3DGameXaml;
using namespace Windows::ApplicationModel;
using namespace Windows::ApplicationModel::Activation;
using namespace Windows::Foundation;
using namespace Windows::UI::Core;
using namespace Windows::UI::Xaml;


//----------------------------------------------------------------------

App::App()
{
    InitializeComponent();
    Suspending += ref new SuspendingEventHandler(this, &App::OnSuspending);
    Resuming += ref new EventHandler<Object^>(this, &App::OnResuming);

#if defined(_DEBUG)
    UnhandledException += ref new UnhandledExceptionEventHandler([](Object^ /* sender */, UnhandledExceptionEventArgs^ args)
    {
        String^ error = "Simple3DGameXaml::App::UnhandledException: " + args->Message + "\n";
        OutputDebugStringW(error->Data());
    });
#endif

    RequiresPointerMode = ApplicationRequiresPointerMode::WhenRequested;
}

//----------------------------------------------------------------------

void App::OnLaunched(_In_ LaunchActivatedEventArgs^ e)
{
	auto rootFrame = dynamic_cast<Controls::Frame^>(Window::Current->Content);

	// Do not repeat app initialization when the Window already has content,
	// just ensure that the window is active
	if (rootFrame == nullptr)
	{
		// Create a Frame to act as the navigation context and associate it with
		// a SuspensionManager key
		rootFrame = ref new Controls::Frame();

		rootFrame->NavigationFailed += ref new Windows::UI::Xaml::Navigation::NavigationFailedEventHandler(this, &App::OnNavigationFailed);

		if (e->PreviousExecutionState == ApplicationExecutionState::Terminated)
		{
			// TODO: Restore the saved session state only when appropriate, scheduling the
			// final launch steps after the restore is complete
		}

		if (rootFrame->Content == nullptr)
		{
			// When the navigation stack isn't restored navigate to the first page,
			// configuring the new page by passing required information as a navigation
			// parameter
			rootFrame->Navigate(Interop::TypeName(DirectXPage::typeid), e->Arguments);
		}
		// Place the frame in the current Window
		Window::Current->Content = rootFrame;
		// Ensure the current window is active
		Window::Current->Activate();
		
		// Set up a handle to the main page.
		// This enables the various events such as
		// Suspending and Resuming.
		m_mainPage = (DirectXPage^) rootFrame->Content;
	}
	else
	{
		if (rootFrame->Content == nullptr)
		{
			// When the navigation stack isn't restored navigate to the first page,
			// configuring the new page by passing required information as a navigation
			// parameter
			
			rootFrame->Navigate(Interop::TypeName(DirectXPage::typeid), e->Arguments);
		}
		// Ensure the current window is active
		Window::Current->Activate();
	}
}

void App::OnNavigationFailed(Platform::Object ^sender, Windows::UI::Xaml::Navigation::NavigationFailedEventArgs ^e)
{
	throw ref new FailureException("Failed to load Page " + e->SourcePageType.Name);
}

//----------------------------------------------------------------------

void App::OnSuspending(
    _In_ Object^ /* sender */,
    _In_ SuspendingEventArgs^ args
    )
{
    m_mainPage->OnSuspending();
}

//----------------------------------------------------------------------

void App::OnResuming(
    _In_ Object^ /* sender */,
    _In_ Object^ /* args */
    )
{
    m_mainPage->OnResuming();
}

//----------------------------------------------------------------------