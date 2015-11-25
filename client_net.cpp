#include "client_net.h"

Client::Client(){
	WSAStartup(MAKEWORD(2, 2), &wsa);
}

Client::~Client(){
	closesocket(sock);// closesocket()
	WSACleanup();// ���� ����
}

void Client::socket_set(){
	sock = socket(AF_INET, SOCK_STREAM, 0);
	if (sock == INVALID_SOCKET) err_quit("socket()");
}

void Client::connect_set(){//�̰� �������� ��.. ��Ե� �������̶� ���߸� ��.. �����ؾ߰��� �Ű������� �޾Ƽ�
	ZeroMemory(&serveraddr, sizeof(serveraddr));
	serveraddr.sin_family = AF_INET;
	serveraddr.sin_addr.s_addr = inet_addr(SERVERIP);
	serveraddr.sin_port = htons(SERVERPORT);
	retval = connect(sock, (SOCKADDR *)&serveraddr, sizeof(serveraddr));
	if (retval == SOCKET_ERROR) err_quit("connect()");
}

int Client::recvn(SOCKET s, char *buf, int len, int flags){
	int received;
	char *ptr = buf;
	int left = len;

	while (left > 0){
		received = recv(s, ptr, left, flags);
		if (received == SOCKET_ERROR)
			return SOCKET_ERROR;
		else if (received == 0)
			break;
		left -= received;
		ptr += received;
	}

	return (len - left);
}

void Client::msg_transfer(){
	// ������ ������ ���
	while (1){
		// ������ �Է�
		printf("\n[���� ������] ");
		if (fgets(buf, BUFSIZE + 1, stdin) == NULL)
			break;

		// '\n' ���� ����
		len = strlen(buf);
		if (buf[len - 1] == '\n')
			buf[len - 1] = '\0';
		if (strlen(buf) == 0)
			break;

		// ������ ������
		//���ۺκ��� ���� ������ �ؾ��� ��Ŷ������ �����ִ� �۾��� ����
		//set_packet()

		retval = send(sock, buf, strlen(buf), 0);
		if (retval == SOCKET_ERROR){
			err_display("send()");
			break;
		}
		printf("[TCP Ŭ���̾�Ʈ] %d����Ʈ�� ���½��ϴ�.\n", retval);


		//�Ľ̺κ� ���� ������ �� �޴°� �������
		// ������ �ޱ�
		retval = recvn(sock, buf, retval, 0);
		if (retval == SOCKET_ERROR){
			err_display("recv()");
			break;
		}
		else if (retval == 0)
			break;

		// ���� ������ ���
		buf[retval] = '\0';
		printf("[TCP Ŭ���̾�Ʈ] %d����Ʈ�� �޾ҽ��ϴ�.\n", retval);
		printf("[���� ������] %s\n", buf);
	}
}

//char* Client::get_msg(){//�̷��� �ϴ°��� �𸣰ڴ�..
//	return buf;
//}

void Client::set_position(float x, float y, float z){//���� �����ο��� ������Ʈ ��ǥ �����ð�
	xpos = x;
	ypos = y;
	zpos = z;
}

void Client::set_packet(){
	//��ǥ�� �� �̰������ؼ� ��Ŷ �����Һκ�
}

char Client::get_packer(){
	//return buf; �Ƹ� �̰� �����ͷ� ���� ������ �����ȴ�
}

void Client::run_network(){
	socket_set();
	connect_set();
	msg_transfer();
}