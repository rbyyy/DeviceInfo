// DeviceInfo.cpp : 定义应用程序的入口点。
//

#include "framework.h"
#include "DeviceInfo.h"
#include "AppMainWindow.h"
#include <thread>
#include <future>
#include <iostream>

enum ThreadId
{
	kThreadUI
};

void RecResult(int result) {
    unsigned long tId = GetCurrentThreadId();
    std::cout << "122tid result: " << tId << std::endl;
	std::cout << "result: " << result << std::endl;
}

int APIENTRY wWinMain(_In_ HINSTANCE hInstance,
                     _In_opt_ HINSTANCE hPrevInstance,
                     _In_ LPWSTR    lpCmdLine,
                     _In_ int       nCmdShow)
{
    UNREFERENCED_PARAMETER(hPrevInstance);
    UNREFERENCED_PARAMETER(lpCmdLine);

    MainThread mainThread;
    //std::thread::id curId = std::this_thread::get_id();
    unsigned long tId = GetCurrentThreadId();
    std::cout << "tid result: " << tId << std::endl;

    std::promise<int> promise;
    std::future<int> future = promise.get_future();
    /*TestRequest testRequest;
    
    testRequest.SetCallback([&mainThread](std::wstring res) {
        unsigned long tId = GetCurrentThreadId();
		mainThread.GetMainWindow()->SetLabelContent(res);
    });*/
    //testRequest.Test();
    //std::thread thread(&TestRequest::Test);

    //thread.detach();
	
    OutputDebugStringW(L"12345678\n");

    mainThread.RunOnCurrentThreadWithLoop(nbase::MessageLoop::kUIMessageLoop);
    
    return 0;
}

void MainThread::Init()
{
    nbase::ThreadManager::RegisterThread(kThreadUI);
    std::wstring themeDir = nbase::win32::GetCurrentModuleDirectory();
#ifdef _DEBUG
    ui::GlobalManager::Startup(themeDir + L"resources\\", ui::CreateControlCallback(), false);
#else
#endif // _DEBUG
    m_pMainWindow = new AppMainWindow();
    if (nullptr != m_pMainWindow)
    {
        m_pMainWindow->Create(NULL, AppMainWindow::kClassName.c_str(), WS_OVERLAPPEDWINDOW & ~WS_MAXIMIZEBOX, 0);
        m_pMainWindow->CenterWindow();
        m_pMainWindow->ShowWindow();
    }
}

void MainThread::Cleanup()
{
    ui::GlobalManager::Shutdown();
    SetThreadWasQuitProperly(true);
    nbase::ThreadManager::UnregisterThread();
	
}
