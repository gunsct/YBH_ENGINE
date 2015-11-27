#pragma comment(lib, "ws2_32")
#include <winsock2.h>
#include <stdlib.h>
#include <stdio.h>
#include <conio.h>
#include <string.h>

#define SERVERIP   "127.0.0.1"
#define SERVERPORT 9000
#define BUFSIZE    512

// 소켓 함수 오류 출력 후 종료
void err_quit(char *msg)
{
	LPVOID lpMsgBuf;
	FormatMessage(
		FORMAT_MESSAGE_ALLOCATE_BUFFER | FORMAT_MESSAGE_FROM_SYSTEM,
		NULL, WSAGetLastError(),
		MAKELANGID(LANG_NEUTRAL, SUBLANG_DEFAULT),
		(LPTSTR)&lpMsgBuf, 0, NULL);
	MessageBox(NULL, (LPCTSTR)lpMsgBuf, msg, MB_ICONERROR);
	LocalFree(lpMsgBuf);
	exit(1);
}

// 소켓 함수 오류 출력
void err_display(char *msg)
{
	LPVOID lpMsgBuf;
	FormatMessage(
		FORMAT_MESSAGE_ALLOCATE_BUFFER | FORMAT_MESSAGE_FROM_SYSTEM,
		NULL, WSAGetLastError(),
		MAKELANGID(LANG_NEUTRAL, SUBLANG_DEFAULT),
		(LPTSTR)&lpMsgBuf, 0, NULL);
	printf("[%s] %s", msg, (char *)lpMsgBuf);
	LocalFree(lpMsgBuf);
}

class Client{
private:
	int retval;
	WSADATA wsa;

	SOCKET sock;
	SOCKADDR_IN serveraddr;

	// 데이터 통신에 사용할 변수
	char buf[BUFSIZE + 1];
	int len;

	//패킷구성용
	int cli_num;
	int regi;
	float xpos, ypos, zpos;
	char temp[];//나중에 inot같은거로 변환시 사용될듯


public:
	Client();
	~Client();

	//클라 구성
	void socket_set();
	void connect_set();
	int recvn(SOCKET s, char *buf, int len, int flags);
	void msg_transfer();

	//패킷부분하자
	//char* get_msg(); 생각해보니 이건 파싱에서 가져가야지...
	void set_position(float x, float y, float z);//게임 구동부에서 오브젝트 좌표 가져올것
	
	void set_packet();
	char get_packer();

	float get_xpos();
	float get_ypos();
	float get_zpos();

	//최종구동
	void run_network();//묶어서 한방에 돌리자
};