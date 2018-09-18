// PrivateDlg.cpp : 实现文件
//

#include "stdafx.h"
#include "ChatRoom.h"
#include "PrivateDlg.h"
#include "afxdialogex.h"


// CPrivateDlg 对话框

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
}


BEGIN_MESSAGE_MAP(CPrivateDlg, CDialogEx)
END_MESSAGE_MAP()


// CPrivateDlg 消息处理程序
