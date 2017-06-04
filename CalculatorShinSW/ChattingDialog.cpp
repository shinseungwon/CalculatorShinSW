// ChattingDialog.cpp : 구현 파일입니다.
//

#include "stdafx.h"
#include "CalculatorShinSW.h"
#include "ChattingDialog.h"
#include "afxdialogex.h"


// ChattingDialog 대화 상자입니다.

IMPLEMENT_DYNAMIC(ChattingDialog, CDialogEx)

ChattingDialog::ChattingDialog(CWnd* pParent /*=NULL*/)
	: CDialogEx(ChattingDialog::IDD, pParent)
{

}

ChattingDialog::~ChattingDialog()
{
	GetExitCodeThread( p1->m_hThread, &dwExitCode );
}

void ChattingDialog::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
	DDX_Control(pDX, IDC_IP_INPUT, CHATTING_IPINPUT);
	DDX_Control(pDX, IDC_PORT_INPUT, CHATTING_PORTINPUT);
	DDX_Control(pDX, IDC_SEND_TEXT, CHATTING_TEXTINPUT);
	DDX_Control(pDX, IDC_SEND_HEXA, CHATTING_HEXAINPUT);
	DDX_Control(pDX, IDC_CHATTING_LIST, CHATTING_LISTINPUT);
	DDX_Control(pDX, IDC_STATUS, STATUS_LINE);
	DDX_Control(pDX, IDC_CHATTING_SEND, CHATTING_SEND_TAG);
	DDX_Control(pDX, IDC_CHATTING_CONNECT, CHATTING_CONNECT_TAG);
}


BEGIN_MESSAGE_MAP(ChattingDialog, CDialogEx)
	ON_BN_CLICKED(IDC_CHATTING_CONNECT, &ChattingDialog::OnBnClickedChattingConnect)
	ON_BN_CLICKED(IDC_CHATTING_SEND, &ChattingDialog::OnBnClickedChattingSend)
	
	ON_LBN_SELCHANGE(IDC_CHATTING_LIST, &ChattingDialog::OnLbnSelchangeChattingList)
END_MESSAGE_MAP()


// ChattingDialog 메시지 처리기입니다.


BOOL ChattingDialog::OnInitDialog()
{
	CDialogEx::OnInitDialog();
	connected=false;
	// TODO:  여기에 추가 초기화 작업을 추가합니다.
	//IP/PORT 불러오기
	ifstream inFile(IP_PORT_DIR);
	CString iptag("IP : ");
	inFile.getline(ip, MAX_OUTPUT_SIZE);	
	inFile.getline(port, MAX_OUTPUT_SIZE);
	port_int=atoi(port);
	CString IP_PORT;
	CString ipc;
	ipc=(LPSTR)ip;
	CString portc;
	portc=(LPSTR)port;	
	CHATTING_IPINPUT.SetWindowTextW(ipc);
	CHATTING_PORTINPUT.SetWindowTextW(portc);	
    inFile.close();
	CHATTING_SEND_TAG.EnableWindow(TRUE);

	//thread t(&Recv,sockfd); //방법 
	//t.join(); //join()을 실행시키면 t가 종료되기 전까지 기다린다.



	return TRUE;  // return TRUE unless you set the focus to a control
	// 예외: OCX 속성 페이지는 FALSE를 반환해야 합니다.
}

bool ChattingDialog :: Connect(char* ip,int port)
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

void ChattingDialog :: sendData(char * data_addr,int count,int length)
{			
	const char* const ptrTpPass = static_cast<const char* const>(data_addr);
	cout <<"Sent : "<< ptrTpPass<<endl;
	send(sockfd, ptrTpPass, strlen(data_addr), 0);
}

void ChattingDialog :: DisConnect(){
	closesocket(sockfd);
	WSACleanup();
}


void ChattingDialog::OnBnClickedChattingConnect()
{
	// TODO: 여기에 컨트롤 알림 처리기 코드를 추가합니다.
		if(connected){
		DisConnect();
		connected=false;
		STATUS_LINE.SetWindowTextW(_T("DISCONNECTED"));				
		CHATTING_CONNECT_TAG.SetWindowTextW(_T("CONNECT"));
		CHATTING_SEND_TAG.EnableWindow(FALSE);
	}
	else{
		CString iptemp;
		CHATTING_IPINPUT.GetWindowTextW(iptemp);
		char Buffer1[255];		
		size_t CharactersConverted1 = 0;
		wcstombs_s(&CharactersConverted1, Buffer1, iptemp.GetLength()+1, iptemp, _TRUNCATE);
		
		CString porttemp;
		CHATTING_PORTINPUT.GetWindowTextW(porttemp);
		int portnum=_ttoi(porttemp);

		if(Connect(Buffer1,portnum)){
			connected=true;
			STATUS_LINE.SetWindowTextW(_T("SUCCESSFULLY CONNECTED"));
			CHATTING_SEND_TAG.EnableWindow(TRUE);
			CHATTING_CONNECT_TAG.SetWindowTextW(_T("DISCONNECT"));

			p1 = NULL;
			p1 = AfxBeginThread(Recvd, this);	
			if (p1 == NULL)    
				AfxMessageBox(L"Error");    		
		}
		else{
			STATUS_LINE.SetWindowTextW(_T("CONNECTION FAILED"));			
			Sleep(1000);
			CHATTING_CONNECT_TAG.SetWindowTextW(_T("CONNECT"));
		}
	}	
}




