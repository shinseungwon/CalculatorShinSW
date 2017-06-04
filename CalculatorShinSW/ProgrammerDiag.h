#pragma once
#include "afxwin.h"
#include "SimpleCalculatorModule.h"
#include "fstream"
#include "iostream"
#include "winsock2.h"
#include "thread"
#define MAX_OUTPUT_SIZE 100
#define MAX_INPUT_SIZE 1000
#define FILE_DIR "Calculator_output.txt"
#define IP_PORT_DIR "ip_port.txt"
#define HD_SEND_SIZE 4
using namespace std;
#pragma warning(disable:4996)
// ProgrammerDiag ��ȭ �����Դϴ�.

class ProgrammerDiag : public CDialog
{
	DECLARE_DYNAMIC(ProgrammerDiag)
private:
	void sendData(char ** data_addr,int count,int length);
	bool Connect(char* ip,int port);
	void DisConnect();
	SOCKET sockfd;
	WSADATA wsaData;
	struct sockaddr_in addr;
	bool connected;
	char ip[20];
	char port[10];
	int port_int;
public:
	ProgrammerDiag(CWnd* pParent = NULL);   // ǥ�� �������Դϴ�.
	virtual ~ProgrammerDiag();

// ��ȭ ���� �������Դϴ�.
	enum { IDD = IDD_PROGRAMMERDIAG };

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV �����Դϴ�.

	DECLARE_MESSAGE_MAP()
public:	
	CEdit Input;
	CEdit bi;
	CEdit hd;
	afx_msg void OnBnClickedExecute();
	CEdit dc;		
	SimpleCalculatorModule M;
	int m_Radio;
	afx_msg void OnEnChangeEdit3();
	afx_msg void OnBnClickedAnd();
	afx_msg void OnBnClickedOr();
	afx_msg void OnBnClickedXor();
	CEdit Calc_Value_1;
	CEdit Calc_Value_2;
	CEdit Calc_Result;
	CListBox List;
	afx_msg void OnBnClickedSelectionSort();
	afx_msg void OnBnClickedInsertionSort();
	afx_msg void OnBnClickedBubbleSort();
	afx_msg void OnBnClickedSaveAsFile();	
	afx_msg void OnBnClickedLoadFile();
	CEdit IP_PORT_NUM;
	afx_msg void OnBnClickedSend();
	afx_msg void OnBnClickedGetIp();
		
	CButton BUTTON_SEND;
	afx_msg void OnBnClickedConnect();
	CEdit RECEIVED_DATA;
	CButton CONNECT_BUTTON_TAG;
	virtual BOOL OnInitDialog();
};