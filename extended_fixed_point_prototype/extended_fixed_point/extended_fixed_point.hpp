#include "fixed_point_utils.hpp"

#ifndef EXTENDED_FIXED_POINT_HPP
#define EXTENDED_FIXED_POINT_HPP

#include <cmath>
#include <iomanip>
#include <ostream>
#include <stdint.h>

#include "fixed_point_utils.hpp"

/// A fixed-point integer type
/** \tparam INT_BITS The number of bits before the radix point
 *  \tparam FRAC_BITS The number of bits after the radix point
 *  \warning INT_BITS and FRAC_BITS can assume any integer value, and their sum cannot exceed 64
 *
 *  Fixed point numbers are signed, so extended_fixed_point_t<5,2>, for example, has a
 *  range of -16.00 to +15.75
 *
 *  The internal storage (extended_fixed_point_t::raw) is rounded up to the next highest
 *  power of 2, so a 17 bit number occupies 32 physical bits. Consider that the
 *  multiplication of a 5 bit fixed point (which occupies 8 bits of space) with
 *  an 10 bit fixed point (which occupies 16 bits of space) results in a 15 bit
 *  fixed point which occupies 16 bits of space.
 */
template <int16_t INT_BITS = 1, int16_t FRAC_BITS = 15>
struct extended_fixed_point_t
{

    //---------------------------------------------------------------------------
	// type definitions for internal data
	//---------------------------------------------------------------------------

    //Maybe these definitions can be more that int16

public:
	static const int16_t integer_length = INT_BITS;
	static const int16_t fractional_length = FRAC_BITS;
	static const int16_t bit_width = INT_BITS + FRAC_BITS;

	/// The integer type used internally to store the value
	typedef typename get_int_with_length<INT_BITS + FRAC_BITS>::RESULT raw_t;

protected:
	typedef extended_fixed_point_t<INT_BITS, FRAC_BITS> this_t;

private:
	raw_t raw;

public:
	static const raw_t one  = ((raw_t)1) << FRAC_BITS;
	static const raw_t zero = ((raw_t)0) << FRAC_BITS;

public:
	//---------------------------------------------------------------------------
	// constructors
	//---------------------------------------------------------------------------

	/// Create a fixed-point with equivalent integer value
	/** For example in 4.12 fixed-point, the number "2" is 0010.000000000000  */
	extended_fixed_point_t(const int8_t value)   : raw(static_cast<raw_t>(value) << FRAC_BITS) {}
	extended_fixed_point_t(const uint8_t value)  : raw(static_cast<raw_t>(value) << FRAC_BITS) {}
	extended_fixed_point_t(const int16_t value)  : raw(static_cast<raw_t>(value) << FRAC_BITS) {}
	extended_fixed_point_t(const uint16_t value) : raw(static_cast<raw_t>(value) << FRAC_BITS) {}
	extended_fixed_point_t(const int32_t value)  : raw(static_cast<raw_t>(value) << FRAC_BITS) {}
	extended_fixed_point_t(const uint32_t value) : raw(static_cast<raw_t>(value) << FRAC_BITS) {}
	extended_fixed_point_t(const int64_t value)  : raw(static_cast<raw_t>(value) << FRAC_BITS) {}
	extended_fixed_point_t(const uint64_t value) : raw(static_cast<raw_t>(value) << FRAC_BITS) {}
	extended_fixed_point_t(const long double value) : raw((raw_t)(value * one)) {}
	extended_fixed_point_t(const double value)      : raw((raw_t)(value * one)) {}
	extended_fixed_point_t(const float value)       : raw((raw_t)(value * one)) {}
	#if _FIXED_POINT_REDEFINE_INT_TYPES_
	extended_fixed_point_t(const int value)         : raw(static_cast<raw_t>(value) << FRAC_BITS) {}
	extended_fixed_point_t(const unsigned int value): raw(static_cast<raw_t>(value) << FRAC_BITS) {}
	#endif

	explicit extended_fixed_point_t() : raw(0) {}

	static this_t createRaw(raw_t data) {
		this_t val;
		val.raw = data;
		return val;
	}

