#include <stdio.h>
#include <conio.h>
#include <winsock2.h>
#include <windef.h>
#include <pthread.h>

#include "ClientSocket_test.h"
#include "CheckInput.h"

int main(int argc, char **argv)
{
	int port = 0;
	char *pIpAddr = NULL;

	pIpAddr = (char *)malloc(sizeof(char) * IP_LEN);
	memset(pIpAddr, '\0', IP_LEN);
	CheckMainInput(argc, argv, pIpAddr, &port);
	// SetNewPort(&port);
	ClientSocket(pIpAddr, port);

	free(pIpAddr);
	pIpAddr = NULL;

	return 0;
}

int ClientSocket(char *pIpAddr, int port)
{
	WSADATA wsaData;
	SOCKET client_sock;
	SOCKADDR_IN client_addr;
	int netStatus = 0;
	char *pBuffer = NULL;
	int buffer_len = 1024;

	pthread_t recieve_thread_id;
	pthread_t send_thread_id;
	int recieve_thread_ret = 0;
	int send_thread_ret = 0;
	SockInfo sock_data;

	netStatus = WSAStartup((WORD)0x0202, (LPWSADATA)&wsaData);
	if (netStatus != 0)
	{
		printf("error: netStatus = %d\n", netStatus);
		WSACleanup();
		getch();
		return -1;
	}

	client_sock = socket(AF_INET, SOCK_STREAM, IPPROTO_TCP);
	memset(&client_addr, 0x00, sizeof(client_addr));
	client_addr.sin_family = AF_INET;
	client_addr.sin_port = htons(port);
	// client_addr.sin_addr.s_addr = htonl(INADDR_ANY);
	client_addr.sin_addr.s_addr = inet_addr(pIpAddr);

	netStatus = connect(client_sock, (struct sockaddr *)&client_addr,
	sizeof(client_addr));
	if (netStatus != 0)
	{
		printf("error : %d\n", WSAGetLastError());
		closesocket(client_sock);
		WSACleanup();
		getch();
		return -1;
	}

	pBuffer = (char *)malloc(sizeof(char) * buffer_len);
	memset(pBuffer, '\0', buffer_len);

	sock_data.sock = client_sock;
	sock_data.pBuffer = pBuffer;
	sock_data.buffer_len = buffer_len;

	send_thread_ret = pthread_create(&send_thread_id, NULL,
	SendThread,
	&sock_data);

	while (1)
	{
		// printf("Input string:");
		// memset(pBuffer, '\0', buffer_len);
		// scanf("%s", pBuffer);
		// send(client_sock, pBuffer, strlen(pBuffer), 0);
		// memset(pBuffer, '\0', buffer_len);
		// netStatus = recv(client_sock, pBuffer, buffer_len, 0);
		// if (netStatus < 0)
		// {
		// printf(Server_Ubind);
		// getch();
		// break;
		// }
		// // printf("Server : %s\n", pBuffer);
		// Sleep(10);

		recieve_thread_ret = pthread_create(&recieve_thread_id, NULL,
		RecieveThread,
		&sock_data);

		if (strcmp(sock_data.pBuffer, Server_Ubind) == 0)
		{
			printf("%s\n", sock_data.pBuffer);
			// getch();
			break;
		}
	}

	free(pBuffer);
	pBuffer = NULL;

	closesocket(client_sock);
	WSACleanup();

	return 0;
}

void* SendThread(void *pInfo)
{
	SockInfo sock_data = *(SockInfo *)pInfo;

	while (1)
	{
		printf(Input_Str);
		memset(sock_data.pBuffer, '\0', sock_data.buffer_len);
		scanf("%s", sock_data.pBuffer);
		send(sock_data.sock, sock_data.pBuffer,
		strlen(sock_data.pBuffer), 0);
		Sleep(10);
	}

	return sock_data.pBuffer;
}

void* RecieveThread(void *pInfo)
{
	SockInfo sock_data = *(SockInfo *)pInfo;
	int netStatus = 0;

	memset(sock_data.pBuffer, '\0', sock_data.buffer_len);
	netStatus = recv(sock_data.sock, sock_data.pBuffer,
	sock_data.buffer_len, 0);
	if (netStatus < 0)
	{
		memset(sock_data.pBuffer, '\0', sock_data.buffer_len);
		strcpy(sock_data.pBuffer, Server_Ubind);
		pthread_exit(NULL);
		return pInfo;
	}
	if (strcmp(sock_data.pBuffer, Recieve_OK) != 0
			&& sock_data.pBuffer != NULL)
	{
		printf("\nServer : %s\n", sock_data.pBuffer);
		printf(Input_Str);
	}
	Sleep(10);
	// send(sock_data.sock, Recieve_OK, strlen(Recieve_OK), 0);
	Sleep(10);

	pthread_exit(NULL);

	return pInfo;
}
