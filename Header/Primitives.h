#pragma once

#include <stdint.h>
#include <error.h>

/** \namespace KronosPrim
* 	\brief namespace containing primitives*/
namespace KronosPrim
{

	typedef uint8_t uint8; //!< unsigned integer of size 1 byte
	typedef uint16_t uint16; //!< unsigned integer of size 2 byte
	typedef uint32_t uint32; //!< unsigned integer of size 4 byte
	typedef uint64_t uint64; //!< unsigned integer of size 8 byte
	typedef __uint128_t uint128; //!< unsigned integer of size 16 byte

	typedef int8_t int8; //!< integer of size 1 byte
	typedef int16_t int16; //!< integer of size 2 byte
	typedef int32_t int32; //!< integer of size 4 byte
	typedef int64_t int64; //!< integer of size 8 byte
	typedef __int128_t int128; //!< integer of size 16 byte

	/** \struct SFloatQuarter 
	* \brief struct to support full floating point precision of 1 by 1 byte
	* \warning EXPERIMENTAL*/
	//----<THIS IS FOR FUTURE TESTING, DO NOT USE>----//
	struct SFloatQuarter
	{
		bool sign; //!< Flag for positive or negative value
		uint8 exponent; //!< floating point exponent
		uint8 decimal; //!< floating point decimal
	};

	/** \struct SFloatHalf
	* \brief struct to support full floating point precision of 2 by 2 byte
	* \warning EXPERIMENTAL*/
	//----<THIS IS FOR FUTURE TESTING, DO NOT USE>----//
	struct SFloatHalf
	{
		bool sign; //!< Flag for positive or negative value
		uint16 exponent; //!< floating point exponent
		uint16 decimal; //!< floating point decimal
	};

	/** \struct SFloat
	* \brief struct to support full floating point precision of 4 by 4 byte
	* \warning EXPERIMENTAL*/
	//----<THIS IS FOR FUTURE TESTING, DO NOT USE>----//
	struct SFloat
	{
		bool sign; //!< Flag for positive or negative value
		uint32 exponent; //!< floating point exponent
		uint32 decimal; //!< floating point decimal
	};

	/** \struct SDouble
	* \brief struct to support full floating point precision of 8 by 8 byte
	* \warning EXPERIMENTAL*/
	//----<THIS IS FOR FUTURE TESTING, DO NOT USE>----//
	struct SDouble
	{
		bool sign; //!< Flag for positive or negative value
		uint64 exponent; //!< floating point exponent
		uint64 decimal; //!< floating point decimal
	};

	/** \struct SQuad
	* \brief !EXPERIMENTAL struct to support full floating point precision of 16 by 16 byte
	* \warning EXPERIMENTAL*/
	//----<THIS IS FOR FUTURE TESTING, DO NOT USE>----//
	struct SQuad
	{
		bool sign; //!< Flag for positive or negative value
		uint128 exponent; //!< floating point exponent
		uint128 decimal; //!< floating point decimal
	};
}