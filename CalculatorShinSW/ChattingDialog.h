#pragma once
#include "SimpleCalculatorModule.h"
#include "afxwin.h"
#include "fstream"
#include "iostream"
#include "winsock2.h"
#include "thread"
#define IP_PORT_DIR "ip_port.txt"
#define HD_SEND_SIZE 4
#define MAX_OUTPUT_SIZE 100
#define MAX_INPUT_SIZE 1000
#define MAX_CHATTING_SIZE 1000
using namespace std;
#pragma warning(disable:4996)
// ChattingDialog 대화 상자입니다.

class ChattingDialog : public CDialogEx
{
	DECLARE_DYNAMIC(ChattingDialog)
	void sendData(char * data_addr,int count,int length);
	bool Connect(char* ip,int port);
	static UINT Recvd(LPVOID _mothod);
	void DisConnect();	
	CString GetTime();
	WSADATA wsaData;
	struct sockaddr_in addr;
	char ip[20];
	char port[10];
	int port_int;
	SimpleCalculatorModule M;
	CWinThread *p1;
	DWORD dwExitCode;
public:
	ChattingDialog(CWnd* pParent = NULL);   // 표준 생성자입니다.
	virtual ~ChattingDialog();

// 대화 상자 데이터입니다.
	enum { IDD = IDD_CHATTING_DIALOG };

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV 지원입니다.

	DECLARE_MESSAGE_MAP()
public:
	virtual BOOL OnInitDialog();
	CEdit CHATTING_IPINPUT;
	CEdit CHATTING_PORTINPUT;
	afx_msg void OnBnClickedChattingConnect();
	afx_msg void OnBnClickedChattingSend();
	CEdit CHATTING_TEXTINPUT;
	CEdit CHATTING_HEXAINPUT;
	CListBox CHATTING_LISTINPUT;
	
	CEdit STATUS_LINE;
	CButton CHATTING_SEND_TAG;
	CButton CHATTING_CONNECT_TAG;
	virtual BOOL PreTranslateMessage(MSG* pMsg);
	SOCKET sockfd;
	bool connected;
	
	afx_msg void OnLbnSelchangeChattingList();
};
