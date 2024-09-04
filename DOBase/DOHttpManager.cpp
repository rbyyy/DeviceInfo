#include "DOHttpManager.h"
#include <mutex>

static DOHttpManager* instance = nullptr;
static std::mutex mtx;
DOHttpManager* DOHttpManager::GetInstance()
{
	if (nullptr == instance)
	{
		std::lock_guard<std::mutex> lock(mtx);
		if (nullptr == instance)
		{
			instance = new DOHttpManager();
		}
	}
	return instance;
}

void DOHttpManager::HttpRequest(DOBaseRequest* request, BaseResponse callback)
{
	AddTask([=]() {
		if (nullptr != request)
		{
			request->Execute(callback);
		}
	});
}

void DOHttpManager::Stop()
{
	m_IsRunning = false;
	m_Condition.notify_all();
}

DOHttpManager::DOHttpManager()
	: m_IsRunning(true)
{
	threads.push_back(std::thread([this]() {
		while (true) {
			std::unique_lock<std::mutex> lock(m_Mutex, std::try_to_lock);
			if (lock.owns_lock())
			{
				m_Condition.wait(lock, [this]() { return !m_TaskQueue.empty() || !m_IsRunning; });
				if (!m_IsRunning && m_TaskQueue.empty())
				{
					break;
				}
				auto task = m_TaskQueue.front();
				m_TaskQueue.pop();
				task();
				lock.unlock();
			}
			else
			{
				std::this_thread::sleep_for(std::chrono::milliseconds(10));
			}
		}
	}));
}

DOHttpManager::~DOHttpManager()
{
}

