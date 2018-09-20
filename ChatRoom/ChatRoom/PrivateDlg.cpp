// PrivateDlg.cpp : ʵ���ļ�
//

#include "stdafx.h"
#include "ChatRoom.h"
#include "PrivateDlg.h"
#include "afxdialogex.h"
#include "DataType.h"
#include "PrivateChat.h"

// CPrivateDlg �Ի���

IMPLEMENT_DYNAMIC(CPrivateDlg, CDialogEx)

CPrivateDlg::CPrivateDlg(CWnd* pParent /*=NULL*/)
	: CDialogEx(IDD_DIALOGSin, pParent)
{

}

CPrivateDlg::~CPrivateDlg()
{
}

void CPrivateDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
	DDX_Control(pDX, IDC_LIST1, PrivateList);
}


BEGIN_MESSAGE_MAP(CPrivateDlg, CDialogEx)
	ON_MESSAGE(WM_UPDATEFRND, &CPrivateDlg::OnUpdatefrnd)
	ON_NOTIFY(NM_DBLCLK, IDC_LIST1, &CPrivateDlg::OnDblclkList1)
END_MESSAGE_MAP()


// CPrivateDlg ��Ϣ�������


BOOL CPrivateDlg::OnInitDialog()
{
	CDialogEx::OnInitDialog();

	// TODO:  �ڴ���Ӷ���ĳ�ʼ��
	CRect rc;
	PrivateList.GetClientRect(rc);
	int Width = rc.Width();
	PrivateList.InsertColumn(0, L"��������", LVCFMT_CENTER, Width/2);
	PrivateList.InsertColumn(1, L"����ID", LVCFMT_CENTER, Width/2);
	::PostMessage(AfxGetMainWnd()->m_hWnd, WM_Search, (WPARAM)m_hWnd, NULL);
	return TRUE;
}

afx_msg LRESULT CPrivateDlg::OnUpdatefrnd(WPARAM wParam, LPARAM lParam)
{
	RecvSearch* update = (RecvSearch*)lParam;

	// ��ȡ���뵽��λ��
	int index = PrivateList.GetItemCount();

	// ����û������б�
	// &update->name[1]  ��Python��صı�������
	PrivateList.InsertItem(index,CString(update->nick));
	PrivateList.SetItemText(index, 1, CString(update->name));
	return 0;
}


void CPrivateDlg::OnDblclkList1(NMHDR *pNMHDR, LRESULT *pResult)
{
	LPNMITEMACTIVATE pNMItemActivate = reinterpret_cast<LPNMITEMACTIVATE>(pNMHDR);
	// TODO: �ڴ���ӿؼ�֪ͨ����������
	CString person = PrivateList.GetItemText(pNMItemActivate->iItem, 1);
	CPrivateChat* m_prichat = new CPrivateChat(person);
	m_prichat->Create(IDD_DIALOG1,this);
	m_prichat->ShowWindow(SW_SHOW);
	*pResult = 0;
}
