
// CalculatorShinSW.h : PROJECT_NAME ���� ���α׷��� ���� �� ��� �����Դϴ�.
//

#pragma once

#ifndef __AFXWIN_H__
	#error "PCH�� ���� �� ������ �����ϱ� ���� 'stdafx.h'�� �����մϴ�."
#endif

#include "resource.h"		// �� ��ȣ�Դϴ�.


// CCalculatorShinSWApp:
// �� Ŭ������ ������ ���ؼ��� CalculatorShinSW.cpp�� �����Ͻʽÿ�.
//

class CCalculatorShinSWApp : public CWinApp
{
public:
	CCalculatorShinSWApp();

// �������Դϴ�.
public:
	virtual BOOL InitInstance();

// �����Դϴ�.

	DECLARE_MESSAGE_MAP()
};

extern CCalculatorShinSWApp theApp;