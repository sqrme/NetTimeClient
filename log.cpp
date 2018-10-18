#include "log.h"
#include "QQueue"
#include "stdio.h"
#include "time.h"

Log::Log()
{
}


    QQueue<LogInfo>  * Log::logInfoQueue= new QQueue<LogInfo>;

void Log::RaiseLogInfo(LogInfoType infoType, string infoBody){
    time_t now;
    struct tm* tm_now;
    time(&now);
    tm_now=localtime(&now);
    QString dateStr=QString::number(tm_now->tm_year+1990)+"-"+QString::number(tm_now->tm_mon)+"-"+QString::number(tm_now->tm_mday);
    QString timeStr=QString::number(tm_now->tm_hour)+":"+QString::number(tm_now->tm_min)+":"+QString::number(tm_now->tm_sec);
    logInfoQueue->enqueue(LogInfo{dateStr+timeStr,infoType,QString::fromStdString(infoBody)});
    if(logInfoQueue->count()>=MAXLOGCOUNT){
        logInfoQueue->clear();
    }
}

bool Log::GetLogInfo(LogInfo & logInfo){
    bool ret;
    if(!logInfoQueue->isEmpty()){
        logInfo=logInfoQueue->dequeue();
        ret= true;
    }else{
        ret= false;
    }
    return ret;
}
