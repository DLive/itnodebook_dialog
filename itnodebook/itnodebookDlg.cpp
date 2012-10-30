// itnodebookDlg.cpp : 实现文件
//

#include "stdafx.h"
#include "itnodebook.h"
#include "itnodebookDlg.h"
#include   <afxpriv.h> 
#include "MyPropertySheet.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#endif

#ifndef OBM_SIZE
#define OBM_SIZE 32766
#endif


// 用于应用程序“关于”菜单项的 CAboutDlg 对话框

class CAboutDlg : public CDialog
{
public:
	CAboutDlg();

// 对话框数据
	enum { IDD = IDD_ABOUTBOX };

	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV 支持

// 实现
protected:
	DECLARE_MESSAGE_MAP()
};

CAboutDlg::CAboutDlg() : CDialog(CAboutDlg::IDD)
{
}

void CAboutDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
}

BEGIN_MESSAGE_MAP(CAboutDlg, CDialog)
END_MESSAGE_MAP()


// CitnodebookDlg 对话框




CitnodebookDlg::CitnodebookDlg(CWnd* pParent /*=NULL*/)
	: CDialog(CitnodebookDlg::IDD, pParent)
{
	m_hIcon = AfxGetApp()->LoadIcon(IDR_MAINFRAME);
	m_bFirstTime = TRUE;
}

void CitnodebookDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
}

BEGIN_MESSAGE_MAP(CitnodebookDlg, CDialog)
	ON_WM_SYSCOMMAND()
	ON_WM_PAINT()
	ON_WM_QUERYDRAGICON()
	ON_NOTIFY_EX_RANGE(TTN_NEEDTEXTW, 0, 0xFFFF, OnToolTipText)//工具栏提示信息
	ON_NOTIFY_EX_RANGE(TTN_NEEDTEXTA, 0, 0xFFFF, OnToolTipText)
	
	//}}AFX_MSG_MAP
	ON_WM_CTLCOLOR()
	ON_WM_SIZE()
	ON_WM_SIZING()
	
	ON_WM_SETFOCUS()
	ON_BN_CLICKED(B_ARTICLE, &CitnodebookDlg::OnBnClickedArticle)
	ON_BN_CLICKED(B_LOCALSER, &CitnodebookDlg::OnBnClickedLocalser)
	ON_BN_CLICKED(B_ONLINESER, &CitnodebookDlg::OnBnClickedOnlineser)
	ON_COMMAND(IDM_NEWFILE, &CitnodebookDlg::OnNewfile)
END_MESSAGE_MAP()


// CitnodebookDlg 消息处理程序

