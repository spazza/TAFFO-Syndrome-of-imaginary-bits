#ifndef EXTENDED_FIXED_POINT_UTILS_HPP
#define EXTENDED_FIXED_POINT_UTILS_HPP

#include <cstdint>

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

template <> struct get_int_with_length<8>   { typedef int8_t RESULT; };

template <> struct get_int_with_length<16>  { typedef int16_t RESULT; };

template <> struct get_int_with_length<32>  { typedef int32_t RESULT; };

template <> struct get_int_with_length<64>  { typedef int64_t RESULT; };

#ifdef _IS64bit
template <> struct get_int_with_length<128> { typedef __int128 RESULT; };
#endif

// early stop
template <> struct get_int_with_length<256> { typedef TooManyBits RESULT; };

// avoid compilation segfault
template <> struct get_int_with_length<65535> { typedef TooManyBits RESULT; };

//-----------------------------------------------------------------------------
// CONVERSION TEMPLATES
//-----------------------------------------------------------------------------

/**
 * \brief Structure to allow the conversion at compile time. Seven possible types of conversions are possible, 
 * the others are not considered because the value is erased during conversion. The conversion works shifting 
 * the value on left or right depending on the output type.
 * 
 * \tparam src_t source type of the value
 * \tparam dst_t destination type, the value is transformed into this type
 * \tparam int_bits number of integer bits of the source value
 * \tparam frac_bits number of fractional bits of the source value
 * \tparam int_bits_new number of integer bits of the destination value
 * \tparam frac_bits_new number of fractional bits of the destination value
 * \tparam intPos true if int_bits > 0, otherwise false
 * \tparam fracPos true if frac_bits > 0, otherwise false
 * \tparam intNewPos true if int_bits_new > 0, otherwise false
 * \tparam fracNewPos true if frac_bits_new > 0, otherwise false
 */
template<typename src_t, typename dst_t, int16_t int_bits, int16_t frac_bits, int16_t int_bits_new, int16_t frac_bits_new, bool intPos, bool fracPos, bool intNewPos, bool fracNewPos>
struct convert_fixed_point {
	static dst_t exec(src_t src, uint16_t &raw_reminder);
};

// From (INT_BITS > 0, FRAC_BITS > 0) to (INT_BITS > 0, FRAC_BITS > 0)

template<typename src_t, typename dst_t, int16_t int_bits, int16_t frac_bits, int16_t int_bits_new, int16_t frac_bits_new>
struct convert_fixed_point<src_t, dst_t, int_bits, frac_bits, int_bits_new, frac_bits_new, true, true, true, true> {
	/**
	 * @brief 
	 * 
	 * @param src source value type src_t
	 * @param raw_reminder 
	 * @return dst_t 
	 */
	static dst_t exec(src_t src, uint16_t &raw_reminder) {
		if(frac_bits > frac_bits_new) {
			src_t intermediate = src;
			uint32_t sha = frac_bits - frac_bits_new;
			intermediate >>= sha;
			return static_cast<dst_t>(intermediate); 
		} else {
			dst_t intermediate = static_cast<dst_t>(src);
			uint32_t sha = frac_bits_new - frac_bits;
			intermediate <<= sha;
			return intermediate;
		} 
	}
}; 

// From (INT_BITS > 0, FRAC_BITS > 0) to (INT_BITS > 0, FRAC_BITS < 0)

template<typename src_t, typename dst_t, int16_t int_bits, int16_t frac_bits, int16_t int_bits_new, int16_t frac_bits_new>
struct convert_fixed_point<src_t, dst_t, int_bits, frac_bits, int_bits_new, frac_bits_new, true, true, true, false> {
	static dst_t exec(src_t src, uint16_t &raw_reminder) {
		src_t intermediate = src;
		uint32_t sha = frac_bits + abs(frac_bits_new);
		intermediate >>= sha;
		return static_cast<dst_t>(intermediate);
	} 
}; 

// From (INT_BITS > 0, FRAC_BITS > 0) to (INT_BITS < 0, FRAC_BITS > 0)

