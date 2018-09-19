// PrivateChat.cpp : 实现文件
//

#include "stdafx.h"
#include "ChatRoom.h"
#include "PrivateChat.h"
#include "afxdialogex.h"
#include "resource.h"
#include "DataType.h"
#include "FriendList.h"
// CPrivateChat 对话框

IMPLEMENT_DYNAMIC(CPrivateChat, CDialogEx)

CPrivateChat::CPrivateChat(CString Title, CWnd* pParent /*=NULL*/)
	: CDialogEx(IDD_DIALOG1, pParent)
	, PriTextView(_T(""))
	, PriEditView(_T(""))
{
	this->Title_name = Title;
}

CPrivateChat::~CPrivateChat()
{
}

void CPrivateChat::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
	DDX_Text(pDX, IDC_PRITEXTVIEW, PriTextView);
	//  DDX_Control(pDX, IDC_EDIT1, PriEditView);
	DDX_Text(pDX, IDC_EDIT1, PriEditView);
}


BEGIN_MESSAGE_MAP(CPrivateChat, CDialogEx)
	ON_MESSAGE(WM_GETFRIENDMSG, &CPrivateChat::OnGetfriendmsg)
	ON_BN_CLICKED(IDSEND, &CPrivateChat::OnBnClickedSend)
END_MESSAGE_MAP()


// CPrivateChat 消息处理程序


BOOL CPrivateChat::OnInitDialog()
{
	CDialogEx::OnInitDialog();

	// TODO:  在此添加额外的初始化
	SetWindowText(Title_name);
	return TRUE; 
}


afx_msg LRESULT CPrivateChat::OnGetfriendmsg(WPARAM wParam, LPARAM lParam)
{
	FrdChatMsg* RecvInfo = (FrdChatMsg*)lParam;

	// 获取当前时间
	SYSTEMTIME now = { 0 };
	GetSystemTime(&now);
	CString Time;
	Time.Format(L"%d-%2d-%2d %2d:%2d:%2d", now.wYear, now.wMonth, now.wDay,
		now.wHour, now.wMinute, now.wSecond);

	// 组合语句加入到编辑框
	PriTextView = PriTextView + RecvInfo->from + L"说(" + Time + L"):\r\n    " + RecvInfo->msg + L"\r\n";

	// 更新到界面
	UpdateData(FALSE);

	return 0;
}




void CPrivateChat::OnBnClickedSend()
{
	// TODO: 在此添加控件通知处理程序代码
	// 获取编辑框内的数据
	UpdateData(TRUE);

	// 获取当前时间
	SYSTEMTIME now = { 0 };
	GetSystemTime(&now);
	CString Time;
	Time.Format(L"%d-%2d-%2d %2d:%2d:%2d", now.wYear, now.wMonth, now.wDay,
		now.wHour, now.wMinute, now.wSecond);

	// 组合语句加入到编辑框
	PriTextView = PriTextView + L"你说(" + Time + L"):\r\n    " + PriEditView + L"\r\n";

	// 获取主对话框
	//CFriendList *main = (CFriendList*)AfxGetMainWnd();
	CString str;
	CWnd* main = GetParent();
	//main = main->GetParent();
	main->GetWindowTextW(str);
	//MessageBox(str, str, NULL);
	// 填写用户的信息
	MsgInfo msg = { MsgType::FRIENDMSG, m_hWnd };
	memcpy(msg.frdchat_msg.msg, PriEditView.GetBuffer(), PriEditView.GetLength() * 2);
	memcpy(msg.frdchat_msg.from, str.GetBuffer(),str.GetLength() * 2);

	// 获取发送对象，即窗口名
	CString To;
	this->GetWindowTextW(To);
	memcpy(msg.frdchat_msg.to, To.GetBuffer(), To.GetLength() * 2);
	main = AfxGetMainWnd();
	// 通过主窗口发送消息
	::SendMessage(main->m_hWnd, WM_SENDMSG, NULL, (LPARAM)&msg);

	UpdateData(FALSE);
}

