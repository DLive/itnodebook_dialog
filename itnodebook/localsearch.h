#pragma once


// Clocalsearch �Ի���

class Clocalsearch : public CPropertyPage
{
	DECLARE_DYNAMIC(Clocalsearch)

public:
	Clocalsearch();
	virtual ~Clocalsearch();

// �Ի�������
	enum { IDD = P_LOCALSEARCH };

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV ֧��

	DECLARE_MESSAGE_MAP()
public:
	afx_msg void OnSize(UINT nType, int cx, int cy);
};
