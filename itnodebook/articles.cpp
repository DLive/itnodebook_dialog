// articles.cpp : ʵ���ļ�
//

#include "stdafx.h"
#include "itnodebook.h"
#include "articles.h"


// Carticles �Ի���

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
	//ѡ�����Ϣ
	ON_NOTIFY(CTCN_CLICK, T_ARTICLES, OnLButtonClickedTab)
	ON_NOTIFY(CTCN_SELCHANGE, T_ARTICLES, OnSelchangeTab)

	ON_COMMAND(IDM_NEWFILE, &Carticles::OnNewfile)
END_MESSAGE_MAP()


// Carticles ��Ϣ�������

void Carticles::OnSize(UINT nType, int cx, int cy)
{
	CWnd *pWnd;
	pWnd=GetDlgItem(T_ARTICLES); //��ȡ�ؼ���� 
	CRect prect;
	//CWnd *ppWnd;
	//*ppWnd->GetDlgItem(P_ARTICLE);
	//*ppWnd->GetWindowRect(&prect);
	ScreenToClient(&prect);
	if(pWnd)//�ж��Ƿ�Ϊ�գ���Ϊ�Ի��򴴽�ʱ����ô˺���������ʱ�ؼ���δ���� 
	{ 
	 CRect rect; //��ȡ�ؼ��仯ǰ��С 
	 pWnd->GetWindowRect(&rect); 
	 ScreenToClient(&rect);//���ؼ���Сת��Ϊ�ڶԻ����е��������� 
	 //��cx/m_rect.Width()Ϊ�Ի����ں���ı仯����
	 rect.right=rect.right+(cx-m_oldrect.Width());
	 //rect.bottom=rect.bottom+(cy-m_oldrect.Height());
	 pWnd->MoveWindow(rect);//���ÿؼ���С 
	}
	
	pWnd=GetDlgItem(IDC_CONTAINER);//���ݴ�С
	if(pWnd)//�ж��Ƿ�Ϊ�գ���Ϊ�Ի��򴴽�ʱ����ô˺���������ʱ�ؼ���δ���� 
	{ 
	 CRect rect; //��ȡ�ؼ��仯ǰ��С 
	 pWnd->GetWindowRect(&rect); 
	 ScreenToClient(&rect);//���ؼ���Сת��Ϊ�ڶԻ����е��������� 
	 //��cx/m_rect.Width()Ϊ�Ի����ں���ı仯����
	 rect.left=rect.left;//   *cx/m_oldrect.Width();/**//////�����ؼ���С 
	 rect.right=rect.right+(cx-m_oldrect.Width());
	 //rect.top=rect.top*cy/m_oldrect.Height();
	 rect.bottom=rect.bottom+(cy-m_oldrect.Height());
	 richRect=rect;
	 pWnd->MoveWindow(rect);//���ÿؼ���С 
	}
	GetClientRect(&m_oldrect);

	//GetClientRect(&rect);//���仯��ĶԻ����С��Ϊ�ɴ�
	CDialog::OnSize(nType, cx, cy);

	// TODO: �ڴ˴������Ϣ����������
}

BOOL Carticles::OnInitDialog()
{
	CDialog::OnInitDialog();
	GetClientRect(&m_oldrect);
	// TODO:  �ڴ���Ӷ���ĳ�ʼ��
	//m_Articles.InsertItem(0,_T("��ʼҳ"));
	
	
	//m_Articles.Create(WS_VISIBLE|WS_CHILD,CRect(0,0,100,20),this,1);
	
	m_Articles.ModifyStyle(CTCS_RIGHT,CTCS_TOP|CTCS_CLOSEBUTTON|CTCS_BUTTONSAFTER,0);
	m_Articles.SetDragCursors(AfxGetApp()->LoadCursor(IDC_CURSORMOVE),AfxGetApp()->LoadCursor(IDC_CURSORCOPY));
	m_Articles.InsertItem(0,_T("SS_BLACKRECT"));
	m_Articles.SetItemData(0,SS_BLACKRECT);
	m_nowMaxPage=1;
	m_Articles.SetCurSel(0);
	
	return TRUE;  // return TRUE unless you set the focus to a control
	// �쳣: OCX ����ҳӦ���� FALSE
}

HBRUSH Carticles::OnCtlColor(CDC* pDC, CWnd* pWnd, UINT nCtlColor)
{
	HBRUSH hbr = CDialog::OnCtlColor(pDC, pWnd, nCtlColor);

	// TODO:  �ڴ˸��� DC ���κ�����
	COLORREF backColor = RGB(199,221,242);

	return CreateSolidBrush(backColor);
	// TODO:  ���Ĭ�ϵĲ������軭�ʣ��򷵻���һ������
	//return hbr;
}

BOOL Carticles::OnNotify(WPARAM wParam, LPARAM lParam, LRESULT* pResult)
{
	// TODO: �ڴ����ר�ô����/����û���

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

	// TODO: �ڴ���������������
	
}

// //�����ҳ��
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
