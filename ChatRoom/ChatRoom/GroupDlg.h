#pragma once


// GroupDlg �Ի���

class GroupDlg : public CDialogEx
{
	DECLARE_DYNAMIC(GroupDlg)

public:
	GroupDlg(CWnd* pParent = NULL);   // ��׼���캯��
	virtual ~GroupDlg();

// �Ի�������
#ifdef AFX_DESIGN_TIME
	enum { IDD = IDD_DIALOGGroup };
#endif

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV ֧��

	DECLARE_MESSAGE_MAP()
};
