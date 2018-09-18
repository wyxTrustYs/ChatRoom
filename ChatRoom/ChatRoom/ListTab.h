#pragma once


// ListTab

class ListTab : public CTabCtrl
{
	DECLARE_DYNAMIC(ListTab)

public:
	ListTab();
	virtual ~ListTab();
	CDialogEx* m_dia[2];
protected:
	DECLARE_MESSAGE_MAP()
public:
	afx_msg void OnTcnSelchange(NMHDR *pNMHDR, LRESULT *pResult);
};


