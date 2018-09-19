#pragma once
#include "ListTab.h"
#include "Mysocket.h"


// CFriendList 对话框

class CFriendList : public CDialogEx
{
	DECLARE_DYNAMIC(CFriendList)

public:
	
	CFriendList(CString m_title,CWnd* pParent = NULL);   // 标准构造函数
	virtual ~CFriendList();

// 对话框数据
#ifdef AFX_DESIGN_TIME
	enum { IDD = IDD_Dlg };
#endif

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV 支持

	DECLARE_MESSAGE_MAP()
public:
	CString title;
	ListTab m_ListTab;
	virtual BOOL OnInitDialog();
	CMysocket m_socket;
protected:
public:
	afx_msg void OnClose();
};
