#pragma once
#include <string>
#include <map>
#include <functional>

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

	void Execute(std::function<void(int, std::string)> callback);

private:
	void GetRequest(std::function<void(int, std::string)> callback);
	void PostRequest(std::function<void(int, std::string)> callback);

};

