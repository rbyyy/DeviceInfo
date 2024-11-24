#pragma once
#include "OSOperUtilAPI.h"

class DLL_API PersonalizationCustom
{
public:
	enum MyEnum
	{

	};

public:
	PersonalizationCustom();
	~PersonalizationCustom();

	/*
	* Dark Theme  : 0
	* Light Theme : 1
	*/
	int  GetPersonalizationThemeMode();
	void SetPersonalizationThemeMode(int mode);
};

