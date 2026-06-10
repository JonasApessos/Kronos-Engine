#pragma once

#include <chrono>
#include <vector>

#include "Primitives.h"

using namespace std::literals;

using std::chrono::time_point, std::chrono::high_resolution_clock;
using std::chrono::duration, std::chrono::duration_cast;
using std::vector;

using KronosPrim::uint64, KronosPrim::int8;

class Timer;

/** @struct SInfoTimer
*   @brief Structure helper for timer manager class with support for signal
callback*/
struct SInfoTimer
{
    uint64 iHashID = 0;
    char* cName = nullptr;
    Timer* rTimer = nullptr;
    void (*rCallback)() = nullptr;
};

/** @class Timer
*   @brief Timer object used for simple time tracking using highest possible
resolution*/
class Timer
{
public:
    bool bRunOnce = false;
    bool bAutostart = true;

    Timer();
    Timer(bool InbRunOnce, bool InbAutostart);

    inline void Start();
    inline void End();
    inline time_point<high_resolution_clock> GetStart();
    inline time_point<high_resolution_clock> GetEnd();
    inline duration<double> GetElapsedTime();

protected:

private:
    time_point<high_resolution_clock> iStart, iEnd;

    high_resolution_clock rClock;
};

inline void Timer::Start() { iStart = rClock.now(); }
inline void Timer::End() { iEnd = rClock.now(); }

inline time_point<high_resolution_clock> Timer::GetStart() { return iStart; }
inline time_point<high_resolution_clock> Timer::GetEnd() { return iEnd; }
inline duration<double> Timer::GetElapsedTime()
{
    End();

    return duration<double>(iEnd - iStart);
}


/** @class ManagerTimer
*   @brief Singleton class that manages timers with signal callback using SInfoTimer helper struct
*	@todo handle timers
*   @todo support callback signal
*   @todo compensate execution time for correct timing execution*/
class ManagerTimer
{
    public:
        int8 Queue(SInfoTimer & InrInfoTimer);

        void ExecQueue();

    protected:

    private:
        vector<SInfoTimer> rQueueTimers;

        uint64 GenerateHash();
};
