#pragma once
#include "DOBaseAPI.h"
#include <functional>
#include <string>

#include "DOBaseRequest.h"

typedef void(*IntCallback)(int);

class DO_BASE_API TestRequest : public DOBaseRequest
{
public:
	TestRequest();
	virtual ~TestRequest() {};

	std::string Method() override;
	std::string Url() override;
	std::string Path() override;

	void Test();
	void SetCallback(std::function<void(std::wstring)> cb);

private:
	std::function<void(std::wstring)> m_Callback = nullptr;
	
};

