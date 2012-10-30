// articles.cpp : 实现文件
//

#include "stdafx.h"
#include "itnodebook.h"
#include "articles.h"


// Carticles 对话框

IMPLEMENT_DYNAMIC(Carticles, CDialog)

Carticles::Carticles(CWnd* pParent /*=NULL*/)
	: CDialog(Carticles::IDD, pParent)
{
	AfxInitRichEdit2();
	m_nowPage=-1;
}

Carticles::~Carticles()
{
}

void Carticles::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	DDX_Control(pDX, T_ARTICLES, m_Articles);
}


BEGIN_MESSAGE_MAP(Carticles, CDialog)
	ON_WM_SIZE()
	ON_WM_CTLCOLOR()
	//选项卡的消息
	ON_NOTIFY(CTCN_CLICK, T_ARTICLES, OnLButtonClickedTab)
	ON_NOTIFY(CTCN_SELCHANGE, T_ARTICLES, OnSelchangeTab)

	ON_COMMAND(IDM_NEWFILE, &Carticles::OnNewfile)
END_MESSAGE_MAP()


// Carticles 消息处理程序

void Carticles::OnSize(UINT nType, int cx, int cy)
{
	CWnd *pWnd;
	pWnd=GetDlgItem(T_ARTICLES); //获取控件句柄 
	CRect prect;
	//CWnd *ppWnd;
	//*ppWnd->GetDlgItem(P_ARTICLE);
	//*ppWnd->GetWindowRect(&prect);
	ScreenToClient(&prect);
	if(pWnd)//判断是否为空，因为对话框创建时会调用此函数，而当时控件还未创建 
	{ 
	 CRect rect; //获取控件变化前大小 
	 pWnd->GetWindowRect(&rect); 
	 ScreenToClient(&rect);//将控件大小转换为在对话框中的区域坐标 
	 //　cx/m_rect.Width()为对话框在横向的变化比例
	 rect.right=rect.right+(cx-m_oldrect.Width());
	 //rect.bottom=rect.bottom+(cy-m_oldrect.Height());
	 pWnd->MoveWindow(rect);//设置控件大小 
	}
	
	pWnd=GetDlgItem(IDC_CONTAINER);//内容大小
	if(pWnd)//判断是否为空，因为对话框创建时会调用此函数，而当时控件还未创建 
	{ 
	 CRect rect; //获取控件变化前大小 
	 pWnd->GetWindowRect(&rect); 
	 ScreenToClient(&rect);//将控件大小转换为在对话框中的区域坐标 
	 //　cx/m_rect.Width()为对话框在横向的变化比例
	 rect.left=rect.left;//   *cx/m_oldrect.Width();/**//////调整控件大小 
	 rect.right=rect.right+(cx-m_oldrect.Width());
	 //rect.top=rect.top*cy/m_oldrect.Height();
	 rect.bottom=rect.bottom+(cy-m_oldrect.Height());
	 richRect=rect;
	 pWnd->MoveWindow(rect);//设置控件大小 
	}
	GetClientRect(&m_oldrect);

	//GetClientRect(&rect);//将变化后的对话框大小设为旧大
	CDialog::OnSize(nType, cx, cy);

	// TODO: 在此处添加消息处理程序代码
}

BOOL Carticles::OnInitDialog()
{
	CDialog::OnInitDialog();
	GetClientRect(&m_oldrect);
	// TODO:  在此添加额外的初始化
	//m_Articles.InsertItem(0,_T("初始页"));
	
	
	//m_Articles.Create(WS_VISIBLE|WS_CHILD,CRect(0,0,100,20),this,1);
	
	m_Articles.ModifyStyle(CTCS_RIGHT,CTCS_TOP|CTCS_CLOSEBUTTON|CTCS_BUTTONSAFTER,0);
	m_Articles.SetDragCursors(AfxGetApp()->LoadCursor(IDC_CURSORMOVE),AfxGetApp()->LoadCursor(IDC_CURSORCOPY));
	m_Articles.InsertItem(0,_T("SS_BLACKRECT"));
	m_Articles.SetItemData(0,SS_BLACKRECT);
	m_nowMaxPage=1;
	m_Articles.SetCurSel(0);
	
	return TRUE;  // return TRUE unless you set the focus to a control
	// 异常: OCX 属性页应返回 FALSE
}

HBRUSH Carticles::OnCtlColor(CDC* pDC, CWnd* pWnd, UINT nCtlColor)
{
	HBRUSH hbr = CDialog::OnCtlColor(pDC, pWnd, nCtlColor);

	// TODO:  在此更改 DC 的任何属性
	COLORREF backColor = RGB(199,221,242);

	return CreateSolidBrush(backColor);
	// TODO:  如果默认的不是所需画笔，则返回另一个画笔
	//return hbr;
}

BOOL Carticles::OnNotify(WPARAM wParam, LPARAM lParam, LRESULT* pResult)
{
	// TODO: 在此添加专用代码和/或调用基类

	return CDialog::OnNotify(wParam, lParam, pResult);
}

