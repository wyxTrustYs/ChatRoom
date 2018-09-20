// FriendList.cpp : 实现文件
//

#include "stdafx.h"
#include "ChatRoom.h"
#include "FriendList.h"
#include "afxdialogex.h"
#include "PrivateDlg.h"
#include "GroupDlg.h"
#include "resource.h"
#include "DataType.h"
// CFriendList 对话框

IMPLEMENT_DYNAMIC(CFriendList, CDialogEx)

CFriendList::CFriendList(CString m_title,CWnd* pParent /*=NULL*/)
	: CDialogEx(IDD_Dlg, pParent)
	, CSearch(_T(""))
{
	this->title = m_title;
}

CFriendList::~CFriendList()
{
}

void CFriendList::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
	DDX_Control(pDX, IDC_TAB3, m_ListTab);
	DDX_Text(pDX, IDC_EDIT1, CSearch);
	DDX_Control(pDX, IDC_BUTTON1, AddFriend);
}


BEGIN_MESSAGE_MAP(CFriendList, CDialogEx)

	ON_WM_CLOSE()
	ON_BN_CLICKED(IDC_BUTTON1, &CFriendList::OnBnClickedButton1)
END_MESSAGE_MAP()


// CFriendList 消息处理程序


BOOL CFriendList::OnInitDialog()
{
	CDialogEx::OnInitDialog();
	SetWindowText(title);
	m_ListTab.InsertItem(0, L"好友");
	m_ListTab.InsertItem(1, L"群聊");

	m_ListTab.m_dia[0] = new CPrivateDlg();
	m_ListTab.m_dia[1] = new GroupDlg();

	m_ListTab.m_dia[0]->Create(IDD_DIALOGSin, &m_ListTab);
	m_ListTab.m_dia[1]->Create(IDD_DIALOGGroup, &m_ListTab);

	CRect rc;
	m_ListTab.GetClientRect(rc);
	rc.DeflateRect(2, 24, 3, 2);
	m_ListTab.m_dia[0]->MoveWindow(rc);
	m_ListTab.m_dia[1]->MoveWindow(rc);

	m_ListTab.m_dia[0]->ShowWindow(SW_SHOW);
	m_ListTab.m_dia[1]->ShowWindow(SW_HIDE);


	//::PostMessage(AfxGetMainWnd()->m_hWnd, WM_Search, (WPARAM)m_hWnd, NULL);

	return TRUE;  
}


void CFriendList::OnClose()
{
	// TODO: 在此添加消息处理程序代码和/或调用默认值
	ExitProcess(0);
	CDialogEx::OnClose();
}


void CFriendList::OnBnClickedButton1()
{
	// TODO: 在此添加控件通知处理程序代码

}
