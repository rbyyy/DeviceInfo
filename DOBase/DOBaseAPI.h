#pragma once

#ifdef DOBASE_EXPORTS
#	define DO_BASE_API __declspec(dllexport)
#else
#	define DO_BASE_API __declspec(dllimport)
#endif