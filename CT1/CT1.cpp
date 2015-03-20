#include "CT1.h"

CCT1::CCT1()
{
	Rf();
}

CCT1::~CCT1()
{}

void CCT1::Rf()
{
	setlocale(LC_ALL, "korean");
	CStdioFile rfile, wfile;
	CString data_str;
	std::regex pattern("\\w*\t([0-9]{4})""/([0-9]{2})""/([0-9]{2})"" ([0-9]{2})"":([0-9]{2})"":([0-9]{2})""\t([\\w]*):""[a-zA-Z0-9\\s]*\\[[a-zA-Z0-9\\s]*\\][a-zA-Z0-9\\s]*\\[(\\S*)\\]"" ([a-zA-Z0-9\\s\\[\\]\\.]*)");
	std::string replacer = "$7,$8,$1년 $2월 $3일 $4시 $5분 $6초,$9\n";
	if (rfile.Open(_T("Q_1.txt"), CFile::modeRead | CFile::typeText))
	{
		wfile.Open((CString)"Q_1.csv", CFile::modeCreate | CFile::modeNoTruncate | CFile::modeReadWrite);
		while (rfile.ReadString(data_str))
		{
			CT2CA pszConvertedAnsiString(data_str);
			wfile.WriteString((CString)std::regex_replace((std::string)pszConvertedAnsiString, pattern, replacer).c_str());
		}
		rfile.Close();
		wfile.Close();
	}
	else
	{
		MessageBoxW(0, _T("Q_1.txt이 없다."), 0, 0);
	}
}

int _tmain(int argc, _TCHAR* argv[])
{
	CCT1 ★;
	return 0;
}