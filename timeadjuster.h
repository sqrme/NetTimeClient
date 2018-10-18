#include "configinfo.h"
#include "common.h"

#ifndef TIMEADJUSTER_H
#define TIMEADJUSTER_H

class TimeAdjuster
{
    bool isInAdjustRange(int zeroProtectRange);
public:
    TimeAdjuster();
    void Adjust(TimeInformation *timeInfo);
    void Adjust(TimeInformation * timeInfo,int zeroProtectRange);
};

#endif // TIMEADJUSTER_H
