// CT4.cpp : 콘솔 응용 프로그램에 대한 진입점을 정의합니다.
//

#include "stdafx.h"
#include "CT4.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#endif

int _tmain(int argc, TCHAR* argv[], TCHAR* envp[])
{
	CppSQLite3DB srcDB;
	CString strDBPath, Query, query2, save, temp;
	CppSQLite3Table Result, Result2;
	CStdioFile file;

	strDBPath.Format(_T("Q_4.db"));
	if (!PathFileExists(strDBPath))					return FALSE;
	if (!srcDB.Open_Optimization(strDBPath))		return FALSE;
	Query = _T("SELECT * from Table_a");
	Result = srcDB.getTable(Query.GetBuffer());
	file.Open(_T("CT4.csv"), CFile::modeCreate | CFile::modeWrite);

	if (Result.GetRowCount() == 0){
		file.Close();
		return FALSE;
	}

	for (int i = 0; i<Result.GetRowCount(); i++){
		Result.setRow(i);
		query2.Format(_T("SELECT * from Table_b where no=%d"), Result.getIntField("no"));
		Result2 = srcDB.getTable(query2.GetBuffer());
		for (int j = 0; j<Result2.GetRowCount(); j++){
			temp.Format(_T("%d, %s\n"), i, (CString)Result2.getStringField("email")); save = save + temp;
		}
	}

	file.WriteString(save);
	file.Close();
	srcDB.close();
	return 0;
}