BOOL CitnodebookDlg::OnInitDialog()
{
	CDialog::OnInitDialog();

	// 将“关于...”菜单项添加到系统菜单中。

	// IDM_ABOUTBOX 必须在系统命令范围内。
	ASSERT((IDM_ABOUTBOX & 0xFFF0) == IDM_ABOUTBOX);
	ASSERT(IDM_ABOUTBOX < 0xF000);

	CMenu* pSysMenu = GetSystemMenu(FALSE);
	if (pSysMenu != NULL)
	{
		CString strAboutMenu;
		strAboutMenu.LoadString(IDS_ABOUTBOX);
		if (!strAboutMenu.IsEmpty())
		{
			pSysMenu->AppendMenu(MF_SEPARATOR);
			pSysMenu->AppendMenu(MF_STRING, IDM_ABOUTBOX, strAboutMenu);
		}
	}

	// 设置此对话框的图标。当应用程序主窗口不是对话框时，框架将自动
	//  执行此操作
	SetIcon(m_hIcon, TRUE);			// 设置大图标
	SetIcon(m_hIcon, FALSE);		// 设置小图标

	// TODO: 在此添加额外的初始化代码
	
	//加载菜单
	CMenu menu;
	menu.LoadMenuW(IDR_MENU1);
	SetMenu(&menu);
	DrawMenuBar();
	
	//添加工具栏
	if(!m_itbar.CreateEx(this,TBSTYLE_FLAT,WS_CHILD|WS_VISIBLE|CBRS_ALIGN_TOP|CBRS_GRIPPER|CBRS_TOOLTIPS|CBRS_FLYBY)||!m_itbar.LoadToolBar(IDR_TOOLBAR1))
	{
		TRACE0("添加工具栏失败");
		return FALSE;
	}
	m_itbar.ShowWindow(SW_SHOW);
	//RepositionBars(AFX_IDW_CONTROLBAR_FIRST,AFX_IDW_CONTROLBAR_LAST,0);
	
	/*if(!m_itbar.Create(this)||!m_itbar.LoadToolBar(IDR_TOOLBAR1))
	{
		TRACE0("添加工具条失败");
		EndDialog(IDCANCEL);
	}
	
	m_itbar.ShowWindow(SW_SHOW);*/
	CRect rcClientStart;
	CRect rcClientNow;
	GetClientRect(rcClientStart);
	RepositionBars(AFX_IDW_CONTROLBAR_FIRST,AFX_IDW_CONTROLBAR_LAST,0, reposQuery, rcClientNow);
	//在对话框中移动控件，确定控制条在工作区的顶部或左侧占用的空间
	CPoint ptOffset(rcClientNow.left - rcClientStart.left,
                rcClientNow.top - rcClientStart.top);
	CRect rcChild;
	CWnd* pwndChild = GetWindow(GW_CHILD);
	while (pwndChild)
    {
       pwndChild->GetWindowRect(rcChild);
       ScreenToClient(rcChild);
       rcChild.OffsetRect(ptOffset);
       pwndChild->MoveWindow(rcChild, FALSE);
       pwndChild = pwndChild->GetNextWindow();
    }
	//根据控制条占用的空间量，增加对话框窗口的尺寸。
	CRect rcWindow;
	GetWindowRect(rcWindow);
	m_toolBarHeight=rcClientStart.Height() - rcClientNow.Height();
	rcWindow.right += rcClientStart.Width() - rcClientNow.Width();
	rcWindow.bottom += rcClientStart.Height() - rcClientNow.Height();
	MoveWindow(rcWindow, FALSE);
	RepositionBars(AFX_IDW_CONTROLBAR_FIRST,AFX_IDW_CONTROLBAR_LAST,0);
	

	m_statusBar.Create(WS_CHILD|WS_VISIBLE|SBT_OWNERDRAW,CRect(0,0,0,0),this,0);
	int strPartDim[3]={100,200,-1};
	m_statusBar.SetParts(3,strPartDim);
	m_statusBar.SetText(_T("分栏一"),1,0);
	m_statusBar.SetText(_T("分栏二"),1,0);
	m_statusBar.SetText(_T("分栏三"),2,0);

	//添加文章属性页
	m_pArticle.Create(P_ARTICLE,this);
	CRect rs;
	GetClientRect(&rs);
	//调整子对话框在父窗口中的位置
	int pwidth=rs.Width();
	int pheight=rs.Height();
	rs.top+=m_toolBarHeight;
	rs.right-=120;
	rs.bottom-=22;
	m_proPageRect=rs;
	m_pArticle.MoveWindow(&rs);
	m_pArticle.ShowWindow(true);
	
	m_pLocalsearch.Create(P_LOCALSEARCH,this);
	m_pLocalsearch.MoveWindow(&rs);
	m_pLocalsearch.ShowWindow(false);

	m_pOnlinesearch.Create(P_NETSEARCH,this);
	m_pOnlinesearch.MoveWindow(&rs);
	m_pOnlinesearch.ShowWindow(false);
	//SetWindowPos(GetDlgItem(P_ARTICLE),200,200,pwidth-300,pheight-300,SWP_SHOWWINDOW|SWP_FRAMECHANGED);
	
	//设置可改变对话框大小
	ModifyStyle(0, WS_SIZEBOX);
	// 以对话框的初始大小作为对话框的宽度和高度的最小值
	CRect rectDlg;
	GetWindowRect(rectDlg);
	m_iMinWidth = rectDlg.Width();
	m_iMinHeight = rectDlg.Height();//设成最小高度
	// 得到对话框client区域的大小
	CRect rectClient;
	GetClientRect(rectClient);
	m_iClientWidth = rectClient.Width();//对话框client区域的宽度
	m_iClientHeight = rectClient.Height();//对话框client区域的高度
	// Load图标
	m_bmpSizeIcon.LoadOEMBitmap(OBM_SIZE);//拉伸加载图标
	m_bmpSizeIcon.GetBitmap(&m_bitmap);//
	// 创建显示图标的静态控件并放在对话框右下角
	m_wndSizeIcon.Create(NULL, WS_CHILD | WS_VISIBLE | SS_BITMAP, CRect(0, 0, m_bitmap.bmWidth, m_bitmap.bmHeight), this, 0);
	m_wndSizeIcon.SetBitmap(m_bmpSizeIcon);
	m_wndSizeIcon.MoveWindow(m_iClientWidth - m_bitmap.bmWidth, m_iClientHeight - m_bitmap.bmHeight, m_bitmap.bmWidth, m_bitmap.bmHeight);
	// 显示图标
	m_wndSizeIcon.ShowWindow(m_bShowSizeIcon);
	
	//设置对话框可改变大小结束
	
	static DLGCTLINFO dcMenuGroup[] =
	{
		
		{B_ARTICLE,MOVEXY,100},
		{B_ONLINESER,MOVEXY,100},
		{B_LOCALSER,MOVEXY,100}

	};
	m_bArticle.SubclassDlgItem(B_ARTICLE,this);
	m_bArticle.SetIcon(ICO_ARTICLES);

	m_bOnline.SubclassDlgItem(B_ONLINESER,this);
	m_bOnline.SetIcon(ICO_ONLINE);

	m_bLocal.SubclassDlgItem(B_LOCALSER,this);
	m_bLocal.SetIcon(ICO_LOCAL);
	if (m_bFirstTime == TRUE)
	{
		m_bFirstTime = FALSE;
		m_bArticle.DrawTransparent(TRUE);
		m_bOnline.DrawTransparent(TRUE);
		m_bLocal.DrawTransparent(TRUE);
		
	}

// 设置控件信息-改变窗口大小时用。
	SetControlProperty(dcMenuGroup, sizeof(dcMenuGroup)/sizeof(DLGCTLINFO));
	
	return TRUE;  // 除非将焦点设置到控件，否则返回 TRUE
}

