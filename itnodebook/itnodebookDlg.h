// itnodebookDlg.h : 头文件
//
#include "articles.h"
#include "localsearch.h"
#include "onlinesearch.h"
#include "BtnST.h"
#pragma once


// CitnodebookDlg 对话框
class CitnodebookDlg : public CDialog
{
// 构造
public:
	CitnodebookDlg(CWnd* pParent = NULL);	// 标准构造函数
	
// 对话框数据
	enum { IDD = IDD_ITNODEBOOK_DIALOG };
	
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);	// DDX/DDV 支持
	
	//属性页大小
	CRect m_proPageRect;
	//添加工具栏
	CToolBar m_itbar;
	int m_toolBarHeight;
	//添加状态栏
	CStatusBarCtrl m_statusBar;
	//添加文章属性页
	Carticles m_pArticle;
	//添加本地搜索
	Clocalsearch m_pLocalsearch;
	//添加在线搜索
	Conlinesearch m_pOnlinesearch;
	
	CButtonST m_bArticle;
	CButtonST m_bOnline;
	CButtonST m_bLocal;

	BOOL m_bFirstTime;
// 实现
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
	int m_iClientWidth; // 对话框client区域的宽度
	int m_iClientHeight; // 对话框client区域的高度
	int m_iMinWidth; // 对话框的最小宽
	int m_iMinHeight; // 对话框的最小高度
	PDLGCTLINFO m_pControlArray; // 控件信息数组指针
	int m_iControlNumber; // 设置控件信息的控件个数
	BOOL m_bShowSizeIcon; // 是否显示表示可改变大小的图标
	CStatic m_wndSizeIcon; // 放图标的静态控件
	// 保存图标的bitmap
	CBitmap m_bmpSizeIcon;
	BITMAP m_bitmap;

protected:
	HICON m_hIcon;
	
	// 生成的消息映射函数
	virtual BOOL OnInitDialog();
	afx_msg void OnSysCommand(UINT nID, LPARAM lParam);
	afx_msg void OnPaint();
	afx_msg HCURSOR OnQueryDragIcon();
	afx_msg BOOL OnToolTipText(UINT nID, NMHDR* pNMHDR, LRESULT* pResult);//工具提示信息消息
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
