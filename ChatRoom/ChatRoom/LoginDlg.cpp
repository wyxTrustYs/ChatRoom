
// LoginDlg.cpp : ʵ���ļ�
//

#include "stdafx.h"
#include "ChatRoom.h"
#include "LoginDlg.h"
#include "afxdialogex.h"
#include "Registe.h"
#include "DataType.h"
#include "FriendList.h"
#ifdef _DEBUG
#define new DEBUG_NEW
#endif


// ����Ӧ�ó��򡰹��ڡ��˵���� CAboutDlg �Ի���

class CAboutDlg : public CDialogEx
{
public:
	CAboutDlg();

// �Ի�������
#ifdef AFX_DESIGN_TIME
	enum { IDD = IDD_ABOUTBOX };
#endif

	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV ֧��

// ʵ��
protected:
	DECLARE_MESSAGE_MAP()

};

CAboutDlg::CAboutDlg() : CDialogEx(IDD_ABOUTBOX)
{
}

void CAboutDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
}

BEGIN_MESSAGE_MAP(CAboutDlg, CDialogEx)

END_MESSAGE_MAP()


// CLoginDlg �Ի���



CLoginDlg::CLoginDlg(CWnd* pParent /*=NULL*/)
	: CDialogEx(IDD_LoginDlg, pParent)
	, EditPsd(_T(""))
	, EditAccount(_T(""))
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
}

BEGIN_MESSAGE_MAP(CLoginDlg, CDialogEx)
	ON_WM_SYSCOMMAND()
	ON_WM_PAINT()
	ON_WM_QUERYDRAGICON()
	ON_BN_CLICKED(IDbtnLogin, &CLoginDlg::OnBnClickedbtnlogin)
	ON_BN_CLICKED(IDbtnRegiste, &CLoginDlg::OnBnClickedbtnregiste)

//	ON_MESSAGE(WM_LOGIN, &CLoginDlg::OnLogin)
ON_MESSAGE(WM_LOGIN, &CLoginDlg::OnClicklogin)
ON_MESSAGE(WM_REGISTER1, &CLoginDlg::OnRegister1)
ON_MESSAGE(WM_Search, &CLoginDlg::OnSearch)
END_MESSAGE_MAP()


// CLoginDlg ��Ϣ�������

BOOL CLoginDlg::OnInitDialog()
{
	CDialogEx::OnInitDialog();

	// ��������...���˵�����ӵ�ϵͳ�˵��С�

	// IDM_ABOUTBOX ������ϵͳ���Χ�ڡ�
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

	// ���ô˶Ի����ͼ�ꡣ  ��Ӧ�ó��������ڲ��ǶԻ���ʱ����ܽ��Զ�
	//  ִ�д˲���
	SetIcon(m_hIcon, TRUE);			// ���ô�ͼ��
	SetIcon(m_hIcon, FALSE);		// ����Сͼ��

	// TODO: �ڴ���Ӷ���ĳ�ʼ������

	// ���ӵ��������� �����Ͷ˿�
	if (!m_socket.Connect(L"192.168.2.154",8000))
	{
		MessageBox(L"����������ʧ��", L"������Ϣ", MB_OK | MB_ICONERROR);
		ExitProcess(-1);
	}

	return TRUE;  // ���ǽ��������õ��ؼ������򷵻� TRUE
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

// �����Ի��������С����ť������Ҫ����Ĵ���
//  �����Ƹ�ͼ�ꡣ  ����ʹ���ĵ�/��ͼģ�͵� MFC Ӧ�ó���
//  �⽫�ɿ���Զ���ɡ�

void CLoginDlg::OnPaint()
{
	if (IsIconic())
	{
		CPaintDC dc(this); // ���ڻ��Ƶ��豸������

		SendMessage(WM_ICONERASEBKGND, reinterpret_cast<WPARAM>(dc.GetSafeHdc()), 0);

		// ʹͼ���ڹ����������о���
		int cxIcon = GetSystemMetrics(SM_CXICON);
		int cyIcon = GetSystemMetrics(SM_CYICON);
		CRect rect;
		GetClientRect(&rect);
		int x = (rect.Width() - cxIcon + 1) / 2;
		int y = (rect.Height() - cyIcon + 1) / 2;

		// ����ͼ��
		dc.DrawIcon(x, y, m_hIcon);
	}
	else
	{
		CDialogEx::OnPaint();
	}
}

//���û��϶���С������ʱϵͳ���ô˺���ȡ�ù��
//��ʾ��
HCURSOR CLoginDlg::OnQueryDragIcon()
{
	return static_cast<HCURSOR>(m_hIcon);
}



void CLoginDlg::OnBnClickedbtnlogin()
{
	// TODO: �ڴ���ӿؼ�֪ͨ����������
	UpdateData(TRUE);

	// �����¼��Ҫ�õ�����Ϣ
	MsgInfo msg = { MsgType::LOGIN };
	msg.hWnd = this->GetSafeHwnd();
	memcpy(msg.login_info.name, EditAccount.GetBuffer(), EditAccount.GetLength() * 2);
	memcpy(msg.login_info.pswd, EditPsd.GetBuffer(), EditPsd.GetLength() * 2);

	// ���͵�¼��Ϣ��������
	m_socket.Send(&msg, sizeof(MsgInfo));
	
}


void CLoginDlg::OnReceive(RecvInfo* szText)
{
	switch (szText->type)
	{
	case RecvType::LOGIN:
		// ������Ϣ�����������Ƿ�ɹ�
		::SendMessage(szText->hWnd, WM_LOGIN, NULL, (LPARAM)&szText->login_info);
		break;
	case RecvType::REGISTER:
		::SendMessage(szText->hWnd, WM_REGISTER2, NULL, (LPARAM)&szText->reg_info);
		break;
	}
}



void CLoginDlg::OnBnClickedbtnregiste()
{
	// TODO: �ڴ���ӿؼ�֪ͨ����������
	CRegiste *myregiste = new CRegiste();
	myregiste->Create(IDD_RegistDlg);
	myregiste->ShowWindow(SW_SHOW);
}




afx_msg LRESULT CLoginDlg::OnClicklogin(WPARAM wParam, LPARAM lParam)
{
	// ��ȡ���յ�����Ϣ
	RecvLogin* msg = (RecvLogin*)lParam;

	if (msg->sucess)
	{
		MessageBox(L"��¼�ɹ�", L"��Ϣ", MB_OK);
		ShowWindow(SW_HIDE);
		CFriendList* Lfriend = new CFriendList();
		Lfriend->DoModal();
	}
	else
	{
		MessageBox(CString(msg->msg), L"������Ϣ", MB_OK | MB_ICONERROR);
	}

	return 0;
}



afx_msg LRESULT CLoginDlg::OnRegister1(WPARAM wParam, LPARAM lParam)
{
	// �����������ע����Ϣ
	m_socket.Send((void*)lParam, sizeof(MsgInfo));
	// �ͷŶѿռ�
	delete (MsgInfo*)lParam;
	return 0;
}


afx_msg LRESULT CLoginDlg::OnSearch(WPARAM wParam, LPARAM lParam)
{
	m_socket.Send((void*)2,4);
	delete (MsgInfo*)lParam;
	return 0;
}
