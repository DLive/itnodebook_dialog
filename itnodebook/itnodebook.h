// itnodebook.h : PROJECT_NAME Ӧ�ó������ͷ�ļ�
//

#pragma once

#ifndef __AFXWIN_H__
	#error "�ڰ������ļ�֮ǰ������stdafx.h�������� PCH �ļ�"
#endif

#include "resource.h"		// ������


// CitnodebookApp:
// �йش����ʵ�֣������ itnodebook.cpp
//

class CitnodebookApp : public CWinApp
{
public:
	CitnodebookApp();

// ��д
	public:
	virtual BOOL InitInstance();

// ʵ��

	DECLARE_MESSAGE_MAP()
};

extern CitnodebookApp theApp;