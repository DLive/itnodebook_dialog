// itnodebookDlg.cpp : ʵ���ļ�
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


// ����Ӧ�ó��򡰹��ڡ��˵���� CAboutDlg �Ի���

class CAboutDlg : public CDialog
{
public:
	CAboutDlg();

// �Ի�������
	enum { IDD = IDD_ABOUTBOX };

	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV ֧��

// ʵ��
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


// CitnodebookDlg �Ի���




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
	ON_NOTIFY_EX_RANGE(TTN_NEEDTEXTW, 0, 0xFFFF, OnToolTipText)//��������ʾ��Ϣ
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


// CitnodebookDlg ��Ϣ�������

BOOL CitnodebookDlg::OnInitDialog()
{
	CDialog::OnInitDialog();

	// ��������...���˵�����ӵ�ϵͳ�˵��С�

	// IDM_ABOUTBOX ������ϵͳ���Χ�ڡ�
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

	// ���ô˶Ի����ͼ�ꡣ��Ӧ�ó��������ڲ��ǶԻ���ʱ����ܽ��Զ�
	//  ִ�д˲���
	SetIcon(m_hIcon, TRUE);			// ���ô�ͼ��
	SetIcon(m_hIcon, FALSE);		// ����Сͼ��

	// TODO: �ڴ���Ӷ���ĳ�ʼ������
	
	//���ز˵�
	CMenu menu;
	menu.LoadMenuW(IDR_MENU1);
	SetMenu(&menu);
	DrawMenuBar();
	
	//��ӹ�����
	if(!m_itbar.CreateEx(this,TBSTYLE_FLAT,WS_CHILD|WS_VISIBLE|CBRS_ALIGN_TOP|CBRS_GRIPPER|CBRS_TOOLTIPS|CBRS_FLYBY)||!m_itbar.LoadToolBar(IDR_TOOLBAR1))
	{
		TRACE0("��ӹ�����ʧ��");
		return FALSE;
	}
	m_itbar.ShowWindow(SW_SHOW);
	//RepositionBars(AFX_IDW_CONTROLBAR_FIRST,AFX_IDW_CONTROLBAR_LAST,0);
	
	/*if(!m_itbar.Create(this)||!m_itbar.LoadToolBar(IDR_TOOLBAR1))
	{
		TRACE0("��ӹ�����ʧ��");
		EndDialog(IDCANCEL);
	}
	
	m_itbar.ShowWindow(SW_SHOW);*/
	CRect rcClientStart;
	CRect rcClientNow;
	GetClientRect(rcClientStart);
	RepositionBars(AFX_IDW_CONTROLBAR_FIRST,AFX_IDW_CONTROLBAR_LAST,0, reposQuery, rcClientNow);
	//�ڶԻ������ƶ��ؼ���ȷ���������ڹ������Ķ��������ռ�õĿռ�
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
	//���ݿ�����ռ�õĿռ��������ӶԻ��򴰿ڵĳߴ硣
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
	m_statusBar.SetText(_T("����һ"),1,0);
	m_statusBar.SetText(_T("������"),1,0);
	m_statusBar.SetText(_T("������"),2,0);

	//�����������ҳ
	m_pArticle.Create(P_ARTICLE,this);
	CRect rs;
	GetClientRect(&rs);
	//�����ӶԻ����ڸ������е�λ��
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
	
	//���ÿɸı�Ի����С
	ModifyStyle(0, WS_SIZEBOX);
	// �ԶԻ���ĳ�ʼ��С��Ϊ�Ի���Ŀ�Ⱥ͸߶ȵ���Сֵ
	CRect rectDlg;
	GetWindowRect(rectDlg);
	m_iMinWidth = rectDlg.Width();
	m_iMinHeight = rectDlg.Height();//�����С�߶�
	// �õ��Ի���client����Ĵ�С
	CRect rectClient;
	GetClientRect(rectClient);
	m_iClientWidth = rectClient.Width();//�Ի���client����Ŀ��
	m_iClientHeight = rectClient.Height();//�Ի���client����ĸ߶�
	// Loadͼ��
	m_bmpSizeIcon.LoadOEMBitmap(OBM_SIZE);//�������ͼ��
	m_bmpSizeIcon.GetBitmap(&m_bitmap);//
	// ������ʾͼ��ľ�̬�ؼ������ڶԻ������½�
	m_wndSizeIcon.Create(NULL, WS_CHILD | WS_VISIBLE | SS_BITMAP, CRect(0, 0, m_bitmap.bmWidth, m_bitmap.bmHeight), this, 0);
	m_wndSizeIcon.SetBitmap(m_bmpSizeIcon);
	m_wndSizeIcon.MoveWindow(m_iClientWidth - m_bitmap.bmWidth, m_iClientHeight - m_bitmap.bmHeight, m_bitmap.bmWidth, m_bitmap.bmHeight);
	// ��ʾͼ��
	m_wndSizeIcon.ShowWindow(m_bShowSizeIcon);
	
	//���öԻ���ɸı��С����
	
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

// ���ÿؼ���Ϣ-�ı䴰�ڴ�Сʱ�á�
	SetControlProperty(dcMenuGroup, sizeof(dcMenuGroup)/sizeof(DLGCTLINFO));
	
	return TRUE;  // ���ǽ��������õ��ؼ������򷵻� TRUE
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

// �����Ի��������С����ť������Ҫ����Ĵ���
//  �����Ƹ�ͼ�ꡣ����ʹ���ĵ�/��ͼģ�͵� MFC Ӧ�ó���
//  �⽫�ɿ���Զ���ɡ�

void CitnodebookDlg::OnPaint()
{
	if (IsIconic())
	{
		CPaintDC dc(this); // ���ڻ��Ƶ��豸������

		SendMessage(WM_ICONERASEBKGND, reinterpret_cast<WPARAM>(dc.GetSafeHdc()), 0);

		// ʹͼ���ڹ����������о���
		int cxIcon = GetSystemMetrics(SM_CXICON);
		int cyIcon = GetSystemMetrics(SM_CYICON);
		CRect rect;
		GetClientRect(&rect);
		int x = (rect.Width() - cxIcon + 1) / 2;
		int y = (rect.Height() - cyIcon + 1) / 2;

		// ����ͼ��
		dc.DrawIcon(x, y, m_hIcon);
	}
	else
	{
		CDialog::OnPaint();
	}
}

//���û��϶���С������ʱϵͳ���ô˺���ȡ�ù��
//��ʾ��
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

	// TODO:  �ڴ˸��� DC ���κ�����
	COLORREF backColor = RGB(199,221,242);
	// TODO:  ���Ĭ�ϵĲ������軭�ʣ��򷵻���һ������

	return CreateSolidBrush(backColor);
	//return hbr;
}

void CitnodebookDlg::OnSize(UINT nType, int cx, int cy)
{
	CDialog::OnSize(nType, cx, cy);
	
	//���ÿɸı��С������
	int iIncrementX = cx - m_iClientWidth;
	int iIncrementY = cy - m_iClientHeight;
	// ��С��ʱ����Ϊ0
	if (nType == SIZE_MINIMIZED)
	{
		iIncrementX = iIncrementY = 0;
	}
	//�ƶ�������
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
		// ��Чֵ
		if ((iPercent < 0) || (iPercent > 100))
			continue;
		// �õ��ؼ�ָ��
		
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
					case MOVEX: // X�����ƶ�
						iLeft += (iIncrementX * iPercent / 100);
						break;
					case MOVEY: // Y�����ƶ�
						iTop += (iIncrementY * iPercent / 100);
						break;
					case MOVEXY: // X�����Y����ͬʱ�ƶ�
						iLeft += (iIncrementX * iPercent / 100);
						iTop += (iIncrementY * iPercent / 100);
						break;
					case ELASTICX: // X����ı��С
						iWidth += (iIncrementX * iPercent / 100);
						break;
					case ELASTICY: // Y����ı��С
						iHeight += (iIncrementY * iPercent / 100);
						break;
					case ELASTICXY: // X�����Y����ͬʱ�ı��С
						iWidth += (iIncrementX * iPercent / 100);
						iHeight += (iIncrementY * iPercent / 100);
						break;
					default:
							;
				}
				// �ѿؼ��ƶ�����λ��
				pWndCtrl->MoveWindow(iLeft, iTop, iWidth, iHeight);
			}
		
		
	}
	//�޸�����ҳ
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
	// ��ͼ���ƶ����Ի������½�
	if (IsWindow(m_wndSizeIcon.GetSafeHwnd()))
		m_wndSizeIcon.MoveWindow(cx - m_bitmap.bmWidth, cy - m_bitmap.bmHeight, m_bitmap.bmWidth, m_bitmap.bmHeight);
	// ��¼�Ի���client����Ĵ�С
	if (nType != SIZE_MINIMIZED)
	{
		m_iClientWidth = cx;
		m_iClientHeight = cy;
	}
	
	// TODO: �ڴ˴������Ϣ����������
	
}
void CitnodebookDlg::OnSizing(UINT fwSide, LPRECT pRect)
{

	CDialog::OnSizing(fwSide, pRect);

	// �Ի�����С�ڳ�ʼ��С
	int iWidth = pRect->right - pRect->left;
	int iHeight = pRect->bottom - pRect->top;
	if (iWidth <= m_iMinWidth)
		pRect->right=pRect->left + m_iMinWidth;
	if(iHeight <= m_iMinHeight)
		pRect->bottom= pRect->top + m_iMinHeight;

	// TODO: �ڴ˴������Ϣ����������
}

