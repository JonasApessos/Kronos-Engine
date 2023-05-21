#pragma once
#include <stdint.h>
#include <error.h>


namespace KronosPrim
{
#ifdef _WIN32
	#define ERRORCODE errno_t
#elif defined __linux__
	#define ERRORCODE error_t
#endif

	typedef uint8_t uint8;
	typedef uint16_t uint16;
	typedef uint32_t uint32;
	typedef uint64_t uint64;

	typedef int8_t int8;
	typedef int16_t int16;
	typedef int32_t int32;
	typedef int64_t int64;

	//----<THIS IS FOR FUTURE TESTING, DO NOT USE>----//
	struct FFloatQuarter
	{
		bool sign;
		uint8 exponent;
		uint8 decimal;
	};

	//----<THIS IS FOR FUTURE TESTING, DO NOT USE>----//
	struct FFloatHalf
	{
		bool sign;
		uint16 exponent;
		uint16 decimal;
	};

	//----<THIS IS FOR FUTURE TESTING, DO NOT USE>----//
	struct FFloat
	{
		bool sign;
		uint32 exponent;
		uint32 decimal;
	};

	//----<THIS IS FOR FUTURE TESTING, DO NOT USE>----//
	struct FDouble
	{
		bool sign;
		uint64 exponent;
		uint64 decimal;
	};
}