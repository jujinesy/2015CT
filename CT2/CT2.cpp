#include "CT2.h"


CCT2::CCT2()
{
}


CCT2::~CCT2()
{
}

BOOL WINAPI CCT2::MyFileTimeToSystemTime(FILETIME *lpFileTime, LPSYSTEMTIME lpSystemTime){
	return FileTimeToSystemTime(lpFileTime, lpSystemTime);
}