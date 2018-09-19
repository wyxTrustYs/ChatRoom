// Mysocket.cpp : ʵ���ļ�
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

	// ��ʼ��ģ�鲢�����ж�
	if (WSAStartup(MAKEWORD(2, 2), &WsaData))
	{
		MessageBox(NULL, L"��ʼ��ģ��ʧ��", L"������Ϣ", MB_OK | MB_ICONERROR);
		ExitProcess(-1);
	}

	// �жϰ汾���Ƿ���ȷ



	// ʹ�� Create ����һ���׽���
	if (!this->Create())
	{
		int index = GetLastError();
		MessageBox(NULL, L"�����׽���ʧ��", L"������Ϣ", MB_OK | MB_ICONERROR);
		ExitProcess(-1);
	}
}
//
CMysocket::~CMysocket()
{
	// �����׽��ֺ�ģ��
	this->Close();
	WSACleanup();
}


// CMysocket ��Ա����

//��Ҫ�������������������receivce�������зַ�

void CMysocket::OnReceive(int nErrorCode)
{
	// TODO: �ڴ����ר�ô����/����û���
	char s[2048] = { 0 };
	int size = Receive(s, sizeof(s));
	CLoginDlg* pDlg = (CLoginDlg*)AfxGetMainWnd();
	pDlg->OnReceive(size,(RecvInfo*)s);
	CSocket::OnReceive(nErrorCode);
}



