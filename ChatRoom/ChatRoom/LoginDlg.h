
// LoginDlg.h : 头文件
//

#pragma once
#include "afxwin.h"
#include "Mysocket.h"
#include "DataType.h"
typedef struct
{
	int cuserlen;
	int psdlen;
	char cuser[1024];
	char passwod[1024];
}user;
// CLoginDlg 对话框
class CLoginDlg : public CDialogEx
{
// 构造
public:
	CLoginDlg(CWnd* pParent = NULL);	// 标准构造函数

// 对话框数据
#ifdef AFX_DESIGN_TIME
	enum { IDD = IDD_LoginDlg };
#endif

	protected:
	virtual void DoDataExchange(CDataExchange* pDX);	// DDX/DDV 支持


// 实现
protected:
	HICON m_hIcon;

	// 生成的消息映射函数
	virtual BOOL OnInitDialog();
	afx_msg void OnSysCommand(UINT nID, LPARAM lParam);
	afx_msg void OnPaint();
	afx_msg HCURSOR OnQueryDragIcon();
	DECLARE_MESSAGE_MAP()
public:
	CButton BtnRegiste;
	CButton BtnLogin;
	CButton BtnCancel;
	CString EditPsd;
	CString EditAccount;
	CMysocket m_socket;
	afx_msg void OnBnClickedbtnlogin();
	void OnReceive(int size,RecvInfo* szText);
	afx_msg void OnBnClickedbtnregiste();
protected:
	afx_msg LRESULT OnClicklogin(WPARAM wParam, LPARAM lParam);
	afx_msg LRESULT OnRegister1(WPARAM wParam, LPARAM lParam);
	afx_msg LRESULT OnSearch(WPARAM wParam, LPARAM lParam);
};
