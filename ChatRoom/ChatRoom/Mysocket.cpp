// Mysocket.cpp : 实现文件
//

#include "stdafx.h"
#include "ChatRoom.h"
#include "Mysocket.h"
#include "LoginDlg.h"
#include "DataType.h"
// CMysocket

CMysocket::CMysocket()
{
	WSAData WsaData = { 0 };

	// 初始化模块并进行判断
	if (WSAStartup(MAKEWORD(2, 2), &WsaData))
	{
		MessageBox(NULL, L"初始化模块失败", L"错误信息", MB_OK | MB_ICONERROR);
		ExitProcess(-1);
	}

	// 判断版本号是否正确



	// 使用 Create 创建一个套接字
	if (!this->Create())
	{
		int index = GetLastError();
		MessageBox(NULL, L"创建套接字失败", L"错误信息", MB_OK | MB_ICONERROR);
		ExitProcess(-1);
	}
}
//
CMysocket::~CMysocket()
{
	// 清理套接字和模块
	this->Close();
	WSACleanup();
}


// CMysocket 成员函数

//需要在这个函数内主动调用receivce函数进行分发

void CMysocket::OnReceive(int nErrorCode)
{
	// TODO: 在此添加专用代码和/或调用基类
	char s[2048] = { 0 };
	int size = Receive(s, sizeof(s));
	CLoginDlg* pDlg = (CLoginDlg*)AfxGetMainWnd();
	pDlg->OnReceive(size,(RecvInfo*)s);
	CSocket::OnReceive(nErrorCode);
}



