#pragma once
#include "afxcmn.h"


// CGroupChat �Ի���

class CGroupChat : public CDialogEx
{
	DECLARE_DYNAMIC(CGroupChat)

public:
	CGroupChat(CString title,CString id,CWnd* pParent = NULL);   // ��׼���캯��
	virtual ~CGroupChat();

// �Ի�������
#ifdef AFX_DESIGN_TIME
	enum { IDD = IDD_DIALOGGrouChat };
#endif

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV ֧��

	DECLARE_MESSAGE_MAP()
public:
	CListCtrl UserList;
	CString GroupText;
	CString GroupEdit;
	CString WndTitle;
	CString Groupid;

	virtual BOOL OnInitDialog();
protected:
	afx_msg LRESULT OnUpdatememberingrup(WPARAM wParam, LPARAM lParam);
public:
	afx_msg void OnBnClickedGroupsend();
protected:
	afx_msg LRESULT OnGetgroupmsg(WPARAM wParam, LPARAM lParam);
public:
//	afx_msg void OnIdclose();
	afx_msg void OnClose();
};
