#pragma once
#include "afxcmn.h"
#include "CustomTabCtrl.h"
#include "richedits.h"


// Carticles 对话框

class Carticles : public CDialog
{
	DECLARE_DYNAMIC(Carticles)

public:
	Carticles(CWnd* pParent = NULL);   // 标准构造函数
	virtual ~Carticles();

// 对话框数据
	enum { IDD = P_ARTICLE };
	CRect m_oldrect;

	

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV 支持
	
	// Notify messages from CCustomTabCtrl
	afx_msg void OnLButtonClickedTab(NMHDR* pNMHDR, LRESULT* pResult) ;
	afx_msg void OnSelchangeTab(NMHDR* pNMHDR, LRESULT* pResult);
	
	DECLARE_MESSAGE_MAP()
public:
	afx_msg void OnSize(UINT nType, int cx, int cy);
	virtual BOOL OnInitDialog();
	// 选项卡变量
	//选项卡现在最大值
	int m_nowMaxPage;
	
	//richedit属性页数组
	CArray <Crichedits,Crichedits&> richedits;
	Crichedits richtest;
	CList <Crichedits,Crichedits&> richeditss;
	
	//选项卡实例
	CCustomTabCtrl m_Articles;
	
	//当前显示页面
	int m_nowPage;
	//richedit的区域
	CRect richRect;
	afx_msg HBRUSH OnCtlColor(CDC* pDC, CWnd* pWnd, UINT nCtlColor);
protected:
	virtual BOOL OnNotify(WPARAM wParam, LPARAM lParam, LRESULT* pResult);
public:
	afx_msg void OnNewfile();
	// //添加新页面
	int createNewpage();
};
