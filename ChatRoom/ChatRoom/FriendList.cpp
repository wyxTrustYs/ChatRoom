// FriendList.cpp : 实现文件
//

#include "stdafx.h"
#include "ChatRoom.h"
#include "FriendList.h"
#include "afxdialogex.h"
#include "PrivateDlg.h"
#include "GroupList.h"
#include "resource.h"
// CFriendList 对话框

IMPLEMENT_DYNAMIC(CFriendList, CDialogEx)

CFriendList::CFriendList(CWnd* pParent /*=NULL*/)
	: CDialogEx(IDD_Dlg, pParent)
{
	
}

CFriendList::~CFriendList()
{
}

void CFriendList::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
	DDX_Control(pDX, IDC_TAB3, m_ListTab);
}


BEGIN_MESSAGE_MAP(CFriendList, CDialogEx)

//	ON_MESSAGE(WM_SearchFriendAndGroup, &CFriendList::OnSearchfriendandgroup)
END_MESSAGE_MAP()


// CFriendList 消息处理程序


BOOL CFriendList::OnInitDialog()
{
	CDialogEx::OnInitDialog();

	m_ListTab.InsertItem(0, L"好友");
	m_ListTab.InsertItem(1, L"群聊");

	m_ListTab.m_dia[0] = new CPrivateDlg();
	m_ListTab.m_dia[1] = new CGroupList();

	m_ListTab.m_dia[0]->Create(IDD_DIALOGSin, &m_ListTab);
	m_ListTab.m_dia[1]->Create(IDD_DIALOGGroup, &m_ListTab);

	CRect rc;
	m_ListTab.GetClientRect(rc);
	rc.DeflateRect(2, 24, 3, 2);
	m_ListTab.m_dia[0]->MoveWindow(rc);
	m_ListTab.m_dia[1]->MoveWindow(rc);

	m_ListTab.m_dia[0]->ShowWindow(SW_SHOW);
	m_ListTab.m_dia[0]->ShowWindow(SW_HIDE);


	::PostMessage(AfxGetMainWnd()->m_hWnd, WM_Search, (WPARAM)m_hWnd, NULL);

	return TRUE;  
}


