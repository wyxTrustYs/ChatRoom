// GroupDlg.cpp : ʵ���ļ�
//

#include "stdafx.h"
#include "ChatRoom.h"
#include "GroupDlg.h"
#include "afxdialogex.h"


// GroupDlg �Ի���

IMPLEMENT_DYNAMIC(GroupDlg, CDialogEx)

GroupDlg::GroupDlg(CWnd* pParent /*=NULL*/)
	: CDialogEx(IDD_DIALOGGroup, pParent)
{

}

GroupDlg::~GroupDlg()
{
}

void GroupDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
	DDX_Control(pDX, IDC_LISTGroup, CGroupList);
}


BEGIN_MESSAGE_MAP(GroupDlg, CDialogEx)
END_MESSAGE_MAP()


// GroupDlg ��Ϣ�������


BOOL GroupDlg::OnInitDialog()
{
	CDialogEx::OnInitDialog();

	// TODO:  �ڴ���Ӷ���ĳ�ʼ��
	CRect rc;
	CGroupList.GetClientRect(rc);
	//int Width = rc.Width();
	CGroupList.InsertColumn(0, L"Ⱥ����", 0, 200);
//	::PostMessage(AfxGetMainWnd()->m_hWnd, WM_Search, (WPARAM)m_hWnd, NULL);
	return TRUE;  
}
