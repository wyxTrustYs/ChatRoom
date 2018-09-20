// GroupDlg.cpp : 实现文件
//

#include "stdafx.h"
#include "ChatRoom.h"
#include "GroupDlg.h"
#include "afxdialogex.h"
#include "DataType.h"
#include "GroupChat.h"
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
	ON_MESSAGE(WM_UPDATEGROUP, &GroupDlg::OnUpdategroup)
	ON_NOTIFY(NM_DBLCLK, IDC_LISTGroup, &GroupDlg::OnDblclkListgroup)
END_MESSAGE_MAP()


// GroupDlg 消息处理程序


BOOL GroupDlg::OnInitDialog()
{
	CDialogEx::OnInitDialog();

	// TODO:  在此添加额外的初始化
	CRect rc;
	CGroupList.GetClientRect(rc);
	int Width = rc.Width();
	CGroupList.InsertColumn(0, L"群名称", 0, Width/2);
	CGroupList.InsertColumn(1, L"群ID", 0, Width / 2);
	::PostMessage(AfxGetMainWnd()->m_hWnd, WM_SearchGroup, (WPARAM)m_hWnd, NULL);
	return TRUE;  
}


afx_msg LRESULT GroupDlg::OnUpdategroup(WPARAM wParam, LPARAM lParam)
{
	RecvSearch* update = (RecvSearch*)lParam;

	// 获取插入到的位置
	int index = CGroupList.GetItemCount();

	// 添加用户名到列表
	// &update->name[1]  和Python相关的编码问题
	CGroupList.InsertItem(index, CString(update->nick));
	CGroupList.SetItemText(index, 1, CString(update->ID));
	return 0;
}


void GroupDlg::OnDblclkListgroup(NMHDR *pNMHDR, LRESULT *pResult)
{
	LPNMITEMACTIVATE pNMItemActivate = reinterpret_cast<LPNMITEMACTIVATE>(pNMHDR);
	CString title = CGroupList.GetItemText(pNMItemActivate->iItem, 0);
	CString id = CGroupList.GetItemText(pNMItemActivate->iItem, 1);
	CGroupChat* m_prichat = new CGroupChat(title,id);
	m_prichat->Create(IDD_DIALOGGrouChat, this);
	m_prichat->ShowWindow(SW_SHOW);
	*pResult = 0;
}
