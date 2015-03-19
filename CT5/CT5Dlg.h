
// CT5Dlg.h : 헤더 파일
//

#pragma once


// CCT5Dlg 대화 상자
class CCT5Dlg : public CDialogEx
{
// 생성입니다.
public:
	CCT5Dlg(CWnd* pParent = NULL);	// 표준 생성자입니다.

// 대화 상자 데이터입니다.
	enum { IDD = IDD_CT5_DIALOG };

	protected:
	virtual void DoDataExchange(CDataExchange* pDX);	// DDX/DDV 지원입니다.


// 구현입니다.
protected:
	HICON m_hIcon;
	char szFilePath[MAX_PATH];
	HANDLE	hFile;
	LPVOID	hFileMapping;
	LPVOID ImageBase;

	// 생성된 메시지 맵 함수
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
