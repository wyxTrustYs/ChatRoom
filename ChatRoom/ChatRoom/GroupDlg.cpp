// GroupDlg.cpp : 实现文件
//

#include "stdafx.h"
#include "ChatRoom.h"
#include "GroupDlg.h"
#include "afxdialogex.h"


// GroupDlg 对话框

IMPLEMENT_DYNAMIC(GroupDlg, CDialogEx)

GroupDlg::GroupDlg(CWnd* pParent /*=NULL*/)
	: CDialogEx(IDD_DIALOGGroup, pParent)
{

}

GroupDlg::~GroupDlg()
{
}

void GroupDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
	DDX_Control(pDX, IDC_LISTGroup, CGroupList);
}


BEGIN_MESSAGE_MAP(GroupDlg, CDialogEx)
END_MESSAGE_MAP()


// GroupDlg 消息处理程序


BOOL GroupDlg::OnInitDialog()
{
	CDialogEx::OnInitDialog();

	// TODO:  在此添加额外的初始化
	CRect rc;
	CGroupList.GetClientRect(rc);
	//int Width = rc.Width();
	CGroupList.InsertColumn(0, L"群名单", 0, 200);
//	::PostMessage(AfxGetMainWnd()->m_hWnd, WM_Search, (WPARAM)m_hWnd, NULL);
	return TRUE;  
}
