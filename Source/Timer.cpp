#include "Timer.h"

Timer::Timer() {}

Timer::Timer(bool InbRunOnce, bool InbAutostart) : bRunOnce(InbRunOnce), bAutostart(InbAutostart)
{
    if(bAutostart)
        iStart = rClock.now();
}




int8 ManagerTimer::Queue(SInfoTimer & InrInfoTimer)
{
    InrInfoTimer.iHashID = GenerateHash();

    rQueueTimers.push_back(InrInfoTimer);
    return 0;
}


void ManagerTimer::ExecQueue()
{
    for (size_t i = 0; i < rQueueTimers.size(); i++)
    {
        if (rQueueTimers[0].rCallback != nullptr)
            rQueueTimers[0].rCallback();
    }
}

uint64 ManagerTimer::GenerateHash()
{
    return 0;
}
