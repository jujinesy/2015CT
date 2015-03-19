
// CT5Dlg.cpp : ���� ����
//

#include "stdafx.h"
#include "CT5.h"
#include "CT5Dlg.h"
#include "afxdialogex.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#endif


// ���� ���α׷� ������ ���Ǵ� CAboutDlg ��ȭ �����Դϴ�.

class CAboutDlg : public CDialogEx
{
public:
	CAboutDlg();

// ��ȭ ���� �������Դϴ�.
	enum { IDD = IDD_ABOUTBOX };

	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV �����Դϴ�.

// �����Դϴ�.
protected:
	DECLARE_MESSAGE_MAP()
};

CAboutDlg::CAboutDlg() : CDialogEx(CAboutDlg::IDD)
{
}

void CAboutDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
}

BEGIN_MESSAGE_MAP(CAboutDlg, CDialogEx)
END_MESSAGE_MAP()


// CCT5Dlg ��ȭ ����



CCT5Dlg::CCT5Dlg(CWnd* pParent /*=NULL*/)
	: CDialogEx(CCT5Dlg::IDD, pParent)
{
	m_hIcon = AfxGetApp()->LoadIcon(IDR_MAINFRAME);
}

void CCT5Dlg::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
}

BEGIN_MESSAGE_MAP(CCT5Dlg, CDialogEx)
	ON_WM_SYSCOMMAND()
	ON_WM_PAINT()
	ON_WM_QUERYDRAGICON()
	ON_BN_CLICKED(IDC_OPEN_BTN, &CCT5Dlg::OnBnClickedOpenBtn)
END_MESSAGE_MAP()


// CCT5Dlg �޽��� ó����

BOOL CCT5Dlg::OnInitDialog()
{
	CDialogEx::OnInitDialog();

	// �ý��� �޴��� "����..." �޴� �׸��� �߰��մϴ�.

	// IDM_ABOUTBOX�� �ý��� ��� ������ �־�� �մϴ�.
	ASSERT((IDM_ABOUTBOX & 0xFFF0) == IDM_ABOUTBOX);
	ASSERT(IDM_ABOUTBOX < 0xF000);

	CMenu* pSysMenu = GetSystemMenu(FALSE);
	if (pSysMenu != NULL)
	{
		BOOL bNameValid;
		CString strAboutMenu;
		bNameValid = strAboutMenu.LoadString(IDS_ABOUTBOX);
		ASSERT(bNameValid);
		if (!strAboutMenu.IsEmpty())
		{
			pSysMenu->AppendMenu(MF_SEPARATOR);
			pSysMenu->AppendMenu(MF_STRING, IDM_ABOUTBOX, strAboutMenu);
		}
	}

	// �� ��ȭ ������ �������� �����մϴ�.  ���� ���α׷��� �� â�� ��ȭ ���ڰ� �ƴ� ��쿡��
	//  �����ӿ�ũ�� �� �۾��� �ڵ����� �����մϴ�.
	SetIcon(m_hIcon, TRUE);			// ū �������� �����մϴ�.
	SetIcon(m_hIcon, FALSE);		// ���� �������� �����մϴ�.

	// TODO: ���⿡ �߰� �ʱ�ȭ �۾��� �߰��մϴ�.

	return TRUE;  // ��Ŀ���� ��Ʈ�ѿ� �������� ������ TRUE�� ��ȯ�մϴ�.
}

void CCT5Dlg::OnSysCommand(UINT nID, LPARAM lParam)
{
	if ((nID & 0xFFF0) == IDM_ABOUTBOX)
	{
		CAboutDlg dlgAbout;
		dlgAbout.DoModal();
	}
	else
	{
		CDialogEx::OnSysCommand(nID, lParam);
	}
}

// ��ȭ ���ڿ� �ּ�ȭ ���߸� �߰��� ��� �������� �׸�����
//  �Ʒ� �ڵ尡 �ʿ��մϴ�.  ����/�� ���� ����ϴ� MFC ���� ���α׷��� ��쿡��
//  �����ӿ�ũ���� �� �۾��� �ڵ����� �����մϴ�.

void CCT5Dlg::OnPaint()
{
	if (IsIconic())
	{
		CPaintDC dc(this); // �׸��⸦ ���� ����̽� ���ؽ�Ʈ�Դϴ�.

		SendMessage(WM_ICONERASEBKGND, reinterpret_cast<WPARAM>(dc.GetSafeHdc()), 0);

		// Ŭ���̾�Ʈ �簢������ �������� ����� ����ϴ�.
		int cxIcon = GetSystemMetrics(SM_CXICON);
		int cyIcon = GetSystemMetrics(SM_CYICON);
		CRect rect;
		GetClientRect(&rect);
		int x = (rect.Width() - cxIcon + 1) / 2;
		int y = (rect.Height() - cyIcon + 1) / 2;

		// �������� �׸��ϴ�.
		dc.DrawIcon(x, y, m_hIcon);
	}
	else
	{
		CDialogEx::OnPaint();
	}
}

