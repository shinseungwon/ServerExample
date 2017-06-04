#include <winsock2.h>
#include <iostream>

#define MAX_PACKETLEN 1024
#define PORT 3500

#pragma warning(disable : 4996)
#pragma comment(lib, "ws2_32.lib")

void main() {
	WSADATA wsaData;
	SOCKET listen_s, client_s;
	struct sockaddr_in server_addr, client_addr;
	char szReceiveBuffer[MAX_PACKETLEN];

	int readn, writen;
	int len;

	if (WSAStartup(MAKEWORD(2, 2), &wsaData) != 0) {
		return;
	}
	listen_s = socket(AF_INET, SOCK_STREAM, IPPROTO_TCP);
	if (listen_s == INVALID_SOCKET) {
		return;
	}

	ZeroMemory(&server_addr, sizeof(struct sockaddr_in));

	server_addr.sin_family = PF_INET;
	server_addr.sin_port = htons(PORT);
	server_addr.sin_addr.S_un.S_addr = htonl(INADDR_ANY);

	if (bind(listen_s, (struct sockaddr*)&server_addr, sizeof(struct sockaddr_in)) == SOCKET_ERROR) {
		return;
	}
	if (listen(listen_s, 5) == SOCKET_ERROR) {
		return;
	}

	while (1) {
		ZeroMemory(&client_addr, sizeof(struct sockaddr_in));
		len = sizeof(struct sockaddr_in);
		client_s = accept(listen_s, (struct sockaddr *)&client_addr, &len);
		readn = recv(client_s, szReceiveBuffer, MAX_PACKETLEN, 0); 
		if (readn > 0) {
			writen = send(client_s, szReceiveBuffer, readn, 0);
		}
		printf("%s\n",&szReceiveBuffer);
		closesocket(client_s);
	}
	closesocket(listen_s);
	WSACleanup();
}