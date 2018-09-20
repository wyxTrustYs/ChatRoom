#pragma once

// ע����Ϣ
#define WM_REGISTER1 WM_USER + 1
#define WM_REGISTER2 WM_USER + 2
#define WM_LOGIN WM_USER + 3
#define WM_Search WM_USER + 4
#define WM_UPDATEFRND WM_USER + 5
#define WM_SENDMSG WM_USER + 6
#define WM_GETFRIENDMSG WM_USER + 7
#define WM_SearchGroup WM_USER + 8
#define WM_UPDATEGROUP WM_USER + 9
#define WM_UPDATEMEMBERINGRUP WM_USER + 10
#define WM_GETGROUPMSG WM_USER + 11
// ǿö������
enum class MsgType
{
	REGISTER = 0,
	LOGIN = 1,
	Search = 2,
	FRIENDMSG = 3,
	SearchGroup = 4,
	UserInGroup = 5,
	GROUPMSG = 6
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

// ����˽�ĵĽṹ��
struct FrdChatMsg
{
	WCHAR from[20];	// �û���
	WCHAR to[20];	// ���͸�˭
	WCHAR msg[100];// ��Ϣ
};

// �����б����Ϣ
struct UpdateFrd
{
	// �Լ������ֻ���ѵ�����
	WCHAR name[20];
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
		FrdChatMsg frdchat_msg;
		UpdateFrd updatefrd_msg;
		FrdChatMsg groupchat_msg;
		char groupid[10];
	};
};
//���ظ��º����б����Ϣ
struct RecvSearch
{
	char ID[10];
	char nick[20];
};



// ע���Ƿ�ɹ�
struct RecvReg
{
	BOOL sucess;
	char msg[20];
};

// ���յ�¼�Ƿ�ɹ�
struct RecvLogin
{
	BOOL sucess;
	char msg[20];
	char nick[20];
};


// ���ڱ������н��յ�����Ϣ�Ľṹ��
struct RecvInfo
{
	MsgType type;		// ö��
	HWND hWnd;
	// ����������Ϣ�Ľṹ��
	// ���Ĵ�С��������͵Ĵ�С
	union {
		RecvReg reg_info;
		RecvLogin login_info;
		RecvSearch searchFred;
		UpdateFrd updatefrd_msg;
		FrdChatMsg frdchat_msg;
		char str[100];
	};
};