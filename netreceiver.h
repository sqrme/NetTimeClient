#include "nettimeclient.h"
#include <string>
#include "sys/socket.h"
#include <sys/types.h>
#include <sys/time.h>
#include <sys/ioctl.h>
#include "netinet/in.h"
#include "netdb.h"
#include "stdio.h"
#include "unistd.h"
#include "stdlib.h"
#include "string.h"
#include "nettimeclient.h"
#include "common.h"

using namespace std;

#ifndef NETRECEIVER_H
#define NETRECEIVER_H


class NetReceiver
{
    struct sockaddr_in localSock;
    ip_mreq_source group;
    int sockfd;
    bool socketReady;
    TimeInformation *timeInfo;
    char readBuffer[1000];
    timeval timeOut;
    void ParseTimePacket();
public:
    NetReceiver(string localIP, string receiveIP,string sourceIP, int port, TimeInformation *timeInfo);
    void StartReceiving();
};

#endif // NETRECEIVER_H
