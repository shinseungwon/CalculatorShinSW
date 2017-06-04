// ProgrammerDiag.cpp : 구현 파일입니다.
//

#include "stdafx.h"
#include "CalculatorShinSW.h"
#include "ProgrammerDiag.h"
#include "afxdialogex.h"


// ProgrammerDiag 대화 상자입니다.

IMPLEMENT_DYNAMIC(ProgrammerDiag, CDialog)

ProgrammerDiag::ProgrammerDiag(CWnd* pParent /*=NULL*/)
	: CDialog(ProgrammerDiag::IDD, pParent)	
	, m_Radio(0)
{
	connected=false;
}

ProgrammerDiag::~ProgrammerDiag()
{
}

void ProgrammerDiag::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	DDX_Control(pDX, IDC_EDIT1, Input);
	DDX_Control(pDX, IDC_BINARY, bi);
	DDX_Control(pDX, IDC_DECIMAL, dc);
	DDX_Control(pDX, IDC_HEXADECIMAL, hd);

	DDX_Radio(pDX, IDC_BINARY_RADIO, m_Radio);
	DDX_Control(pDX, IDC_BINARY_CAL_1, Calc_Value_1);
	DDX_Control(pDX, IDC_BINARY_CAL_2, Calc_Value_2);
	DDX_Control(pDX, IDC_RESULT, Calc_Result);
	DDX_Control(pDX, IDC_LIST2, List);
	DDX_Control(pDX, IDC_IP_PORT, IP_PORT_NUM);
	DDX_Control(pDX, IDC_SEND, BUTTON_SEND);
	DDX_Control(pDX, IDC_EDIT2, RECEIVED_DATA);
	DDX_Control(pDX, IDC_CONNECT, CONNECT_BUTTON_TAG);
}


BEGIN_MESSAGE_MAP(ProgrammerDiag, CDialog)
	ON_BN_CLICKED(IDC_BUTTON1, &ProgrammerDiag::OnBnClickedExecute)
	ON_BN_CLICKED(IDC_AND, &ProgrammerDiag::OnBnClickedAnd)
	ON_BN_CLICKED(IDC_OR, &ProgrammerDiag::OnBnClickedOr)
	ON_BN_CLICKED(IDC_XOR, &ProgrammerDiag::OnBnClickedXor)
	ON_BN_CLICKED(IDC_SELECTION_SORT, &ProgrammerDiag::OnBnClickedSelectionSort)
	ON_BN_CLICKED(IDC_INSERTION_SORT, &ProgrammerDiag::OnBnClickedInsertionSort)
	ON_BN_CLICKED(IDC_BUBBLE_SORT, &ProgrammerDiag::OnBnClickedBubbleSort)
	ON_BN_CLICKED(IDC_SAVE_AS_FILE, &ProgrammerDiag::OnBnClickedSaveAsFile)
	ON_BN_CLICKED(IDC_LOAD_FILE, &ProgrammerDiag::OnBnClickedLoadFile)
	ON_BN_CLICKED(IDC_SEND, &ProgrammerDiag::OnBnClickedSend)
	ON_BN_CLICKED(IDC_GET_IP, &ProgrammerDiag::OnBnClickedGetIp)
	ON_BN_CLICKED(IDC_CONNECT, &ProgrammerDiag::OnBnClickedConnect)
END_MESSAGE_MAP()


// ProgrammerDiag 메시지 처리기입니다.

//진법 변환 버튼 이벤트 처리기
void ProgrammerDiag::OnBnClickedExecute()
{		
	
	CString numbertext;
	int number;
	Input.GetWindowTextW(numbertext);
	number=_ttoi(numbertext);
	UpdateData(true);

	CString temp;
	
	switch(m_Radio)
	{
	case 0:
		bi.SetWindowTextW(M.intConverter(numbertext,2,2));
		dc.SetWindowTextW(M.intConverter(numbertext,2,10));
		hd.SetWindowTextW(M.intConverter(numbertext,2,16));
		temp=M.intConverter(numbertext,2,10);		
		List.InsertString(-1,temp);		
		M.save(_ttoi(temp));
		break;
	case 1:
		bi.SetWindowTextW(M.intConverter(numbertext,10,2));
		dc.SetWindowTextW(M.intConverter(numbertext,10,10));
		hd.SetWindowTextW(M.intConverter(numbertext,10,16));
		temp=M.intConverter(numbertext,10,10);		
		List.InsertString(-1,temp);
		M.save(_ttoi(temp));
		break;
	case 2:
		bi.SetWindowTextW(M.intConverter(numbertext,16,2));
		dc.SetWindowTextW(M.intConverter(numbertext,16,10));
		hd.SetWindowTextW(M.intConverter(numbertext,16,16));
		temp=M.intConverter(numbertext,16,10);		
		List.InsertString(-1,temp);
		M.save(_ttoi(temp));
		break;
	}
}

