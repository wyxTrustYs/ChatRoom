#pragma once
#include "afxwin.h"


// CPrivateChat 对话框

class CPrivateChat : public CDialogEx
{
	DECLARE_DYNAMIC(CPrivateChat)

public:
	CPrivateChat(CString Title,CWnd* pParent = NULL);   // 标准构造函数
	virtual ~CPrivateChat();

// 对话框数据
#ifdef AFX_DESIGN_TIME
	enum { IDD = IDD_DIALOG1 };
#endif

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV 支持

	DECLARE_MESSAGE_MAP()
public:
	CString Title_name;
	CString PriTextView;
	CString PriEditView;

	virtual BOOL OnInitDialog();
protected:
	afx_msg LRESULT OnGetfriendmsg(WPARAM wParam, LPARAM lParam);
public:
	afx_msg void OnBnClickedSend();

};