void CitnodebookDlg::OnSysCommand(UINT nID, LPARAM lParam)
{
	if ((nID & 0xFFF0) == IDM_ABOUTBOX)
	{
		CAboutDlg dlgAbout;
		dlgAbout.DoModal();
	}
	else
	{
		CDialog::OnSysCommand(nID, lParam);
	}
}

// 如果向对话框添加最小化按钮，则需要下面的代码
//  来绘制该图标。对于使用文档/视图模型的 MFC 应用程序，
//  这将由框架自动完成。

void CitnodebookDlg::OnPaint()
{
	if (IsIconic())
	{
		CPaintDC dc(this); // 用于绘制的设备上下文

		SendMessage(WM_ICONERASEBKGND, reinterpret_cast<WPARAM>(dc.GetSafeHdc()), 0);

		// 使图标在工作区矩形中居中
		int cxIcon = GetSystemMetrics(SM_CXICON);
		int cyIcon = GetSystemMetrics(SM_CYICON);
		CRect rect;
		GetClientRect(&rect);
		int x = (rect.Width() - cxIcon + 1) / 2;
		int y = (rect.Height() - cyIcon + 1) / 2;

		// 绘制图标
		dc.DrawIcon(x, y, m_hIcon);
	}
	else
	{
		CDialog::OnPaint();
	}
}

//当用户拖动最小化窗口时系统调用此函数取得光标
//显示。
HCURSOR CitnodebookDlg::OnQueryDragIcon()
{
	return static_cast<HCURSOR>(m_hIcon);
}

