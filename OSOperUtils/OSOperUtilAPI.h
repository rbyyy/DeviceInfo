#pragma once

#ifdef OSOPERUTILS_EXPORTS
#	define DLL_API __declspec(dllexport)
#else
#	define DLL_API __declspec(dllimport)
#endif