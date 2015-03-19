#pragma once
#include <windows.h>

#ifdef myexport
#define MYCT2 __declspec(dllexport)
#else
#define MYCT2 __declspec(dllimport)
#endif


class MYCT2 CCT2
{
public:
	CCT2();
	virtual ~CCT2();
	BOOL WINAPI MyFileTimeToSystemTime(FILETIME *lpFileTime, LPSYSTEMTIME lpSystemTime);
};

