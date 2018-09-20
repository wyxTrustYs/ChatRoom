// GroupChat.cpp : 实现文件
//

#include "stdafx.h"
#include "ChatRoom.h"
#include "GroupChat.h"
#include "afxdialogex.h"
#include "resource.h"
#include "LoginDlg.h"
// CGroupChat 对话框
#include <map>
using std::map;
extern map<CString, HWND> ChatWindows;
CLoginDlg *main;
IMPLEMENT_DYNAMIC(CGroupChat, CDialogEx)

CGroupChat::CGroupChat(CString title,CString id,CWnd* pParent /*=NULL*/)
	: CDialogEx(IDD_DIALOGGrouChat, pParent)
	, GroupText(_T(""))
	, GroupEdit(_T(""))
{
	this->WndTitle = title;
	this->Groupid = id;
}

CGroupChat::~CGroupChat()
{
}

void CGroupChat::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
	DDX_Control(pDX, IDC_LISTGroup, UserList);
	DDX_Text(pDX, IDC_TextView, GroupText);
	DDX_Text(pDX, IDC_EDITGroup, GroupEdit);
}


BEGIN_MESSAGE_MAP(CGroupChat, CDialogEx)
	ON_MESSAGE(WM_UPDATEMEMBERINGRUP, &CGroupChat::OnUpdatememberingrup)
	ON_BN_CLICKED(IDGroupSend, &CGroupChat::OnBnClickedGroupsend)
	ON_MESSAGE(WM_GETGROUPMSG, &CGroupChat::OnGetgroupmsg)

	ON_WM_CLOSE()
END_MESSAGE_MAP()


// CGroupChat 消息处理程序


BOOL CGroupChat::OnInitDialog()
{
	CDialogEx::OnInitDialog();
	CRect rc;
	UserList.GetClientRect(rc);
	int Width = rc.Width();
	UserList.InsertColumn(0, L"用户名单", LVCFMT_CENTER, Width / 2);
	UserList.InsertColumn(1, L"用户ID", LVCFMT_CENTER, Width / 2);
	// TODO:  在此添加额外的初始化
	if (Groupid == L"1")
	{
		SetWindowTextW(L"同城寂寞少妇");
	}
	else
	{
		SetWindowTextW(L"激情美女裸聊");
	}
	ChatWindows[Groupid] = GetSafeHwnd();
	main = (CLoginDlg*)AfxGetMainWnd();
	MsgInfo msg = {MsgType::UserInGroup,m_hWnd};
	
	memcpy(msg.groupid, Groupid.GetBuffer(), Groupid.GetLength() * 2);

	::SendMessage(main->m_hWnd, WM_SENDMSG, NULL, (LPARAM)&msg);
	
	return TRUE;  
}


afx_msg LRESULT CGroupChat::OnUpdatememberingrup(WPARAM wParam, LPARAM lParam)
{
	RecvSearch* update = (RecvSearch*)lParam;

	// 获取插入到的位置
	int index = UserList.GetItemCount();

	// 添加用户名到列表
	// &update->name[1]  和Python相关的编码问题
	UserList.InsertItem(index, CString(update->nick));
	UserList.SetItemText(index, 1, CString(update->ID));
	return 0;
}




void CGroupChat::OnBnClickedGroupsend()
{
	// TODO: 在此添加控件通知处理程序代码
	UpdateData(TRUE);

	// 获取当前时间
	SYSTEMTIME now = { 0 };
	GetSystemTime(&now);
	CString Time;
	Time.Format(L"%d-%2d-%2d %2d:%2d:%2d", now.wYear, now.wMonth, now.wDay,
		now.wHour, now.wMinute, now.wSecond);

	// 组合语句加入到编辑框
	GroupText = GroupText + L"你说(" + Time + L"):\r\n    " + GroupEdit + L"\r\n";

	// 获取主对话框
	//CLoginDlg *main = (CLoginDlg*)AfxGetMainWnd();

	// 填写用户的信息
 	MsgInfo msg = { MsgType::GROUPMSG, m_hWnd };
//	memcpy(msg.groupchat_msg.msg, L"abcdef", 12);
 	memcpy(msg.groupchat_msg.msg, GroupEdit.GetBuffer(), GroupEdit.GetLength() * 2);
//	memcpy(msg.groupchat_msg.from, L"1234", 4 * 2);
 	memcpy(msg.groupchat_msg.from, main->EditAccount.GetBuffer(), main->EditAccount.GetLength() * 2);


// // 	// 获取发送对象，即窗口名
	
//	memcpy(msg.groupchat_msg.to, L"1",1 * 2);
 	memcpy(msg.groupchat_msg.to, Groupid.GetBuffer(), Groupid.GetLength() * 2);
// 	// 通过主窗口发送消息
	::SendMessage(main->m_hWnd, WM_SENDMSG, NULL, (LPARAM)&msg);

	GroupEdit = "";
	UpdateData(FALSE);
}


afx_msg LRESULT CGroupChat::OnGetgroupmsg(WPARAM wParam, LPARAM lParam)
{
	// 获取发送来的消息
	FrdChatMsg* RecvInfo = (FrdChatMsg*)lParam;

	// 获取当前时间
	SYSTEMTIME now = { 0 };
	GetSystemTime(&now);
	CString Time;
	Time.Format(L"%d-%2d-%2d %2d:%2d:%2d", now.wYear, now.wMonth, now.wDay,
		now.wHour, now.wMinute, now.wSecond);

	// 组合语句加入到编辑框
	GroupText = GroupText + RecvInfo->from + L"说(" + Time + L"):\r\n    " + RecvInfo->msg + L"\r\n";

	// 更新到界面
	UpdateData(FALSE);
	return 0;
}




void CGroupChat::OnClose()
{
	// TODO: 在此添加消息处理程序代码和/或调用默认值
	ChatWindows.erase(Groupid);
	CDialogEx::OnClose();
}
