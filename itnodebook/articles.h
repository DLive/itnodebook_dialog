#pragma once
#include "afxcmn.h"
#include "CustomTabCtrl.h"
#include "richedits.h"


// Carticles �Ի���

class Carticles : public CDialog
{
	DECLARE_DYNAMIC(Carticles)

public:
	Carticles(CWnd* pParent = NULL);   // ��׼���캯��
	virtual ~Carticles();

// �Ի�������
	enum { IDD = P_ARTICLE };
	CRect m_oldrect;

	

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV ֧��
	
	// Notify messages from CCustomTabCtrl
	afx_msg void OnLButtonClickedTab(NMHDR* pNMHDR, LRESULT* pResult) ;
	afx_msg void OnSelchangeTab(NMHDR* pNMHDR, LRESULT* pResult);
	
	DECLARE_MESSAGE_MAP()
public:
	afx_msg void OnSize(UINT nType, int cx, int cy);
	virtual BOOL OnInitDialog();
	// ѡ�����
	//ѡ��������ֵ
	int m_nowMaxPage;
	
	//richedit����ҳ����
	CArray <Crichedits,Crichedits&> richedits;
	Crichedits richtest;
	CList <Crichedits,Crichedits&> richeditss;
	
	//ѡ�ʵ��
	CCustomTabCtrl m_Articles;
	
	//��ǰ��ʾҳ��
	int m_nowPage;
	//richedit������
	CRect richRect;
	afx_msg HBRUSH OnCtlColor(CDC* pDC, CWnd* pWnd, UINT nCtlColor);
protected:
	virtual BOOL OnNotify(WPARAM wParam, LPARAM lParam, LRESULT* pResult);
public:
	afx_msg void OnNewfile();
	// //�����ҳ��
	int createNewpage();
};
