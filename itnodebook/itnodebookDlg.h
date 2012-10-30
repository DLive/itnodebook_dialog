// itnodebookDlg.h : ͷ�ļ�
//
#include "articles.h"
#include "localsearch.h"
#include "onlinesearch.h"
#include "BtnST.h"
#pragma once


// CitnodebookDlg �Ի���
class CitnodebookDlg : public CDialog
{
// ����
public:
	CitnodebookDlg(CWnd* pParent = NULL);	// ��׼���캯��
	
// �Ի�������
	enum { IDD = IDD_ITNODEBOOK_DIALOG };
	
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);	// DDX/DDV ֧��
	
	//����ҳ��С
	CRect m_proPageRect;
	//��ӹ�����
	CToolBar m_itbar;
	int m_toolBarHeight;
	//���״̬��
	CStatusBarCtrl m_statusBar;
	//�����������ҳ
	Carticles m_pArticle;
	//��ӱ�������
	Clocalsearch m_pLocalsearch;
	//�����������
	Conlinesearch m_pOnlinesearch;
	
	CButtonST m_bArticle;
	CButtonST m_bOnline;
	CButtonST m_bLocal;

	BOOL m_bFirstTime;
// ʵ��
public:
	typedef struct _dlgControlTag
	{
		int iId;
		int iFlag;
		int iPercent;
	}DLGCTLINFO, *PDLGCTLINFO;
	enum
	{
		MOVEX = 0,
		MOVEY,
		MOVEXY,
		ELASTICX,
		ELASTICY,
		ELASTICXY
	};

	BOOL SetControlProperty(PDLGCTLINFO lp, int nElements);
	void ShowSizeIcon(BOOL bShow = TRUE);
private:
	int m_iClientWidth; // �Ի���client����Ŀ��
	int m_iClientHeight; // �Ի���client����ĸ߶�
	int m_iMinWidth; // �Ի������С��
	int m_iMinHeight; // �Ի������С�߶�
	PDLGCTLINFO m_pControlArray; // �ؼ���Ϣ����ָ��
	int m_iControlNumber; // ���ÿؼ���Ϣ�Ŀؼ�����
	BOOL m_bShowSizeIcon; // �Ƿ���ʾ��ʾ�ɸı��С��ͼ��
	CStatic m_wndSizeIcon; // ��ͼ��ľ�̬�ؼ�
	// ����ͼ���bitmap
	CBitmap m_bmpSizeIcon;
	BITMAP m_bitmap;

protected:
	HICON m_hIcon;
	
	// ���ɵ���Ϣӳ�亯��
	virtual BOOL OnInitDialog();
	afx_msg void OnSysCommand(UINT nID, LPARAM lParam);
	afx_msg void OnPaint();
	afx_msg HCURSOR OnQueryDragIcon();
	afx_msg BOOL OnToolTipText(UINT nID, NMHDR* pNMHDR, LRESULT* pResult);//������ʾ��Ϣ��Ϣ
	DECLARE_MESSAGE_MAP()
public:
	afx_msg HBRUSH OnCtlColor(CDC* pDC, CWnd* pWnd, UINT nCtlColor);
	afx_msg void OnSize(UINT nType, int cx, int cy);
	afx_msg void OnSizing(UINT fwSide, LPRECT pRect);
	afx_msg void OnBnClickedButton1();
	afx_msg void OnSetFocus(CWnd* pOldWnd);
	afx_msg void OnBnClickedArticle();
	afx_msg void OnBnClickedLocalser();
	afx_msg void OnBnClickedOnlineser();
	afx_msg void OnNewfile();
};
