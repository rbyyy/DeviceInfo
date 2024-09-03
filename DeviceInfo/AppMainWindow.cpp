#include "AppMainWindow.h"
#include <sstream>
#include <string>
//#include "base/base.h"
#include "../DOBase/TestRequest.h"
#include "../DOBase/DOHttpManager.h"

const std::wstring AppMainWindow::kClassName = L"AppMainWindow";

LRESULT AppMainWindow::MessageHandler(UINT uMsg, WPARAM wParam, LPARAM lParam, BOOL& bHandled)
{
    return LRESULT();
}

LRESULT AppMainWindow::HandleMessage(UINT uMsg, WPARAM wParam, LPARAM lParam)
{
    OutputDebugStringW(L"12345678");
    __super::HandleMessage(uMsg, wParam, lParam);
    return TRUE;
}

std::wstring AppMainWindow::GetSkinFolder()
{
    return L"MainWindow";
}

std::wstring AppMainWindow::GetSkinFile()
{
    return L"MainWindow.xml";
}

std::wstring AppMainWindow::GetWindowClassName() const
{
    return kClassName;
}

void AppMainWindow::InitWindow()
{
	m_pLabel = static_cast<ui::Label*>(FindControl(L"tooltip"));
	m_pBtnTest = static_cast<ui::Button*>(FindControl(L"btn_request"));
    m_pBtnTest->AttachClick([this](ui::EventArgs* args) {
		OnBtnTestClick(args);
        return true;
    });
}

LRESULT AppMainWindow::OnClose(UINT uMsg, WPARAM wParam, LPARAM lParam, BOOL& bHandled)
{
    PostQuitMessage(0L);
    return __super::OnClose(uMsg, wParam, lParam, bHandled);
}

void AppMainWindow::SetLabelContent(std::wstring& text)
{
    unsigned long tId = GetCurrentThreadId();
	m_pLabel->SetText(text.c_str());
}

void AppMainWindow::OnBtnTestClick(ui::EventArgs* args)
{
	//std::wstringstream wss;
	//wss << L"Button clicked";
	//m_pLabel->SetText(wss.str().c_str());
	//MessageBox(m_hWnd, wss.str().c_str(), L"Info", MB_OK);

    TestRequest *testRequest = new TestRequest();
	DOHttpManager::GetInstance()->HttpRequest(testRequest, [=](int code, std::string res) {
		unsigned long tId = GetCurrentThreadId();
		std::wstring wres(res.begin(), res.end());
		this->SetLabelContent(wres);
		delete testRequest;
	});

	/*m_vecTestRequest.push(testRequest);

    testRequest->SetCallback([this](std::wstring res) {
        unsigned long tId = GetCurrentThreadId();
        this->SetLabelContent(res);
        if (m_vecTestRequest.size() > 0)
        {
			m_vecTestRequest.pop();
        }
    });*/
}