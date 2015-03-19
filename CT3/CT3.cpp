#include "CT3.h"


CCT3::CCT3()
{
	Rf();
}

CCT3::~CCT3()
{}

void CCT3::Rf()
{
	HANDLE	hFile;
	LPVOID	hFileMapping, ImageBase;
	PIMAGE_DOS_HEADER  pDH = NULL;
	PIMAGE_NT_HEADERS  pNtH = NULL;
	PIMAGE_FILE_HEADER pFH = NULL;
	PIMAGE_OPTIONAL_HEADER pOH = NULL;
	char   cBuff[30];
	CStdioFile file;
	CString save, temp;
	file.Open(_T("CT1.txt"), CFile::modeCreate | CFile::modeWrite);

	hFile = CreateFile(L"CT1.exe", GENERIC_READ, \
		FILE_SHARE_READ, NULL, \
		OPEN_EXISTING, FILE_ATTRIBUTE_NORMAL, 0);
	hFileMapping = CreateFileMapping(hFile, NULL, PAGE_READONLY, 0, 0, NULL);
	ImageBase = MapViewOfFile(hFileMapping, FILE_MAP_READ, 0, 0, 0);
	pDH = (PIMAGE_DOS_HEADER)ImageBase;
	pNtH = (PIMAGE_NT_HEADERS32)((DWORD)pDH + pDH->e_lfanew);
	pFH = &pNtH->FileHeader;
	pOH = &pNtH->OptionalHeader;

	save.Format(_T("DOS-Header\n"));
	wsprintf((LPWSTR)cBuff, L"0x%04lX", pDH->e_magic);				temp.Format(_T("e_magic=%s\n"), cBuff); save = save + temp;
	wsprintf((LPWSTR)cBuff, L"0x%04lX", pDH->e_ip);					temp.Format(_T("e_ip=%s\n"), cBuff); save = save + temp;
	wsprintf((LPWSTR)cBuff, L"0x%04lX", pDH->e_cs);					temp.Format(_T("e_cs=%s\n"), cBuff); save = save + temp;
	wsprintf((LPWSTR)cBuff, L"0x%04lX", sizeof(IMAGE_DOS_HEADER));	temp.Format(_T("size of DOS-Header=%s\n\n"), cBuff); save = save + temp;

	temp.Format(_T("PE-Header\n")); save = save + temp;
	wsprintf((LPWSTR)cBuff, L"0x%04lX", pNtH->Signature);			temp.Format(_T("Signature=%s\n"), cBuff); save = save + temp;
	wsprintf((LPWSTR)cBuff, L"0x%04lX", pFH->Machine);				temp.Format(_T("Machine=%s\n"), cBuff); save = save + temp;
	wsprintf((LPWSTR)cBuff, L"0x%04lX", pFH->NumberOfSections);		temp.Format(_T("NumberOfSections=%s\n"), cBuff); save = save + temp;
	wsprintf((LPWSTR)cBuff, L"0x%08lX", pFH->TimeDateStamp);		temp.Format(_T("TimeDateStamp=%s\n"), cBuff); save = save + temp;
	wsprintf((LPWSTR)cBuff, L"0x%08lX", pFH->PointerToSymbolTable);	temp.Format(_T("PointerToSymbolTable=%s\n"), cBuff); save = save + temp;
	wsprintf((LPWSTR)cBuff, L"0x%08lX", pFH->NumberOfSymbols);		temp.Format(_T("NumberOfSymbols=%s\n"), cBuff); save = save + temp;
	wsprintf((LPWSTR)cBuff, L"0x%04lX", pFH->SizeOfOptionalHeader);	temp.Format(_T("SizeOfOptionalHeader=%s\n"), cBuff); save = save + temp;
	wsprintf((LPWSTR)cBuff, L"0x%04lX", pFH->Characteristics);		temp.Format(_T("Characteristics=%s\n\n"), cBuff); save = save + temp;

	temp.Format(_T("Optional-Header\n")); save = save + temp;
	wsprintf((LPWSTR)cBuff, L"0x%08lX", pOH->AddressOfEntryPoint);	temp.Format(_T("AddressOfEntryPoint=%s\n"), cBuff); save = save + temp;
	wsprintf((LPWSTR)cBuff, L"0x%08lX", pOH->ImageBase);			temp.Format(_T("ImageBase=%s\n"), cBuff); save = save + temp;
	wsprintf((LPWSTR)cBuff, L"0x%08lX", pOH->BaseOfCode);			temp.Format(_T("BaseOfCode=%s\n"), cBuff); save = save + temp;
	wsprintf((LPWSTR)cBuff, L"0x%08lX", pOH->BaseOfData);			temp.Format(_T("BaseOfData=%s\n"), cBuff); save = save + temp;
	wsprintf((LPWSTR)cBuff, L"0x%08lX", pOH->SizeOfImage);			temp.Format(_T("SizeOfImage=%s\n"), cBuff); save = save + temp;
	wsprintf((LPWSTR)cBuff, L"0x%08lX", pOH->SizeOfHeaders);		temp.Format(_T("SizeOfHeaders=%s\n"), cBuff); save = save + temp;
	wsprintf((LPWSTR)cBuff, L"0x%08lX", pOH->SectionAlignment);		temp.Format(_T("SectionAlignment=%s\n"), cBuff); save = save + temp;
	wsprintf((LPWSTR)cBuff, L"0x%08lX", pOH->FileAlignment);		temp.Format(_T("FileAlignment=%s\n"), cBuff); save = save + temp;
	wsprintf((LPWSTR)cBuff, L"0x%08lX", pOH->Subsystem);			temp.Format(_T("Subsystem=%s\n"), cBuff); save = save + temp;
	wsprintf((LPWSTR)cBuff, L"0x%04lX", pOH->CheckSum);				temp.Format(_T("CheckSum=%s\n"), cBuff); save = save + temp;
	wsprintf((LPWSTR)cBuff, L"0x%04lX", pOH->DllCharacteristics);	temp.Format(_T("DllCharacteristics=%s\n"), cBuff); save = save + temp;

	file.WriteString(save);
	file.Close();
}
int _tmain(int argc, _TCHAR* argv[])
{
	CCT3 ¡Ú;
	return 0;
}