//and 연산 버튼 이벤트 처리기
void ProgrammerDiag::OnBnClickedAnd()
{		
	CString value1, value2;
	Calc_Value_1.GetWindowTextW(value1);
	Calc_Value_2.GetWindowTextW(value2);
	Calc_Result.SetWindowTextW(M.calAndOrXor(value1,value2,1));
}

//or 연산 버튼 이벤트 처리기
void ProgrammerDiag::OnBnClickedOr()
{	
	CString value1, value2;
	Calc_Value_1.GetWindowTextW(value1);
	Calc_Value_2.GetWindowTextW(value2);
	Calc_Result.SetWindowTextW(M.calAndOrXor(value1,value2,2));
}

//xor 연산 버튼 이벤트 처리기
void ProgrammerDiag::OnBnClickedXor()
{	
	CString value1, value2;
	Calc_Value_1.GetWindowTextW(value1);
	Calc_Value_2.GetWindowTextW(value2);
	Calc_Result.SetWindowTextW(M.calAndOrXor(value1,value2,3));
}

//선택정렬 버튼 이벤트 처리기
void ProgrammerDiag::OnBnClickedSelectionSort()
{
	List.ResetContent();
	M.SelectionSort();
	for(int i=0;i<M.getSize();i++)
		List.InsertString(-1,M.getIndexof(i));
}

//삽입정렬 버튼 이벤트 처리기
void ProgrammerDiag::OnBnClickedInsertionSort()
{
	List.ResetContent();
	M.InsertionSort();
	for(int i=0;i<M.getSize();i++)
		List.InsertString(-1,M.getIndexof(i));
}

//버블정렬 버튼 이벤트 처리기
void ProgrammerDiag::OnBnClickedBubbleSort()
{
	List.ResetContent();
	M.BubbleSort();
	for(int i=0;i<M.getSize();i++)
		List.InsertString(-1,M.getIndexof(i));
}

//파일 저장 버튼 이벤트 처리기
void ProgrammerDiag::OnBnClickedSaveAsFile()
{
	ofstream outFile(FILE_DIR);
	int output=0;
	
	for(int i=0;i<M.getSize();i++){
		output=_ttoi(M.getIndexof(i));
		outFile<<output<<endl;
	}
	outFile.close();
}

//파일 불러오기 버튼 이벤트 처리기
void ProgrammerDiag::OnBnClickedLoadFile()
{
	List.ResetContent();
	ifstream inFile(FILE_DIR);
	char inputString[MAX_OUTPUT_SIZE];
	CString forList;
	while(!inFile.eof()){
		inFile.getline(inputString, MAX_OUTPUT_SIZE);
		forList=(LPSTR)inputString;
		List.InsertString(-1,forList);
        }
    inFile.close();
}



//보내기 버튼
void ProgrammerDiag::OnBnClickedSend()
{	
	char** Data=(char**)malloc(sizeof(char*)*M.getSize());
	for(int i=0;i<M.getSize();i++){		
		Data[i]=new char[HD_SEND_SIZE];
		strcpy( Data[i], CStringA(M.intConverter(M.getIndexof(i),10,16)).GetString() );
	}
	/*
	for(int i=0;i<M.getSize();i++)
		cout << Data[i]<<endl;
		*/
	
	sendData(Data,M.getSize(),HD_SEND_SIZE);	
}

