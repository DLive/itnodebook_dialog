#pragma once


// Conlinesearch �Ի���

class Conlinesearch : public CPropertyPage
{
	DECLARE_DYNAMIC(Conlinesearch)

public:
	Conlinesearch();
	virtual ~Conlinesearch();

// �Ի�������
	enum { IDD = P_NETSEARCH };

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV ֧��

	DECLARE_MESSAGE_MAP()
};
