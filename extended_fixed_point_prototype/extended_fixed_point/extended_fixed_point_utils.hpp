#ifndef EXTENDED_FIXED_POINT_UTILS_HPP
#define EXTENDED_FIXED_POINT_UTILS_HPP

#include <cstdint>
#include "extended_fixed_point_conversion.hpp"

// ----------------------------------------------------------------------------
// 32 VS 64 BIT ARCHITECTURE CHECK
// ----------------------------------------------------------------------------

// Check windows
#if _WIN32 || _WIN64
#if _WIN64
#define _IS64bit 1
#else
#define _IS32bit 1
#endif
#endif

// Check GCC
#if __GNUC__
#if __x86_64__ || __ppc64__
#define _IS64bit 1
#else
#define _IS32bit 1
#endif
#endif

#ifdef _MIOSIX
#  define _FIXED_POINT_REDEFINE_INT_TYPES_ true
#else
#  define _FIXED_POINT_REDEFINE_INT_TYPES_ false
#endif // miosix specific case

template<typename raw_t, int16_t INT_BITS, int16_t FRAC_BITS, int16_t INT_BITS_NEW, int16_t FRAC_BITS_NEW>
struct TypeConverter {
public:

	raw_t raw;

	static_assert(!((INT_BITS > 0 && FRAC_BITS < 0 && INT_BITS_NEW < 0 && FRAC_BITS_NEW > 0) ||
				    (INT_BITS < 0 && FRAC_BITS > 0 && INT_BITS_NEW > 0 && FRAC_BITS_NEW < 0)),
					 "The conversion erases the raw value of the extended fixed point");

	TypeConverter(int8_t raw) : raw(raw) {}

	TypeConverter(int16_t raw) : raw(raw) {}
	
	TypeConverter(int32_t raw) : raw(raw) {}
	
	TypeConverter(int64_t raw) : raw(raw) {}
	
	#ifdef _IS64bit
	TypeConverter(__int128 raw) : raw(raw) {}
	#endif

	raw_t convert() const {
		Converter<raw_t> *converter = nullptr;

		if(INT_BITS >= 0 && FRAC_BITS >= 0 && INT_BITS_NEW >= 0 && FRAC_BITS_NEW >= 0)   
			converter = new ConverterPPPP<raw_t>(FRAC_BITS, FRAC_BITS_NEW);
		else if(INT_BITS >= 0 && FRAC_BITS >= 0 && INT_BITS_NEW >= 0 && FRAC_BITS_NEW < 0) 
			converter = new ConverterPPPN<raw_t>(FRAC_BITS, std::abs(FRAC_BITS_NEW));
		else if(INT_BITS >= 0 && FRAC_BITS >= 0 && INT_BITS_NEW < 0 && FRAC_BITS_NEW >= 0) 
			converter = new ConverterPPNP<raw_t>(FRAC_BITS, std::abs(INT_BITS_NEW) + FRAC_BITS_NEW);
		else if(INT_BITS >= 0 && FRAC_BITS < 0 && INT_BITS_NEW >= 0 && FRAC_BITS_NEW >= 0) 
			converter = new ConverterPNPP<raw_t>(FRAC_BITS, FRAC_BITS_NEW);
		else if(INT_BITS >= 0 && FRAC_BITS < 0 && INT_BITS_NEW >= 0 && FRAC_BITS_NEW < 0) 
			converter = new ConverterPNPN<raw_t>(std::abs(FRAC_BITS), std::abs(FRAC_BITS_NEW));
		else if(INT_BITS < 0 && FRAC_BITS >= 0 && INT_BITS_NEW >= 0 && FRAC_BITS_NEW >= 0)
			converter = new ConverterNPPP<raw_t>(std::abs(INT_BITS) + FRAC_BITS, FRAC_BITS_NEW);
		else 
			converter = new ConverterNPNP<raw_t>(std::abs(INT_BITS) + FRAC_BITS, std::abs(INT_BITS_NEW) + FRAC_BITS_NEW);

		return converter -> convert(raw);
	}
};

//-----------------------------------------------------------------------------
// LENGHT RELATED TEMPLATE HELPERS
//-----------------------------------------------------------------------------

// This is a dummy type which means there are too many bits in the data type
struct TooManyBits;

// \return smallest signed integer type with at least BITS bit width
template <uint16_t BITS>
struct get_int_with_length
{
	// The default is that an integer with N bits can be represented
	// by an integer with N+1 bits
	typedef typename get_int_with_length<BITS+1>::RESULT RESULT;
};

template <> struct get_int_with_length<7>   { typedef int8_t RESULT; };

template <> struct get_int_with_length<15>  { typedef int16_t RESULT; };

template <> struct get_int_with_length<31>  { typedef int32_t RESULT; };

template <> struct get_int_with_length<63>  { typedef int64_t RESULT; };

#ifdef _IS64bit
template <> struct get_int_with_length<127> { typedef __int128 RESULT; };
#endif

// early stop
template <> struct get_int_with_length<256> { typedef TooManyBits RESULT; };

// avoid compilation segfault
template <> struct get_int_with_length<65535> { typedef TooManyBits RESULT; };


#endif /* end of include guard: EXTENDED_FIXED_POINT_UTILS_HPP */

/*

	// All these functions to be moved in their subclasses
	void shift_raw_PPPP() {
		bool sh_dir_right = FRAC_BITS > FRAC_BITS_NEW;

		if(sh_dir_right) 
			raw >>= FRAC_BITS - FRAC_BITS_NEW;
		else
			raw <<= FRAC_BITS_NEW - FRAC_BITS;
	}

	void shift_raw_PPPN() {
		raw >>= FRAC_BITS + FRAC_BITS_NEW;
	}

	void shift_raw_PPNP() {
		bool sh_dir_right = FRAC_BITS > std::abs(INT_BITS_NEW) + FRAC_BITS_NEW; 

		if(sh_dir_right) 
			raw >>= FRAC_BITS - (std::abs(INT_BITS_NEW) + FRAC_BITS_NEW);
		else
			raw <<= (std::abs(INT_BITS_NEW) + FRAC_BITS_NEW) - FRAC_BITS;
	}

	void shift_raw_PNPP() {
		raw <<= FRAC_BITS + FRAC_BITS_NEW;
	}

	void shift_raw_PNPN() {
		bool sh_dir_right = std::abs(FRAC_BITS) > std::abs(FRAC_BITS_NEW);

		if(sh_dir_right) 
			raw >>= std::abs(FRAC_BITS) - std::abs(FRAC_BITS_NEW);
		else
			raw <<= std::abs(FRAC_BITS_NEW) - std::abs(FRAC_BITS);
	}

	void shift_raw_NPPP() {
		bool sh_dir_right = std::abs(INT_BITS) + FRAC_BITS < FRAC_BITS_NEW;

		if(sh_dir_right)
			raw >>= FRAC_BITS_NEW - (std::abs(INT_BITS) + FRAC_BITS);
		else
			raw <<= (std::abs(INT_BITS) + FRAC_BITS) - FRAC_BITS_NEW;
	}

	void shift_raw_NPNP() {
		bool sh_dir_right = std::abs(INT_BITS) + FRAC_BITS > std::abs(INT_BITS_NEW) + FRAC_BITS_NEW;

		if(sh_dir_right)
			raw >>= (std::abs(INT_BITS) + FRAC_BITS) - (std::abs(INT_BITS_NEW) + FRAC_BITS_NEW);
		else
			raw <<= (std::abs(INT_BITS_NEW) + FRAC_BITS_NEW) - (std::abs(INT_BITS) + FRAC_BITS);
	}*/