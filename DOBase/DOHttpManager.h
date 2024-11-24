#pragma once
#include "DOBaseAPI.h"
#include <thread>
#include <queue>
#include <functional>
#include <mutex>
#include <condition_variable>

#include "DOBaseRequest.h"

class DO_BASE_API DOHttpManager
{
public:
	static DOHttpManager* GetInstance();

public:
	template<typename FunctionType>
	void AddTask(FunctionType&& task)
	{
		{
			std::lock_guard<std::mutex> lock(m_Mutex);
			m_TaskQueue.push(std::forward<FunctionType>(task));
		}
		m_Condition.notify_one();
	}

	void HttpRequest(DOBaseRequest* request, BaseResponse callback);
	void Stop();

private:
	DOHttpManager();
	~DOHttpManager();
	DOHttpManager(const DOHttpManager&) = delete;
	DOHttpManager& operator=(const DOHttpManager&) = delete;

private:
	std::queue<std::function<void()>> m_TaskQueue;
	std::mutex m_Mutex;
	std::condition_variable m_Condition;
	bool m_IsRunning;
	//std::thread m_WorkerThread;
	std::vector<std::thread> threads;
};

