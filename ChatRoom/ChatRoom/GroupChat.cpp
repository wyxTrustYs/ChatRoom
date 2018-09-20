// GroupChat.cpp : ʵ���ļ�
//

#include "stdafx.h"
#include "ChatRoom.h"
#include "GroupChat.h"
#include "afxdialogex.h"
#include "resource.h"
#include "LoginDlg.h"
// CGroupChat �Ի���
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


// CGroupChat ��Ϣ�������


BOOL CGroupChat::OnInitDialog()
{
	CDialogEx::OnInitDialog();
	CRect rc;
	UserList.GetClientRect(rc);
	int Width = rc.Width();
	UserList.InsertColumn(0, L"�û�����", LVCFMT_CENTER, Width / 2);
	UserList.InsertColumn(1, L"�û�ID", LVCFMT_CENTER, Width / 2);
	// TODO:  �ڴ���Ӷ���ĳ�ʼ��
	if (Groupid == L"1")
	{
		SetWindowTextW(L"ͬ�Ǽ�į�ٸ�");
	}
	else
	{
		SetWindowTextW(L"������Ů����");
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

	// ��ȡ���뵽��λ��
	int index = UserList.GetItemCount();

	// ����û������б�
	// &update->name[1]  ��Python��صı�������
	UserList.InsertItem(index, CString(update->nick));
	UserList.SetItemText(index, 1, CString(update->ID));
	return 0;
}




void CGroupChat::OnBnClickedGroupsend()
{
	// TODO: �ڴ���ӿؼ�֪ͨ����������
	UpdateData(TRUE);

	// ��ȡ��ǰʱ��
	SYSTEMTIME now = { 0 };
	GetSystemTime(&now);
	CString Time;
	Time.Format(L"%d-%2d-%2d %2d:%2d:%2d", now.wYear, now.wMonth, now.wDay,
		now.wHour, now.wMinute, now.wSecond);

	// ��������뵽�༭��
	GroupText = GroupText + L"��˵(" + Time + L"):\r\n    " + GroupEdit + L"\r\n";

	// ��ȡ���Ի���
	//CLoginDlg *main = (CLoginDlg*)AfxGetMainWnd();

	// ��д�û�����Ϣ
 	MsgInfo msg = { MsgType::GROUPMSG, m_hWnd };
//	memcpy(msg.groupchat_msg.msg, L"abcdef", 12);
 	memcpy(msg.groupchat_msg.msg, GroupEdit.GetBuffer(), GroupEdit.GetLength() * 2);
//	memcpy(msg.groupchat_msg.from, L"1234", 4 * 2);
 	memcpy(msg.groupchat_msg.from, main->EditAccount.GetBuffer(), main->EditAccount.GetLength() * 2);


// // 	// ��ȡ���Ͷ��󣬼�������
	
//	memcpy(msg.groupchat_msg.to, L"1",1 * 2);
 	memcpy(msg.groupchat_msg.to, Groupid.GetBuffer(), Groupid.GetLength() * 2);
// 	// ͨ�������ڷ�����Ϣ
	::SendMessage(main->m_hWnd, WM_SENDMSG, NULL, (LPARAM)&msg);

	GroupEdit = "";
	UpdateData(FALSE);
}


afx_msg LRESULT CGroupChat::OnGetgroupmsg(WPARAM wParam, LPARAM lParam)
{
	// ��ȡ����������Ϣ
	FrdChatMsg* RecvInfo = (FrdChatMsg*)lParam;

	// ��ȡ��ǰʱ��
	SYSTEMTIME now = { 0 };
	GetSystemTime(&now);
	CString Time;
	Time.Format(L"%d-%2d-%2d %2d:%2d:%2d", now.wYear, now.wMonth, now.wDay,
		now.wHour, now.wMinute, now.wSecond);

	// ��������뵽�༭��
	GroupText = GroupText + RecvInfo->from + L"˵(" + Time + L"):\r\n    " + RecvInfo->msg + L"\r\n";

	// ���µ�����
	UpdateData(FALSE);
	return 0;
}




void CGroupChat::OnClose()
{
	// TODO: �ڴ������Ϣ�����������/�����Ĭ��ֵ
	ChatWindows.erase(Groupid);
	CDialogEx::OnClose();
}
