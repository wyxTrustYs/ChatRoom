// GroupDlg.cpp : ʵ���ļ�
//

#include "stdafx.h"
#include "ChatRoom.h"
#include "GroupDlg.h"
#include "afxdialogex.h"
#include "DataType.h"
#include "GroupChat.h"
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
	ON_MESSAGE(WM_UPDATEGROUP, &GroupDlg::OnUpdategroup)
	ON_NOTIFY(NM_DBLCLK, IDC_LISTGroup, &GroupDlg::OnDblclkListgroup)
END_MESSAGE_MAP()


// GroupDlg ��Ϣ�������


BOOL GroupDlg::OnInitDialog()
{
	CDialogEx::OnInitDialog();

	// TODO:  �ڴ���Ӷ���ĳ�ʼ��
	CRect rc;
	CGroupList.GetClientRect(rc);
	int Width = rc.Width();
	CGroupList.InsertColumn(0, L"Ⱥ����", 0, Width/2);
	CGroupList.InsertColumn(1, L"ȺID", 0, Width / 2);
	::PostMessage(AfxGetMainWnd()->m_hWnd, WM_SearchGroup, (WPARAM)m_hWnd, NULL);
	return TRUE;  
}


afx_msg LRESULT GroupDlg::OnUpdategroup(WPARAM wParam, LPARAM lParam)
{
	RecvSearch* update = (RecvSearch*)lParam;

	// ��ȡ���뵽��λ��
	int index = CGroupList.GetItemCount();

	// ����û������б�
	// &update->name[1]  ��Python��صı�������
	CGroupList.InsertItem(index, CString(update->nick));
	CGroupList.SetItemText(index, 1, CString(update->ID));
	return 0;
}


void GroupDlg::OnDblclkListgroup(NMHDR *pNMHDR, LRESULT *pResult)
{
	LPNMITEMACTIVATE pNMItemActivate = reinterpret_cast<LPNMITEMACTIVATE>(pNMHDR);
	CString title = CGroupList.GetItemText(pNMItemActivate->iItem, 0);
	CString id = CGroupList.GetItemText(pNMItemActivate->iItem, 1);
	CGroupChat* m_prichat = new CGroupChat(title,id);
	m_prichat->Create(IDD_DIALOGGrouChat, this);
	m_prichat->ShowWindow(SW_SHOW);
	*pResult = 0;
}
