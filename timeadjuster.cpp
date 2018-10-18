#include "timeadjuster.h"
#include "time.h"
#include "sys/time.h"
#include "iostream"
#include "math.h"
#include "log.h"
#include "common.h"

using namespace std;

TimeAdjuster::TimeAdjuster()
{

}

bool TimeAdjuster::isInAdjustRange(int zeroProtectRange){
    time_t tm,tm_start,tm_end;
    struct tm * tm_ptr;
    time(&tm);
    tm_ptr=localtime(&tm);
    //set zero time of day
    tm_ptr->tm_hour=23;
    tm_ptr->tm_min=59;
    tm_ptr->tm_sec=60;
    tm_end=mktime(tm_ptr);
    //set satrt time of day
    tm_ptr->tm_hour=0;
    tm_ptr->tm_min=0;
    tm_ptr->tm_sec=0;
    tm_start=mktime(tm_ptr);
    //compare
    if((fabs(difftime(tm, tm_start))<zeroProtectRange)||(fabs(difftime(tm, tm_end))<zeroProtectRange)){
        return true;
    }
    else{
        //cout<<"out range"<<endl;
        return false;
    }
}


void TimeAdjuster::Adjust(TimeInformation *timeInfo){
    struct tm ts;
    struct timeval tv;
    ts.tm_year=timeInfo->Year-1900;
    ts.tm_mon=timeInfo->Month-1;
    ts.tm_mday=timeInfo->Day;
    ts.tm_hour=timeInfo->Hour;
    ts.tm_min=timeInfo->Minute;
    ts.tm_sec=timeInfo->Second;
    tv.tv_sec=mktime(&ts);
    tv.tv_usec=timeInfo->MSecond*1000;
    if(settimeofday(&tv,(struct timezone*)0)<0){
        Log::RaiseLogInfo(Error,"调整本机系统时间错误！");
    }
    else{
        //cout<<"setting time ok."<<endl;
    }
}


void TimeAdjuster::Adjust(TimeInformation *timeInfo,int zeroProtectRange){
    if(this->isInAdjustRange(zeroProtectRange)){
        Log::RaiseLogInfo(Warning,"不在安全的校时区间。");
    }else{
        this->Adjust(timeInfo);
    }
}
