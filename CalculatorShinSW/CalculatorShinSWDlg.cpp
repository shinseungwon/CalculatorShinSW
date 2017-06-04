
// CalculatorShinSWDlg.cpp : 구현 파일
//

#include "stdafx.h"
#include "CalculatorShinSW.h"
#include "CalculatorShinSWDlg.h"
#include "afxdialogex.h"
#include "string"
#include "SimpleCalculatorModule.h"
#include "ProgrammerDiag.h"
#include "ChattingDialog.h"
#ifdef _DEBUG
#define new DEBUG_NEW
#endif

using namespace std;



// 응용 프로그램 정보에 사용되는 CAboutDlg 대화 상자입니다.

class CAboutDlg : public CDialogEx
{
public:
	CAboutDlg();

	

// 대화 상자 데이터입니다.
	enum { IDD = IDD_ABOUTBOX };


	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV 지원입니다.

// 구현입니다.
protected:
	DECLARE_MESSAGE_MAP()
};

CAboutDlg::CAboutDlg() : CDialogEx(CAboutDlg::IDD)
{
}

void CAboutDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
}

BEGIN_MESSAGE_MAP(CAboutDlg, CDialogEx)
END_MESSAGE_MAP()


// CCalculatorShinSWDlg 대화 상자



CCalculatorShinSWDlg::CCalculatorShinSWDlg(CWnd* pParent /*=NULL*/)
	: CDialogEx(CCalculatorShinSWDlg::IDD, pParent)
{
	m_hIcon = AfxGetApp()->LoadIcon(IDR_MAINFRAME);
	
}

void CCalculatorShinSWDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
	DDX_Control(pDX, IDC_TOTAL, TotalLine);
	DDX_Control(pDX, IDC_CURRENT, Sentence);
}

BEGIN_MESSAGE_MAP(CCalculatorShinSWDlg, CDialogEx)
	ON_WM_SYSCOMMAND()
	ON_WM_PAINT()
	ON_WM_QUERYDRAGICON()

	ON_BN_CLICKED(IDC_BUTTON1, &CCalculatorShinSWDlg::OnBnClickedButton1)
	ON_BN_CLICKED(IDC_BUTTON2, &CCalculatorShinSWDlg::OnBnClickedButton2)
	ON_BN_CLICKED(IDC_BUTTON3, &CCalculatorShinSWDlg::OnBnClickedButton3)
	ON_BN_CLICKED(IDC_BUTTON4, &CCalculatorShinSWDlg::OnBnClickedButton4)
	ON_BN_CLICKED(IDC_BUTTON5, &CCalculatorShinSWDlg::OnBnClickedButton5)
	ON_BN_CLICKED(IDC_BUTTON6, &CCalculatorShinSWDlg::OnBnClickedButton6)
	ON_BN_CLICKED(IDC_BUTTON7, &CCalculatorShinSWDlg::OnBnClickedButton7)
	ON_BN_CLICKED(IDC_BUTTON8, &CCalculatorShinSWDlg::OnBnClickedButton8)
	ON_BN_CLICKED(IDC_BUTTON9, &CCalculatorShinSWDlg::OnBnClickedButton9)
	ON_BN_CLICKED(IDC_BUTTON10, &CCalculatorShinSWDlg::OnBnClickedButton10)
	ON_BN_CLICKED(IDC_ADD, &CCalculatorShinSWDlg::OnBnClickedAdd)
	ON_BN_CLICKED(IDC_SUB, &CCalculatorShinSWDlg::OnBnClickedSub)
	ON_BN_CLICKED(IDC_MUL, &CCalculatorShinSWDlg::OnBnClickedMul)
	ON_BN_CLICKED(IDC_MOD, &CCalculatorShinSWDlg::OnBnClickedMod)
	ON_BN_CLICKED(IDC_EQUAL, &CCalculatorShinSWDlg::OnBnClickedEqual)
	ON_BN_CLICKED(IDC_AC, &CCalculatorShinSWDlg::OnBnClickedAc)
	ON_BN_CLICKED(IDC_PDIAG, &CCalculatorShinSWDlg::OnBnClickedPdiag)
	ON_BN_CLICKED(IDC_CHATTING_DIALOG, &CCalculatorShinSWDlg::OnBnClickedChattingDialog)
END_MESSAGE_MAP()


// CCalculatorShinSWDlg 메시지 처리기

