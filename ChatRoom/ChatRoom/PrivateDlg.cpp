// PrivateDlg.cpp : ʵ���ļ�
//

#include "stdafx.h"
#include "ChatRoom.h"
#include "PrivateDlg.h"
#include "afxdialogex.h"
#include "DataType.h"

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
END_MESSAGE_MAP()


// CPrivateDlg ��Ϣ�������


BOOL CPrivateDlg::OnInitDialog()
{
	CDialogEx::OnInitDialog();

	// TODO:  �ڴ���Ӷ���ĳ�ʼ��
	CRect rc;
	PrivateList.GetClientRect(rc);
	//int Width = rc.Width();
	PrivateList.InsertColumn(0, L"��������", 0, 200);
	::PostMessage(AfxGetMainWnd()->m_hWnd, WM_Search, (WPARAM)m_hWnd, NULL);
	return TRUE;
}

afx_msg LRESULT CPrivateDlg::OnUpdatefrnd(WPARAM wParam, LPARAM lParam)
{
	RecvSearch* update = (RecvSearch*)lParam;

	// ��ȡ���뵽��λ��
	int index = PrivateList.GetItemCount()+1;

	// ����û������б�
	// &update->name[1]  ��Python��صı�������
	PrivateList.InsertItem(index,CString(update->name));
	// ff fe 4d 00 61 00 78 00 41 00��.?M.a.x.A��
	return 0;
}
