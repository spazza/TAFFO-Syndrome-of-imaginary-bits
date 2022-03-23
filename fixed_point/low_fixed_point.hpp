#ifndef LOW_FIXED_POINT_HPP
#define LOW_FIXED_POINT_HPP

#include "fixed_point.hpp"

struct low_fixed_point_t : public fixed_point_t {

    low_fixed_point_t(const int fractional_bits, const int outside_bits) : fixed_point_t(0, fractional_bits, outside_bits) {
        setRaw(static_cast<raw_t>(0));
    }

    low_fixed_point_t(const int fractional_bits, const int outside_bits, const float value) : fixed_point_t(0, fractional_bits, outside_bits) { 
        raw_t one = ((raw_t)1) << (fractional_bits);
        setRaw(((raw_t)(value * one)) << outside_bits);
    }

    low_fixed_point_t(const int fractional_bits, const int outside_bits, const double value) : fixed_point_t(0, fractional_bits, outside_bits) { 
        raw_t one = ((raw_t)1) << (fractional_bits);
        setRaw(((raw_t)(value * one)) << outside_bits);
    }

    low_fixed_point_t(const int fractional_bits, const int outside_bits, const long double value) : fixed_point_t(0, fractional_bits, outside_bits) { 
        raw_t one = ((raw_t)1) << (fractional_bits);
        setRaw(((raw_t)(value * one)) << outside_bits);
    }    

public:

    // -------------------------------------------------
    // Accessors
    // -------------------------------------------------

    float getValueF() const override { 
        raw_t one = ((raw_t)1) << fractional_bits;
        return static_cast<float>(getRaw() >> outside_bits)/one; 
    }

    double getValueFD() const override { 
        raw_t one = ((raw_t)1) << fractional_bits;
        return static_cast<double>(getRaw() >> outside_bits)/one;  
    }

    long double getValueFLD() const override { 
        raw_t one = ((raw_t)1) << fractional_bits;
        return static_cast<long double>(getRaw() >> outside_bits)/one;  
    }

    raw_t getValue() const override { return static_cast<raw_t>(getRaw() >> outside_bits); }

    // -------------------------------------------------
    // Assignment operators
    // -------------------------------------------------

    fixed_point_t& operator=(const fixed_point_t& value) override {
        if(this->fractional_bits == value.fractional_bits && this->outside_bits == value.outside_bits) {
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
        if(this->fractional_bits == value.fractional_bits && this->outside_bits == value.outside_bits) {
            return this->getRaw() < value.getRaw();
        } else {
            // TO-DO
            return false;
        }
    }

    bool operator>(const fixed_point_t& value) const override {
        if(this->fractional_bits == value.fractional_bits && this->outside_bits == value.outside_bits) {
            return this->getRaw() > value.getRaw();
        } else {
            // TO-DO
            return false;
        }
    }

    bool operator==(const fixed_point_t& value) const override {
        if(this->fractional_bits == value.fractional_bits && this->outside_bits == value.outside_bits) {
            return this->getRaw() == value.getRaw();
        } else {
            // TO-DO
            return false;
        }
    }

    bool operator!=(const fixed_point_t& value) const override {
        if(this->fractional_bits == value.fractional_bits && this->outside_bits == value.outside_bits) {
            return this->getRaw() != value.getRaw();
        } else {
            // TO-DO
            return false;
        }
    }

    bool operator<=(const fixed_point_t& value) const override {
        if(this->fractional_bits == value.fractional_bits && this->outside_bits == value.outside_bits) {
            return !(*this > value);
        } else {
            // TO-DO
            return false;
        }
    }

    bool operator>=(const fixed_point_t& value) const override {
        if(this->fractional_bits == value.fractional_bits && this->outside_bits == value.outside_bits) {
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

    fixed_point_t& operator+(const fixed_point_t& value) const override {
        if(this->fractional_bits == value.fractional_bits && this->outside_bits == value.outside_bits) {
            fixed_point_t *new_fp = new low_fixed_point_t(fractional_bits, outside_bits);
            new_fp->setRaw(this->getRaw() + value.getRaw());
            return *new_fp;
        } else {
            // TO-DO
            return *(new low_fixed_point_t(fractional_bits, outside_bits));
        }
    }

    fixed_point_t& operator+=(const fixed_point_t& value) override {
        if(this->fractional_bits == value.fractional_bits && this->outside_bits == value.outside_bits) {
            setRaw(getRaw() + value.getRaw());
            return *this;
        } else {
            // TO-DO
            return *this;
        }
    }

    // Difference

    fixed_point_t& operator-(const fixed_point_t& value) const override {
        if(this->fractional_bits == value.fractional_bits && this->outside_bits == value.outside_bits) {
            fixed_point_t *new_fp = new low_fixed_point_t(fractional_bits, outside_bits);
            new_fp->setRaw(this->getRaw() - value.getRaw());
            return *new_fp;
        } else {
            // TO-DO
            return *(new low_fixed_point_t(fractional_bits, outside_bits));
        }
    }

    fixed_point_t& operator-=(const fixed_point_t& value) override {
        if(this->fractional_bits == value.fractional_bits && this->outside_bits == value.outside_bits) {
            setRaw(getRaw() - value.getRaw());
            return *this;
        } else {
            // TO-DO
            return *this;
        }
    }

    // Product

    fixed_point_t& operator*(const fixed_point_t& value) const override {
        if(this->fractional_bits == value.fractional_bits && this->outside_bits == value.outside_bits) {
            fixed_point_t *new_fp = new low_fixed_point_t(fractional_bits, outside_bits);
            new_fp->setRaw(this->getRaw() * value.getRaw());
            return *new_fp;
        } else {
            // TO-DO
            return *(new low_fixed_point_t(fractional_bits, outside_bits));
        }
    }

    fixed_point_t& operator*=(const fixed_point_t& value) override {
        if(this->fractional_bits == value.fractional_bits && this->outside_bits == value.outside_bits) {
            setRaw(getRaw() * value.getRaw());
            return *this;
        } else {
            // TO-DO
            return *this;
        }
    }
};

#endif