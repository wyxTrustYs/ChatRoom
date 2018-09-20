
// LoginDlg.cpp : 实现文件
//

#include "stdafx.h"
#include "ChatRoom.h"
#include "LoginDlg.h"
#include "afxdialogex.h"
#include "Registe.h"
#include "DataType.h"
#include "FriendList.h"
#include "PrivateChat.h"
#ifdef _DEBUG
#define new DEBUG_NEW
#endif
#include <map>
using std::map;
// 当前已经打开的所有窗口
map<CString, HWND> ChatWindows;

// 用于应用程序“关于”菜单项的 CAboutDlg 对话框

class CAboutDlg : public CDialogEx
{
public:
	CAboutDlg();

	// 对话框数据
#ifdef AFX_DESIGN_TIME
	enum { IDD = IDD_ABOUTBOX };
#endif

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV 支持

// 实现
protected:
	DECLARE_MESSAGE_MAP()

public:
	//	afx_msg void OnClose();
//	virtual BOOL OnInitDialog();
};

CAboutDlg::CAboutDlg() : CDialogEx(IDD_ABOUTBOX)
{
}

void CAboutDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
}

BEGIN_MESSAGE_MAP(CAboutDlg, CDialogEx)

	//	ON_WM_CLOSE()
END_MESSAGE_MAP()


// CLoginDlg 对话框



CLoginDlg::CLoginDlg(CWnd* pParent /*=NULL*/)
	: CDialogEx(IDD_LoginDlg, pParent)
	, EditPsd(_T("1234"))
	, EditAccount(_T("1234"))
{
	m_hIcon = AfxGetApp()->LoadIcon(IDR_MAINFRAME);
}

void CLoginDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
	DDX_Control(pDX, IDbtnRegiste, BtnRegiste);
	DDX_Control(pDX, IDbtnLogin, BtnLogin);
	DDX_Control(pDX, IDbtnCancel, BtnCancel);
	DDX_Text(pDX, IDCPassword, EditPsd);
	DDX_Text(pDX, IDCAccount, EditAccount);
	DDX_Control(pDX, IDC_STATIC1, CStringName);
}

BEGIN_MESSAGE_MAP(CLoginDlg, CDialogEx)
	ON_WM_SYSCOMMAND()
	ON_WM_PAINT()
	ON_WM_QUERYDRAGICON()
	ON_BN_CLICKED(IDbtnLogin, &CLoginDlg::OnBnClickedbtnlogin)
	ON_BN_CLICKED(IDbtnRegiste, &CLoginDlg::OnBnClickedbtnregiste)

	ON_MESSAGE(WM_LOGIN,&CLoginDlg::OnClicklogin)
	ON_MESSAGE(WM_REGISTER1, &CLoginDlg::OnRegister1)
	ON_MESSAGE(WM_Search, &CLoginDlg::OnSearch)
	ON_MESSAGE(WM_SENDMSG, &CLoginDlg::OnSendmsg)
	ON_MESSAGE(WM_SearchGroup, &CLoginDlg::OnSearchgroup)
END_MESSAGE_MAP()


// CLoginDlg 消息处理程序

BOOL CLoginDlg::OnInitDialog()
{
	CDialogEx::OnInitDialog();

	// 将“关于...”菜单项添加到系统菜单中。

	// IDM_ABOUTBOX 必须在系统命令范围内。
	ASSERT((IDM_ABOUTBOX & 0xFFF0) == IDM_ABOUTBOX);
	ASSERT(IDM_ABOUTBOX < 0xF000);

	CMenu* pSysMenu = GetSystemMenu(FALSE);
	if (pSysMenu != NULL)
	{
		BOOL bNameValid;
		CString strAboutMenu;
		bNameValid = strAboutMenu.LoadString(IDS_ABOUTBOX);
		ASSERT(bNameValid);
		if (!strAboutMenu.IsEmpty())
		{
			pSysMenu->AppendMenu(MF_SEPARATOR);
			pSysMenu->AppendMenu(MF_STRING, IDM_ABOUTBOX, strAboutMenu);
		}
	}

	// 设置此对话框的图标。  当应用程序主窗口不是对话框时，框架将自动
	//  执行此操作
	SetIcon(m_hIcon, TRUE);			// 设置大图标
	SetIcon(m_hIcon, FALSE);		// 设置小图标

	// TODO: 在此添加额外的初始化代码

	// 连接到服务器， 主机和端口
	if (!m_socket.Connect(L"192.168.2.154", 8000))
	{
		MessageBox(L"服务器连接失败", L"错误信息", MB_OK | MB_ICONERROR);
		ExitProcess(-1);
	}

	return TRUE;  // 除非将焦点设置到控件，否则返回 TRUE
}

