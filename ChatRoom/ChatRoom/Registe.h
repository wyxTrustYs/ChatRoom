#pragma once


// CRegiste �Ի���


class CRegiste : public CDialogEx
{
	DECLARE_DYNAMIC(CRegiste)

public:
	CRegiste(CWnd* pParent = NULL);   // ��׼���캯��
	virtual ~CRegiste();

// �Ի�������
#ifdef AFX_DESIGN_TIME
	enum { IDD = IDD_RegistDlg };
#endif

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV ֧��

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
