#include "DOStringUtil.h"

int DOStringUtil::ToUpper(int c)
{
	if (c >= 'a' && c <= 'z')
	{
		c += 'A' - 'a';
	}
    return c;
}

int DOStringUtil::ToLower(int c)
{
	if (c >= 'A' && c <= 'Z')
	{
		c += 'a' - 'A';
	}
	return c;
}
