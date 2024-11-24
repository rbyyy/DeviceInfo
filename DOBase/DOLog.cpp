#include "DOLog.h"
#include "spdlog/async.h"
#include "spdlog/sinks/daily_file_sink.h"
#include "spdlog/sinks/stdout_color_sinks.h"
#include "spdlog/sinks/rotating_file_sink.h"
#include "spdlog/sinks/msvc_sink.h"


// DeviceInfo
std::shared_ptr<spdlog::logger> g_DeviceInfoLogger;

namespace DOBase
{
    void DOBase::InitLogging(const std::string& dirPath)
    {
        if (g_DeviceInfoLogger != nullptr)
        {
            return;
        }
		//queue with max 32kb items 1 backing thread
		spdlog::init_thread_pool(32 * 1024, 1);
        spdlog::flush_every(std::chrono::seconds(5));

        // deviceinfo log max size 5M * 200
        std::string logFile = dirPath + "DeviceInfo.log";
        std::vector<spdlog::sink_ptr> sinks;
		sinks.push_back(std::make_shared<spdlog::sinks::daily_file_sink_mt>(logFile, 0, 0));
        sinks.push_back(std::make_shared<spdlog::sinks::stdout_color_sink_mt>());
        sinks.push_back(std::make_shared<spdlog::sinks::msvc_sink_mt>());
        //sinks.push_back(std::make_shared<spdlog::sinks::rotating_file_sink_mt>(logFile, 5, 200));
        g_DeviceInfoLogger = std::make_shared<spdlog::async_logger>("deviceinfo-logger", sinks.begin(), sinks.end(), spdlog::thread_pool(), spdlog::async_overflow_policy::block);
        g_DeviceInfoLogger->set_pattern("[%^%l%$] %Y-%m-%d %H:%M:%S.%e [%@][%!][thread:%t]: %v");
        g_DeviceInfoLogger->flush_on(spdlog::level::err);

#ifdef _DEBUG
        g_DeviceInfoLogger->set_level(spdlog::level::trace);
#else
        g_DeviceInfoLogger->set_level(spdlog::level::info);
#endif
        spdlog::register_logger(g_DeviceInfoLogger);
    }

    void DOBase::CloseLogging()
    {
        spdlog::drop_all();
        spdlog::shutdown();
    }

    std::shared_ptr<spdlog::logger>DO_BASE_API GetLogger(LogSystem logSystem)
    {
        if (logSystem == LogSystem::DeviceInfo)
        {
            return g_DeviceInfoLogger;
        }
        return nullptr;
    }
}