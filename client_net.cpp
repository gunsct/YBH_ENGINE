#include "client_net.h"

Client::Client(){
	WSAStartup(MAKEWORD(2, 2), &wsa);
}

Client::~Client(){
	closesocket(sock);// closesocket()
	WSACleanup();// 윈속 종료
}

void Client::socket_set(){
	sock = socket(AF_INET, SOCK_STREAM, 0);
	if (sock == INVALID_SOCKET) err_quit("socket()");
}

void Client::connect_set(){//이게 웹서버나 뭐.. 어떻게든 서버쪽이랑 맞추면 뭐.. 수정해야겠지 매개변수로 받아서
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
	// 서버와 데이터 통신
	while (1){
		// 데이터 입력
		printf("\n[보낼 데이터] ");
		if (fgets(buf, BUFSIZE + 1, stdin) == NULL)
			break;

		// '\n' 문자 제거
		len = strlen(buf);
		if (buf[len - 1] == '\n')
			buf[len - 1] = '\0';
		if (strlen(buf) == 0)
			break;

		// 데이터 보내기
		//전송부분을 이제 수정을 해야함 패킷단위로 묶어주는 작업을 하자
		//set_packet()

		retval = send(sock, buf, strlen(buf), 0);
		if (retval == SOCKET_ERROR){
			err_display("send()");
			break;
		}
		printf("[TCP 클라이언트] %d바이트를 보냈습니다.\n", retval);


		//파싱부분 만들어서 데이터 값 받는거 해줘야함
		// 데이터 받기
		retval = recvn(sock, buf, retval, 0);
		if (retval == SOCKET_ERROR){
			err_display("recv()");
			break;
		}
		else if (retval == 0)
			break;

		// 받은 데이터 출력
		buf[retval] = '\0';
		printf("[TCP 클라이언트] %d바이트를 받았습니다.\n", retval);
		printf("[받은 데이터] %s\n", buf);
	}
}

//char* Client::get_msg(){//이렇게 하는건지 모르겠다..
//	return buf;
//}

void Client::set_position(float x, float y, float z){//게임 구동부에서 오브젝트 좌표 가져올것
	xpos = x;
	ypos = y;
	zpos = z;
}

void Client::set_packet(){
	//좌표랑 뭐 이것저것해서 패킷 구성할부분
}

char Client::get_packer(){
	//return buf; 아마 이거 포인터로 하지 않을까 생각된다
}

void Client::run_network(){
	socket_set();
	connect_set();
	msg_transfer();
}