#include "TestRequest.h"
#include "../ThirdParty/cpp-httplib/httplib.h"

TestRequest::TestRequest()
{

}

std::string TestRequest::Method()
{
	return "Get";
}

std::string TestRequest::Url()
{
	return "http://cpp-httplib-server.yhirose.repl.co";
}

std::string TestRequest::Path()
{
	return "hi";
}

void TestRequest::Test()
{
	httplib::Client cli("http://cpp-httplib-server.yhirose.repl.co");
	auto res = cli.Get("/hi");
	if (res) {
		if (res->status == 200) {
			printf("%s\n", res->body.c_str());
		}
		unsigned long tId = GetCurrentThreadId();
		std::cout << "1233tid result: " << tId << std::endl;
		//PostAppMessage(tId, 100024, 0, 0);
		Sleep(3000);
		if (m_Callback)
		{
			//m_Callback(std::to_wstring(m_count));
		}
	}
}

void TestRequest::SetCallback(std::function<void(std::wstring)> cb)
{
	m_Callback = cb;
}