void CLoginDlg::OnSysCommand(UINT nID, LPARAM lParam)
{
	if ((nID & 0xFFF0) == IDM_ABOUTBOX)
	{
		CAboutDlg dlgAbout;
		dlgAbout.DoModal();
	}
	else
	{
		CDialogEx::OnSysCommand(nID, lParam);
	}
}

// 如果向对话框添加最小化按钮，则需要下面的代码
//  来绘制该图标。  对于使用文档/视图模型的 MFC 应用程序，
//  这将由框架自动完成。

void CLoginDlg::OnPaint()
{
	if (IsIconic())
	{
		CPaintDC dc(this); // 用于绘制的设备上下文

		SendMessage(WM_ICONERASEBKGND, reinterpret_cast<WPARAM>(dc.GetSafeHdc()), 0);

		// 使图标在工作区矩形中居中
		int cxIcon = GetSystemMetrics(SM_CXICON);
		int cyIcon = GetSystemMetrics(SM_CYICON);
		CRect rect;
		GetClientRect(&rect);
		int x = (rect.Width() - cxIcon + 1) / 2;
		int y = (rect.Height() - cyIcon + 1) / 2;

		// 绘制图标
		dc.DrawIcon(x, y, m_hIcon);
	}
	else
	{
		CDialogEx::OnPaint();
	}
}

//当用户拖动最小化窗口时系统调用此函数取得光标
//显示。
HCURSOR CLoginDlg::OnQueryDragIcon()
{
	return static_cast<HCURSOR>(m_hIcon);
}



void CLoginDlg::OnBnClickedbtnlogin()
{
	// TODO: 在此添加控件通知处理程序代码
	UpdateData(TRUE);

	// 构造登录需要用到的消息
	MsgInfo msg = { MsgType::LOGIN };
	msg.hWnd = this->GetSafeHwnd();
	memcpy(msg.login_info.name, EditAccount.GetBuffer(), EditAccount.GetLength() * 2);
	memcpy(msg.login_info.pswd, EditPsd.GetBuffer(), EditPsd.GetLength() * 2);

	// 发送登录消息到服务器
	m_socket.Send(&msg, sizeof(MsgInfo));

}


