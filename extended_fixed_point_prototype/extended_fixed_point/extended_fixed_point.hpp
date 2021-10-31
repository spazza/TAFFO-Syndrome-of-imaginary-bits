#ifndef EXTENDED_FIXED_POINT_HPP
#define EXTENDED_FIXED_POINT_HPP

#include <iostream>

#include <cmath>
#include <iomanip>
#include <ostream>
#include <stdint.h>

#include "extended_fixed_point_utils.hpp"

template <int16_t INT_BITS = 1, int16_t FRAC_BITS = 15>
struct extended_fixed_point_t {

	//---------------------------------------------------------------------------
	// type definitions for internal data
	//---------------------------------------------------------------------------

public:
	static const int16_t integer_length = INT_BITS;
	static const int16_t fractional_length = FRAC_BITS;
	static const uint16_t bit_width = INT_BITS > 0 ? (FRAC_BITS > 0 ? INT_BITS + FRAC_BITS : INT_BITS) 
												   : (FRAC_BITS > 0 ? FRAC_BITS : 0);

	// The integer type used internally to store the value
	typedef typename get_int_with_length<bit_width>::RESULT raw_t;

	// In case both INT_BITS and FRAC_BITS are negative raise a compile time error
	static_assert(INT_BITS >= 0 || FRAC_BITS >= 0, "Invalid initialization of template parameters");

protected:
	typedef extended_fixed_point_t<INT_BITS, FRAC_BITS> this_t;

private:
	raw_t raw;

	static const raw_t raw_booster = ((raw_t)1) << (FRAC_BITS > 0 ? FRAC_BITS : 0);

public:
	// In case the comma is placed out of left it is necessary to retreive the correct value
	uint32_t raw_helper = 0;

public:

	//---------------------------------------------------------------------------
	// constructors
	//---------------------------------------------------------------------------

	extended_fixed_point_t(const int8_t value)   : raw(static_cast<raw_t>(value)) { raw_normalizer(); }
	extended_fixed_point_t(const uint8_t value)  : raw(static_cast<raw_t>(value)) { raw_normalizer(); }
	extended_fixed_point_t(const int16_t value)  : raw(static_cast<raw_t>(value)) { raw_normalizer(); }
	extended_fixed_point_t(const uint16_t value) : raw(static_cast<raw_t>(value)) { raw_normalizer(); }
	extended_fixed_point_t(const int32_t value)  : raw(static_cast<raw_t>(value)) { raw_normalizer(); }
	extended_fixed_point_t(const uint32_t value) : raw(static_cast<raw_t>(value)) { raw_normalizer(); }
	extended_fixed_point_t(const int64_t value)  : raw(static_cast<raw_t>(value)) { raw_normalizer(); }
	extended_fixed_point_t(const uint64_t value) : raw(static_cast<raw_t>(value)) { raw_normalizer(); }
	extended_fixed_point_t(const long double value) : raw((raw_t)(value * raw_booster)) { raw_normalizer_float(); } 
	extended_fixed_point_t(const double value)      : raw((raw_t)(value * raw_booster)) { raw_normalizer_float(); }
	extended_fixed_point_t(const float value)       : raw((raw_t)(value * raw_booster)) { raw_normalizer_float(); }
	#if _FIXED_POINT_REDEFINE_INT_TYPES_
	extended_fixed_point_t(const int value)         : raw(static_cast<raw_t>(value)) { raw_normalizer(); }
	extended_fixed_point_t(const unsigned int value): raw(static_cast<raw_t>(value)) { raw_normalizer(); }
	#endif

	explicit extended_fixed_point_t() : raw(0) {}

private:

	//---------------------------------------------------------------------------
	// normalization functions
	//---------------------------------------------------------------------------

	void raw_normalizer() {
		if(integer_length >= 0 && fractional_length >= 0)
			raw <<= fractional_length;
		if(integer_length >= 0 && fractional_length < 0)
			raw >>= abs(fractional_length);
	}

	void raw_normalizer_float() {
		if(integer_length < 0 && fractional_length >= 0) 
			raw <<= abs(integer_length);	
	}

	raw_t raw_denormalizer() const {
		raw_t value = raw;

		if(integer_length >= 0 && fractional_length >= 0)
			value >>= fractional_length;
	 	if(integer_length >= 0 && fractional_length < 0)
			value <<= abs(fractional_length);	
			
		return static_cast<raw_t>(value);
	}

	template<typename T>
	T raw_denormalizer_float() const {
		raw_t value = raw;

		if(integer_length >= 0 && fractional_length < 0)
			value <<= abs(fractional_length);
		if(integer_length < 0 && fractional_length >= 0) 
			value >>= abs(integer_length) + raw_helper;

		return static_cast<T>(value)/raw_booster;
	}

public:
   
	static this_t createRaw(raw_t data, int16_t raw_h) {
		this_t val;
		val.raw = data;
		val.raw_helper = raw_h;
		return val;
	}

	raw_t getRaw() const {
		return this->raw;
	}

	//---------------------------------------------------------------------------
	// conversion
	//---------------------------------------------------------------------------
public:

	this_t covert() const {
		return *this;
	}

	template<int16_t INT_BITS_NEW, int16_t FRAC_BITS_NEW>
	extended_fixed_point_t<INT_BITS_NEW, FRAC_BITS_NEW> convert() const {
		typedef extended_fixed_point_t<INT_BITS_NEW, FRAC_BITS_NEW> target_t;
		typedef typename target_t::raw_t target_raw_t;

		uint16_t raw_h = raw_helper;
		target_raw_t new_raw = convert_fixed_point<
				raw_t,
				target_raw_t,
				INT_BITS,
				FRAC_BITS,
				INT_BITS_NEW,
				FRAC_BITS_NEW,
				INT_BITS      >= 0,
				FRAC_BITS     >= 0,
				INT_BITS_NEW  >= 0,
				FRAC_BITS_NEW >= 0
				>::exec(raw, raw_h);

		return target_t::createRaw(new_raw, raw_h);
	}

	//---------------------------------------------------------------------------
	// pretty print
	//---------------------------------------------------------------------------

	// !!! TEMPORARY PRINT
	/// Write to an output stream
	std::ostream& emit(std::ostream& os) const {
		auto old_precision = os.precision();
		auto old_flags = os.flags();
		float print_value;

		if(INT_BITS < 0) 
			print_value = static_cast<float>(static_cast<int64_t>(raw) >> std::abs(INT_BITS))/raw_booster; 
		else if(FRAC_BITS < 0)
				print_value = static_cast<float>(static_cast<int64_t>(raw) << std::abs(FRAC_BITS))/raw_booster; 
			else 
				print_value = getValueF(); 

		os << std::fixed << std::setprecision(((FRAC_BITS + std::abs(INT_BITS)) * 3 + 9) / 10)
			<< print_value << std::setprecision(old_precision);
		os.flags(old_flags);
		return os;
	}


	//---------------------------------------------------------------------------
	// accessors
	//---------------------------------------------------------------------------

	/// Get the value as a floating point
	float getValueF() const { return raw_denormalizer_float<float>(); }

	/// Get the value as a floating point double precision
	double getValueFD() const { return raw_denormalizer_float<double>(); }

	/// Get the value as a floating point quadruple precision
	long double getValueFLD() const { return raw_denormalizer_float<long double>(); }

	/// Get the value truncated to an integer
	raw_t getValue() const { return raw_denormalizer(); }

	/// Get the closest integer value
	raw_t round() const { return static_cast<raw_t>(round(getValueF())); }

};

#include "extended_fixed_point_external_operators.hpp"

#endif