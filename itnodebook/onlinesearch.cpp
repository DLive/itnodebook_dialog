// onlinesearch.cpp : 实现文件
//

#include "stdafx.h"
#include "itnodebook.h"
#include "onlinesearch.h"


// Conlinesearch 对话框

IMPLEMENT_DYNAMIC(Conlinesearch, CPropertyPage)

Conlinesearch::Conlinesearch()
	: CPropertyPage(Conlinesearch::IDD)
{

}

Conlinesearch::~Conlinesearch()
{
}

void Conlinesearch::DoDataExchange(CDataExchange* pDX)
{
	CPropertyPage::DoDataExchange(pDX);
}


BEGIN_MESSAGE_MAP(Conlinesearch, CPropertyPage)
END_MESSAGE_MAP()


// Conlinesearch 消息处理程序