void CLoginDlg::OnReceive(int size, RecvInfo* szText)
{
	switch (szText->type)
	{
	case MsgType::LOGIN:
		// 发送消息告诉主窗口是否成功
		::SendMessage(szText->hWnd, WM_LOGIN, NULL, (LPARAM)&szText->login_info);
		break;
	case MsgType::REGISTER:
		::SendMessage(szText->hWnd, WM_REGISTER2, NULL, (LPARAM)&szText->reg_info);
		break;
	case MsgType::Search:
	{
		char* update = (char*)szText->searchFred.ID;
		while (size >= 28)
		{
			::SendMessage(szText->hWnd, WM_UPDATEFRND, NULL, (LPARAM)update);
			size -= 28; update += 28;
		}
		break;
	}
	case MsgType::FRIENDMSG:
	{
		CString Name = szText->frdchat_msg.from;
		if (ChatWindows.find(Name) != ChatWindows.end())
		{
			::SendMessage(ChatWindows[Name], WM_GETFRIENDMSG, NULL, (LPARAM)&szText->frdchat_msg);
		}
		// 如果不存在，就创建窗口
		else
		{
			CPrivateChat* Chat = new CPrivateChat(Name);
			Chat->Create(IDD_DIALOG1, this);
			// 将窗口放入到字典中
			ChatWindows[Name] = Chat->GetSafeHwnd();
			Chat->SetWindowTextW(Name);
			Chat->ShowWindow(SW_SHOW);
			::SendMessage(ChatWindows[Name], WM_GETFRIENDMSG, NULL, (LPARAM)&szText->frdchat_msg);
		}
		break;
	}
	case MsgType::SearchGroup:
	{
		char* update = (char*)szText->searchFred.ID;
		while (size >= 28)
		{
			::SendMessage(szText->hWnd, WM_UPDATEGROUP, NULL, (LPARAM)update);
			size -= 28; update += 28;
		}
		break;
	}
	case MsgType::UserInGroup:
	{
		char* update = (char*)szText->searchFred.ID;
		while (size >= 28)
		{
			::SendMessage(szText->hWnd, WM_UPDATEMEMBERINGRUP, NULL, (LPARAM)update);
			size -= 28; update += 28;
		}
		break;
	}
	case MsgType::GROUPMSG:
	{
		CString groupid = szText->frdchat_msg.to;
		if (ChatWindows.find(groupid) != ChatWindows.end())
		{
			::SendMessage(ChatWindows[groupid], WM_GETGROUPMSG, NULL, (LPARAM)&szText->frdchat_msg);
		}
		// 如果不存在，就创建窗口
		else
		{
			CGroupChat* Chat = new CGroupChat(L"name",groupid);
			Chat->Create(IDD_DIALOGGrouChat, this);
			// 将窗口放入到字典中
			ChatWindows[groupid] = Chat->GetSafeHwnd();
			//Chat->SetWindowTextW(CString(L"群聊:") + Name);
			Chat->ShowWindow(SW_SHOW);
			::SendMessage(ChatWindows[groupid], WM_GETGROUPMSG, NULL, (LPARAM)&szText->frdchat_msg);
		}
		break;
	}
	default:
		MessageBox(0, 0, 0);
		break;
	}
}



void CLoginDlg::OnBnClickedbtnregiste()
{
	// TODO: 在此添加控件通知处理程序代码
	CRegiste *myregiste = new CRegiste();
	myregiste->Create(IDD_RegistDlg);
	myregiste->ShowWindow(SW_SHOW);
}




afx_msg LRESULT CLoginDlg::OnClicklogin(WPARAM wParam, LPARAM lParam)
{
	// 获取接收到的信息
	RecvLogin* msg = (RecvLogin*)lParam;

	if (msg->sucess)
	{
		MessageBox(L"登录成功", L"信息", MB_OK);
		ShowWindow(SW_HIDE);
		CFriendList* Lfriend = new CFriendList(CString(msg->nick));
		Lfriend->Create(IDD_Dlg);
		Lfriend->ShowWindow(SW_SHOW);
	}
	else
	{
		MessageBox(CString(msg->msg), L"错误信息", MB_OK | MB_ICONERROR);
	}

	return 0;
}



afx_msg LRESULT CLoginDlg::OnRegister1(WPARAM wParam, LPARAM lParam)
{
	// 向服务器发送注册消息
	m_socket.Send((void*)lParam, sizeof(MsgInfo));
	// 释放堆空间
	delete (MsgInfo*)lParam;
	return 0;
}


afx_msg LRESULT CLoginDlg::OnSearch(WPARAM wParam, LPARAM lParam)
{
	MsgInfo msg = { MsgType::Search };
	msg.hWnd = (HWND)wParam;
	memcpy(msg.login_info.name, EditAccount.GetBuffer(), EditAccount.GetLength() * 2);
	m_socket.Send(&msg, sizeof(MsgInfo));
	delete (MsgInfo*)lParam;
	return 0;
}

//发送网络消息
afx_msg LRESULT CLoginDlg::OnSendmsg(WPARAM wParam, LPARAM lParam)
{
	// 向服务器发送消息
	return m_socket.Send((PVOID)lParam, sizeof(MsgInfo));

}


afx_msg LRESULT CLoginDlg::OnSearchgroup(WPARAM wParam, LPARAM lParam)
{
	MsgInfo msg = { MsgType::SearchGroup };
	msg.hWnd = (HWND)wParam;
	memcpy(msg.login_info.name, EditAccount.GetBuffer(), EditAccount.GetLength() * 2);
	m_socket.Send(&msg, sizeof(MsgInfo));
	delete (MsgInfo*)lParam;
	return 0;
}

