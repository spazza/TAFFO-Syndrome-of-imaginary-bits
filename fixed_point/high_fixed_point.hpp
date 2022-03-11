#ifndef HIGH_FIXED_POINT_HPP
#define HIGH_FIXED_POINT_HPP

#include "fixed_point.hpp"

struct high_fixed_point_t : public fixed_point_t {

public:

    // -------------------------------------------------
    // Constructors
    // -------------------------------------------------
	
    high_fixed_point_t(const int integer_bits, const int outside_bits) : fixed_point_t(integer_bits, 0, outside_bits) {
        setRaw(0);
    }

    high_fixed_point_t(const int integer_bits, const int outside_bits, const int8_t value) : fixed_point_t(integer_bits, 0, outside_bits) { 
        initializeRaw(static_cast<raw_t>(value >> outside_bits);
    }

    high_fixed_point_t(const int integer_bits, const int outside_bits, const uint8_t value) : fixed_point_t(integer_bits, 0, outside_bits) { 
        initializeRaw(static_cast<raw_t>(value >> outside_bits);
    }

    high_fixed_point_t(const int integer_bits, const int outside_bits, const int16_t value) : fixed_point_t(integer_bits, 0, outside_bits) { 
        initializeRaw(static_cast<raw_t>(value >> outside_bits);
    }

    high_fixed_point_t(const int integer_bits, const int outside_bits, const uint16_t value) : fixed_point_t(integer_bits, 0, outside_bits) { 
        initializeRaw(static_cast<raw_t>(value >> outside_bits);
    }

    high_fixed_point_t(const int integer_bits, const int outside_bits, const int32_t value) : fixed_point_t(integer_bits, 0, outside_bits) { 
        initializeRaw(static_cast<raw_t>(value >> outside_bits);
    }

    high_fixed_point_t(const int integer_bits, const int outside_bits, const uint32_t value) : fixed_point_t(integer_bits, 0, outside_bits) { 
        initializeRaw(static_cast<raw_t>(value >> outside_bits);
    }

    high_fixed_point_t(const int integer_bits, const int outside_bits, const int64_t value) : fixed_point_t(integer_bits, 0, outside_bits) { 
        initializeRaw(static_cast<raw_t>(value >> outside_bits);
    }

    high_fixed_point_t(const int integer_bits, const int outside_bits, const uint64_t value) : fixed_point_t(integer_bits, 0, outside_bits) { 
        initializeRaw(static_cast<raw_t>(value >> outside_bits);
    }
	
private:

    // -------------------------------------------------
    // Initialization helpers
    // -------------------------------------------------
	
	void initializeRaw(raw_t value) {
		for(int i = 0; i < fractional_bits + integer_bits; ++i) {
			// At each iteration shift the bit
			raw_t considered_bit = 1 << i;
			
			// Retreive the value of the i-bit
			unsigned int temp_value = considered_bit & value;
			
			// Set the value of the i-bit
			setBit(i, temp_value);
		}
	}	
	
	template<T> 
	T getValueT() const override {
		T temp_value = 0;
		
		for(int i = 0; i < fractional_bits; ++i)
			if(getBit(i) == 1)
				temp_value += 2 ^ (fractional_bits - i);
		
		// Start from fractional_bits in the counter because the return value is integer 
		for(int i = fractional_bits; i < fractional_bits + integer_bits; ++i)
			if(getBit(i) == 1)
				temp_value += 2 ^ i;
		
		return temp_value;
	}	
	
public:

    // -------------------------------------------------
    // Accessors
    // -------------------------------------------------

    float getValueF() const override { return getValueT<float>(); }

    double getValueFD() const override { return getValueT<double>(); }
	
	long double getValueFLD() const override { return getValueT<long double>(); }
	
	raw_t getValue() const override { return getValue<raw_t>(); }
	
    // -------------------------------------------------
    // Assignment operators
    // -------------------------------------------------

    fixed_point_t& operator=(const fixed_point_t& value) override {
        if(this->integer_bits == value.integer_bits && this->outside_bits == value.outside_bits) {
            setRaw(value.getRaw());
            return *this;
        } else {
            //TO-DO
            return *this;
        }
    }

    // -------------------------------------------------
    // Logic operators
    // -------------------------------------------------

    bool operator<(const fixed_point_t& value) const override {
        if(this->integer_bits == value.integer_bits && this->outside_bits == value.outside_bits) {
            return this->getRaw() < value.getRaw();
        } else {
            // TO-DO
            return false;
        }
    }

    bool operator>(const fixed_point_t& value) const override {
        if(this->integer_bits == value.integer_bits && this->outside_bits == value.outside_bits) {
            return this->getRaw() > value.getRaw();
        } else {
            // TO-DO
            return false;
        }
    }

    bool operator==(const fixed_point_t& value) const override {
        if(this->integer_bits == value.integer_bits && this->outside_bits == value.outside_bits) {
            return this->getRaw() == value.getRaw();
        } else {
            // TO-DO
            return false;
        }
    }

    bool operator!=(const fixed_point_t& value) const override {
        if(this->integer_bits == value.integer_bits && this->outside_bits == value.outside_bits) {
            return this->getRaw() != value.getRaw();
        } else {
            // TO-DO
            return false;
        }
    }

    bool operator<=(const fixed_point_t& value) const override {
        if(this->integer_bits == value.integer_bits && this->outside_bits == value.outside_bits) {
            return !(*this > value);
        } else {
            // TO-DO
            return false;
        }
    }

    bool operator>=(const fixed_point_t& value) const override {
        if(this->integer_bits == value.integer_bits && this->outside_bits == value.outside_bits) {
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
        if(this->integer_bits == value.integer_bits && this->outside_bits == value.outside_bits) {
            fixed_point_t *new_fp = new high_fixed_point_t(integer_bits, outside_bits);
            new_fp->setRaw(this->getRaw() + value.getRaw());
            return *new_fp;
        } else {
            // TO-DO
            return *(new high_fixed_point_t(integer_bits, outside_bits));
        }
    }

    fixed_point_t& operator+=(const fixed_point_t& value) override{
        if(this->integer_bits == value.integer_bits && this->outside_bits == value.outside_bits) {
            setRaw(getRaw() + value.getRaw());
            return *this;
        } else {
            // TO-DO
            return *this;
        }
    }

    // Difference

    fixed_point_t& operator-(const fixed_point_t& value) const override{
        if(this->integer_bits == value.integer_bits && this->outside_bits == value.outside_bits) {
            fixed_point_t *new_fp = new high_fixed_point_t(integer_bits, outside_bits);
            new_fp->setRaw(this->getRaw() - value.getRaw());
            return *new_fp;
        } else {
            // TO-DO
            return *(new high_fixed_point_t(integer_bits, outside_bits));
        }
    }

    fixed_point_t& operator-=(const fixed_point_t& value) override{
        if(this->integer_bits == value.integer_bits && this->outside_bits == value.outside_bits) {
            setRaw(getRaw() - value.getRaw());
            return *this;
        } else {
            // TO-DO
            return *this;
        }
    }

    // Product

    fixed_point_t& operator*(const fixed_point_t& value) const override{
        if(this->integer_bits == value.integer_bits && this->outside_bits == value.outside_bits) {
            fixed_point_t *new_fp = new high_fixed_point_t(integer_bits, outside_bits);
            new_fp->setRaw(this->getRaw() * value.getRaw());
            return *new_fp;
        } else {
            // TO-DO
            return *(new high_fixed_point_t(integer_bits, outside_bits));
        }
    }

    fixed_point_t& operator*=(const fixed_point_t& value) override{
        if(this->integer_bits == value.integer_bits && this->outside_bits == value.outside_bits) {
            setRaw(getRaw() * value.getRaw());
            return *this;
        } else {
            // TO-DO
            return *this;
        }
    }
};

#endif
