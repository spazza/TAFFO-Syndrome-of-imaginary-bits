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
    // Cloning
    // -------------------------------------------------

    fixed_point_t& clone() const {
        fixed_point_t *copy = new high_fixed_point_t(integer_bits, outside_bits);
        copy->setRaw(this->getRaw());
        return *copy;
    } 

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

    high_fixed_point_t& operator=(const high_fixed_point_t& value) {
        if(this->integer_bits == value.getIntBits() && this->fractional_bits == value.getFracBits()) {
            setRaw(value.getRaw());
            return *this;
        } else {
            high_fixed_point_t temp = dynamic_cast<high_fixed_point_t&>(value.clone());
            temp.convert(this->integer_bits, this->outside_bits);

            return *this = temp;
        }
    }
    
    fixed_point_t& operator=(const fixed_point_t& value) override {
        if(this->integer_bits == value.getIntBits() && this->outside_bits == value.getOutBits()) {
            setRaw(value.getRaw());
            return *this;
        } else {
            fixed_point_t *temp = &value.clone();
            temp->convert(this->integer_bits, this->outside_bits);

            return *this = *temp;
        }
    }

    // -------------------------------------------------
    // Logic operators
    // -------------------------------------------------

    bool operator<(const fixed_point_t& value) const override {
        if(this->integer_bits == value.getIntBits() && this->outside_bits == value.getOutBits()) {
            return this->getRaw() < value.getRaw();
        } else {
            fixed_point_t& temp = value.clone();
            temp.convert(this->integer_bits, this->outside_bits);

            return *this < temp;
        }
    }

    bool operator>(const fixed_point_t& value) const override {
        if(this->integer_bits == value.getIntBits() && this->outside_bits == value.getOutBits()) {
            return this->getRaw() > value.getRaw();
        } else {
            fixed_point_t& temp = value.clone();
            temp.convert(this->integer_bits, this->outside_bits);

            return *this > temp;
        }
    }

    bool operator==(const fixed_point_t& value) const override {
        if(this->integer_bits == value.getIntBits() && this->outside_bits == value.getOutBits()) {
            return this->getRaw() == value.getRaw();
        } else {
            fixed_point_t& temp = value.clone();
            temp.convert(this->integer_bits, this->outside_bits);

            return *this == temp;
        }
    }

    bool operator!=(const fixed_point_t& value) const override {
        if(this->integer_bits == value.getIntBits() && this->outside_bits == value.getOutBits()) {
            return this->getRaw() != value.getRaw();
        } else {
            fixed_point_t& temp = value.clone();
            temp.convert(this->integer_bits, this->outside_bits);

            return *this != temp;
        }
    }

    bool operator<=(const fixed_point_t& value) const override {
        if(this->integer_bits == value.getIntBits() && this->outside_bits == value.getOutBits()) {
            return !(*this > value);
        } else {
            fixed_point_t& temp = value.clone();
            temp.convert(this->integer_bits, this->outside_bits);

            return *this <= temp;
        }
    }

    bool operator>=(const fixed_point_t& value) const override {
        if(this->integer_bits == value.getIntBits() && this->outside_bits == value.getOutBits()) {
            return !(*this < value);
        } else {
            fixed_point_t& temp = value.clone();
            temp.convert(this->integer_bits, this->outside_bits);

            return *this >= temp;
        }
    }

    // -------------------------------------------------
    // Arithmetic operators
    // -------------------------------------------------

    // Sum

    fixed_point_t& operator+(const fixed_point_t& value) const override {
        if(this->integer_bits == value.getIntBits() && this->outside_bits == value.getOutBits()) {
            fixed_point_t *new_fp = new high_fixed_point_t(integer_bits, outside_bits);
            new_fp->setRaw(this->getRaw() + value.getRaw());
            return *new_fp;
        } else {
            fixed_point_t& temp = value.clone();
            temp.convert(this->integer_bits, this->outside_bits);

            return *this + temp;
        }
    }

    fixed_point_t& operator+=(const fixed_point_t& value) override {
        if(this->integer_bits == value.getIntBits() && this->outside_bits == value.getOutBits()) {
            setRaw(getRaw() + value.getRaw());
            return *this;
        } else {
            fixed_point_t& temp = value.clone();
            temp.convert(this->integer_bits, this->outside_bits);

            return *this += temp;
        }
    }

    // Difference

    fixed_point_t& operator-(const fixed_point_t& value) const override {
        if(this->integer_bits == value.getIntBits() && this->outside_bits == value.getOutBits()) {
            fixed_point_t *new_fp = new high_fixed_point_t(integer_bits, outside_bits);
            new_fp->setRaw(this->getRaw() - value.getRaw());
            return *new_fp;
        } else {
            fixed_point_t& temp = value.clone();
            temp.convert(this->integer_bits, this->outside_bits);

            return *this - temp;
        }
    }

    fixed_point_t& operator-=(const fixed_point_t& value) override {
        if(this->integer_bits == value.getIntBits() && this->outside_bits == value.getOutBits()) {
            setRaw(getRaw() - value.getRaw());
            return *this;
        } else {
            fixed_point_t& temp = value.clone();
            temp.convert(this->integer_bits, this->outside_bits);

            return *this -= temp;
        }
    }

    // Product

    fixed_point_t& operator*(const fixed_point_t& value) const override {
        if(integer_bits == value.getIntBits() && outside_bits == value.getOutBits()) {
            // Create a new fixed_point_t with extended range in order to contain the entire value generated by the multiplication
            fixed_point_t *new_fp = new high_fixed_point_t(integer_bits + value.getIntBits(), outside_bits + value.getOutBits());

            new_fp->setRaw(getRaw() * value.getRaw());

            // Come back to the previous representation, this may cause a loss of bits 
            new_fp->convert(integer_bits, outside_bits);
            return *new_fp;
        } else {
            fixed_point_t& temp = value.clone();
            temp.convert(this->integer_bits, this->outside_bits);

            return *this * temp;
        }
    }

    fixed_point_t& operator*=(const fixed_point_t& value) override {
        if(integer_bits == value.getIntBits() && outside_bits == value.getOutBits()) {
            // Save the current raw because in the next operations it is modified
            raw_t curr_raw = getRaw();

            // Convert the current object into a fixed_point_t with extended range in order to contain 
            // the entire value generated by the multiplication
            convert(integer_bits + value.getIntBits(), outside_bits + value.getOutBits());

            setRaw(curr_raw * value.getRaw());

            // Come back to the previous representation, this may cause a loss of bits 
            convert(value.getIntBits(), value.getOutBits());
            return *this;
        } else {
            fixed_point_t& temp = value.clone();
            temp.convert(this->integer_bits, this->outside_bits);

            return *this *= temp;
        }
    }

    // Division

    fixed_point_t& operator/(const fixed_point_t& value) const override {
        if(integer_bits == value.getIntBits() && outside_bits == value.getOutBits()) {
            fixed_point_t *new_fp = new high_fixed_point_t(integer_bits, outside_bits);

            raw_t intermediate = getRaw();

            intermediate >>= value.getOutBits();
            intermediate /= value.getRaw();

            new_fp->setRaw(intermediate);

            return *new_fp;
        } else {
            fixed_point_t& temp = value.clone();
            temp.convert(this->integer_bits, this->outside_bits);

            return *this / temp;
        }
    }

    fixed_point_t& operator/=(const fixed_point_t& value) override {
        if(integer_bits == value.getIntBits() && outside_bits == value.getOutBits()) {

            raw_t intermediate = getRaw();

            intermediate >>= value.getOutBits();

            intermediate /= value.getRaw();

            setRaw(intermediate);
            
            return *this;
        } else {
            fixed_point_t& temp = value.clone();
            temp.convert(this->integer_bits, this->outside_bits);

            return *this /= temp;
        }
    }

    // -------------------------------------------------
    // Conversion
    // -------------------------------------------------

    void convert(unsigned int new_int_bits, unsigned int new_out_bits) override {
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

    // -------------------------------------------------
    // Print
    // -------------------------------------------------
    
    friend std::ostream& operator<<(std::ostream& stream, const high_fixed_point_t& fp) {
        stream << fp.getValue();
        return stream;
    }
};

#endif