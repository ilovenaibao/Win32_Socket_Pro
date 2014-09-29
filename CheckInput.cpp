#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <conio.h>

#include "CheckInput.h"

void CheckMainInput(int argc, char **argv, char *pIpAddr, int *pport)
{
	switch (argc)
	{
		case 3:
		strcpy(pIpAddr, argv[1]);
		CheckInputPort(argv[2], pport);
		break;
		default:
		SetNewMainInput(pIpAddr, pport);
		break;
	}
}

void SetNewPort(int *pport)
{
	char *pTmpPort = NULL;
	
	pTmpPort = (char *)malloc(sizeof(char) * IP_LEN);
	memset(pTmpPort, '\0', IP_LEN);

	printf("Please input port number:\n");
	printf("Port :");
	scanf("%s", pTmpPort);
	CheckInputPort(pTmpPort, pport);
	
	free(pTmpPort);
	pTmpPort = NULL;
}

void SetNewMainInput(char *pIpAddr, int *pport)
{
	char *pTmpPort = NULL;
	
	pTmpPort = (char *)malloc(sizeof(char) * IP_LEN);
	memset(pTmpPort, '\0', IP_LEN);

	printf("Please input Ip and port number:\n");
	printf("Ip :");
	scanf("%s", pIpAddr);
	printf("Port :");
	scanf("%s", pTmpPort);
	CheckInputPort(pTmpPort, pport);
	
	free(pTmpPort);
	pTmpPort = NULL;
}

void CheckInputPort(char *pBuffer, int *pport)
{
	int bufferLen = 0;
	int bufferCount = 0;
	int multiplier = 1;
	
	*pport = 0;
	bufferLen = strlen(pBuffer);	
	for (bufferCount = bufferLen - 1; bufferCount >= 0; bufferCount--)
	{
		*pport += (pBuffer[bufferCount] - 48) * multiplier;
		multiplier *= 10;
	}
}