BOOL CitnodebookDlg::OnToolTipText(UINT, NMHDR* pNMHDR, LRESULT* pResult)
{
     ASSERT(pNMHDR->code == TTN_NEEDTEXTA || pNMHDR->code == TTN_NEEDTEXTW);

     // if there is a top level routing frame then let it handle the message
     if (GetRoutingFrame() != NULL) return FALSE;

     // to be thorough we will need to handle UNICODE versions of the message also !!
     TOOLTIPTEXTA* pTTTA = (TOOLTIPTEXTA*)pNMHDR;
     TOOLTIPTEXTW* pTTTW = (TOOLTIPTEXTW*)pNMHDR;
     TCHAR szFullText[512];
     CString strTipText;
     UINT nID = pNMHDR->idFrom;

     if (pNMHDR->code == TTN_NEEDTEXTA && (pTTTA->uFlags & TTF_IDISHWND) ||
         pNMHDR->code == TTN_NEEDTEXTW && (pTTTW->uFlags & TTF_IDISHWND))
     {
          // idFrom is actually the HWND of the tool 
          nID = ::GetDlgCtrlID((HWND)nID);
     }

     if (nID != 0) // will be zero on a separator
     {
		  AfxLoadString(nID, szFullText);
          strTipText=szFullText;

#ifndef _UNICODE
          if (pNMHDR->code == TTN_NEEDTEXTA)
          {
               lstrcpyn(pTTTA->szText, strTipText, sizeof(pTTTA->szText));
          }
          else
          {
               _mbstowcsz(pTTTW->szText, strTipText, sizeof(pTTTW->szText));
          }
#else
          if (pNMHDR->code == TTN_NEEDTEXTA)
          {
               _wcstombsz(pTTTA->szText, strTipText,sizeof(pTTTA->szText));
          }
          else
          {
               lstrcpyn(pTTTW->szText, strTipText, sizeof(pTTTW->szText));
          }
#endif

          *pResult = 0;

          // bring the tooltip window above other popup windows
          ::SetWindowPos(pNMHDR->hwndFrom, HWND_TOP, 0, 0, 0, 0,SWP_NOACTIVATE|
               SWP_NOSIZE|SWP_NOMOVE|SWP_NOOWNERZORDER); return TRUE;
     }
} 
HBRUSH CitnodebookDlg::OnCtlColor(CDC* pDC, CWnd* pWnd, UINT nCtlColor)
{
	HBRUSH hbr = CDialog::OnCtlColor(pDC, pWnd, nCtlColor);

	// TODO:  在此更改 DC 的任何属性
	COLORREF backColor = RGB(199,221,242);
	// TODO:  如果默认的不是所需画笔，则返回另一个画笔

	return CreateSolidBrush(backColor);
	//return hbr;
}

