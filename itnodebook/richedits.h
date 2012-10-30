#include "itnoderich.h"
#pragma once


// Crichedits 对话框

class Crichedits : public CPropertyPage
{
	DECLARE_DYNAMIC(Crichedits)

public:
	Crichedits();
	Crichedits(int a);
	virtual ~Crichedits();

	const Crichedits & operator=( const Crichedits & scr );

// 对话框数据
	enum { IDD = IDP_RICHEDIT };

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV 支持

	DECLARE_MESSAGE_MAP()
public:
	afx_msg void OnSize(UINT nType, int cx, int cy);
};
