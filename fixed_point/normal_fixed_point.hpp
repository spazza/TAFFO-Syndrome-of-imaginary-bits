#ifndef NORMAL_FIXED_POINT_HPP
#define NORMAL_FIXED_POINT_HPP

#include "fixed_point.hpp"

struct normal_fixed_point_t : public fixed_point_t {

public:

    // -------------------------------------------------
    // Constructors
    // -------------------------------------------------
    normal_fixed_point_t(const int integer_bits, const int fractional_bits) : fixed_point_t(integer_bits, fractional_bits, 0) {
        setRaw(static_cast<raw_t>(0));
    }

    normal_fixed_point_t(const int integer_bits, const int fractional_bits, const int8_t value) : fixed_point_t(integer_bits, fractional_bits, 0) { 
		setRaw(static_cast<raw_t>(value << fractional_bits));
    }

    normal_fixed_point_t(const int integer_bits, const int fractional_bits, const uint8_t value) : fixed_point_t(integer_bits, fractional_bits, 0) { 
        setRaw(static_cast<raw_t>(value << fractional_bits));
    }

    normal_fixed_point_t(const int integer_bits, const int fractional_bits, const int16_t value) : fixed_point_t(integer_bits, fractional_bits, 0) { 
        setRaw(static_cast<raw_t>(value << fractional_bits));
    }

    normal_fixed_point_t(const int integer_bits, const int fractional_bits, const uint16_t value) : fixed_point_t(integer_bits, fractional_bits, 0) { 
        setRaw(static_cast<raw_t>(value << fractional_bits));
    }

    normal_fixed_point_t(const int integer_bits, const int fractional_bits, const int32_t value) : fixed_point_t(integer_bits, fractional_bits, 0) { 
        setRaw(static_cast<raw_t>(value << fractional_bits));
    }

    normal_fixed_point_t(const int integer_bits, const int fractional_bits, const uint32_t value) : fixed_point_t(integer_bits, fractional_bits, 0) { 
        setRaw(static_cast<raw_t>(value << fractional_bits));
    }

    normal_fixed_point_t(const int integer_bits, const int fractional_bits, const int64_t value) : fixed_point_t(integer_bits, fractional_bits, 0) { 
        setRaw(static_cast<raw_t>(value << fractional_bits));
    }

    normal_fixed_point_t(const int integer_bits, const int fractional_bits, const uint64_t value) : fixed_point_t(integer_bits, fractional_bits, 0) { 
        setRaw(static_cast<raw_t>(value << fractional_bits));
    }
 
    normal_fixed_point_t(const int integer_bits, const int fractional_bits, const float value) : fixed_point_t(integer_bits, fractional_bits, 0) { 
        raw_t one = ((raw_t)1) << fractional_bits;
        setRaw((raw_t)(value * one));
    }

    normal_fixed_point_t(const int integer_bits, const int fractional_bits, const double value) : fixed_point_t(integer_bits, fractional_bits, 0) { 
        raw_t one = ((raw_t)1) << fractional_bits;
        setRaw((raw_t)(value * one));
    }

