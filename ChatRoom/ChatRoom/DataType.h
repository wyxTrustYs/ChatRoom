#pragma once

// ע����Ϣ
#define WM_REGISTER1 WM_USER + 1
#define WM_REGISTER2 WM_USER + 2
#define WM_LOGIN WM_USER + 3
#define WM_Search WM_USER + 4
// ǿö������
enum class MsgType
{
	REGISTER = 0,
	LOGIN = 1,
	Search = 2
};

// ǿö������
enum class RecvType
{
	REGISTER = 0,
	LOGIN = 1,
	Search = 2
};

// ����ע����Ϣ�Ľṹ��
struct RegisterInfo
{
	wchar_t sex[4];
	wchar_t name[20];
	wchar_t pswd[20];
	wchar_t nick[20];
	//wchar_t birthday[12];
};

// �����¼��Ϣ�Ľṹ��
struct LoginInfo
{
	wchar_t name[20];
	wchar_t pswd[20];
};

// ���ڱ���������Ϣ�Ľṹ��
struct MsgInfo
{
	MsgType type;		// ö��
	HWND hWnd;
	// ����������Ϣ�Ľṹ��
	// ���Ĵ�С��������͵Ĵ�С
	union {
		RegisterInfo reg_info;
		LoginInfo login_info;
	};
};



// ע���Ƿ�ɹ�
struct RecvReg
{
	BOOL sucess;
	char msg[20];
};

// ���յ�¼�Ƿ�ɹ�
typedef RecvReg RecvLogin;


// ���ڱ������н��յ�����Ϣ�Ľṹ��
struct RecvInfo
{
	RecvType type;		// ö��
	HWND hWnd;
	// ����������Ϣ�Ľṹ��
	// ���Ĵ�С��������͵Ĵ�С
	union {
		RecvReg reg_info;
		RecvLogin login_info;
		char str[100];
	};
};