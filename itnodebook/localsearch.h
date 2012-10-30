#pragma once


// Clocalsearch 对话框

class Clocalsearch : public CPropertyPage
{
	DECLARE_DYNAMIC(Clocalsearch)

public:
	Clocalsearch();
	virtual ~Clocalsearch();

// 对话框数据
	enum { IDD = P_LOCALSEARCH };

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV 支持

	DECLARE_MESSAGE_MAP()
public:
	afx_msg void OnSize(UINT nType, int cx, int cy);
};