    normal_fixed_point_t(const int integer_bits, const int fractional_bits, const long double value) : fixed_point_t(integer_bits, fractional_bits, 0) { 
        raw_t one = ((raw_t)1) << fractional_bits;
        setRaw((raw_t)(value * one));
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

    raw_t getValue() const override { return static_cast<raw_t>(getRaw() >> fractional_bits); }

    // -------------------------------------------------
    // Assignment operators
    // -------------------------------------------------
    
    fixed_point_t& operator=(const fixed_point_t& value) override {
        if(this->integer_bits == value.getIntBits() && this->fractional_bits == value.getFracBits()) {
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
        if(this->integer_bits == value.getIntBits() && this->fractional_bits == value.getFracBits()) {
            return this->getRaw() < value.getRaw();
        } else {
            // TO-DO
            return false;
        }
    }

    bool operator>(const fixed_point_t& value) const override {
        if(this->integer_bits == value.getIntBits() && this->fractional_bits == value.getFracBits()) {
            return this->getRaw() > value.getRaw();
        } else {
            // TO-DO
            return false;
        }
    }

    bool operator==(const fixed_point_t& value) const override {
        if(this->integer_bits == value.getIntBits() && this->fractional_bits == value.getFracBits()) {
            return this->getRaw() == value.getRaw();
        } else {
            // TO-DO
            return false;
        }
    }

    bool operator!=(const fixed_point_t& value) const override {
        if(this->integer_bits == value.getIntBits() && this->fractional_bits == value.getFracBits()) {
            return this->getRaw() != value.getRaw();
        } else {
            // TO-DO
            return false;
        }
    }

    bool operator<=(const fixed_point_t& value) const override {
        if(this->integer_bits == value.getIntBits() && this->fractional_bits == value.getFracBits()) {
            return !(*this > value);
        } else {
            // TO-DO
            return false;
        }
    }

    bool operator>=(const fixed_point_t& value) const override {
        if(this->integer_bits == value.getIntBits() && this->fractional_bits == value.getFracBits()) {
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
        if(this->integer_bits == value.getIntBits() && this->fractional_bits == value.getFracBits()) {
            fixed_point_t *new_fp = new normal_fixed_point_t(integer_bits, fractional_bits);
            new_fp->setRaw(this->getRaw() + value.getRaw());
            return *new_fp;
        } else {
            // TO-DO
            return *(new normal_fixed_point_t(integer_bits, fractional_bits));
        }
    }

    fixed_point_t& operator+=(const fixed_point_t& value) override {
        if(this->integer_bits == value.getIntBits() && this->fractional_bits == value.getFracBits()) {
            setRaw(getRaw() + value.getRaw());
            return *this;
        } else {
            // TO-DO
            return *this;
        }
    }

    // Difference

    fixed_point_t& operator-(const fixed_point_t& value) const override {
        if(this->integer_bits == value.getIntBits() && this->fractional_bits == value.getFracBits()) {
            fixed_point_t *new_fp = new normal_fixed_point_t(integer_bits, fractional_bits);
            new_fp->setRaw(this->getRaw() - value.getRaw());
            return *new_fp;
        } else {
            // TO-DO
            return *(new normal_fixed_point_t(integer_bits, fractional_bits));
        }
    }

    fixed_point_t& operator-=(const fixed_point_t& value) override {
        if(this->integer_bits == value.getIntBits() && this->fractional_bits == value.getFracBits()) {
            setRaw(getRaw() - value.getRaw());
            return *this;
        } else {
            // TO-DO
            return *this;
        }
    }
    
    // Product

    fixed_point_t& operator*(const fixed_point_t& value) const override {
        if(integer_bits == value.getIntBits() && fractional_bits == value.getFracBits()) {
            // Create a new fixed_point_t with extended range in order to contain the entire value generated by the multiplication
            fixed_point_t *new_fp = new normal_fixed_point_t(integer_bits + value.getIntBits(), fractional_bits + value.getFracBits());

            new_fp->setRaw(getRaw() * value.getRaw());

            // Come back to the previous representation, this may cause a loss of bits 
            new_fp->convert_to_normal_fixed_point_t(integer_bits, fractional_bits);

            return *new_fp;
        } else {
            // TO-DO
            return *(new normal_fixed_point_t(integer_bits, fractional_bits));
        }
    }

    fixed_point_t& operator*=(const fixed_point_t& value) override {
        if(integer_bits == value.getIntBits() && fractional_bits == value.getFracBits()) {
            // Save the current raw because in the next operations it is modified
            raw_t curr_raw = getRaw();

            // Convert the current object into a fixed_point_t with extended range in order to contain 
            // the entire value generated by the multiplication
            convert_to_normal_fixed_point_t(integer_bits + value.getIntBits(), fractional_bits + value.getFracBits());

            setRaw(curr_raw * value.getRaw());

            // Come back to the previous representation, this may cause a loss of bits 
            convert_to_normal_fixed_point_t(value.getIntBits(), value.getFracBits());
            return *this;
        } else {
            // TO-DO
            return *this;
        }
    }

    // Division

    fixed_point_t& operator/(const fixed_point_t& value) const override {
        if(integer_bits == value.getIntBits() && fractional_bits == value.getFracBits()) {
            // Create a new fixed_point_t with extended integer range in order to contain the entire value generated for the quotient
            fixed_point_t *new_fp = new normal_fixed_point_t(integer_bits + value.getFracBits(), fractional_bits);

            // Normalize the dividend to obtain a correct fixed_point
            raw_t intermediate = getRaw();
            intermediate <<= value.getFracBits();

            intermediate /= value.getRaw();

            new_fp->setRaw(intermediate);

            // Come back to the previous representation
            new_fp->convert_to_normal_fixed_point_t(integer_bits, fractional_bits);

            return *new_fp;
        } else {
            // TO-DO
            return *(new normal_fixed_point_t(integer_bits, fractional_bits));
        }
    }

    fixed_point_t& operator/=(const fixed_point_t& value) override {
        if(integer_bits == value.getIntBits() && fractional_bits == value.getFracBits()) {

            raw_t intermediate = getRaw();

            convert_to_normal_fixed_point_t(integer_bits + value.getFracBits(), fractional_bits);

            intermediate <<= value.getFracBits();

            intermediate /= value.getRaw();

            setRaw(intermediate);
            convert_to_normal_fixed_point_t(integer_bits, fractional_bits);

            return *this;
        } else {
            // TO-DO
            return *this;
        }
    }

    // -------------------------------------------------
    // Conversion
    // -------------------------------------------------

    void convert_to_normal_fixed_point_t(unsigned int new_int_bits, unsigned int new_frac_bits) override {
        if(new_frac_bits > this->fractional_bits) {
            unsigned int sha = new_frac_bits - this->fractional_bits;
            setRaw(getRaw() << sha);
        } else {
            unsigned int sha = this->fractional_bits - new_frac_bits;
            setRaw(getRaw() >> sha);
        }

        this->integer_bits = new_int_bits;
        this->fractional_bits = new_frac_bits;
    }

    void convert_to_high_fixed_point_t(unsigned int new_int_bits, unsigned int new_out_bits) override {
        // TO-DO
    }

    void convert_to_low_fixed_point_t(unsigned int new_frac_bits, unsigned int new_out_bits) override {
        // TO-DO
    }

    // -------------------------------------------------
    // Print
    // -------------------------------------------------
    
    friend std::ostream& operator<<(std::ostream& stream, const normal_fixed_point_t& fp) {
        auto old_precision = stream.precision();
        auto old_flags = stream.flags();

        stream << std::fixed << std::setprecision((fp.fractional_bits * 3 + 9) / 10)
           << fp.getValueF() << std::setprecision(old_precision);

        stream.flags(old_flags);
        return stream;
    }
};

#endif