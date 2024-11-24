#pragma once

#undef SPDLOG_ACTIVE_LEVEL
#define SPDLOG_ACTIVE_LEVEL SPDLOG_LEVEL_TRACE

#include "DOBaseAPI.h"
#include <string>
#include "spdlog/spdlog.h"
#include <memory>

// multi process external logging
enum LogSystem
{
	DeviceInfo = 0
};

#define LOG_TRACE(...)        SPDLOG_LOGGER_TRACE(DOBase::GetLogger(LogSystem::DeviceInfo), __VA_ARGS__)
#define LOG_DEBUG(...)        SPDLOG_LOGGER_DEBUG(DOBase::GetLogger(LogSystem::DeviceInfo), __VA_ARGS__)
#define LOG_INFO(...)         SPDLOG_LOGGER_INFO(DOBase::GetLogger(LogSystem::DeviceInfo), __VA_ARGS__)
#define LOG_WARN(...)         SPDLOG_LOGGER_WARN(DOBase::GetLogger(LogSystem::DeviceInfo), __VA_ARGS__)
#define LOG_ERROR(...)        SPDLOG_LOGGER_ERROR(DOBase::GetLogger(LogSystem::DeviceInfo), __VA_ARGS__)
#define LOG_CRITICAL(...)     SPDLOG_LOGGER_CRITICAL(DOBase::GetLogger(LogSystem::DeviceInfo), __VA_ARGS__)

namespace DOBase 
{
	//Init Log Path, Enable the logging function
	void DO_BASE_API InitLogging(const std::string& dirPath);

	//Close the logging function
	void DO_BASE_API CloseLogging();

	//Log System
	std::shared_ptr<spdlog::logger> DO_BASE_API GetLogger(LogSystem logSystem);

}


