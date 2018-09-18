#pragma once


// CPrivateDlg 对话框

class CPrivateDlg : public CDialogEx
{
	DECLARE_DYNAMIC(CPrivateDlg)

public:
	CPrivateDlg(CWnd* pParent = NULL);   // 标准构造函数
	virtual ~CPrivateDlg();

// 对话框数据
#ifdef AFX_DESIGN_TIME
	enum { IDD = IDD_DIALOGSin };
#endif

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV 支持

	DECLARE_MESSAGE_MAP()
};
