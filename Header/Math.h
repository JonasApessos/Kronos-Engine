#pragma once

#include <type_traits>

#include "Primitives.h"

#define PI_F 3.1415927f
#define QUARTER_PI_F PI_F * 0.25f
#define HALF_PI_F PI_F * 0.5f
#define TWO_PI_F PI_F * 2.f

#define PI 3.1415926535897932385
#define QUARTER_PI PI * 0.25
#define HALF_PI PI * 0.5
#define TWO_PI PI * 2.0

template<typename T>
inline T DegToRad(T InDeg) noexcept(true) { return (InDeg * HALF_PI) / 90.0; }

template<typename T>
inline T RadToDeg(T InRad) noexcept(true) { return (InRad * 90.0) / HALF_PI; }

template<typename T>
inline T SquarePow(T InBase) noexcept(true) { return InBase * InBase; }

template<typename T>
inline T CubicPow(T InBase) noexcept(true) { return InBase * InBase * InBase; }

template<typename T, typename C>
C Pow(C InBase, T InExponent) noexcept(true)
{ 
    T Index = 0;
    C Result = 1;
    
    while(Index < InExponent)
    { 
        Result = Result * InBase;

        ++Index;
    }
    
    return Result;
}

template<typename T>
T SquarePowShift(T InOffset)  noexcept(true)
{
    T iBase = 1;

    if(InOffset > sizeof(T) * 8 - 1)
        return iBase << sizeof(T) * 8 - 1;
    
    return iBase << InOffset; 
}