BOOL CCalculatorShinSWDlg::OnInitDialog()
{
	CDialogEx::OnInitDialog();

	// 시스템 메뉴에 "정보..." 메뉴 항목을 추가합니다.

	// IDM_ABOUTBOX는 시스템 명령 범위에 있어야 합니다.
	ASSERT((IDM_ABOUTBOX & 0xFFF0) == IDM_ABOUTBOX);
	ASSERT(IDM_ABOUTBOX < 0xF000);

	CMenu* pSysMenu = GetSystemMenu(FALSE);
	if (pSysMenu != NULL)
	{
		BOOL bNameValid;
		CString strAboutMenu;
		bNameValid = strAboutMenu.LoadString(IDS_ABOUTBOX);
		ASSERT(bNameValid);
		if (!strAboutMenu.IsEmpty())
		{
			pSysMenu->AppendMenu(MF_SEPARATOR);
			pSysMenu->AppendMenu(MF_STRING, IDM_ABOUTBOX, strAboutMenu);
		}
	}

	// 이 대화 상자의 아이콘을 설정합니다. 응용 프로그램의 주 창이 대화 상자가 아닐 경우에는
	//  프레임워크가 이 작업을 자동으로 수행합니다.
	SetIcon(m_hIcon, TRUE);			// 큰 아이콘을 설정합니다.
	SetIcon(m_hIcon, FALSE);		// 작은 아이콘을 설정합니다.

	// TODO: 여기에 추가 초기화 작업을 추가합니다.

	return TRUE;  // 포커스를 컨트롤에 설정하지 않으면 TRUE를 반환합니다.
}

void CCalculatorShinSWDlg::OnSysCommand(UINT nID, LPARAM lParam)
{
	if ((nID & 0xFFF0) == IDM_ABOUTBOX)
	{
		CAboutDlg dlgAbout;
		dlgAbout.DoModal();
	}
	else
	{
		CDialogEx::OnSysCommand(nID, lParam);
	}
}

// 대화 상자에 최소화 단추를 추가할 경우 아이콘을 그리려면
//  아래 코드가 필요합니다. 문서/뷰 모델을 사용하는 MFC 응용 프로그램의 경우에는
//  프레임워크에서 이 작업을 자동으로 수행합니다.

void CCalculatorShinSWDlg::OnPaint()
{
	if (IsIconic())
	{
		CPaintDC dc(this); // 그리기를 위한 디바이스 컨텍스트입니다.

		SendMessage(WM_ICONERASEBKGND, reinterpret_cast<WPARAM>(dc.GetSafeHdc()), 0);

		// 클라이언트 사각형에서 아이콘을 가운데에 맞춥니다.
		int cxIcon = GetSystemMetrics(SM_CXICON);
		int cyIcon = GetSystemMetrics(SM_CYICON);
		CRect rect;
		GetClientRect(&rect);
		int x = (rect.Width() - cxIcon + 1) / 2;
		int y = (rect.Height() - cyIcon + 1) / 2;

		// 아이콘을 그립니다.
		dc.DrawIcon(x, y, m_hIcon);
	}
	else
	{
		CDialogEx::OnPaint();
	}
}

// 사용자가 최소화된 창을 끄는 동안에 커서가 표시되도록 시스템에서
//  이 함수를 호출합니다.
HCURSOR CCalculatorShinSWDlg::OnQueryDragIcon()
{
	return static_cast<HCURSOR>(m_hIcon);
}






void CCalculatorShinSWDlg::OnBnClickedButton1()
{
	// TODO: 여기에 컨트롤 알림 처리기 코드를 추가합니다.
	//MessageBox(NULL,_T("Test"),0);
	//TotalLine.SetWindowTextW(TEXT("Test"));
	CString Total;
	TotalLine.GetWindowTextW(Total);
	Total+="1";
	TotalLine.SetWindowTextW(Total);
			
}


void CCalculatorShinSWDlg::OnBnClickedButton2()
{
	// TODO: 여기에 컨트롤 알림 처리기 코드를 추가합니다.
	CString Total;
	TotalLine.GetWindowTextW(Total);
	Total+="2";
	TotalLine.SetWindowTextW(Total);
}


void CCalculatorShinSWDlg::OnBnClickedButton3()
{
	// TODO: 여기에 컨트롤 알림 처리기 코드를 추가합니다.
		CString Total;
	TotalLine.GetWindowTextW(Total);
	Total+="3";
	TotalLine.SetWindowTextW(Total);
}


void CCalculatorShinSWDlg::OnBnClickedButton4()
{
	// TODO: 여기에 컨트롤 알림 처리기 코드를 추가합니다.
		CString Total;
	TotalLine.GetWindowTextW(Total);
	Total+="4";
	TotalLine.SetWindowTextW(Total);
}


void CCalculatorShinSWDlg::OnBnClickedButton5()
{
	// TODO: 여기에 컨트롤 알림 처리기 코드를 추가합니다.
		CString Total;
	TotalLine.GetWindowTextW(Total);
	Total+="5";
	TotalLine.SetWindowTextW(Total);
}


