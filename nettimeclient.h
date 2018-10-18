#include "pthread.h"
#include "common.h"
#ifndef NETTIMECLIENT_H
#define NETTIMECLIENT_H



class NetTimeClient
{
    TimeInformation * timeInfo;
    pthread_t timeRecvThread;
    static void * timeReceiveThread(void *);
public:
    NetTimeClient();
    void Run();
    void stop();
    bool GetTime(TimeInformation *timeInfo);
};

#endif // NETTIMECLIENT_H
