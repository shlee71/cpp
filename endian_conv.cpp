/* 
 * endian_conv.cpp
 * h : host byte order,  n : network byte order
 * s : short ( 16 bit), l : long ( 32bit )
 */

 #include <stdio.h>
 #include <stdlib.h>
 #include <string.h>
 #include <winsock2.h>

 int main( int argc, char **argv)
 {
 	WSADATA wsaData;
     short host_port_order = 0x1234;
     short net_port_order;

     long host_addr_order = 0x12345678;
     long net_addr_order;
     
     if (WSAStartup(MAKEWORD(2,2), &wsaData) != 0) /* Load Winsock 2.2 DLL */
     	printf("WSAStartup() error!");

     net_port_order = htons(host_port_order);
     net_addr_order = htonl(host_addr_order);

     printf(" Host ordered port : %x \n", host_port_order);
     printf(" Network ordered prot : %x \n", net_port_order);

     printf(" Host ordered Address : %x \n", host_addr_order);
     printf(" Network ordered Address : %x \n", net_addr_order);

     return 0;

 }
