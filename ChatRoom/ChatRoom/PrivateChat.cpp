// PrivateChat.cpp : ʵ���ļ�
//

#include "stdafx.h"
#include "ChatRoom.h"
#include "PrivateChat.h"
#include "afxdialogex.h"
#include "resource.h"
#include "DataType.h"
#include "FriendList.h"
// CPrivateChat �Ի���

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


// CPrivateChat ��Ϣ�������


BOOL CPrivateChat::OnInitDialog()
{
	CDialogEx::OnInitDialog();

	// TODO:  �ڴ���Ӷ���ĳ�ʼ��
	SetWindowText(Title_name);
	return TRUE; 
}


afx_msg LRESULT CPrivateChat::OnGetfriendmsg(WPARAM wParam, LPARAM lParam)
{
	FrdChatMsg* RecvInfo = (FrdChatMsg*)lParam;

	// ��ȡ��ǰʱ��
	SYSTEMTIME now = { 0 };
	GetSystemTime(&now);
	CString Time;
	Time.Format(L"%d-%2d-%2d %2d:%2d:%2d", now.wYear, now.wMonth, now.wDay,
		now.wHour, now.wMinute, now.wSecond);

	// ��������뵽�༭��
	PriTextView = PriTextView + RecvInfo->from + L"˵(" + Time + L"):\r\n    " + RecvInfo->msg + L"\r\n";

	// ���µ�����
	UpdateData(FALSE);

	return 0;
}




void CPrivateChat::OnBnClickedSend()
{
	// TODO: �ڴ���ӿؼ�֪ͨ����������
	// ��ȡ�༭���ڵ�����
	UpdateData(TRUE);

	// ��ȡ��ǰʱ��
	SYSTEMTIME now = { 0 };
	GetSystemTime(&now);
	CString Time;
	Time.Format(L"%d-%2d-%2d %2d:%2d:%2d", now.wYear, now.wMonth, now.wDay,
		now.wHour, now.wMinute, now.wSecond);

	// ��������뵽�༭��
	PriTextView = PriTextView + L"��˵(" + Time + L"):\r\n    " + PriEditView + L"\r\n";

	// ��ȡ���Ի���
	//CFriendList *main = (CFriendList*)AfxGetMainWnd();
	CString str;
	CWnd* main = GetParent();
	//main = main->GetParent();
	main->GetWindowTextW(str);
	//MessageBox(str, str, NULL);
	// ��д�û�����Ϣ
	MsgInfo msg = { MsgType::FRIENDMSG, m_hWnd };
	memcpy(msg.frdchat_msg.msg, PriEditView.GetBuffer(), PriEditView.GetLength() * 2);
	memcpy(msg.frdchat_msg.from, str.GetBuffer(),str.GetLength() * 2);

	// ��ȡ���Ͷ��󣬼�������
	CString To;
	this->GetWindowTextW(To);
	memcpy(msg.frdchat_msg.to, To.GetBuffer(), To.GetLength() * 2);
	main = AfxGetMainWnd();
	// ͨ�������ڷ�����Ϣ
	::SendMessage(main->m_hWnd, WM_SENDMSG, NULL, (LPARAM)&msg);

	UpdateData(FALSE);
}

