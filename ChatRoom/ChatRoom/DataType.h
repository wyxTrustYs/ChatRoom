#pragma once

// 注册消息
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
// 强枚举类型
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

// 保存注册信息的结构体
struct RegisterInfo
{
	wchar_t sex[4];
	wchar_t name[20];
	wchar_t pswd[20];
	wchar_t nick[20];
	//wchar_t birthday[12];
};

// 保存登录信息的结构体
struct LoginInfo
{
	wchar_t name[20];
	wchar_t pswd[20];
};

// 保存私聊的结构体
struct FrdChatMsg
{
	WCHAR from[20];	// 用户名
	WCHAR to[20];	// 发送给谁
	WCHAR msg[100];// 消息
};

// 更新列表的消息
struct UpdateFrd
{
	// 自己的名字或好友的名字
	WCHAR name[20];
};

// 用于保存所有信息的结构体
struct MsgInfo
{
	MsgType type;		// 枚举
	HWND hWnd;
	// 保存所有信息的结构体
	// 它的大小是最大类型的大小
	union {
		RegisterInfo reg_info;
		LoginInfo login_info;
		FrdChatMsg frdchat_msg;
		UpdateFrd updatefrd_msg;
		FrdChatMsg groupchat_msg;
		char groupid[10];
	};
};
//返回更新好友列表的消息
struct RecvSearch
{
	char ID[10];
	char nick[20];
};



// 注册是否成功
struct RecvReg
{
	BOOL sucess;
	char msg[20];
};

// 接收登录是否成功
struct RecvLogin
{
	BOOL sucess;
	char msg[20];
	char nick[20];
};


// 用于保存所有接收到的信息的结构体
struct RecvInfo
{
	MsgType type;		// 枚举
	HWND hWnd;
	// 保存所有信息的结构体
	// 它的大小是最大类型的大小
	union {
		RecvReg reg_info;
		RecvLogin login_info;
		RecvSearch searchFred;
		UpdateFrd updatefrd_msg;
		FrdChatMsg frdchat_msg;
		char str[100];
	};
};