#include <iostream>
#include <string.h>
#include <QQueue>
using namespace std;

#ifndef LOG_H
#define LOG_H


#define MAXLOGCOUNT 1000

enum LogInfoType{Info,Warning,Error};
struct LogInfo{
    QString time;
    LogInfoType infoType;
    QString infoBody;
};

class Log
{
private:
    static QQueue<LogInfo> *logInfoQueue;
public:    
    Log();
    static void RaiseLogInfo(LogInfoType infoType,string infoBody);
    static bool GetLogInfo(LogInfo &logInfo);
};

#endif // LOG_H
