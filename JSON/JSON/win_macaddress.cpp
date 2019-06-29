
#include <winsock2.h> // htons() htonl() and other helper functions
#pragma comment(lib, "WS2_32.lib")
#include <Iphlpapi.h> // Used to find information about the device such as default gateway and hardware addresses

#include <windows.h>
#pragma comment(lib, "Iphlpapi.lib")
#include <iostream>
#include <stdio.h>   
/*#include <sys/socket.h>  */ 
/*#include <netinet/in.h>   
#include <arpa/inet.h>  */ 
#include <string.h>  
#include <winsock.h>
int showmac()
{
    ULONG MAC[2], size = 6;
    LPBYTE buffer;
    char data[20];
    /*
            1 > win_macaddress.cpp(16)
        : error C4996 : 'inet_addr' : Use inet_pton() or
        InetPton() instead or
        define _WINSOCK_DEPRECATED_NO_WARNINGS to disable deprecated API warnings
       inet_aton() 转换网络主机地址ip(如192.168.1.10)为二进制数值
	*/

    //in_addr address;
    //inet_aton("192.168.1.10", &address);
    //if (SendARP(address, 0, MAC, &size) == NO_ERROR)
    if (SendARP(inet_addr("192.168.1.10"), 0, MAC, &size) == NO_ERROR)
    {
        buffer = (LPBYTE)MAC;

        // access the address one byte at a time
        sprintf_s(
            data, "%02X:%02X:%02X:%02X:%02X:%02X", buffer[0], buffer[1], buffer[2], buffer[3], buffer[4], buffer[5]);
    }
    std::cout << data << std::endl;
    return 0;
}