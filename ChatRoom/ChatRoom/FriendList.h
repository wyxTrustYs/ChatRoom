#pragma once
#include "ListTab.h"
#include "Mysocket.h"


// CFriendList �Ի���

class CFriendList : public CDialogEx
{
	DECLARE_DYNAMIC(CFriendList)

public:
	CFriendList(CWnd* pParent = NULL);   // ��׼���캯��
	virtual ~CFriendList();

// �Ի�������
#ifdef AFX_DESIGN_TIME
	enum { IDD = IDD_Dlg };
#endif

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV ֧��

	DECLARE_MESSAGE_MAP()
public:

	ListTab m_ListTab;
	virtual BOOL OnInitDialog();
	CMysocket m_socket;
protected:

//	afx_msg LRESULT OnSearchfriendandgroup(WPARAM wParam, LPARAM lParam);
};