// ����ڰ� �ּ�ȭ�� â�� ���� ���ȿ� Ŀ���� ǥ�õǵ��� �ý��ۿ���
//  �� �Լ��� ȣ���մϴ�.
HCURSOR CCT5Dlg::OnQueryDragIcon()
{
	return static_cast<HCURSOR>(m_hIcon);
}



void CCT5Dlg::OnBnClickedOpenBtn()
{
	HWND hwnd = 0;

	OpenFileDlg(hwnd);
	if (!LoadFile((LPTSTR)szFilePath))
	{
		MessageBoxW(_T("Load file failed!"), _T("Load file failed!"), 0);
	}
	if (!IsPEFile(ImageBase))
	{
		MessageBoxW(_T("File is not a PE format file"), _T("Load file failed!"), 0);
	}
	ShowFileHeaderInfo(hwnd);
	ShowOptionHeaderInfo(hwnd);
}

BOOL CCT5Dlg::OpenFileDlg(HWND hwnd)
{
	OPENFILENAME ofn;
	memset(szFilePath, 0, MAX_PATH);
	memset(&ofn, 0, sizeof(ofn));

	ofn.lStructSize = sizeof(ofn);
	ofn.hwndOwner = hwnd;
	ofn.hInstance = GetModuleHandle(NULL);
	ofn.nMaxFile = MAX_PATH;
	ofn.lpstrInitialDir = (LPCWSTR)".";
	ofn.lpstrFile = (LPWSTR)szFilePath;
	ofn.lpstrTitle = (LPCWSTR)"";
	ofn.Flags = OFN_PATHMUSTEXIST | OFN_FILEMUSTEXIST | OFN_HIDEREADONLY;
	ofn.lpstrFilter = (LPCWSTR)"*.*\0*.*\0";
	if (!GetOpenFileName(&ofn))
		return FALSE;
	return TRUE;

}

BOOL CCT5Dlg::LoadFile(LPTSTR lpFilename)
{
	hFile = CreateFile(lpFilename, GENERIC_READ, \
		FILE_SHARE_READ, NULL, \
		OPEN_EXISTING, FILE_ATTRIBUTE_NORMAL, 0);
	if (!hFile)
		return FALSE;
	hFileMapping = CreateFileMapping(hFile, NULL, PAGE_READONLY, 0, 0, NULL);

	if (!hFileMapping)
	{
		CloseHandle(hFile);
		return FALSE;
	}
	ImageBase = MapViewOfFile(hFileMapping, FILE_MAP_READ, 0, 0, 0);
	if (!ImageBase)
	{
		CloseHandle(hFile);
		return FALSE;
	}
	return TRUE;

}

BOOL CCT5Dlg::IsPEFile(LPVOID ImageBase)
{
	PIMAGE_DOS_HEADER  pDH = NULL;
	PIMAGE_NT_HEADERS  pNtH = NULL;

	if (!ImageBase)
		return FALSE;

	pDH = (PIMAGE_DOS_HEADER)ImageBase;
	if (pDH->e_magic != IMAGE_DOS_SIGNATURE)
		return FALSE;

	pNtH = (PIMAGE_NT_HEADERS32)((DWORD)pDH + pDH->e_lfanew);
	if (pNtH->Signature != IMAGE_NT_SIGNATURE)
		return FALSE;

	return TRUE;


}


