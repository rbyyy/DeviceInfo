#pragma once

#include "resource.h"
class AppMainWindow;

class MainThread : public nbase::FrameworkThread
{
public:
	MainThread() : nbase::FrameworkThread("MainThread") {}
	virtual ~MainThread() {}

	AppMainWindow* GetMainWindow() { return m_pMainWindow; }

private:
	virtual void Init() override;
	virtual void Cleanup() override;

private:
	AppMainWindow* m_pMainWindow = nullptr;
};