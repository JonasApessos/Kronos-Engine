#include <chrono>
#include <iostream>
#include "Primitives.h"

using namespace std::literals;

using std::chrono::time_point, std::chrono::high_resolution_clock;
using std::chrono::duration, std::chrono::duration_cast;

using KronosPrim::uint64, KronosPrim::int64;

class Timer
{
public:
    Timer();

    inline void Start();
    inline void End();

    //#TODO: a signal callback function
    void Signal();

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