BOOL CitnodebookDlg::SetControlProperty(PDLGCTLINFO lp, int nElements)
{
	// ���ÿؼ�������Ϣ
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

	
	// TODO: �ڴ���ӿؼ�֪ͨ����������
}

void CitnodebookDlg::OnSetFocus(CWnd* pOldWnd)
{
	CDialog::OnSetFocus(pOldWnd);
	
	// TODO: �ڴ˴������Ϣ����������
}

void CitnodebookDlg::OnBnClickedArticle()
{
	//�л�ѡ�
	m_pArticle.ShowWindow(true);
	m_pLocalsearch.ShowWindow(false);
	m_pOnlinesearch.ShowWindow(false);
}

void CitnodebookDlg::OnBnClickedLocalser()
{
	// TODO: �ڴ���ӿؼ�֪ͨ����������
	//�л�ѡ�
	m_pArticle.ShowWindow(false);
	m_pLocalsearch.ShowWindow(true);
	m_pOnlinesearch.ShowWindow(false);
}

void CitnodebookDlg::OnBnClickedOnlineser()
{
	// TODO: �ڴ���ӿؼ�֪ͨ����������
	//�л�ѡ�
	m_pArticle.ShowWindow(false);
	m_pLocalsearch.ShowWindow(false);
	m_pOnlinesearch.ShowWindow(true);
}

void CitnodebookDlg::OnNewfile()
{
	m_pArticle.createNewpage();
	// TODO: �ڴ���������������
}
