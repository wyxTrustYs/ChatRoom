#pragma once
#include "afxcmn.h"


// CPrivateDlg �Ի���

class CPrivateDlg : public CDialogEx
{
	DECLARE_DYNAMIC(CPrivateDlg)

public:
	CPrivateDlg(CWnd* pParent = NULL);   // ��׼���캯��
	virtual ~CPrivateDlg();

// �Ի�������
#ifdef AFX_DESIGN_TIME
	enum { IDD = IDD_DIALOGSin };
#endif

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV ֧��

	DECLARE_MESSAGE_MAP()
public:

	CListCtrl PrivateList;
	virtual BOOL OnInitDialog();
protected:
	afx_msg LRESULT OnUpdatefrnd(WPARAM wParam, LPARAM lParam);
public:
	afx_msg void OnDblclkList1(NMHDR *pNMHDR, LRESULT *pResult);
};
