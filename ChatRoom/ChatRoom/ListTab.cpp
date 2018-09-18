// ListTab.cpp : ʵ���ļ�
//

#include "stdafx.h"
#include "ChatRoom.h"
#include "ListTab.h"


// ListTab

IMPLEMENT_DYNAMIC(ListTab, CTabCtrl)

ListTab::ListTab()
{

}

ListTab::~ListTab()
{
}


BEGIN_MESSAGE_MAP(ListTab, CTabCtrl)
	ON_NOTIFY_REFLECT(TCN_SELCHANGE, &ListTab::OnTcnSelchange)
END_MESSAGE_MAP()



// ListTab ��Ϣ�������




void ListTab::OnTcnSelchange(NMHDR *pNMHDR, LRESULT *pResult)
{
	int Num = GetCurSel();
	switch (Num)
	{
	case 0:
	{
		m_dia[0]->ShowWindow(SW_SHOW);
		m_dia[1]->ShowWindow(SW_HIDE);
		break;
	}
	case 1:
	{
		m_dia[0]->ShowWindow(SW_HIDE);
		m_dia[1]->ShowWindow(SW_SHOW);
		break;
	}
	default:
		break;
	}
	// TODO: �ڴ���ӿؼ�֪ͨ����������
	*pResult = 0;
}
