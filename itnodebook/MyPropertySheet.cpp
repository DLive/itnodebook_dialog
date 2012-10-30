// MyPropertySheet.cpp : 实现文件
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
// CMyPropertySheet 消息处理程序

INT_PTR CMyPropertySheet::DoModal()
{
	// TODO: 在此添加专用代码和/或调用基类
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
		rectWnd.Width() + 100,//窗口向右扩展
		rectWnd.Height(),//窗口向下扩展
		SWP_NOMOVE | SWP_NOZORDER | SWP_NOACTIVATE);
	GetClientRect(&m_rCrt);//获得初使窗口矩形
	m_bIsInited = TRUE;
	return bResult;
}

void CMyPropertySheet::OnSize(UINT nType, int cx, int cy)
{
	//TABLE内的窗口页在其WM_SIZE响应函数里调整大小即可
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

	// TODO: 在此处添加消息处理程序代码
}

void CMyPropertySheet::OnGetMinMaxInfo(MINMAXINFO* lpMMI)
{
	// TODO: 在此添加消息处理程序代码和/或调用默认值
	if(!m_bIsInited)return;
	lpMMI->ptMinTrackSize.x = 300;//窗口的最小尺寸
	lpMMI->ptMinTrackSize.y = 250;

	lpMMI->ptMaxTrackSize.x = 800;//窗口的最大尺寸
	lpMMI->ptMaxTrackSize.y = 600;
	

	lpMMI->ptMaxPosition.x = 100;//最大化时的位置
	lpMMI->ptMaxPosition.y = 80;

	lpMMI->ptMaxSize.x = 640;//最大化时的尺寸
	lpMMI->ptMaxSize.x = 480;
	CPropertySheet::OnGetMinMaxInfo(lpMMI);
}
