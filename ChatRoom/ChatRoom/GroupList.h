#pragma once


// CGroupList �Ի���

class CGroupList : public CDialogEx
{
	DECLARE_DYNAMIC(CGroupList)

public:
	CGroupList(CWnd* pParent = NULL);   // ��׼���캯��
	virtual ~CGroupList();

// �Ի�������
#ifdef AFX_DESIGN_TIME
	enum { IDD = IDD_DIALOGGroup };
#endif

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV ֧��

	DECLARE_MESSAGE_MAP()
};