template<typename src_t, typename dst_t, int16_t int_bits, int16_t frac_bits, int16_t int_bits_new, int16_t frac_bits_new>
struct convert_fixed_point<src_t, dst_t, int_bits, frac_bits, int_bits_new, frac_bits_new, true, true, false, true> {
	static dst_t exec(src_t src, uint16_t &raw_reminder) {
		dst_t intermediate = static_cast<dst_t>(src);
		uint32_t sha = int_bits + abs(int_bits_new);
		intermediate <<= sha;
		//raw_reminder = int_bits;
		return intermediate;		
	}
};

// From (INT_BITS > 0, FRAC_BITS < 0) to (INT_BITS > 0, FRAC_BITS > 0)

template<typename src_t, typename dst_t, int16_t int_bits, int16_t frac_bits, int16_t int_bits_new, int16_t frac_bits_new>
struct convert_fixed_point<src_t, dst_t, int_bits, frac_bits, int_bits_new, frac_bits_new, true, false, true, true> {
	static dst_t exec(src_t src, uint16_t &raw_reminder) {
		src_t intermediate = src;
		uint32_t sha = abs(frac_bits) + frac_bits_new;
		intermediate <<= sha;
		return intermediate;		
	}
}; 

// From (INT_BITS > 0, FRAC_BITS < 0) to (INT_BITS > 0, FRAC_BITS < 0)

template<typename src_t, typename dst_t, int16_t int_bits, int16_t frac_bits, int16_t int_bits_new, int16_t frac_bits_new>
struct convert_fixed_point<src_t, dst_t, int_bits, frac_bits, int_bits_new, frac_bits_new, true, false, true, false> {
	static dst_t exec(src_t src, uint16_t &raw_reminder) {
		if(abs(frac_bits) > abs(frac_bits_new)) {
			src_t intermediate = src;
			uint32_t sha = abs(frac_bits) - abs(frac_bits_new);
			intermediate <<= sha;
			return static_cast<dst_t>(intermediate); 
		} else {
			dst_t intermediate = static_cast<dst_t>(src);
			uint32_t sha = abs(frac_bits_new) - abs(frac_bits);
			intermediate >>= sha;
			return intermediate;
		}		
	}
}; 

// From (INT_BITS < 0, FRAC_BITS > 0) to (INT_BITS > 0, FRAC_BITS > 0)

template<typename src_t, typename dst_t, int16_t int_bits, int16_t frac_bits, int16_t int_bits_new, int16_t frac_bits_new>
struct convert_fixed_point<src_t, dst_t, int_bits, frac_bits, int_bits_new, frac_bits_new, false, true, true, true> {
	static dst_t exec(src_t src, uint16_t &raw_reminder) {
		src_t intermediate = src;
		uint32_t sha = abs(int_bits) + int_bits_new;
		intermediate >>= sha;
		//raw_reminder = int_bits_new;
		return static_cast<dst_t>(intermediate);		
	}
}; 

// From (INT_BITS < 0, FRAC_BITS > 0) to (INT_BITS < 0, FRAC_BITS > 0)

template<typename src_t, typename dst_t, int16_t int_bits, int16_t frac_bits, int16_t int_bits_new, int16_t frac_bits_new>
struct convert_fixed_point<src_t, dst_t, int_bits, frac_bits, int_bits_new, frac_bits_new, false, true, false, true> {
	static dst_t exec(src_t src, uint16_t &raw_reminder) {
		if(abs(int_bits) > abs(int_bits_new)) {
			src_t intermediate = src;
			uint32_t sha = abs(int_bits) - abs(int_bits_new);
			intermediate >>= sha ;
			if(frac_bits > frac_bits_new) {
				uint32_t sha_frac = frac_bits - frac_bits_new;
				intermediate >>= sha_frac;
			} else {
				uint32_t sha_frac = frac_bits_new - frac_bits;
				intermediate <<= sha_frac;
			}
			return static_cast<dst_t>(intermediate); 
		} else {
			dst_t intermediate = static_cast<dst_t>(src);
			uint32_t sha = abs(int_bits_new) - abs(int_bits);
			intermediate <<= sha;
			if(frac_bits > frac_bits_new) {
				uint32_t sha_frac = frac_bits - frac_bits_new;
				intermediate >>= sha_frac;
			} else {
				uint32_t sha_frac = frac_bits_new - frac_bits;
				intermediate <<= sha_frac;
			}
			return intermediate;
		}
	}
}; 

#endif /* end of include guard: EXTENDED_FIXED_POINT_UTILS_HPP */