UINT ChattingDialog::Recvd(LPVOID _mothod){	
	
	char buf[MAX_INPUT_SIZE];
	ChattingDialog *fir;

	while(1){	
	fir = (ChattingDialog*)_mothod;

	if(fir->connected == FALSE){
		cout <<"No Connection\n";
		continue;
	}else
		cout <<"Connected!\n";

	for(int i=0;i<MAX_INPUT_SIZE;i++)
		buf[i]=NULL;
	cout <<"Waiting receive ..\n";
	
	int retval = recv(fir->sockfd, buf, MAX_INPUT_SIZE, 0);
	cout <<retval<<endl;
	if(retval == SOCKET_ERROR)
	{ 
		cout <<"Socket Error"<<endl; 
		break;
	}else if( retval == 0 ){
		break;
	}
	
	cout <<"Received Message : "<< buf <<endl;	
	CString str;
	str = (LPCSTR)(LPSTR)buf;

	CString output("");
	output+=fir->GetTime();	
	output+=" SERVER says : ";
	output+=str;

	fir->CHATTING_LISTINPUT.InsertString(-1,str);
	fir->STATUS_LINE.SetWindowTextW(output);
	}
	
	return 0;
}


void ChattingDialog::OnBnClickedChattingSend()
{
	// TODO: 여기에 컨트롤 알림 처리기 코드를 추가합니다.

	char* Data=(char*)malloc(sizeof(char)*MAX_CHATTING_SIZE);
	
	Data=new char[HD_SEND_SIZE];
	CString temp;
	CHATTING_TEXTINPUT.GetWindowTextW(temp);
	strcpy( Data, CStringA(temp) );
	
	/*
	for(int i=0;i<M.getSize();i++)
		cout << Data[i]<<endl;
		*/
	
	sendData(Data,M.getSize(),MAX_CHATTING_SIZE);
	CString output("");
	output+=GetTime();	
	output+=" YOU say : ";
	output+=temp;
	CHATTING_LISTINPUT.InsertString(-1,temp);
	CHATTING_TEXTINPUT.SetWindowTextW(_T(""));
	STATUS_LINE.SetWindowTextW(output);
}





BOOL ChattingDialog::PreTranslateMessage(MSG* pMsg)
{
	// TODO: 여기에 특수화된 코드를 추가 및/또는 기본 클래스를 호출합니다.

	if((pMsg->message == WM_KEYDOWN) && (pMsg->wParam == VK_RETURN))
    {
        // 여기에 원하는 동작의 코드를 삽입
		OnBnClickedChattingSend();
        return true;
    }

	return CDialogEx::PreTranslateMessage(pMsg);
}


void ChattingDialog::OnLbnSelchangeChattingList()
{
	// TODO: 여기에 컨트롤 알림 처리기 코드를 추가합니다.
	CString List_Value;
	int List_index;
    
	List_index = CHATTING_LISTINPUT.GetCurSel(); 
	UpdateData(TRUE);

	
	CHATTING_LISTINPUT.GetText(List_index,List_Value);



	char* Buffer=(char*)malloc(sizeof(char)*List_Value.GetLength()+1);
	size_t CharactersConverted = 0;
	wcstombs_s(&CharactersConverted, Buffer, List_Value.GetLength()+1, List_Value, _TRUNCATE);	
	CString output;
	output=output+M.CAtoHA(Buffer,List_Value.GetLength());
	CHATTING_HEXAINPUT.SetWindowTextW(output);
}

CString ChattingDialog::GetTime(){
	CTime cTime = CTime::GetCurrentTime();
	CString strDate, strTime;
	strDate.Format(_T("%04d년 %02d월 %02d일"), cTime.GetYear(),cTime.GetMonth(), cTime.GetDay());
	strTime.Format(_T("%02d시 %02d분 %02d초"), cTime.GetHour(),cTime.GetMinute(),cTime.GetSecond());

	CString output("");
	output+="[";
	output+=strDate;
	output+="/";
	output+=strTime;
	output+="]";
	return output;
}
