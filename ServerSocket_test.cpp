//#include <winsock2.h>
//#include <windef.h>
//#include <stdio.h>
//#include <conio.h>
//#include <pthread.h>
//
//#include "ServerSocket_test.h"
//#include "CheckInput.h"
//
//int main(int argc, char **argv)
//{
//	int port = 0;
//	char *pIpAddr = NULL;
//
//	pIpAddr = (char *)malloc(sizeof(char) * IP_LEN);
//	memset(pIpAddr, '\0', IP_LEN);
//	SetNewPort(&port);
//	// CheckMainInput(argc, argv, pIpAddr, &port);
//	ServerSocket(pIpAddr, port);
//
//	free(pIpAddr);
//	pIpAddr = NULL;
//
//	return 0;
//}
//
//int ServerSocket(char *pIpAddr, int port)
//{
//	WSADATA wsaData;
//	SOCKET ListeningSocket;
//	SOCKET NewConnection;
//	SOCKADDR_IN server_addr;
//	SOCKADDR_IN link_addr;
//	int link_addr_len = 0;
//	int netStatus = 0;
//	char *pBuffer = NULL;
//	int buffer_len = 1024;
//	// char welcome_msg[] = "Server recieve ok\n";
//
//	pthread_t recieve_thread_id;
//	pthread_t send_thread_id;
//	int recieve_thread_ret = 0;
//	int send_thread_ret = 0;
//	SockInfo sock_data;
//
//
//	//初始化Windows Socket2.2
//	netStatus = WSAStartup((WORD)0x0202, (LPWSADATA)&wsaData);
//	if (netStatus != 0)
//	{
//		printf("error : netStatus = %d\n", netStatus);
//		getch();
//		return -1;
//	}
//
//	//創建一個新的Socket來響應客戶端的請求
//	ListeningSocket = socket(AF_INET, SOCK_STREAM, IPPROTO_TCP);
//
//	//填寫服務器地址信息
//	//端口為port
//	//IP地址為INADDR_ANY, 注意使用htonl將IP地址轉換為網絡格式
//	memset(&server_addr, 0x00, sizeof(server_addr));
//	server_addr.sin_family = AF_INET;
//	server_addr.sin_port = htons(port);
//	server_addr.sin_addr.s_addr = htonl(INADDR_ANY);
//	// server_addr.sin_addr.s_addr = inet_addr(pIpAddr);
//
//	//綁定監聽端口
//	if (bind(ListeningSocket, (SOCKADDR *)&server_addr,
//				sizeof(server_addr)) == SOCKET_ERROR)
//	{
//		printf("Error: %d\n", WSAGetLastError());
//		closesocket(ListeningSocket);
//		WSACleanup();
//		getch();
//		return -1;
//	}
//
//	//開始監聽，制定最大同時連接數為1
//	if (listen(ListeningSocket, 1) < 0)
//	{
//		printf("listen faile: %s \n", strerror(errno));
//		closesocket(ListeningSocket);
//		WSACleanup();
//		getch();
//		return -1;
//	}
//
//	pBuffer = (char *)malloc(sizeof(char) * buffer_len);
//	memset(pBuffer, '\0', buffer_len);
//
//	link_addr_len = sizeof(link_addr);
//	memset(&link_addr, 0x00, link_addr_len);
//	NewConnection = accept(ListeningSocket,
//	(struct sockaddr *)&link_addr, &link_addr_len);
//
//	sock_data.sock = NewConnection;
//	sock_data.pBuffer = pBuffer;
//	sock_data.buffer_len = buffer_len;
//
//	send_thread_ret = pthread_create(&send_thread_id, NULL,
//	SendThread,
//	&sock_data);
//
//	while (1)
//	{
//		recieve_thread_ret = pthread_create(&recieve_thread_id, NULL,
//		RecieveThread,
//		&sock_data);
//
//		if (strcmp(sock_data.pBuffer, Client_Ubind) == 0)
//		{
//			printf("%s\n", sock_data.pBuffer);
//			// getch();
//			break;
//		}
//	}
//
//	free(pBuffer);
//	pBuffer = NULL;
//	closesocket(NewConnection);
//	closesocket(ListeningSocket);
//
//	WSACleanup();
//
//	return 0;
//}
//
//void* SendThread(void *pInfo)
//{
//	SockInfo sock_data = *(SockInfo *)pInfo;
//
//	while (1)
//	{
//		printf(Input_Str);
//		memset(sock_data.pBuffer, '\0', sock_data.buffer_len);
//		scanf("%s", sock_data.pBuffer);
//		send(sock_data.sock, sock_data.pBuffer,
//		strlen(sock_data.pBuffer), 0);
//		Sleep(10);
//	}
//
//	return sock_data.pBuffer;
//}
//
//void* RecieveThread(void *pInfo)
//{
//	SockInfo sock_data = *(SockInfo *)pInfo;
//	int netStatus = 0;
//
//	memset(sock_data.pBuffer, '\0', sock_data.buffer_len);
//	netStatus = recv(sock_data.sock, sock_data.pBuffer,
//	sock_data.buffer_len, 0);
//	if (netStatus < 0)
//	{
//		memset(sock_data.pBuffer, '\0', sock_data.buffer_len);
//		strcpy(sock_data.pBuffer, Client_Ubind);
//		pthread_exit(NULL);
//		return pInfo;
//	}
//	if (strcmp(sock_data.pBuffer, Recieve_OK) != 0
//			&& sock_data.pBuffer != NULL)
//	{
//		printf("\nClient : %s\n", sock_data.pBuffer);
//		printf(Input_Str);
//	}
//	Sleep(10);
//	// send(sock_data.sock, Recieve_OK, strlen(Recieve_OK), 0);
//	Sleep(10);
//
//	pthread_exit(NULL);
//
//	return pInfo;
//}
//
//void GetIp()
//{
//	HOSTENT *host = gethostbyname("www.baidu.com");
//	IN_ADDR addr;
//
//	if (host != NULL)
//	{
//		for (int i = 0; host->h_addr_list[i] != NULL; i++)
//		{
//			memset(&addr, 0, sizeof(addr));
//			memcpy(&addr.S_un.S_addr,
//			host->h_addr_list[i],
//			host->h_length);
//
//			printf("%s: %s\n", host->h_name, inet_ntoa(addr));
//		}
//	}
//	else
//	{
//		printf("host is NULL\n");
//	}
//}
