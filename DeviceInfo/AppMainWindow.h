#pragma once
#include <string>
#include "framework.h"

class AppMainWindow : public ui::WindowImplBase
{
public:
	AppMainWindow() {};
	virtual ~AppMainWindow() {};
	virtual LRESULT MessageHandler(UINT uMsg, WPARAM wParam, LPARAM lParam, BOOL& bHandled) override;
	virtual LRESULT HandleMessage(UINT uMsg, WPARAM wParam, LPARAM lParam) override;
	virtual std::wstring GetSkinFolder() override;
	virtual std::wstring GetSkinFile() override;
	virtual std::wstring GetWindowClassName() const override;

	virtual void InitWindow() override;
	virtual LRESULT OnClose(UINT uMsg, WPARAM wParam, LPARAM lParam, BOOL& bHandled) override;

public:
	void SetLabelContent(std::wstring& text);

public:
	static const std::wstring kClassName;

protected:
	void OnBtnTestClick(ui::EventArgs* args);

private:
	ui::Label* m_pLabel = nullptr;
	ui::Button* m_pBtnTest = nullptr;
};

