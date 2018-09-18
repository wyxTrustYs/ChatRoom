// ListTab.cpp : 实现文件
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



// ListTab 消息处理程序




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
	// TODO: 在此添加控件通知处理程序代码
	*pResult = 0;
}
