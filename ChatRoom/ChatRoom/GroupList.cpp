// GroupList.cpp : ʵ���ļ�
//

#include "stdafx.h"
#include "ChatRoom.h"
#include "GroupList.h"
#include "afxdialogex.h"


// CGroupList �Ի���

IMPLEMENT_DYNAMIC(CGroupList, CDialogEx)

CGroupList::CGroupList(CWnd* pParent /*=NULL*/)
	: CDialogEx(IDD_DIALOGGroup, pParent)
{

}

CGroupList::~CGroupList()
{
}

void CGroupList::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
}


BEGIN_MESSAGE_MAP(CGroupList, CDialogEx)
END_MESSAGE_MAP()


// CGroupList ��Ϣ�������
