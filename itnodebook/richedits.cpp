// richedits.cpp : 实现文件
//

#include "stdafx.h"
#include "itnodebook.h"
#include "richedits.h"


// Crichedits 对话框

IMPLEMENT_DYNAMIC(Crichedits, CPropertyPage)

Crichedits::Crichedits()
	: CPropertyPage(Crichedits::IDD)
{

}
Crichedits::Crichedits(int a)
{

}

Crichedits::~Crichedits()
{
}

void Crichedits::DoDataExchange(CDataExchange* pDX)
{
	CPropertyPage::DoDataExchange(pDX);
}


BEGIN_MESSAGE_MAP(Crichedits, CPropertyPage)
	ON_WM_SIZE()
END_MESSAGE_MAP()


// Crichedits 消息处理程序

void Crichedits::OnSize(UINT nType, int cx, int cy)
{
	CPropertyPage::OnSize(nType, cx, cy);
	CWnd * nWnd;
	nWnd=GetDlgItem(IDR_RICHEDIT);
	if(nWnd)
	{
		CRect rc;
		nWnd->GetWindowRect(&rc);
		ScreenToClient(&rc);
		rc.right=cx;
		rc.bottom=cy;
		nWnd->MoveWindow(rc);
	}
	// TODO: 在此处添加消息处理程序代码
}
 const Crichedits &Crichedits::operator =(const Crichedits & scr)
{
	return *this;
}
