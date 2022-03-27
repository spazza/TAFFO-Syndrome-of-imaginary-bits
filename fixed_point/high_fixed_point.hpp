#ifndef HIGH_FIXED_POINT_HPP
#define HIGH_FIXED_POINT_HPP

#include "fixed_point.hpp"

struct high_fixed_point_t : public fixed_point_t {

public:

    // -------------------------------------------------
    // Constructors
    // -------------------------------------------------
	
    high_fixed_point_t(const int integer_bits, const int outside_bits) : fixed_point_t(integer_bits, 0, outside_bits) {
        setRaw(static_cast<raw_t>(0));
    }

    high_fixed_point_t(const int integer_bits, const int outside_bits, const int8_t value) : fixed_point_t(integer_bits, 0, outside_bits) { 
        setRaw(static_cast<raw_t>(value >> outside_bits));
    }

    high_fixed_point_t(const int integer_bits, const int outside_bits, const uint8_t value) : fixed_point_t(integer_bits, 0, outside_bits) { 
        setRaw(static_cast<raw_t>(value >> outside_bits));
    }

    high_fixed_point_t(const int integer_bits, const int outside_bits, const int16_t value) : fixed_point_t(integer_bits, 0, outside_bits) { 
        setRaw(static_cast<raw_t>(value >> outside_bits));
    }

    high_fixed_point_t(const int integer_bits, const int outside_bits, const uint16_t value) : fixed_point_t(integer_bits, 0, outside_bits) { 
        setRaw(static_cast<raw_t>(value >> outside_bits));
    }

    high_fixed_point_t(const int integer_bits, const int outside_bits, const int32_t value) : fixed_point_t(integer_bits, 0, outside_bits) { 
        setRaw(static_cast<raw_t>(value >> outside_bits));
    }

    high_fixed_point_t(const int integer_bits, const int outside_bits, const uint32_t value) : fixed_point_t(integer_bits, 0, outside_bits) { 
        setRaw(static_cast<raw_t>(value >> outside_bits));
    }

    high_fixed_point_t(const int integer_bits, const int outside_bits, const int64_t value) : fixed_point_t(integer_bits, 0, outside_bits) { 
        setRaw(static_cast<raw_t>(value >> outside_bits));
    }

    high_fixed_point_t(const int integer_bits, const int outside_bits, const uint64_t value) : fixed_point_t(integer_bits, 0, outside_bits) { 
        setRaw(static_cast<raw_t>(value >> outside_bits));
    }
	
public:

    // -------------------------------------------------
    // Accessors
    // -------------------------------------------------

    float getValueF() const override { 
        raw_t one = ((raw_t)1) << outside_bits;
        return static_cast<float>(getRaw())/one; 
    }

    double getValueFD() const override { 
        raw_t one = ((raw_t)1) << outside_bits;
        return static_cast<double>(getRaw())/one;  
    }

    long double getValueFLD() const override { 
        raw_t one = ((raw_t)1) << outside_bits;
        return static_cast<long double>(getRaw())/one;  
    }

    raw_t getValue() const override { return static_cast<raw_t>(getRaw() << outside_bits); }
	
    // -------------------------------------------------
    // Assignment operators
    // -------------------------------------------------

