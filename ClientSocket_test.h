#ifndef _CLIENT_SOCKET_H_
#define _CLIENT_SOCKET_H_


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
int ClientSocket(char *pIpAddr, int port);
void* SendThread(void *pInfo);
void* RecieveThread(void *pInfo);




#endif
