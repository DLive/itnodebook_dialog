#include "itnoderich.h"
#pragma once


// Crichedits �Ի���

class Crichedits : public CPropertyPage
{
	DECLARE_DYNAMIC(Crichedits)

public:
	Crichedits();
	Crichedits(int a);
	virtual ~Crichedits();

	const Crichedits & operator=( const Crichedits & scr );

// �Ի�������
	enum { IDD = IDP_RICHEDIT };

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV ֧��

	DECLARE_MESSAGE_MAP()
public:
	afx_msg void OnSize(UINT nType, int cx, int cy);
};
