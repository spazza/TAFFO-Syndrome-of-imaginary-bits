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

	// With this new representation probably it has no sense due to the shift factor that deletes the value
public:
	static const raw_t one  = ((raw_t)1) << (FRAC_BITS > 0 ? FRAC_BITS : 0);
	static const raw_t zero = ((raw_t)0) << (FRAC_BITS > 0 ? FRAC_BITS : 0);


public:
	//---------------------------------------------------------------------------
	// constructors
	//---------------------------------------------------------------------------
	// To be fixed, reduce the declaration
	extended_fixed_point_t(const int8_t value)   : raw(static_cast<raw_t>(value)) {
		if(FRAC_BITS > 0)
			this->raw <<= FRAC_BITS;
	}
	extended_fixed_point_t(const uint8_t value)  : raw(static_cast<raw_t>(value)) {
		if(FRAC_BITS > 0)
			this->raw <<= FRAC_BITS;
	}
	extended_fixed_point_t(const int16_t value)  : raw(static_cast<raw_t>(value)) {
		if(FRAC_BITS > 0)
			this->raw <<= FRAC_BITS;
	}
	extended_fixed_point_t(const uint16_t value) : raw(static_cast<raw_t>(value)) {
		if(FRAC_BITS > 0)
			this->raw <<= FRAC_BITS;
	}
	extended_fixed_point_t(const int32_t value)  : raw(static_cast<raw_t>(value)) {
		if(FRAC_BITS > 0)
			this->raw <<= FRAC_BITS;
	}
	extended_fixed_point_t(const uint32_t value) : raw(static_cast<raw_t>(value)) {
		if(FRAC_BITS > 0)
			this->raw <<= FRAC_BITS;
	}
	extended_fixed_point_t(const int64_t value)  : raw(static_cast<raw_t>(value)) {
		if(FRAC_BITS > 0)
			this->raw <<= FRAC_BITS;
	}
	extended_fixed_point_t(const uint64_t value) : raw(static_cast<raw_t>(value)) {
		if(FRAC_BITS > 0)
			this->raw <<= FRAC_BITS;
	}
	extended_fixed_point_t(const long double value) : raw((raw_t)(value * one)) {}
	extended_fixed_point_t(const double value)      : raw((raw_t)(value * one)) {}
	extended_fixed_point_t(const float value)       : raw((raw_t)(value * one)) {}
	#if _FIXED_POINT_REDEFINE_INT_TYPES_
	extended_fixed_point_t(const int value)         : raw(static_cast<raw_t>(value)) {}
	extended_fixed_point_t(const unsigned int value): raw(static_cast<raw_t>(value)) {}
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

	/*this_t convert() const {
		return *this;
	}*/

	/// Returns a new fixed-point in a new format which is similar in value to the original
	/** This may result in loss of raw if the number of bits for either the
 	* integer or fractional part are less than the original. 
	 */
	template <int16_t INT_BITS_NEW, int16_t FRAC_BITS_NEW>
	extended_fixed_point_t<INT_BITS_NEW, FRAC_BITS_NEW> convert() {
		typedef extended_fixed_point_t<INT_BITS_NEW, FRAC_BITS_NEW> target_t;
		typedef typename target_t::raw_t target_raw_t;
		typedef TypeConverter<raw_t, INT_BITS, FRAC_BITS, INT_BITS_NEW, FRAC_BITS_NEW> Converter;
		Converter converter(raw);

		return target_t::createRaw((target_raw_t)converter.convert());
	}

	//---------------------------------------------------------------------------
	// arithmetic operators
	//---------------------------------------------------------------------------
public:
	this_t operator+(const this_t& value) const {
		return this_t::createRaw(this->getRaw() + value.getRaw());
	}

	template <int16_t INT_BITS2, int16_t FRAC_BITS2>
	this_t operator+(const extended_fixed_point_t<INT_BITS2, FRAC_BITS2>& value) const {
		this_t op2 = value.template convert<INT_BITS, FRAC_BITS>();
		return this_t::createRaw(this->getRaw() + op2.getRaw());

		if(this->integer_length < 0 && value.integer_length < 0){
			auto shift_factor = std::abs(this->integer_length - value.integer_length);
			if(this->integer_length < value.integer_length) 
				return this_t::createRaw(this->getRaw() + (value.getRaw() >> shift_factor));
			else
				return this_t::createRaw(this->getRaw() + (value.getRaw() << shift_factor));
		}

		if(this->integer_length >= 0 && value.integer_length < 0){
			auto shift_factor = std::abs(value.integer_length);
			return this_t::createRaw(this->getRaw() + (value.getRaw() << shift_factor));
		}

		if(this->integer_length < 0 && value.integer_length >= 0){
			auto shift_factor = std::abs(this->integer_length);
			return this_t::createRaw(this->getRaw() + (value.getRaw() >> shift_factor));
		}

		return this_t::createRaw(this->getRaw() + value.getRaw());
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
			print_value = static_cast<float>(static_cast<int64_t>(raw) >> std::abs(INT_BITS))/one; 
		else if(FRAC_BITS < 0)
				print_value = static_cast<float>(static_cast<int64_t>(raw) << std::abs(FRAC_BITS))/one; 
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
	float getValueF() const { return static_cast<float>(raw)/one; }

	/// Get the value as a floating point double precision
	double getValueFD() const { return static_cast<double>(raw)/one; }

	/// Get the value as a floating point quadruple precision
	long double getValueFLD() const { return static_cast<long double>(raw)/one; }

	/// Get the value truncated to an integer
	//raw_t getValue() const { return static_cast<raw_t>(raw >> FRAC_BITS); }

	raw_t getValue() const { 
		raw_t temp_raw = raw;
		FRAC_BITS >= 0 ? temp_raw >>= FRAC_BITS : temp_raw <<= std::abs(FRAC_BITS);
		return temp_raw;
	}

	/// Get the closest integer value
	raw_t round() const { return static_cast<raw_t>(round(getValueF())); }


};

#include "extended_fixed_point_external_operators.hpp"

#endif