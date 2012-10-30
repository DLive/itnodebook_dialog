// MyPropertySheet.cpp : ʵ���ļ�
//

#include "stdafx.h"
#include "itnodebook.h"
#include "MyPropertySheet.h"


// CMyPropertySheet

IMPLEMENT_DYNAMIC(CMyPropertySheet, CPropertySheet)

CMyPropertySheet::CMyPropertySheet(UINT nIDCaption, CWnd* pParentWnd, UINT iSelectPage)
	:CPropertySheet(nIDCaption, pParentWnd, iSelectPage)
{

}

CMyPropertySheet::CMyPropertySheet(LPCTSTR pszCaption, CWnd* pParentWnd, UINT iSelectPage)
	:CPropertySheet(pszCaption, pParentWnd, iSelectPage)
{

}

CMyPropertySheet::~CMyPropertySheet()
{
}


BEGIN_MESSAGE_MAP(CMyPropertySheet, CPropertySheet)
	ON_WM_SIZE()
	ON_WM_GETMINMAXINFO()
END_MESSAGE_MAP()

int CALLBACK PropSheetCallback(HWND hWnd, UINT message, LPARAM lParam)
{
	extern int CALLBACK AfxPropSheetCallback(HWND, UINT message, LPARAM lParam);
	int nRes = AfxPropSheetCallback(hWnd, message, lParam);
	switch (message)
	{
	case PSCB_PRECREATE:
		((LPDLGTEMPLATE)lParam)->style |= (DS_3DLOOK | DS_SETFONT | WS_MAXIMIZEBOX | WS_MINIMIZEBOX
		| WS_THICKFRAME | WS_SYSMENU | WS_POPUP | WS_VISIBLE | WS_CAPTION);
		break;
	}
   return nRes;
}
// CMyPropertySheet ��Ϣ�������

INT_PTR CMyPropertySheet::DoModal()
{
	// TODO: �ڴ����ר�ô����/����û���
	AddPage(&bpage);
	m_psh.dwFlags |= PSH_USECALLBACK;
	m_psh.pfnCallback = PropSheetCallback;
	return CPropertySheet::DoModal();
}

BOOL CMyPropertySheet::OnInitDialog()
{
	BOOL bResult = CPropertySheet::OnInitDialog();


	CRect rectWnd;
	GetWindowRect(rectWnd);
	SetWindowPos(NULL, 0, 0,
		rectWnd.Width() + 100,//����������չ
		rectWnd.Height(),//����������չ
		SWP_NOMOVE | SWP_NOZORDER | SWP_NOACTIVATE);
	GetClientRect(&m_rCrt);//��ó�ʹ���ھ���
	m_bIsInited = TRUE;
	return bResult;
}

void CMyPropertySheet::OnSize(UINT nType, int cx, int cy)
{
	//TABLE�ڵĴ���ҳ����WM_SIZE��Ӧ�����������С����
   CRect rcClient; 
   CPropertySheet::OnSize(nType, cx, cy);

   if(!m_bIsInited)return;
   CTabCtrl *pTab = GetTabControl();
   //ASSERT(NULL != pTab && IsWindow(pTab->m_hWnd));

   int dx = cx - m_rCrt.Width();
   int dy = cy - m_rCrt.Height();
   GetClientRect(&m_rCrt);

   HDWP hDWP = ::BeginDeferWindowPos(5);

   pTab->GetClientRect(&rcClient); 
   rcClient.right += dx; rcClient.bottom += dy;
   ::DeferWindowPos(hDWP, pTab->m_hWnd, NULL,
                    0, 0, rcClient.Width(), rcClient.Height(),
                    SWP_NOACTIVATE|SWP_NOMOVE|SWP_NOZORDER);

	for (CWnd *pChild = GetWindow(GW_CHILD);
	pChild != NULL;
	pChild = pChild->GetWindow(GW_HWNDNEXT))
	{
		if (pChild->SendMessage(WM_GETDLGCODE) & DLGC_BUTTON)
		{
			pChild->GetWindowRect(&rcClient); ScreenToClient(&rcClient); 
			rcClient.top += dy; rcClient.bottom += dy; rcClient.left+= dx; rcClient.right += dx;
			::DeferWindowPos(hDWP, pChild->m_hWnd, NULL,
				rcClient.left, rcClient.top, 0, 0,
				SWP_NOACTIVATE|SWP_NOSIZE|SWP_NOZORDER);
		}
		else
		{
			pChild->GetClientRect(&rcClient); 
			rcClient.right += dx; rcClient.bottom += dy;
			::DeferWindowPos(hDWP, pChild->m_hWnd, NULL, 0, 0, 
				rcClient.Width(), rcClient.Height(),
				SWP_NOACTIVATE|SWP_NOMOVE|SWP_NOZORDER);
		}
	}
	::EndDeferWindowPos(hDWP);

	// TODO: �ڴ˴������Ϣ����������
}

void CMyPropertySheet::OnGetMinMaxInfo(MINMAXINFO* lpMMI)
{
	// TODO: �ڴ������Ϣ�����������/�����Ĭ��ֵ
	if(!m_bIsInited)return;
	lpMMI->ptMinTrackSize.x = 300;//���ڵ���С�ߴ�
	lpMMI->ptMinTrackSize.y = 250;

	lpMMI->ptMaxTrackSize.x = 800;//���ڵ����ߴ�
	lpMMI->ptMaxTrackSize.y = 600;
	

	lpMMI->ptMaxPosition.x = 100;//���ʱ��λ��
	lpMMI->ptMaxPosition.y = 80;

	lpMMI->ptMaxSize.x = 640;//���ʱ�ĳߴ�
	lpMMI->ptMaxSize.x = 480;
	CPropertySheet::OnGetMinMaxInfo(lpMMI);
}
