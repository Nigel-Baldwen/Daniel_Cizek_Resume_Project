#pragma once

#if defined(_DEBUG)
#define DISABLE_XAML_GENERATED_BREAK_ON_UNHANDLED_EXCEPTION 1
#endif

#include "DirectXPage.xaml.h"
#include "App.g.h"

namespace Simple3DGameXaml
{

    [Windows::Foundation::Metadata::WebHostHidden]
    public ref class App sealed
    {
    public:
        App();

        virtual void OnLaunched(
            _In_ Windows::ApplicationModel::Activation::LaunchActivatedEventArgs^ args
            ) override;

    private:
        void OnSuspending(
            _In_ Platform::Object^ sender,
            _In_ Windows::ApplicationModel::SuspendingEventArgs^ args
            );

        void OnResuming(
            _In_ Platform::Object^ sender,
            _In_ Platform::Object^ args
            );

        void OnWindowActivationChanged(
            _In_ Platform::Object^ sender,
            _In_ Windows::UI::Core::WindowActivatedEventArgs^ args
            );

        DirectXPage^ m_mainPage;
    };
}


