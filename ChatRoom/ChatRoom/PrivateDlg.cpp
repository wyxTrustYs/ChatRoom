// PrivateDlg.cpp : 实现文件
//

#include "stdafx.h"
#include "ChatRoom.h"
#include "PrivateDlg.h"
#include "afxdialogex.h"
#include "DataType.h"

// CPrivateDlg 对话框

IMPLEMENT_DYNAMIC(CPrivateDlg, CDialogEx)

CPrivateDlg::CPrivateDlg(CWnd* pParent /*=NULL*/)
	: CDialogEx(IDD_DIALOGSin, pParent)
{

}

CPrivateDlg::~CPrivateDlg()
{
}

void CPrivateDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
	DDX_Control(pDX, IDC_LIST1, PrivateList);
}


BEGIN_MESSAGE_MAP(CPrivateDlg, CDialogEx)
	ON_MESSAGE(WM_UPDATEFRND, &CPrivateDlg::OnUpdatefrnd)
END_MESSAGE_MAP()


// CPrivateDlg 消息处理程序


BOOL CPrivateDlg::OnInitDialog()
{
	CDialogEx::OnInitDialog();

	// TODO:  在此添加额外的初始化
	CRect rc;
	PrivateList.GetClientRect(rc);
	//int Width = rc.Width();
	PrivateList.InsertColumn(0, L"好友名单", 0, 200);
	::PostMessage(AfxGetMainWnd()->m_hWnd, WM_Search, (WPARAM)m_hWnd, NULL);
	return TRUE;
}

afx_msg LRESULT CPrivateDlg::OnUpdatefrnd(WPARAM wParam, LPARAM lParam)
{
	RecvSearch* update = (RecvSearch*)lParam;

	// 获取插入到的位置
	int index = PrivateList.GetItemCount()+1;

	// 添加用户名到列表
	// &update->name[1]  和Python相关的编码问题
	PrivateList.InsertItem(index,CString(update->name));
	// ff fe 4d 00 61 00 78 00 41 00【.?M.a.x.A】
	return 0;
}
