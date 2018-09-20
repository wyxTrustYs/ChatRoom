#pragma once
#include "afxcmn.h"


// GroupDlg 对话框

class GroupDlg : public CDialogEx
{
	DECLARE_DYNAMIC(GroupDlg)

public:
	GroupDlg(CWnd* pParent = NULL);   // 标准构造函数
	virtual ~GroupDlg();

// 对话框数据
#ifdef AFX_DESIGN_TIME
	enum { IDD = IDD_DIALOGGroup };
#endif

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV 支持

	DECLARE_MESSAGE_MAP()
public:
	CListCtrl CGroupList;
	virtual BOOL OnInitDialog();
protected:
	afx_msg LRESULT OnUpdategroup(WPARAM wParam, LPARAM lParam);
public:
	afx_msg void OnDblclkListgroup(NMHDR *pNMHDR, LRESULT *pResult);
};