    fixed_point_t& operator=(const fixed_point_t& value) override {
        if(this->integer_bits == value.getIntBits() && this->outside_bits == value.getOutBits()) {
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
        if(this->integer_bits == value.getIntBits() && this->outside_bits == value.getOutBits()) {
            return this->getRaw() < value.getRaw();
        } else {
            // TO-DO
            return false;
        }
    }

    bool operator>(const fixed_point_t& value) const override {
        if(this->integer_bits == value.getIntBits() && this->outside_bits == value.getOutBits()) {
            return this->getRaw() > value.getRaw();
        } else {
            // TO-DO
            return false;
        }
    }

    bool operator==(const fixed_point_t& value) const override {
        if(this->integer_bits == value.getIntBits() && this->outside_bits == value.getOutBits()) {
            return this->getRaw() == value.getRaw();
        } else {
            // TO-DO
            return false;
        }
    }

    bool operator!=(const fixed_point_t& value) const override {
        if(this->integer_bits == value.getIntBits() && this->outside_bits == value.getOutBits()) {
            return this->getRaw() != value.getRaw();
        } else {
            // TO-DO
            return false;
        }
    }

    bool operator<=(const fixed_point_t& value) const override {
        if(this->integer_bits == value.getIntBits() && this->outside_bits == value.getOutBits()) {
            return !(*this > value);
        } else {
            // TO-DO
            return false;
        }
    }

    bool operator>=(const fixed_point_t& value) const override {
        if(this->integer_bits == value.getIntBits() && this->outside_bits == value.getOutBits()) {
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
        if(this->integer_bits == value.getIntBits() && this->outside_bits == value.getOutBits()) {
            fixed_point_t *new_fp = new high_fixed_point_t(integer_bits, outside_bits);
            new_fp->setRaw(this->getRaw() + value.getRaw());
            return *new_fp;
        } else {
            // TO-DO
            return *(new high_fixed_point_t(integer_bits, outside_bits));
        }
    }

    fixed_point_t& operator+=(const fixed_point_t& value) override{
        if(this->integer_bits == value.getIntBits() && this->outside_bits == value.getOutBits()) {
            setRaw(getRaw() + value.getRaw());
            return *this;
        } else {
            // TO-DO
            return *this;
        }
    }

    // Difference

    fixed_point_t& operator-(const fixed_point_t& value) const override{
        if(this->integer_bits == value.getIntBits() && this->outside_bits == value.getOutBits()) {
            fixed_point_t *new_fp = new high_fixed_point_t(integer_bits, outside_bits);
            new_fp->setRaw(this->getRaw() - value.getRaw());
            return *new_fp;
        } else {
            // TO-DO
            return *(new high_fixed_point_t(integer_bits, outside_bits));
        }
    }

    fixed_point_t& operator-=(const fixed_point_t& value) override{
        if(this->integer_bits == value.getIntBits() && this->outside_bits == value.getOutBits()) {
            setRaw(getRaw() - value.getRaw());
            return *this;
        } else {
            // TO-DO
            return *this;
        }
    }

    // Product

    fixed_point_t& operator*(const fixed_point_t& value) const override{
        if(this->integer_bits == value.getIntBits() && this->outside_bits == value.getOutBits()) {
            fixed_point_t *new_fp = new high_fixed_point_t(integer_bits, outside_bits);
            new_fp->setRaw(this->getRaw() * value.getRaw());
            return *new_fp;
        } else {
            // TO-DO
            return *(new high_fixed_point_t(integer_bits, outside_bits));
        }
    }

    fixed_point_t& operator*=(const fixed_point_t& value) override{
        if(this->integer_bits == value.getIntBits() && this->outside_bits == value.getOutBits()) {
            setRaw(getRaw() * value.getRaw());
            return *this;
        } else {
            // TO-DO
            return *this;
        }
    }

    // Division

    // Conversion

    void convert_to_normal_fixed_point_t(unsigned int new_int_bits, unsigned int new_frac_bits) override {
        // TO-DO
    }

    void convert_to_high_fixed_point_t(unsigned int new_int_bits, unsigned int new_out_bits) override {
        if(new_out_bits > this->outside_bits) {
            unsigned int sha = new_out_bits - this->outside_bits;
            setRaw(getRaw() >> sha);
        } else {
            unsigned int sha = this->outside_bits - new_out_bits;
            setRaw(getRaw() << sha);
        }

        this->integer_bits = new_int_bits;
        this->outside_bits = new_out_bits;
    }

    void convert_to_low_fixed_point_t(unsigned int new_frac_bits, unsigned int new_out_bits) override {
        // TO-DO
    }

    // Print
};

#endif