	raw_t getRaw() const {
		return this->raw;
	}

	//---------------------------------------------------------------------------
	// conversion
	//---------------------------------------------------------------------------
public:

this_t convert() const {
	return *this;
}

/// Returns a new fixed-point in a new format which is similar in value to the original
/** This may result in loss of raw if the number of bits for either the
 * integer or fractional part are less than the original. */
template <int16_t INT_BITS_NEW, int16_t FRAC_BITS_NEW>
extended_fixed_point_t<INT_BITS_NEW, FRAC_BITS_NEW> convert() const
{
	typedef extended_fixed_point_t<INT_BITS_NEW, FRAC_BITS_NEW> target_t;
	typedef typename target_t::raw_t target_raw_t;
	return target_t::createRaw(
		convert_fixed_point<
			raw_t,
			target_raw_t,
			get_max<FRAC_BITS_NEW, FRAC_BITS>::RESULT - get_min<FRAC_BITS_NEW, FRAC_BITS>::RESULT,
			(FRAC_BITS_NEW > FRAC_BITS)
		>:: exec(raw));
}

/// Returns a new fixed-point that reinterprets the binary raw.
/** \warning This should be used sparingly since returns a number whos
 * value is not the necessarily same.
 * \note To just move the radix point, rather use LeftShift or RightShift. */
template <int16_t INT_BITS_NEW, int16_t FRAC_BITS_NEW>
extended_fixed_point_t<INT_BITS_NEW, FRAC_BITS_NEW> reinterpret() const
{
	typedef extended_fixed_point_t<INT_BITS_NEW, FRAC_BITS_NEW> target_t;
	return target_t::createRaw(raw);
}

//---------------------------------------------------------------------------
	// arithmetic operators
	//---------------------------------------------------------------------------
public:

this_t operator+(const this_t& value) const
{
	return this_t::createRaw(this->getRaw() + value.getRaw());
}

template <int16_t INT_BITS2, int16_t FRAC_BITS2>
this_t operator+(const extended_fixed_point_t<INT_BITS2, FRAC_BITS2>& value) const
{
	this_t op2 = value.template convert<INT_BITS, FRAC_BITS>();
	return this_t::createRaw(this->getRaw() + op2.getRaw());
}

this_t& operator+=(const this_t& value)
{
	raw += value.getRaw();
	return *this;
}

template <int16_t INT_BITS2, int16_t FRAC_BITS2>
this_t& operator+=(const extended_fixed_point_t<INT_BITS2, FRAC_BITS2>& value)
{
	this_t op2 = value.template convert<INT_BITS, FRAC_BITS>();
	return *this += op2;
}

template <typename other_t>
this_t operator+(const other_t& value) const
{
	return *this + this_t(value);
}

template <typename other_t>
this_t& operator+=(const other_t& value)
{
	return *this += this_t(value);
}

this_t& operator++(int)
{
	raw += one;
	return *this;
}

this_t& operator++()
{
	raw += one;
	return *this;
}

//---------------------------------------------------------------------------
// pretty print
//---------------------------------------------------------------------------

/// Write to an output stream
std::ostream& emit(std::ostream& os) const
{
	auto old_precision = os.precision();
	auto old_flags = os.flags();
	os << std::fixed << std::setprecision((FRAC_BITS * 3 + 9) / 10)
		<< getValueF() << std::setprecision(old_precision);
	os.flags(old_flags);
	return os;
}

//---------------------------------------------------------------------------
// accessors
//---------------------------------------------------------------------------

/// Get the value as a floating point
float getValueF() const { return static_cast<float>(raw)/one; }

/// Get the value as a floating point double precision
double getValueFD() const { return static_cast<double>(raw)/one; }

/// Get the value as a floating point quadruple precision
long double getValueFLD() const { return static_cast<long double>(raw)/one; }

/// Get the value truncated to an integer
raw_t getValue() const { return static_cast<raw_t>(raw >> FRAC_BITS); }

/// Get the closest integer value
raw_t round() const { return static_cast<raw_t>(round(getValueF())); }

};

#include "extended_fixed_point_external_operators.hpp"

#endif