void CitnodebookDlg::OnSize(UINT nType, int cx, int cy)
{
	CDialog::OnSize(nType, cx, cy);
	
	//设置可改变大小的内容
	int iIncrementX = cx - m_iClientWidth;
	int iIncrementY = cy - m_iClientHeight;
	// 最小化时增量为0
	if (nType == SIZE_MINIMIZED)
	{
		iIncrementX = iIncrementY = 0;
	}
	//移动工具栏
	if(m_itbar.m_hWnd)
	{
		CRect toolrect;
		m_itbar.GetWindowRect(&toolrect);
		ScreenToClient(&toolrect);
		toolrect.right+=iIncrementX;
		m_itbar.MoveWindow(toolrect);
	}
	if(m_statusBar.m_hWnd)
	{
		CRect statusrect;
		m_statusBar.GetWindowRect(&statusrect);
		ScreenToClient(&statusrect);
		statusrect.right+=iIncrementX;
		m_statusBar.MoveWindow(statusrect);
	}
	for (int i = 0; i < m_iControlNumber; i++)
	{

		CWnd *pWndCtrl = NULL;
		int iId = m_pControlArray[i].iId;
		int iFlag = m_pControlArray[i].iFlag;
		int iPercent = m_pControlArray[i].iPercent;
		// 无效值
		if ((iPercent < 0) || (iPercent > 100))
			continue;
		// 得到控件指针
		
			pWndCtrl = GetDlgItem(iId);
			if ((NULL != pWndCtrl) && IsWindow(pWndCtrl->GetSafeHwnd()))
			{
				CRect rectCtrl;
				pWndCtrl->GetWindowRect(rectCtrl);
				ScreenToClient(rectCtrl);
				int iLeft = rectCtrl.left;
				int iTop = rectCtrl.top;
				int iWidth = rectCtrl.Width();
				int iHeight = rectCtrl.Height();
				switch (iFlag)
				{
					case MOVEX: // X方向移动
						iLeft += (iIncrementX * iPercent / 100);
						break;
					case MOVEY: // Y方向移动
						iTop += (iIncrementY * iPercent / 100);
						break;
					case MOVEXY: // X方向和Y方向同时移动
						iLeft += (iIncrementX * iPercent / 100);
						iTop += (iIncrementY * iPercent / 100);
						break;
					case ELASTICX: // X方向改变大小
						iWidth += (iIncrementX * iPercent / 100);
						break;
					case ELASTICY: // Y方向改变大小
						iHeight += (iIncrementY * iPercent / 100);
						break;
					case ELASTICXY: // X方向和Y方向同时改变大小
						iWidth += (iIncrementX * iPercent / 100);
						iHeight += (iIncrementY * iPercent / 100);
						break;
					default:
							;
				}
				// 把控件移动到新位置
				pWndCtrl->MoveWindow(iLeft, iTop, iWidth, iHeight);
			}
		
		
	}
	//修改属性页
	if(IsWindow(m_pArticle.m_hWnd))
	{
	CRect rectCtrl=m_proPageRect;
				int iLeft = rectCtrl.left;
				int iTop = rectCtrl.top;
				int iWidth = rectCtrl.Width();
				int iHeight = rectCtrl.Height();
	iWidth += iIncrementX;
	iHeight += iIncrementY;
	m_pArticle.MoveWindow(iLeft,iTop,iWidth,iHeight);
	m_pLocalsearch.MoveWindow(iLeft,iTop,iWidth,iHeight);
	m_pOnlinesearch.MoveWindow(iLeft,iTop,iWidth,iHeight);
	m_proPageRect.right+=iIncrementX;
	m_proPageRect.bottom+=iIncrementY;

	}
	// 把图标移动到对话框右下角
	if (IsWindow(m_wndSizeIcon.GetSafeHwnd()))
		m_wndSizeIcon.MoveWindow(cx - m_bitmap.bmWidth, cy - m_bitmap.bmHeight, m_bitmap.bmWidth, m_bitmap.bmHeight);
	// 记录对话框client区域的大小
	if (nType != SIZE_MINIMIZED)
	{
		m_iClientWidth = cx;
		m_iClientHeight = cy;
	}
	
	// TODO: 在此处添加消息处理程序代码
	
}
void CitnodebookDlg::OnSizing(UINT fwSide, LPRECT pRect)
{

	CDialog::OnSizing(fwSide, pRect);

	// 对话框不能小于初始大小
	int iWidth = pRect->right - pRect->left;
	int iHeight = pRect->bottom - pRect->top;
	if (iWidth <= m_iMinWidth)
		pRect->right=pRect->left + m_iMinWidth;
	if(iHeight <= m_iMinHeight)
		pRect->bottom= pRect->top + m_iMinHeight;

	// TODO: 在此处添加消息处理程序代码
}

BOOL CitnodebookDlg::SetControlProperty(PDLGCTLINFO lp, int nElements)
{
	// 设置控件数组信息
	if (NULL == lp)
		return FALSE;
	if (nElements <= 0)
		return FALSE;
	m_pControlArray = lp;
	m_iControlNumber = nElements;
	return TRUE;
}
void CitnodebookDlg::ShowSizeIcon(BOOL bShow /*=NULL*/)
{
	m_bShowSizeIcon = bShow;
}

void CitnodebookDlg::OnBnClickedButton1()
{

	
	// TODO: 在此添加控件通知处理程序代码
}

void CitnodebookDlg::OnSetFocus(CWnd* pOldWnd)
{
	CDialog::OnSetFocus(pOldWnd);
	
	// TODO: 在此处添加消息处理程序代码
}

void CitnodebookDlg::OnBnClickedArticle()
{
	//切换选项卡
	m_pArticle.ShowWindow(true);
	m_pLocalsearch.ShowWindow(false);
	m_pOnlinesearch.ShowWindow(false);
}

void CitnodebookDlg::OnBnClickedLocalser()
{
	// TODO: 在此添加控件通知处理程序代码
	//切换选项卡
	m_pArticle.ShowWindow(false);
	m_pLocalsearch.ShowWindow(true);
	m_pOnlinesearch.ShowWindow(false);
}

void CitnodebookDlg::OnBnClickedOnlineser()
{
	// TODO: 在此添加控件通知处理程序代码
	//切换选项卡
	m_pArticle.ShowWindow(false);
	m_pLocalsearch.ShowWindow(false);
	m_pOnlinesearch.ShowWindow(true);
}

void CitnodebookDlg::OnNewfile()
{
	m_pArticle.createNewpage();
	// TODO: 在此添加命令处理程序代码
}
