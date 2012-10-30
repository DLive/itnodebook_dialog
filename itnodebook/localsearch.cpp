// localsearch.cpp : 实现文件
//

#include "stdafx.h"
#include "itnodebook.h"
#include "localsearch.h"


// Clocalsearch 对话框

IMPLEMENT_DYNAMIC(Clocalsearch, CPropertyPage)

Clocalsearch::Clocalsearch()
	: CPropertyPage(Clocalsearch::IDD)
{

}

Clocalsearch::~Clocalsearch()
{
}

void Clocalsearch::DoDataExchange(CDataExchange* pDX)
{
	CPropertyPage::DoDataExchange(pDX);
}


BEGIN_MESSAGE_MAP(Clocalsearch, CPropertyPage)
	ON_WM_SIZE()
END_MESSAGE_MAP()


// Clocalsearch 消息处理程序

void Clocalsearch::OnSize(UINT nType, int cx, int cy)
{
	CPropertyPage::OnSize(nType, cx, cy);

	// TODO: 在此处添加消息处理程序代码
}
