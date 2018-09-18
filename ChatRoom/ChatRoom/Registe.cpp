// Registe.cpp : 实现文件
//

#include "stdafx.h"
#include "ChatRoom.h"
#include "Registe.h"
#include "afxdialogex.h"
#include "DataType.h"

// CRegiste 对话框

IMPLEMENT_DYNAMIC(CRegiste, CDialogEx)

CRegiste::CRegiste(CWnd* pParent /*=NULL*/)
	: CDialogEx(IDD_RegistDlg, pParent)
	, RMan(0)
	, Enickname(_T(""))
	, Erepwd(_T(""))
	, Epwdcom(_T(""))
	, Eid(_T(""))
{

}

CRegiste::~CRegiste()
{
}

void CRegiste::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
	DDX_Radio(pDX, IDC_RADIO1, RMan);
	DDX_Text(pDX, IDC_nickname, Enickname);
	DDX_Text(pDX, IDC_repwd, Erepwd);
	DDX_Text(pDX, IDC_pwdcom, Epwdcom);
	DDX_Text(pDX, IDC_id, Eid);
}


BEGIN_MESSAGE_MAP(CRegiste, CDialogEx)
	ON_BN_CLICKED(IDOK, &CRegiste::OnBnClickedOk)
	ON_MESSAGE(WM_REGISTER2, &CRegiste::OnRegister2)
END_MESSAGE_MAP()


// CRegiste 消息处理程序


void CRegiste::OnBnClickedOk()
{
	// TODO: 在此添加控件通知处理程序代码

	CDialogEx::OnOK();
	UpdateData(TRUE);
	HWND hwnd = AfxGetMainWnd()->m_hWnd;
	
	// 对数据进行检查: 是否为空
	if (Enickname.IsEmpty() || Erepwd.IsEmpty() ||
		Epwdcom.IsEmpty() || Eid.IsEmpty())
	{
		MessageBox(L"有空没填", L"错误信息", MB_OK | MB_ICONERROR);
		return;
	}

	// 对数据进行检查: 密码是否匹配
	if (Erepwd != Epwdcom)
	{
		MessageBox(L"密码不匹配，请重新输入", L"错误信息", MB_OK | MB_ICONERROR);
		return;
	}
	//获取性别
	wchar_t* sex[] = { L"男",L"女" };

	// 构造消息结构，用于发送
	MsgInfo* msg = new MsgInfo{ MsgType::REGISTER };

	// 设置窗口句柄，用于主窗口返回消息
	msg->hWnd = this->GetSafeHwnd();

	// 向结构体添加字符串
	memcpy(msg->reg_info.sex, sex[RMan], 4);
	// 因为CString默认是宽字符，memcpy以字节拷贝，GetLength返回的是长度
	memcpy(msg->reg_info.name, Eid.GetBuffer(), Eid.GetLength() * 2);
	memcpy(msg->reg_info.pswd, Erepwd.GetBuffer(), Erepwd.GetLength() * 2);
	memcpy(msg->reg_info.nick, Enickname.GetBuffer(), Enickname.GetLength() * 2);

	// 自定义一个消息，用于向主窗口发送注册用的结构体
	::PostMessage(AfxGetMainWnd()->m_hWnd, WM_REGISTER1, (WPARAM)m_hWnd, (LPARAM)msg);
}


afx_msg LRESULT CRegiste::OnRegister2(WPARAM wParam, LPARAM lParam)
{
	// 获取接收到的信息
	RecvReg* msg = (RecvReg*)lParam;

	if (msg->sucess)
	{
		MessageBox(L"注册成功", L"信息", MB_OK);

		// 还原父窗口
		GetParent()->ShowWindow(SW_SHOW);
//		DestroyWindow();
		EndDialog(0);
	}
	else
	{
		MessageBox(CString(msg->msg), L"信息", MB_OK | MB_ICONERROR);
	}

	return 0;
}