void CCT5Dlg::ShowFileHeaderInfo(HWND hWnd)
{
	char   cBuff[30];
	PIMAGE_DOS_HEADER  pDH = NULL;
	PIMAGE_NT_HEADERS  pNtH = NULL;
	PIMAGE_FILE_HEADER pFH = NULL;

	pDH = (PIMAGE_DOS_HEADER)ImageBase;
	pNtH = (PIMAGE_NT_HEADERS)((DWORD)pDH + pDH->e_lfanew);
	pFH = &pNtH->FileHeader;
	if (!pFH)
	{
		MessageBoxW(_T("Can't get File Header ! "), _T("PE-Parser"), MB_OK);
		return;
	}
	wsprintf((LPWSTR)cBuff, L"0x%04lX", pDH->e_magic);
	SetDlgItemText(IDC_EDIT_DH_MAGIC, (LPWSTR)cBuff);

	wsprintf((LPWSTR)cBuff, L"0x%04lX", pDH->e_ip);
	SetDlgItemText(IDC_EDIT_DH_IP, (LPWSTR)cBuff);

	wsprintf((LPWSTR)cBuff, L"0x%04lX", pDH->e_cs);
	SetDlgItemText(IDC_EDIT_DH_CS, (LPWSTR)cBuff);

	wsprintf((LPWSTR)cBuff, L"0x%04lX", sizeof(IMAGE_DOS_HEADER));
	SetDlgItemText(IDC_EDIT_DH_SIZE, (LPWSTR)cBuff);

	wsprintf((LPWSTR)cBuff, L"0x%04lX", pNtH->Signature);
	SetDlgItemText(IDC_EDIT_FH_SIG, (LPWSTR)cBuff);

	wsprintf((LPWSTR)cBuff, L"0x%04lX", pFH->Machine);
	SetDlgItemText(IDC_EDIT_FH_MACHINE, (LPWSTR)cBuff);

	wsprintf((LPWSTR)cBuff, L"0x%04lX", pFH->NumberOfSections);
	SetDlgItemText(IDC_EDIT_FH_NUMOFSECTIONS, (LPWSTR)cBuff);

	wsprintf((LPWSTR)cBuff, L"0x%08lX", pFH->TimeDateStamp);
	SetDlgItemText(IDC_EDIT_FH_TDS, (LPWSTR)cBuff);

	wsprintf((LPWSTR)cBuff, L"0x%08lX", pFH->PointerToSymbolTable);
	SetDlgItemText(IDC_EDIT_FH_PTSYMBOL, (LPWSTR)cBuff);

	wsprintf((LPWSTR)cBuff, L"0x%08lX", pFH->NumberOfSymbols);
	SetDlgItemText(IDC_EDIT_FH_NUMOFSYM, (LPWSTR)cBuff);

	wsprintf((LPWSTR)cBuff, L"0x%04lX", pFH->SizeOfOptionalHeader);
	SetDlgItemText(IDC_EDIT_FH_SIZEOFOH, (LPWSTR)cBuff);

	wsprintf((LPWSTR)cBuff, L"0x%04lX", pFH->Characteristics);
	SetDlgItemText(IDC_EDIT_FH_CHARACTERISTICS, (LPWSTR)cBuff);


}

void CCT5Dlg::ShowOptionHeaderInfo(HWND hWnd)
{
	char   cBuff[30];
	PIMAGE_DOS_HEADER  pDH = NULL;
	PIMAGE_NT_HEADERS  pNtH = NULL;
	PIMAGE_OPTIONAL_HEADER pOH = NULL;

	pDH = (PIMAGE_DOS_HEADER)ImageBase;
	pNtH = (PIMAGE_NT_HEADERS)((DWORD)pDH + pDH->e_lfanew);
	pOH = &pNtH->OptionalHeader;
	if (!pOH)
	{
		MessageBoxW(_T("Can't get Optional Header !:("), _T("PEInfo_Example"), MB_OK);
		return;
	}
	wsprintf((LPWSTR)cBuff, L"0x%08lX", pOH->AddressOfEntryPoint);
	SetDlgItemText(IDC_EDIT_OH_EP, (LPWSTR)cBuff);

	wsprintf((LPWSTR)cBuff, L"0x%08lX", pOH->ImageBase);
	SetDlgItemText(IDC_EDIT_OH_IMAGEBASE, (LPWSTR)cBuff);

	wsprintf((LPWSTR)cBuff, L"0x%08lX", pOH->BaseOfCode);
	SetDlgItemText(IDC_EDIT_OH_CODEBASE, (LPWSTR)cBuff);

	wsprintf((LPWSTR)cBuff, L"0x%08lX", pOH->BaseOfData);
	SetDlgItemText(IDC_EDIT_OH_DATABASE, (LPWSTR)cBuff);

	wsprintf((LPWSTR)cBuff, L"0x%08lX", pOH->SizeOfImage);
	SetDlgItemText(IDC_EDIT_OH_IMAGESIZE, (LPWSTR)cBuff);

	wsprintf((LPWSTR)cBuff, L"0x%08lX", pOH->SizeOfHeaders);
	SetDlgItemText(IDC_EDIT_OH_HEADERSIZE, (LPWSTR)cBuff);

	wsprintf((LPWSTR)cBuff, L"0x%08lX", pOH->SectionAlignment);
	SetDlgItemText(IDC_EDIT_OH_SECTIONALIGN, (LPWSTR)cBuff);

	wsprintf((LPWSTR)cBuff, L"0x%08lX", pOH->FileAlignment);
	SetDlgItemText(IDC_EDIT_OH_FILEALIGN, (LPWSTR)cBuff);

	wsprintf((LPWSTR)cBuff, L"0x%08lX", pOH->Subsystem);
	SetDlgItemText(IDC_EDIT_OH_SUBSYSTEM, (LPWSTR)cBuff);

	wsprintf((LPWSTR)cBuff, L"0x%04lX", pOH->CheckSum);
	SetDlgItemText(IDC_EDIT_OH_CHECKSUM, (LPWSTR)cBuff);

	wsprintf((LPWSTR)cBuff, L"0x%04lX", pOH->DllCharacteristics);
	SetDlgItemText(IDC_EDIT_OH_DLLFLAGS, (LPWSTR)cBuff);
}