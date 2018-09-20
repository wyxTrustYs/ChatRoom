// PrivateDlg.cpp : 实现文件
//

#include "stdafx.h"
#include "ChatRoom.h"
#include "PrivateDlg.h"
#include "afxdialogex.h"
#include "DataType.h"
#include "PrivateChat.h"

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
	ON_NOTIFY(NM_DBLCLK, IDC_LIST1, &CPrivateDlg::OnDblclkList1)
END_MESSAGE_MAP()


// CPrivateDlg 消息处理程序


BOOL CPrivateDlg::OnInitDialog()
{
	CDialogEx::OnInitDialog();

	// TODO:  在此添加额外的初始化
	CRect rc;
	PrivateList.GetClientRect(rc);
	int Width = rc.Width();
	PrivateList.InsertColumn(0, L"好友名单", LVCFMT_CENTER, Width/2);
	PrivateList.InsertColumn(1, L"好友ID", LVCFMT_CENTER, Width/2);
	::PostMessage(AfxGetMainWnd()->m_hWnd, WM_Search, (WPARAM)m_hWnd, NULL);
	return TRUE;
}

afx_msg LRESULT CPrivateDlg::OnUpdatefrnd(WPARAM wParam, LPARAM lParam)
{
	RecvSearch* update = (RecvSearch*)lParam;

	// 获取插入到的位置
	int index = PrivateList.GetItemCount();

	// 添加用户名到列表
	// &update->name[1]  和Python相关的编码问题
	PrivateList.InsertItem(index,CString(update->nick));
	PrivateList.SetItemText(index, 1, CString(update->name));
	return 0;
}


void CPrivateDlg::OnDblclkList1(NMHDR *pNMHDR, LRESULT *pResult)
{
	LPNMITEMACTIVATE pNMItemActivate = reinterpret_cast<LPNMITEMACTIVATE>(pNMHDR);
	// TODO: 在此添加控件通知处理程序代码
	CString person = PrivateList.GetItemText(pNMItemActivate->iItem, 1);
	CPrivateChat* m_prichat = new CPrivateChat(person);
	m_prichat->Create(IDD_DIALOG1,this);
	m_prichat->ShowWindow(SW_SHOW);
	*pResult = 0;
}
