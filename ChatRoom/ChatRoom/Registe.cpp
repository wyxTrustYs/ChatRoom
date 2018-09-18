// Registe.cpp : ʵ���ļ�
//

#include "stdafx.h"
#include "ChatRoom.h"
#include "Registe.h"
#include "afxdialogex.h"
#include "DataType.h"

// CRegiste �Ի���

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


// CRegiste ��Ϣ�������


void CRegiste::OnBnClickedOk()
{
	// TODO: �ڴ���ӿؼ�֪ͨ����������

	CDialogEx::OnOK();
	UpdateData(TRUE);
	HWND hwnd = AfxGetMainWnd()->m_hWnd;
	
	// �����ݽ��м��: �Ƿ�Ϊ��
	if (Enickname.IsEmpty() || Erepwd.IsEmpty() ||
		Epwdcom.IsEmpty() || Eid.IsEmpty())
	{
		MessageBox(L"�п�û��", L"������Ϣ", MB_OK | MB_ICONERROR);
		return;
	}

	// �����ݽ��м��: �����Ƿ�ƥ��
	if (Erepwd != Epwdcom)
	{
		MessageBox(L"���벻ƥ�䣬����������", L"������Ϣ", MB_OK | MB_ICONERROR);
		return;
	}
	//��ȡ�Ա�
	wchar_t* sex[] = { L"��",L"Ů" };

	// ������Ϣ�ṹ�����ڷ���
	MsgInfo* msg = new MsgInfo{ MsgType::REGISTER };

	// ���ô��ھ�������������ڷ�����Ϣ
	msg->hWnd = this->GetSafeHwnd();

	// ��ṹ������ַ���
	memcpy(msg->reg_info.sex, sex[RMan], 4);
	// ��ΪCStringĬ���ǿ��ַ���memcpy���ֽڿ�����GetLength���ص��ǳ���
	memcpy(msg->reg_info.name, Eid.GetBuffer(), Eid.GetLength() * 2);
	memcpy(msg->reg_info.pswd, Erepwd.GetBuffer(), Erepwd.GetLength() * 2);
	memcpy(msg->reg_info.nick, Enickname.GetBuffer(), Enickname.GetLength() * 2);

	// �Զ���һ����Ϣ�������������ڷ���ע���õĽṹ��
	::PostMessage(AfxGetMainWnd()->m_hWnd, WM_REGISTER1, (WPARAM)m_hWnd, (LPARAM)msg);
}


afx_msg LRESULT CRegiste::OnRegister2(WPARAM wParam, LPARAM lParam)
{
	// ��ȡ���յ�����Ϣ
	RecvReg* msg = (RecvReg*)lParam;

	if (msg->sucess)
	{
		MessageBox(L"ע��ɹ�", L"��Ϣ", MB_OK);

		// ��ԭ������
		GetParent()->ShowWindow(SW_SHOW);
//		DestroyWindow();
		EndDialog(0);
	}
	else
	{
		MessageBox(CString(msg->msg), L"��Ϣ", MB_OK | MB_ICONERROR);
	}

	return 0;
}