void Carticles::OnLButtonClickedTab(NMHDR* pNMHDR, LRESULT* pResult) 
{	
	switch(((CTC_NMHDR*)pNMHDR)->nItem)
	{
	case CTCHT_ONCLOSEBUTTON:
		{
		TRACE("OnLButtonClicked: Close\n");
		int nowpage=m_Articles.GetCurSel();
		if(m_Articles.DeleteItem(m_Articles.GetCurSel())!=CTCERR_NOERROR)
			AfxMessageBox(_T("DeleteItem(...) failed.\nPossible errors:\n1. Item index out of range."));
		if(nowpage>=1)
			richedits[nowpage].DestroyWindow();
		break;
		}
	case CTCHT_ONFIRSTBUTTON:
		TRACE("OnLButtonClicked: First\n");
		break;
	case CTCHT_ONPREVBUTTON:
		TRACE("OnLButtonClicked: Prev\n");
		break;
	case CTCHT_ONNEXTBUTTON:
		TRACE("OnLButtonClicked: Next\n");
		break;
	case CTCHT_ONLASTBUTTON:
		TRACE("OnLButtonClicked: Last\n");
		break;
	case CTCHT_NOWHERE:
		TRACE("OnLButtonClicked: Nowhere\n");
		break;
	default:
		{
			TRACE("Notify(CTCN_CLICK): nItem(%d) pszText(\'%s\') lParam(%d) point(x=%d,y=%d) rect(l=%d,t=%d,r=%d,b=%d) bSelected(%d) bHighlighted(%d)\n",
				((CTC_NMHDR*)pNMHDR)->nItem,
				((CTC_NMHDR*)pNMHDR)->pszText,
				((CTC_NMHDR*)pNMHDR)->lParam,
				((CTC_NMHDR*)pNMHDR)->ptHitTest.x,
				((CTC_NMHDR*)pNMHDR)->ptHitTest.y,
				((CTC_NMHDR*)pNMHDR)->rItem.left,
				((CTC_NMHDR*)pNMHDR)->rItem.top,
				((CTC_NMHDR*)pNMHDR)->rItem.right,
				((CTC_NMHDR*)pNMHDR)->rItem.bottom,
				((CTC_NMHDR*)pNMHDR)->fSelected,
				((CTC_NMHDR*)pNMHDR)->fHighlighted);
		}
		break;
	}
	*pResult = 0;
}
void Carticles::OnSelchangeTab(NMHDR* pNMHDR, LRESULT* pResult) 
{
	/*TRACE("Notify(CTCN_SELCHANGE): nItem(%d) pszText(\'%s\') lParam(%d) point(x=%d,y=%d) rect(l=%d,t=%d,r=%d,b=%d) bSelected(%d) bHighlighted(%d)\n",
				((CTC_NMHDR*)pNMHDR)->nItem,
				((CTC_NMHDR*)pNMHDR)->pszText,
				((CTC_NMHDR*)pNMHDR)->lParam,
				((CTC_NMHDR*)pNMHDR)->ptHitTest.x,
				((CTC_NMHDR*)pNMHDR)->ptHitTest.y,
				((CTC_NMHDR*)pNMHDR)->rItem.left,
				((CTC_NMHDR*)pNMHDR)->rItem.top,
				((CTC_NMHDR*)pNMHDR)->rItem.right,
				((CTC_NMHDR*)pNMHDR)->rItem.bottom,
				((CTC_NMHDR*)pNMHDR)->fSelected,
				((CTC_NMHDR*)pNMHDR)->fHighlighted);
	m_ctrlColor.ModifyStyle(SS_BLACKRECT|SS_GRAYRECT|SS_WHITERECT,((CTC_NMHDR*)pNMHDR)->lParam);
	m_ctrlColor.Invalidate();*/
	int i=m_Articles.GetCurSel();
	if(i>=1)
	{
		if(m_nowPage>=1)
			richedits[m_nowPage].ShowWindow(false);
		richedits[i].ShowWindow(true);
		m_nowPage=i;
	}
	else
	{
		richedits[m_nowPage].ShowWindow(false);
	}
	*pResult = 0;
}
void Carticles::OnNewfile()
{

	// TODO: 在此添加命令处理程序代码
	
}

// //添加新页面
int Carticles::createNewpage()
{
	m_Articles.InsertItem(m_nowMaxPage,_T("asdfsa"));
	m_Articles.SetCurSel(m_nowMaxPage);
	
	CRect rc=richRect;
	CRect tabRect;
	GetDlgItem(T_ARTICLES)->GetWindowRect(&tabRect);
	ScreenToClient(&tabRect);
	rc.top=rc.top+tabRect.Height();
	rc.left-=4;
	rc.bottom=rc.bottom+tabRect.Height();

	richedits.SetAtGrow(m_nowMaxPage,*(new Crichedits(m_nowMaxPage)));

	richedits[m_nowMaxPage].Create(IDP_RICHEDIT,GetDlgItem(P_ARTICLE));
	richedits[m_nowMaxPage].MoveWindow(rc);
	if(m_nowPage>=1)
	{
		richedits[m_nowPage].ShowWindow(false);
	}
	richedits[m_nowMaxPage].ShowWindow(true);
	m_nowPage=m_nowMaxPage;
	m_nowMaxPage++;
	
	return 0;
}
