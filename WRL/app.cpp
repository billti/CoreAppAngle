/*
A UWP app built directly against the WRL library.

For WRL details  https://docs.microsoft.com/en-us/cpp/cppcx/wrl/wrl-reference
Code structure   https://docs.microsoft.com/en-us/archive/msdn-magazine/2013/august/windows-with-c-the-windows-runtime-application-model
Useful reference https://github.com/Medium/phantomjs-1/blob/master/src/qt/qtbase/src/winmain/qtmain_winrt.cpp
See also code at https://hg.mozilla.org/mozilla-central/rev/5f0882ee58c0
*/

#if !defined(WINAPI_FAMILY) || (WINAPI_FAMILY != WINAPI_FAMILY_APP)
#error This app is should be compiled as a Windows Universal app
#endif

#include <assert.h>
#include <memory>

#include <Windows.h>

#include <wrl.h>
#include <wrl/wrappers/corewrappers.h>

#include <Windows.ApplicationModel.Core.h>
#include <Windows.ApplicationModel.Activation.h>

#include "SimpleRenderer.h"

using namespace Microsoft::WRL;
using namespace Microsoft::WRL::Wrappers;
using namespace ABI::Windows::Foundation;
using namespace ABI::Windows::ApplicationModel::Core;
using namespace ABI::Windows::ApplicationModel::Activation;
using namespace ABI::Windows::UI::Core;

using namespace CoreAppAngle;

typedef ITypedEventHandler<CoreApplicationView*, IActivatedEventArgs*> ActivatedEventHandler;

class MyApp : public RuntimeClass<IFrameworkView, IFrameworkViewSource>
{
  public:
    STDMETHODIMP CreateView(IFrameworkView** viewProvider) {
      *viewProvider = static_cast<IFrameworkView*>(this);
      return S_OK;
    }

    STDMETHODIMP Initialize(ICoreApplicationView* applicationView) {
      return applicationView->add_Activated(Callback<ActivatedEventHandler>(this, &MyApp::OnActivated).Get(), &m_token);
    }

    STDMETHODIMP SetWindow(ICoreWindow* window) {
      m_coreWindow = window;
      return S_OK;
    }

    STDMETHODIMP Load( HSTRING entryPoint) {
      return S_OK;
    }

    STDMETHODIMP OnActivated(ICoreApplicationView*, IActivatedEventArgs*) {
      return m_coreWindow->Activate();
    }

    STDMETHODIMP Run(void) {
      ComPtr<ICoreDispatcher> coreDispatcher;
      HRESULT hr = m_coreWindow->get_Dispatcher(coreDispatcher.GetAddressOf());
      if (FAILED(hr)) return hr;

      return coreDispatcher->ProcessEvents(CoreProcessEventsOption_ProcessUntilQuit);
    }

    STDMETHODIMP Uninitialize(void) {
      return S_OK;
    }

  private:
    ICoreWindow* m_coreWindow;
    EventRegistrationToken m_token;

    bool mWindowClosed;
    bool mWindowVisible;

    EGLDisplay mEglDisplay;
    EGLContext mEglContext;
    EGLSurface mEglSurface;

    std::unique_ptr<SimpleRenderer> mCubeRenderer;
};

int __stdcall wWinMain(HINSTANCE, HINSTANCE, PWSTR, int)
{
  HRESULT hr = RoInitialize(RO_INIT_MULTITHREADED);
  if (FAILED(hr)) return -1;

  ComPtr<IFrameworkViewSource> myApp = Make<MyApp>();

  ComPtr<ICoreApplication> coreApp;
  HString coreAppName;
  coreAppName.Set(RuntimeClass_Windows_ApplicationModel_Core_CoreApplication);
  hr = RoGetActivationFactory(coreAppName.Get(), __uuidof(ICoreApplication), reinterpret_cast<void**>(coreApp.GetAddressOf()));
  if (FAILED(hr)) return -2;

  coreApp->Run(myApp.Get());

  return 0;
}
