#ifndef _SERVER_SOCKET_TEST_H_
#define _SERVER_SOCKET_TEST_H_


//add define
#define Input_Str ("Input string:")
#define Recieve_OK ("recieve ok")
#define Send_OK ("send ok")
#define Server_Ubind ("server is unbind...")
#define Client_Ubind ("client is unbind...")

//add struct
typedef struct sock_info
{
	SOCKET sock;
	char *pBuffer;
	int buffer_len;
}SockInfo;

//add func
int ServerSocket(char *pIpAddr, int port);
void* SendThread(void *pInfo);
void* RecieveThread(void *pInfo);
void GetIp();




#endif
