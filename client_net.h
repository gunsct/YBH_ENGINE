#pragma comment(lib, "ws2_32")
#include <winsock2.h>
#include <stdlib.h>
#include <stdio.h>
#include <conio.h>
#include <string.h>

#define SERVERIP   "127.0.0.1"
#define SERVERPORT 9000
#define BUFSIZE    512

// ���� �Լ� ���� ��� �� ����
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

// ���� �Լ� ���� ���
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

	// ������ ��ſ� ����� ����
	char buf[BUFSIZE + 1];
	int len;

	//��Ŷ������
	int cli_num;
	int regi;
	float xpos, ypos, zpos;
	char temp[];//���߿� inot�����ŷ� ��ȯ�� ���ɵ�


public:
	Client();
	~Client();

	//Ŭ�� ����
	void socket_set();
	void connect_set();
	int recvn(SOCKET s, char *buf, int len, int flags);
	void msg_transfer();

	//��Ŷ�κ�����
	//char* get_msg(); �����غ��� �̰� �Ľ̿��� ����������...
	void set_position(float x, float y, float z);//���� �����ο��� ������Ʈ ��ǥ �����ð�
	
	void set_packet();
	char get_packer();

	float get_xpos();
	float get_ypos();
	float get_zpos();

	//��������
	void run_network();//��� �ѹ濡 ������
};