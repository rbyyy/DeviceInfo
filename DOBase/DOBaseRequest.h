#pragma once
#include <string>
#include <map>
#include <functional>

/*
* int: status code
* std::string: response body
* std::string: error message
*/
using BaseResponse = std::function<void(int, std::string, std::string)>;

class DOBaseRequest
{
public:
	DOBaseRequest();
	virtual ~DOBaseRequest();
	
	virtual std::string Method() = 0;
	virtual std::string Url() = 0;
	virtual std::string Path();
	virtual std::multimap<std::string, std::string> CustomHeaders() { return {}; };
	virtual std::multimap<std::string, std::string> CustomParameters() { return {}; };
	virtual int CustomTimeout() { return 5; }

	void Execute(BaseResponse callback);

private:
	void GetRequest(BaseResponse callback);
	void PostRequest(BaseResponse callback);

};

