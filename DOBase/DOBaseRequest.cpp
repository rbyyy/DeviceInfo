#include "DOBaseRequest.h"
#include <assert.h>
#include <algorithm>
#include "../ThirdParty/cpp-httplib/httplib.h"

DOBaseRequest::DOBaseRequest()
{
}

DOBaseRequest::~DOBaseRequest()
{
}

std::string DOBaseRequest::Path()
{
	return std::string();
}

void DOBaseRequest::Execute(BaseResponse callback)
{
	std::string method = Method();
	assert(!method.empty());
	std::transform(method.begin(), method.end(), method.begin(), ::toupper);
	if (method == "GET")
	{
		GetRequest(callback);
	}
	else if (method == "POST")
	{
		PostRequest(callback);
	}
}

#pragma region Private
void DOBaseRequest::GetRequest(BaseResponse callback)
{
	std::string url = Url();
	assert(!url.empty());

	httplib::Client cli(url);
	int timeout = CustomTimeout();
	if (timeout > 0)
	{
		cli.set_read_timeout(timeout, 0);
		cli.set_write_timeout(timeout, 0);
	}

	std::string path = Path();
	auto customHeaders = CustomHeaders();
	httplib::Headers headers;
	headers.insert(customHeaders.begin(), customHeaders.end());
	auto res = cli.Get("/" + path, headers);
	if (callback)
	{
		if (res)
		{
			callback(res->status, res->body, "");
		}
		else {
			auto err = res.error();
			std::string errorMsg = httplib::to_string(err);
			callback(-1, "", errorMsg);
		}
	}
}

void DOBaseRequest::PostRequest(BaseResponse callback)
{
	std::string url = Url();
	assert(!url.empty());
	httplib::Client cli(url);
	int timeout = CustomTimeout();
	if (timeout > 0)
	{
		cli.set_read_timeout(timeout, 0);
		cli.set_write_timeout(timeout, 0);
	}

	std::string path = Path();
	auto customHeaders = CustomHeaders();
	httplib::Headers headers;
	headers.insert(customHeaders.begin(), customHeaders.end());
	httplib::Params customParameters = CustomParameters();
	auto res = cli.Post(path, headers, customParameters);
	if (callback)
	{
		if (res)
		{
			callback(res->status, res->body, "");
		}
		else {
			auto err = res.error();
			std::string errorMsg = httplib::to_string(err);
			callback(-1, "", errorMsg);
		}
	}
}
#pragma endregion
