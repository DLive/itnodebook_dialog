// localsearch.cpp : ʵ���ļ�
//

#include "stdafx.h"
#include "itnodebook.h"
#include "localsearch.h"


// Clocalsearch �Ի���

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


// Clocalsearch ��Ϣ�������

void Clocalsearch::OnSize(UINT nType, int cx, int cy)
{
	CPropertyPage::OnSize(nType, cx, cy);

	// TODO: �ڴ˴������Ϣ����������
}
