
// CalculatorShinSWDlg.h : ��� ����
//

#pragma once
#include "afxwin.h"
#include "string"
#include "SimpleCalculatorModule.h"

// CCalculatorShinSWDlg ��ȭ ����
class CCalculatorShinSWDlg : public CDialogEx
{
// �����Դϴ�.
public:
	CCalculatorShinSWDlg(CWnd* pParent = NULL);	// ǥ�� �������Դϴ�.


// ��ȭ ���� �������Դϴ�.
	enum { IDD = IDD_CALCULATORSHINSW_DIALOG };

	protected:
	virtual void DoDataExchange(CDataExchange* pDX);	// DDX/DDV �����Դϴ�.


// �����Դϴ�.
protected:
	HICON m_hIcon;

	// ������ �޽��� �� �Լ�
	virtual BOOL OnInitDialog();
	afx_msg void OnSysCommand(UINT nID, LPARAM lParam);
	afx_msg void OnPaint();
	afx_msg HCURSOR OnQueryDragIcon();
	DECLARE_MESSAGE_MAP()
public:

	CEdit TotalLine;
	CEdit Sentence;
	afx_msg void OnBnClickedButton1();
	afx_msg void OnBnClickedButton2();
	afx_msg void OnBnClickedButton3();
	afx_msg void OnBnClickedButton4();
	afx_msg void OnBnClickedButton5();
	afx_msg void OnBnClickedButton6();
	afx_msg void OnBnClickedButton7();
	afx_msg void OnBnClickedButton8();
	afx_msg void OnBnClickedButton9();
	afx_msg void OnBnClickedButton10();
	afx_msg void OnBnClickedAdd();
	afx_msg void OnBnClickedSub();
	afx_msg void OnBnClickedMul();
	afx_msg void OnBnClickedMod();
	
	SimpleCalculatorModule C;
	


	afx_msg void OnBnClickedEqual();
	afx_msg void OnEnChangeCurrent();
	afx_msg void OnEnChangeTotal();
	afx_msg void OnBnClickedAc();
	afx_msg void OnBnClickedPdiag();
	afx_msg void OnBnClickedChattingDialog();
};
