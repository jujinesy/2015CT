
// CT5Dlg.h : ��� ����
//

#pragma once


// CCT5Dlg ��ȭ ����
class CCT5Dlg : public CDialogEx
{
// �����Դϴ�.
public:
	CCT5Dlg(CWnd* pParent = NULL);	// ǥ�� �������Դϴ�.

// ��ȭ ���� �������Դϴ�.
	enum { IDD = IDD_CT5_DIALOG };

	protected:
	virtual void DoDataExchange(CDataExchange* pDX);	// DDX/DDV �����Դϴ�.


// �����Դϴ�.
protected:
	HICON m_hIcon;
	char szFilePath[MAX_PATH];
	HANDLE	hFile;
	LPVOID	hFileMapping;
	LPVOID ImageBase;

	// ������ �޽��� �� �Լ�
	virtual BOOL OnInitDialog();
	afx_msg void OnSysCommand(UINT nID, LPARAM lParam);
	afx_msg void OnPaint();
	afx_msg HCURSOR OnQueryDragIcon();
	DECLARE_MESSAGE_MAP()
public:
	afx_msg void OnBnClickedOpenBtn();

	BOOL OpenFileDlg(HWND hwnd);
	BOOL LoadFile(LPTSTR lpFilename);
	BOOL IsPEFile(LPVOID ImageBase);
	void ShowFileHeaderInfo(HWND hWnd);
	void ShowOptionHeaderInfo(HWND hWnd);
};
