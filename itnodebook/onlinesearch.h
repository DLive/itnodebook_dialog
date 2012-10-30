#pragma once


// Conlinesearch 对话框

class Conlinesearch : public CPropertyPage
{
	DECLARE_DYNAMIC(Conlinesearch)

public:
	Conlinesearch();
	virtual ~Conlinesearch();

// 对话框数据
	enum { IDD = P_NETSEARCH };

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV 支持

	DECLARE_MESSAGE_MAP()
};
