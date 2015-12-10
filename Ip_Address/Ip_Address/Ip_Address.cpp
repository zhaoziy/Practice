// Ip_Address.cpp : 定义控制台应用程序的入口点。
//

#include "stdafx.h"
#include <winsock2.h>
#include <string>

using namespace std;

#define bzero(a, b) memset(a, 0, b)

bool getPublicIp(string& ip)
{
	int    sock;
	char **pptr = NULL;
	struct sockaddr_in    destAddr;
	struct hostent    *ptr = NULL;
	char destIP[128];

	sock = socket(AF_INET, SOCK_STREAM, 0);
	if (-1 == sock) {
		perror("creat socket failed");
		return false;
	}
	bzero((void *)&destAddr, sizeof(destAddr));
	destAddr.sin_family = AF_INET;
	destAddr.sin_port = htons(80);
	ptr = gethostbyname("www.ip138.com");
	if (NULL == ptr) 
	{
		perror("gethostbyname error");
		return false;
	}
	for (pptr = ptr->h_addr_list; NULL != *pptr; ++pptr) 
	{
		//inet_ntop(ptr->h_addrtype, *pptr, destIP, sizeof(destIP));
		printf("addr:%s\n", destIP);
		ip = destIP;
		return true;
	}
	return true;
}

int main()
{
	string a;
	getPublicIp(a);
    return 0;
}

