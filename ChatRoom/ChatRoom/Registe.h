#pragma once


// CRegiste 对话框


class CRegiste : public CDialogEx
{
	DECLARE_DYNAMIC(CRegiste)

public:
	CRegiste(CWnd* pParent = NULL);   // 标准构造函数
	virtual ~CRegiste();

// 对话框数据
#ifdef AFX_DESIGN_TIME
	enum { IDD = IDD_RegistDlg };
#endif

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV 支持

	DECLARE_MESSAGE_MAP()
public:
	int RMan;
	CString Enickname;
	CString Erepwd;
	CString Epwdcom;
	CString Eid;
	afx_msg void OnBnClickedOk();
protected:
	afx_msg LRESULT OnRegister2(WPARAM wParam, LPARAM lParam);
};
