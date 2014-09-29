#ifndef _CHECK_IN_PUT_H_
#define _CHECK_IN_PUT_H_


#define BUILD_SERVER    1
#define BUILD_CLIENT    0

//add define
#define IP_LEN 100

//add struct


//add func
void CheckMainInput(int argc, char **argv, char *pIpAddr, int *pport);
void SetNewPort(int *pport);
void SetNewMainInput(char *pIpAddr, int *pport);
void CheckInputPort(char *pBuffer, int *pport);



#endif
