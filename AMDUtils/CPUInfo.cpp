#include "pch.h"
#include "CPUInfo.h"
#include <Pdh.h>
#include "spdlog/spdlog.h"

#pragma comment(lib, "Pdh.lib")

CPUInfo::CPUInfo()
{
	spdlog::info("CPUInfo Construction");
}

CPUInfo::~CPUInfo()
{
}

void CPUInfo::GetCPUFrequency()
{
	HQUERY hQuery;
	PDH_STATUS status = PdhOpenQuery(NULL, 0, &hQuery);
	if (status != ERROR_SUCCESS)
	{

	}
}
