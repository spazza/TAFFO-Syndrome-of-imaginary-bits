#ifndef NORMAL_FIXED_POINT_HPP
#define NORMAL_FIXED_POINT_HPP

#include "fixed_point.hpp"

struct normal_fixed_point_t : public fixed_point_t {

public:

    // -------------------------------------------------
    // Constructors
    // -------------------------------------------------
    normal_fixed_point_t(const int integer_bits, const int fractional_bits) : fixed_point_t(integer_bits, fractional_bits, 0) {
        setRaw(0);
    }

    normal_fixed_point_t(const int integer_bits, const int fractional_bits, const int8_t value) : fixed_point_t(integer_bits, fractional_bits, 0) { 
		initializeRaw(static_cast<raw_t>(value << fractional_bits);
    }

    normal_fixed_point_t(const int integer_bits, const int fractional_bits, const uint8_t value) : fixed_point_t(integer_bits, fractional_bits, 0) { 
        initializeRaw(static_cast<raw_t>(value << fractional_bits);
    }

    normal_fixed_point_t(const int integer_bits, const int fractional_bits, const int16_t value) : fixed_point_t(integer_bits, fractional_bits, 0) { 
        initializeRaw(static_cast<raw_t>(value << fractional_bits));
    }

    normal_fixed_point_t(const int integer_bits, const int fractional_bits, const uint16_t value) : fixed_point_t(integer_bits, fractional_bits, 0) { 
        initializeRaw(static_cast<raw_t>(value << fractional_bits));
    }

    normal_fixed_point_t(const int integer_bits, const int fractional_bits, const int32_t value) : fixed_point_t(integer_bits, fractional_bits, 0) { 
        initializeRaw(static_cast<raw_t>(value << fractional_bits));
    }

    normal_fixed_point_t(const int integer_bits, const int fractional_bits, const uint32_t value) : fixed_point_t(integer_bits, fractional_bits, 0) { 
        initializeRaw(static_cast<raw_t>(value << fractional_bits));
    }

    normal_fixed_point_t(const int integer_bits, const int fractional_bits, const int64_t value) : fixed_point_t(integer_bits, fractional_bits, 0) { 
        initializeRaw(static_cast<raw_t>(value << fractional_bits));
    }

    normal_fixed_point_t(const int integer_bits, const int fractional_bits, const uint64_t value) : fixed_point_t(integer_bits, fractional_bits, 0) { 
        initializeRaw(static_cast<raw_t>(value << fractional_bits));
    }
 
    normal_fixed_point_t(const int integer_bits, const int fractional_bits, const float value) : fixed_point_t(integer_bits, fractional_bits, 0) { 
        raw_t one = ((raw_t)1) << fractional_bits;
        initializeRaw((raw_t)(value * one));
    }

    normal_fixed_point_t(const int integer_bits, const int fractional_bits, const double value) : fixed_point_t(integer_bits, fractional_bits, 0) { 
        raw_t one = ((raw_t)1) << fractional_bits;
        initializeRaw((raw_t)(value * one));
    }

    normal_fixed_point_t(const int integer_bits, const int fractional_bits, const long double value) : fixed_point_t(integer_bits, fractional_bits, 0) { 
        raw_t one = ((raw_t)1) << fractional_bits;
        initializeRaw((raw_t)(value * one));
    }

private:

    // -------------------------------------------------
    // Initialization helpers
    // -------------------------------------------------
	
	void initializeRaw(raw_t value) {
		for(int i = 0; i < fractional_bits + fractional_bits; ++i) {
			// At each iteration shift the bit
			raw_t considered_bit = 1 << i;
			
			// Retreive the value of the i-bit
			unsigned int temp_value = considered_bit & value;
			
			// Set the value of the i-bit
			setBit(i, temp_value);
		}
	}	

	void initializeFracPart(raw_t value) {
		for(int i = 0; i < fractional_bits; ++i) {
			// At each iteration shift the bit
			raw_t considered_bit = 1 << i;
			
			// Retreive the value of the i-bit
			unsigned int temp_value = considered_bit & value;
			
			// Set the value of the i-bit
			setBit(i, temp_value);
		}
	}

    void initializeIntPart(raw_t value) {
		// It starts from i = fractional_bits because the previous bits have been already set
        for(int i = fractional_bits; i < fractional_bits + integer_bits; ++i) {
            // At each iteration shift the bit
            raw_t considered_bit = 1 << i;

            // Retreive the value of the i-bit
            unsigned int temp_value = considered_bit & value;

            // Set the value of the i-bit
            setBit(i, temp_value);
        }
    }	

public:

    // -------------------------------------------------
    // Accessors
    // -------------------------------------------------

    float getValueF() const override {
        raw_t one = ((raw_t)1) << fractional_bits;
        return static_cast<float>(this->getRaw())/one;
    }

    double getValueFD() const override {
        raw_t one = ((raw_t)1) << fractional_bits;
        return static_cast<double>(this->getRaw())/one;
    }

    long double getValueFLD() const override {
        raw_t one = ((raw_t)1) << fractional_bits;
        return static_cast<long double>(this->getRaw())/one;
    }

    raw_t getValue() const override {
        return static_cast<raw_t>(this->getRaw() >> fractional_bits);
    }

    // -------------------------------------------------
    // Assignment operators
    // -------------------------------------------------

    fixed_point_t& operator=(const fixed_point_t& value) override {
        if(this->integer_bits == value.integer_bits && this->fractional_bits == value.fractional_bits) {
            setRaw(value.getRaw());
            return *this;
        } else {
            // TO-DO
            return *this;
        }
    }

    // -------------------------------------------------
    // Logic operators
    // -------------------------------------------------

    bool operator<(const fixed_point_t& value) const override {
        if(this->integer_bits == value.integer_bits && this->fractional_bits == value.fractional_bits) {
            return this->getRaw() < value.getRaw();
        } else {
            // TO-DO
            return false;
        }
    }

    bool operator>(const fixed_point_t& value) const override {
        if(this->integer_bits == value.integer_bits && this->fractional_bits == value.fractional_bits) {
            return this->getRaw() > value.getRaw();
        } else {
            // TO-DO
            return false;
        }
    }

    bool operator==(const fixed_point_t& value) const override {
        if(this->integer_bits == value.integer_bits && this->fractional_bits == value.fractional_bits) {
            return this->getRaw() == value.getRaw();
        } else {
            // TO-DO
            return false;
        }
    }

    bool operator!=(const fixed_point_t& value) const override {
        if(this->integer_bits == value.integer_bits && this->fractional_bits == value.fractional_bits) {
            return this->getRaw() != value.getRaw();
        } else {
            // TO-DO
            return false;
        }
    }

    bool operator<=(const fixed_point_t& value) const override {
        if(this->integer_bits == value.integer_bits && this->fractional_bits == value.fractional_bits) {
            return !(*this > value);
        } else {
            // TO-DO
            return false;
        }
    }

    bool operator>=(const fixed_point_t& value) const override {
        if(this->integer_bits == value.integer_bits && this->fractional_bits == value.fractional_bits) {
            return !(*this < value);
        } else {
            // TO-DO
            return false;
        }
    }

    // -------------------------------------------------
    // Arithmetic operators
    // -------------------------------------------------

    // Sum

    fixed_point_t& operator+(const fixed_point_t& value) const override{
        if(this->integer_bits == value.integer_bits && this->fractional_bits == value.fractional_bits) {
            fixed_point_t *new_fp = new normal_fixed_point_t(integer_bits, fractional_bits);
            new_fp->setRaw(this->getRaw() + value.getRaw());
            return *new_fp;
        } else {
            // TO-DO
            return *(new normal_fixed_point_t(integer_bits, fractional_bits));
        }
    }

    fixed_point_t& operator+=(const fixed_point_t& value) override {
        if(this->integer_bits == value.integer_bits && this->fractional_bits == value.fractional_bits) {
            setRaw(getRaw() + value.getRaw());
            return *this;
        } else {
            // TO-DO
            return *this;
        }
    }

    // Difference

    fixed_point_t& operator-(const fixed_point_t& value) const override {
        if(this->integer_bits == value.integer_bits && this->fractional_bits == value.fractional_bits) {
            fixed_point_t *new_fp = new normal_fixed_point_t(integer_bits, fractional_bits);
            new_fp->setRaw(this->getRaw() - value.getRaw());
            return *new_fp;
        } else {
            // TO-DO
            return *(new normal_fixed_point_t(integer_bits, fractional_bits));
        }
    }

    fixed_point_t& operator-=(const fixed_point_t& value) override {
        if(this->integer_bits == value.integer_bits && this->fractional_bits == value.fractional_bits) {
            setRaw(getRaw() - value.getRaw());
            return *this;
        } else {
            // TO-DO
            return *this;
        }
    }

    // Product

    fixed_point_t& operator*(const fixed_point_t& value) const override {
        if(this->integer_bits == value.integer_bits && this->fractional_bits == value.fractional_bits) {
            fixed_point_t *new_fp = new normal_fixed_point_t(integer_bits, fractional_bits);
            new_fp->setRaw(this->getRaw() * value.getRaw());
            return *new_fp;
        } else {
            // TO-DO
            return *(new normal_fixed_point_t(integer_bits, fractional_bits));
        }
    }

    fixed_point_t& operator*=(const fixed_point_t& value) override {
        if(this->integer_bits == value.integer_bits && this->fractional_bits == value.fractional_bits) {
            setRaw(getRaw() * value.getRaw());
            return *this;
        } else {
            // TO-DO
            return *this;
        }
    }
};

#endif
