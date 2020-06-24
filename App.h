#pragma once

#include <string>

#include "pch.h"
#include "SimpleRenderer.h"

using namespace winrt;
using namespace winrt::Windows::ApplicationModel::Activation;
using namespace winrt::Windows::ApplicationModel::Core;
using namespace winrt::Windows::UI::Core;

namespace CoreAppAngle
{
	struct App : winrt::implements<App, IFrameworkView>
    {
    public:
        App();

        // IFrameworkView Methods.
        void Initialize(CoreApplicationView const & applicationView);
        void SetWindow(CoreWindow const & window);
        void Load(hstring const & entryPoint);
        void Run();
        void Uninitialize();

    private:
        void RecreateRenderer();

        // Application lifecycle event handlers.
        void OnActivated(CoreApplicationView const & applicationView, IActivatedEventArgs const & args);

        // Window event handlers.
        void OnVisibilityChanged(CoreWindow const & sender, VisibilityChangedEventArgs const & args);
        void OnWindowClosed(CoreWindow const & sender, CoreWindowEventArgs const & args);

        void InitializeEGL(CoreWindow const & window);
        void CleanupEGL();

        bool mWindowClosed;
        bool mWindowVisible;

        EGLDisplay mEglDisplay;
        EGLContext mEglContext;
        EGLSurface mEglSurface;

        std::unique_ptr<SimpleRenderer> mCubeRenderer;
    };

}
