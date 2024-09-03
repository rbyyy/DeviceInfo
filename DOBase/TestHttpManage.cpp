#include "TestHttpManage.h"
#include <mutex>

static TestHttpManage* instance = nullptr;
static std::mutex mtx;
TestHttpManage* TestHttpManage::getInstance()
{
	if (nullptr == instance)
	{
		std::lock_guard<std::mutex> lock(mtx);
		if (nullptr == instance)
		{
			instance = new TestHttpManage();
		}
	}
	return instance;
}

TestHttpManage::TestHttpManage()
{
	threads.push_back(std::thread([this]() {
		while (true) {
			std::unique_lock<std::mutex> lock(m_Mutex);
			m_Condition.wait(lock, [this]() { return !m_TaskQueue.empty() || !m_IsRunning; });
			if (!m_IsRunning && m_TaskQueue.empty())
			{
				std::this_thread::sleep_for(std::chrono::milliseconds(10));
				continue;
			}
			auto task = m_TaskQueue.front();
			m_TaskQueue.pop();
			lock.unlock();
			task();
		}
	}));
}

TestHttpManage::~TestHttpManage()
{
}

void TestHttpManage::Stop()
{
	m_IsRunning = false;
	m_Condition.notify_all();
}


