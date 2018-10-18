#include "nettimeclient.h"
#include "netreceiver.h"
#include "configinfo.h"
#include "pthread.h"
#include "iostream"
#include "log.h"
#include "common.h"

using  namespace std;

NetTimeClient::NetTimeClient()
{
    this->timeInfo=new TimeInformation{0,0,0,0,0,0,0,0,false,0,false,0,false,0,false,0,false,0,false};
}

void* NetTimeClient::timeReceiveThread(void *args){
    int res=pthread_setcancelstate(PTHREAD_CANCEL_ENABLE,NULL);
        if(res!=0){
            Log::RaiseLogInfo(Error,"线程可取消属性配置错误。");
            exit(EXIT_FAILURE);
        }

        res=pthread_setcanceltype(PTHREAD_CANCEL_DEFERRED,NULL);
        if(res!=0){
            Log::RaiseLogInfo(Error,"线程可取消类型配置错误!");
            exit(EXIT_FAILURE);
        }

        ConfigInfo * configInfo=new ConfigInfo();
        if(configInfo->LoadConfig(TIMESERVERCONFIGURE)){
            string localIP=configInfo->getLocalIP();
            string recvIP=configInfo->getSendIP();
            string sourceIP=configInfo->getSourceIP();
            int port=configInfo->getPort();
            TimeInformation * timeInfo=(TimeInformation*) args;
            NetReceiver* netReciver=new NetReceiver(localIP,recvIP,sourceIP,port,timeInfo);
            Log::RaiseLogInfo(Info,"网络时统客户端启动！");
            netReciver->StartReceiving();
        }
        else{
            Log::RaiseLogInfo(Error,"配置文件载入错误！");
        }
}

void NetTimeClient::Run(){
    int res=pthread_create(&this->timeRecvThread,NULL,timeReceiveThread,this->timeInfo);
        if(res!=0){
            Log::RaiseLogInfo(Error,"线程创建失败！");
        }
}

bool NetTimeClient::GetTime(TimeInformation *timeInfo){
    if(this->timeInfo->Year!=0){
         *timeInfo=*this->timeInfo;
        return true;
    }else{
        return false;
    }

}

void NetTimeClient::stop(){
    //cancel thread..
        int res=pthread_cancel(this->timeRecvThread);
        if(res!=0){
            Log::RaiseLogInfo(Error,"线程终止失败！");
        }
}
