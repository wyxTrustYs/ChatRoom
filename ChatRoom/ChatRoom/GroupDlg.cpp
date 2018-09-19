// GroupDlg.cpp : 实现文件
//

#include "stdafx.h"
#include "ChatRoom.h"
#include "GroupDlg.h"
#include "afxdialogex.h"


// GroupDlg 对话框

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
}


BEGIN_MESSAGE_MAP(GroupDlg, CDialogEx)
END_MESSAGE_MAP()


// GroupDlg 消息处理程序
