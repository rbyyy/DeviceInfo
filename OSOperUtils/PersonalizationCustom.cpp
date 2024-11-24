#include "pch.h"
#include "PersonalizationCustom.h"

PersonalizationCustom::PersonalizationCustom()
{
}

PersonalizationCustom::~PersonalizationCustom()
{
}

int PersonalizationCustom::GetPersonalizationThemeMode()
{
    HKEY hKey;
    const wchar_t* subKey = L"SOFTWARE\\Microsoft\\Windows\\CurrentVersion\\Themes\\Personalize";
    const wchar_t* valueName = L"AppsUseLightTheme";
    DWORD value = -1;
    DWORD valueSize = sizeof(DWORD);
    if (RegOpenKeyEx(HKEY_CURRENT_USER, subKey, 0, KEY_READ, &hKey) == ERROR_SUCCESS)
    {
        HRESULT hr = RegGetValue(hKey, nullptr, valueName, RRF_RT_REG_DWORD, nullptr, &value, &valueSize);
        if (hr != S_OK)
        {
            value = -1;
        }
        RegCloseKey(hKey);
    }

    if (value == 0)
    {
        // dark mode
        return 0;
    }
    else if (value == 1)
    {
        // light mode
        return 1;
    }
    else
    {
        // unknown
    }
    return -1;
}

void PersonalizationCustom::SetPersonalizationThemeMode(int mode)
{
	HKEY hKey;
	const wchar_t* subKey = L"SOFTWARE\\Microsoft\\Windows\\CurrentVersion\\Themes\\Personalize";
	const wchar_t* valueName = L"AppsUseLightTheme";
    const wchar_t* sysValueName = L"SystemUsesLightTheme";
	DWORD value = mode;
	DWORD valueSize = sizeof(DWORD);
	

    if (RegOpenKeyEx(HKEY_CURRENT_USER, subKey, 0, KEY_WRITE, &hKey) == ERROR_SUCCESS)
    {
		HRESULT hr = RegSetValueEx(hKey, sysValueName, 0, REG_DWORD, (const BYTE*)&value, valueSize);
		if (hr != S_OK)
		{
			// failed
		}
		RegCloseKey(hKey);
    }

    if (RegOpenKeyEx(HKEY_CURRENT_USER, subKey, 0, KEY_WRITE, &hKey) == ERROR_SUCCESS)
    {
        HRESULT hr = RegSetValueEx(hKey, valueName, 0, REG_DWORD, (const BYTE*)&value, valueSize);
        if (hr != S_OK)
        {
            // failed
        }
        RegCloseKey(hKey);
    }
}
