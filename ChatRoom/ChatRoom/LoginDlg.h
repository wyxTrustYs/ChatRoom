
// LoginDlg.h : ͷ�ļ�
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
// CLoginDlg �Ի���
class CLoginDlg : public CDialogEx
{
// ����
public:
	CLoginDlg(CWnd* pParent = NULL);	// ��׼���캯��

// �Ի�������
#ifdef AFX_DESIGN_TIME
	enum { IDD = IDD_LoginDlg };
#endif

	protected:
	virtual void DoDataExchange(CDataExchange* pDX);	// DDX/DDV ֧��


// ʵ��
protected:
	HICON m_hIcon;

	// ���ɵ���Ϣӳ�亯��
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
