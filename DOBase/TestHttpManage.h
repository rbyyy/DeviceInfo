#pragma once
#include <thread>
#include <queue>
#include <functional>
#include <mutex>
#include <condition_variable>

class TestHttpManage
{
public:
	static TestHttpManage* getInstance();

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

	void Stop();

private:
	TestHttpManage();
	~TestHttpManage();
	TestHttpManage(const TestHttpManage&) = delete;
	TestHttpManage& operator=(const TestHttpManage&) = delete;

private:
	std::queue<std::function<void()>> m_TaskQueue;
	std::mutex m_Mutex;
	std::condition_variable m_Condition;
	bool m_IsRunning = false;
	//std::thread m_WorkerThread;
	std::vector<std::thread> threads;

};