//IP 불러오기 버튼
void ProgrammerDiag::OnBnClickedGetIp()
{
	ifstream inFile(IP_PORT_DIR);

	CString iptag("IP : ");
	inFile.getline(ip, MAX_OUTPUT_SIZE);
	CString porttag("/");
	inFile.getline(port, MAX_OUTPUT_SIZE);
	port_int=atoi(port);
	CString IP_PORT;
	CString ipc;
	ipc=(LPSTR)ip;
	CString portc;
	portc=(LPSTR)port;
	IP_PORT=iptag+ipc+porttag+portc;
	IP_PORT_NUM.SetWindowTextW(IP_PORT);
	
    inFile.close();
	CONNECT_BUTTON_TAG.EnableWindow(TRUE);
}
//소켓으로 데이터 보내기
void ProgrammerDiag :: sendData(char ** data_addr,int count,int length)
{		
	for(int i=0;i<count;i++){
		const char* const ptrTpPass = static_cast<const char* const>(data_addr[i]);
		cout <<"Sent : "<< ptrTpPass<<endl;
		send(sockfd, ptrTpPass, strlen(data_addr[i]), 0);
	}

	const char* const ptrTpPass = static_cast<const char* const>("!");
	cout <<"Sent : "<< ptrTpPass<<endl;
	send(sockfd, ptrTpPass, strlen("!"), 0);
		 
	char buf[MAX_INPUT_SIZE];
	for(int i=0;i<MAX_INPUT_SIZE;i++)
		buf[i]=NULL;
	
	recv(sockfd, buf, MAX_INPUT_SIZE, 0);
	cout <<"Received Message : "<< buf <<endl;	
	CString str;
	str = (LPCSTR)(LPSTR)buf;
	
	RECEIVED_DATA.SetWindowTextW(str);
	return;
}

bool ProgrammerDiag :: Connect(char* ip,int port)
{		
	if(WSAStartup(MAKEWORD(2,2), &wsaData) != NO_ERROR)
		return false;
			
	if((sockfd = socket(AF_INET,SOCK_STREAM, 0)) == INVALID_SOCKET) 
		return false;
	
	memset((void *)&addr, 0x00, sizeof(addr));
	addr.sin_family = AF_INET;
	addr.sin_addr.s_addr = inet_addr(ip);
	addr.sin_port = htons(port);
	
	if(connect(sockfd, (struct sockaddr *)&addr, sizeof(addr)) == SOCKET_ERROR)
		return false;
	else
		return true;
}

void ProgrammerDiag :: DisConnect(){
	closesocket(sockfd);	
	WSACleanup();
}

void ProgrammerDiag::OnBnClickedConnect()
{
	if(connected){
		DisConnect();
		connected=false;
		CONNECT_BUTTON_TAG.SetWindowTextW(_T("DISCONNECTED"));
		CONNECT_BUTTON_TAG.EnableWindow(FALSE);
		Sleep(1000);
		CONNECT_BUTTON_TAG.EnableWindow(TRUE);
		CONNECT_BUTTON_TAG.SetWindowTextW(_T("CONNECT"));
		BUTTON_SEND.EnableWindow(FALSE);
	}
	else{
		if(Connect(ip,port_int)){
			connected=true;
			CONNECT_BUTTON_TAG.SetWindowTextW(_T("SUCCESSFULLY CONNECTED\n(Click to disconnect)"));
			BUTTON_SEND.EnableWindow(TRUE);
		}
		else{
			CONNECT_BUTTON_TAG.SetWindowTextW(_T("CONNECTION FAILED"));
			CONNECT_BUTTON_TAG.EnableWindow(FALSE);
			Sleep(1000);
			CONNECT_BUTTON_TAG.EnableWindow(TRUE);
			CONNECT_BUTTON_TAG.SetWindowTextW(_T("CONNECT"));
		}
	}
}


BOOL ProgrammerDiag::OnInitDialog()
{
	CDialog::OnInitDialog();

	// TODO:  여기에 추가 초기화 작업을 추가합니다.
	ifstream inFile(IP_PORT_DIR);

	CString iptag("IP : ");
	inFile.getline(ip, MAX_OUTPUT_SIZE);
	CString porttag("/");
	inFile.getline(port, MAX_OUTPUT_SIZE);
	port_int=atoi(port);
	CString IP_PORT;
	CString ipc;
	ipc=(LPSTR)ip;
	CString portc;
	portc=(LPSTR)port;
	IP_PORT=iptag+ipc+porttag+portc;
	IP_PORT_NUM.SetWindowTextW(IP_PORT);
	
    inFile.close();
	CONNECT_BUTTON_TAG.EnableWindow(TRUE);


	return TRUE;  // return TRUE unless you set the focus to a control
	// 예외: OCX 속성 페이지는 FALSE를 반환해야 합니다.
}
