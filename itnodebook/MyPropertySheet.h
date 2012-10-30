#pragma once
#include "articles.h"
#include "localsearch.h"


// CMyPropertySheet

class CMyPropertySheet : public CPropertySheet
{
	DECLARE_DYNAMIC(CMyPropertySheet)

public:
	Carticles apage;
	Clocalsearch bpage;
	CMyPropertySheet(UINT nIDCaption, CWnd* pParentWnd = NULL, UINT iSelectPage = 0);
	CMyPropertySheet(LPCTSTR pszCaption, CWnd* pParentWnd = NULL, UINT iSelectPage = 0);
	virtual ~CMyPropertySheet();

protected:
	BOOL m_bIsInited;//该值初使化为FLASE
	CRect m_rCrt; 
	DECLARE_MESSAGE_MAP()
public:
	virtual INT_PTR DoModal();
	virtual BOOL OnInitDialog();
	afx_msg void OnSize(UINT nType, int cx, int cy);
	afx_msg void OnGetMinMaxInfo(MINMAXINFO* lpMMI);
};