void CCalculatorShinSWDlg::OnBnClickedButton6()
{
	// TODO: 여기에 컨트롤 알림 처리기 코드를 추가합니다.
		CString Total;
	TotalLine.GetWindowTextW(Total);
	Total+="6";
	TotalLine.SetWindowTextW(Total);
}


void CCalculatorShinSWDlg::OnBnClickedButton7()
{
	// TODO: 여기에 컨트롤 알림 처리기 코드를 추가합니다.
		CString Total;
	TotalLine.GetWindowTextW(Total);
	Total+="7";
	TotalLine.SetWindowTextW(Total);
}


void CCalculatorShinSWDlg::OnBnClickedButton8()
{
	// TODO: 여기에 컨트롤 알림 처리기 코드를 추가합니다.
		CString Total;
	TotalLine.GetWindowTextW(Total);
	Total+="8";
	TotalLine.SetWindowTextW(Total);
}


void CCalculatorShinSWDlg::OnBnClickedButton9()
{
	// TODO: 여기에 컨트롤 알림 처리기 코드를 추가합니다.
		CString Total;
	TotalLine.GetWindowTextW(Total);
	Total+="9";
	TotalLine.SetWindowTextW(Total);
}


void CCalculatorShinSWDlg::OnBnClickedButton10()
{
	// TODO: 여기에 컨트롤 알림 처리기 코드를 추가합니다.
		CString Total;
	TotalLine.GetWindowTextW(Total);
	Total+="0";
	TotalLine.SetWindowTextW(Total);
}


void CCalculatorShinSWDlg::OnBnClickedAdd()
{
	
	CString Total;
	TotalLine.GetWindowTextW(Total);
	
	
	C.a=_ttoi(Total);
	
	Total+=" + ";
	TotalLine.SetWindowTextW(NULL);
	Sentence.SetWindowTextW(Total);
	C.status=1;
	

}


void CCalculatorShinSWDlg::OnBnClickedSub()
{
	CString Total;

		TotalLine.GetWindowTextW(Total);
	
	
	C.a=_ttoi(Total);

	Total+=" - ";
	TotalLine.SetWindowTextW(NULL);
	Sentence.SetWindowTextW(Total);
	C.status=2;
}


void CCalculatorShinSWDlg::OnBnClickedMul()
{
	CString Total;

		TotalLine.GetWindowTextW(Total);
	
	
	C.a=_ttoi(Total);

	Total+=" * ";
		TotalLine.SetWindowTextW(NULL);
	Sentence.SetWindowTextW(Total);
	C.status=3;
}


void CCalculatorShinSWDlg::OnBnClickedMod()
{
	CString Total;

		TotalLine.GetWindowTextW(Total);
	
	
	C.a=_ttoi(Total);
	
	Total+=" / ";
	TotalLine.SetWindowTextW(NULL);
	Sentence.SetWindowTextW(Total);
	C.status=4;
}


void CCalculatorShinSWDlg::OnBnClickedEqual()
{
	
	// TODO: 여기에 컨트롤 알림 처리기 코드를 추가합니다.
	CString Total;
	CString sentence;

	CString result;

	TotalLine.GetWindowTextW(Total);
	C.b=_ttoi(Total);
	Sentence.GetWindowTextW(sentence);
	sentence+=Total;
	sentence+=" = ";


	switch(C.status){

	case 1:
		result.Format(_T("%d"),C.add());		
		sentence+=result;
		break;
		
	case 2:
		result.Format(_T("%d"),C.sub());		
		sentence+=result;
		break;
		
	case 3:
		result.Format(_T("%d"),C.mul());		
		sentence+=result;
		break;
		
	case 4:
		result.Format(_T("%lf"),C.mod());		
		sentence+=result;
		break;
		
	default:
		break;
	}
	//temp.Format( _T("%d"), C.b);

	//print1.Format("%d",C.a);
	//print2.Format("%d",C.b);
	//AfxMessageBox(_T("TestMessage"+print1+","+print2),MB_ICONEXCLAMATION);
	Sentence.SetWindowTextW(sentence);
	TotalLine.SetWindowTextW(NULL);
}


void CCalculatorShinSWDlg::OnBnClickedAc()
{
	// TODO: 여기에 컨트롤 알림 처리기 코드를 추가합니다.
	C.reset();
	TotalLine.SetWindowTextW(NULL);
	Sentence.SetWindowTextW(NULL);
}


void CCalculatorShinSWDlg::OnBnClickedPdiag()
{
	// TODO: 여기에 컨트롤 알림 처리기 코드를 추가합니다.
	ProgrammerDiag dlg;
	
	dlg.DoModal();
	
}


void CCalculatorShinSWDlg::OnBnClickedChattingDialog()
{
	// TODO: 여기에 컨트롤 알림 처리기 코드를 추가합니다.
	ChattingDialog dlg;

	dlg.DoModal();
}
