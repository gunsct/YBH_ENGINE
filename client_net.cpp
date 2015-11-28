#include "client_net.h"

Client::Client(){
	WSAStartup(MAKEWORD(2, 2), &wsa);
	cli_num = 0;
	regi = 0;
}

Client::~Client(){
	closesocket(sock);// closesocket()
	WSACleanup();// ���� ����
}

void Client::socket_set(){//��..�̰� �����Ƿ� �ٲ������
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

		//// '\n' ���� ����
		//len = strlen(buf);
		//if (buf[len - 1] == '\n')
		//	buf[len - 1] = '\0';
		//if (strlen(buf) == 0)
		//	break;

		// ������ ������
		//���ۺκ��� ���� ������ �ؾ��� ��Ŷ������ �����ִ� �۾��� ����
		//set_packet()

		retval = send(sock, buf, strlen(buf), 0);
		if (retval == SOCKET_ERROR){
			err_display("send()");
			break;
		}
		printf("[TCP Ŭ���̾�Ʈ] %d����Ʈ�� ���½��ϴ�.\n", retval);

		regi = 1;//���� ��Ͻ� 0�� ����� 1�� ��Ͼ���

		//�Ľ̺κ� ���� ������ �� �޴°� �������
		// ������ �ޱ�
		retval = recvn(sock, buf, retval, 0);
		if (retval == SOCKET_ERROR){
			err_display("recv()");
			break;
		}
		else if (retval == 0)
			break;

		//���� �޽��� �Ľ��ؼ� ��ǥ�� �� �Ѱ��ٵ�
		//parsing_msg

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
	////��Ŷ������
	//int cli_num;
	//char regi;
	//float xpos, ypos, zpos;
	sprintf(buf, "%d %d %f %f %f", cli_num, regi, xpos, ypos, zpos);
}

void Client::parsing_msg(char packet){
	int point_num = 0;//�Ź� �� �Լ� �θ������� �翬�� �� �ʱ�ȭ �Ǿߵ�
	int buf_pos = 0;
	char pnum[2] = "";
	char pregi[1] = "";
	char pxp[100] = "";
	char pyp[100] = "";
	char pzp[100] = "";

	for (int i = 0; i < sizeof(buf); i++){//�� ��Ҹ� �����ؼ� ���ڹ迭�� �־��� �̰� �ٸ� �ڷ������� �ٵ� ��ȯ�Ұ���
		if (buf[i] == ' '){ //���� �������� ��Ŷ�� ��ҷ� ������
			point_num++;//��� ���� �÷���
			buf_pos = 0;//��� ������ġ�� �ٽ� 0����
		}

		else{//���� �ƴҶ��� ��� ���ҵȰ� ���� �־���
			switch (point_num){
				case 0:
					pnum[buf_pos] = buf[i];
					buf_pos++;
					break;

				case 1:
					pregi[buf_pos] = buf[i];
					buf_pos++;
					break;

				case 2:
					pxp[buf_pos] = buf[i];
					buf_pos++;
					break;

				case 3:
					pyp[buf_pos] = buf[i];
					buf_pos++;
					break;

				case 4:
					pzp[buf_pos] = buf[i];
					buf_pos++;
					break;

			}
		}
	}

	//�� ���� �迭�� �� ��ҵ� �ڷ�����ȯ�ؾ���
	cli_num = atoi(pnum);
	regi = atoi(pregi);
	xpos = atof(pxp);
	ypos = atof(pyp);
	zpos = atof(pzp);
}

char Client::get_packer(){
	//return buf; �Ƹ� �̰� �����ͷ� ���� ������ �����ȴ�
}

int Client::get_cli_num(){
	return cli_num;
}

float  Client::get_xpos(){
	return xpos;
}

float  Client::get_ypos(){
	return ypos;
}

float  Client::get_zpos(){
	return zpos;
}

void Client::run_network(){
	socket_set();
	connect_set();
	msg_transfer();
}