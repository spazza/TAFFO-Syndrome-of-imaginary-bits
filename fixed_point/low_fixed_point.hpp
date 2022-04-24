#ifndef LOW_FIXED_POINT_HPP
#define LOW_FIXED_POINT_HPP

#include "fixed_point.hpp"

struct low_fixed_point_t : public fixed_point_t {

    low_fixed_point_t(const int fractional_bits, const int outside_bits) : fixed_point_t(0, fractional_bits, outside_bits) {
        setRaw(static_cast<raw_t>(0));
    }

    low_fixed_point_t(const int fractional_bits, const int outside_bits, const float value) : fixed_point_t(0, fractional_bits, outside_bits) { 
        raw_t one = ((raw_t)1) << fractional_bits;
        setRaw(((raw_t)(value * one)) << outside_bits);
    }

    low_fixed_point_t(const int fractional_bits, const int outside_bits, const double value) : fixed_point_t(0, fractional_bits, outside_bits) { 
        raw_t one = ((raw_t)1) << fractional_bits;
        setRaw(((raw_t)(value * one)) << outside_bits);
    }

    low_fixed_point_t(const int fractional_bits, const int outside_bits, const long double value) : fixed_point_t(0, fractional_bits, outside_bits) { 
        raw_t one = ((raw_t)1) << fractional_bits;
        setRaw(((raw_t)(value * one)) << outside_bits);
    }    

public:

    // -------------------------------------------------
    // Cloning
    // -------------------------------------------------

    fixed_point_t& clone() const {
        fixed_point_t *copy = new low_fixed_point_t(fractional_bits, outside_bits);
        copy->setRaw(this->getRaw());
        return *copy;
    } 

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

    low_fixed_point_t& operator=(const low_fixed_point_t& value) {
        if(this->integer_bits == value.getIntBits() && this->fractional_bits == value.getFracBits()) {
            setRaw(value.getRaw());
            return *this;
        } else {
            low_fixed_point_t temp = dynamic_cast<low_fixed_point_t&>(value.clone());
            temp.convert(this->fractional_bits, this->outside_bits);

            return *this = temp;
        }
    }

    fixed_point_t& operator=(const fixed_point_t& value) override {
        if(this->fractional_bits == value.getFracBits() && this->outside_bits == value.getOutBits()) {
            setRaw(value.getRaw());
            return *this;
        } else {
            fixed_point_t *temp = &value.clone();
            temp->convert(this->fractional_bits, this->outside_bits);

            return *this = *temp;
        }
    }

    // -------------------------------------------------
    // Logic operators
    // -------------------------------------------------

    bool operator<(const fixed_point_t& value) const override {
        if(this->fractional_bits == value.getFracBits() && this->outside_bits == value.getOutBits()) {
            return this->getRaw() < value.getRaw();
        } else {
            fixed_point_t& temp = value.clone();
            temp.convert(this->fractional_bits, this->outside_bits);

            return *this < temp;
        }
    }

    bool operator>(const fixed_point_t& value) const override {
        if(this->fractional_bits == value.getFracBits() && this->outside_bits == value.getOutBits()) {
            return this->getRaw() > value.getRaw();
        } else {
            fixed_point_t& temp = value.clone();
            temp.convert(this->fractional_bits, this->outside_bits);

            return *this > temp;
        }
    }

    bool operator==(const fixed_point_t& value) const override {
        if(this->fractional_bits == value.getFracBits() && this->outside_bits == value.getOutBits()) {
            return this->getRaw() == value.getRaw();
        } else {
            fixed_point_t& temp = value.clone();
            temp.convert(this->fractional_bits, this->outside_bits);

            return *this == temp;
        }
    }

    bool operator!=(const fixed_point_t& value) const override {
        if(this->fractional_bits == value.getFracBits() && this->outside_bits == value.getOutBits()) {
            return this->getRaw() != value.getRaw();
        } else {
            fixed_point_t& temp = value.clone();
            temp.convert(this->fractional_bits, this->outside_bits);

            return *this != temp;
        }
    }

    bool operator<=(const fixed_point_t& value) const override {
        if(this->fractional_bits == value.getFracBits() && this->outside_bits == value.getOutBits()) {
            return !(*this > value);
        } else {
            fixed_point_t& temp = value.clone();
            temp.convert(this->fractional_bits, this->outside_bits);

            return *this <= temp;
        }
    }

    bool operator>=(const fixed_point_t& value) const override {
        if(this->fractional_bits == value.getFracBits() && this->outside_bits == value.getOutBits()) {
            return !(*this < value);
        } else {
            fixed_point_t& temp = value.clone();
            temp.convert(this->fractional_bits, this->outside_bits);

            return *this >= temp;
        }
    }

    // -------------------------------------------------
    // Arithmetic operators
    // -------------------------------------------------

    // Sum

    fixed_point_t& operator+(const fixed_point_t& value) const override {
        if(this->fractional_bits == value.getFracBits() && this->outside_bits == value.getOutBits()) {
            fixed_point_t *new_fp = new low_fixed_point_t(fractional_bits, outside_bits);
            new_fp->setRaw(this->getRaw() + value.getRaw());
            return *new_fp;
        } else {
            fixed_point_t& temp = value.clone();
            temp.convert(this->fractional_bits, this->outside_bits);

            return *this + temp;
        }
    }

    fixed_point_t& operator+=(const fixed_point_t& value) override {
        if(this->fractional_bits == value.getFracBits() && this->outside_bits == value.getOutBits()) {
            setRaw(getRaw() + value.getRaw());
            return *this;
        } else {
            fixed_point_t& temp = value.clone();
            temp.convert(this->fractional_bits, this->outside_bits);

            return *this += temp;
        }
    }

    // Difference

    fixed_point_t& operator-(const fixed_point_t& value) const override {
        if(this->fractional_bits == value.getFracBits() && this->outside_bits == value.getOutBits()) {
            fixed_point_t *new_fp = new low_fixed_point_t(fractional_bits, outside_bits);
            new_fp->setRaw(this->getRaw() - value.getRaw());
            return *new_fp;
        } else {
            fixed_point_t& temp = value.clone();
            temp.convert(this->fractional_bits, this->outside_bits);

            return *this - temp;
        }
    }

    fixed_point_t& operator-=(const fixed_point_t& value) override {
        if(this->fractional_bits == value.getFracBits() && this->outside_bits == value.getOutBits()) {
            setRaw(getRaw() - value.getRaw());
            return *this;
        } else {
            fixed_point_t& temp = value.clone();
            temp.convert(this->fractional_bits, this->outside_bits);

            return *this -= temp;
        }
    }

    // Product

    fixed_point_t& operator*(const fixed_point_t& value) const override {
        if(fractional_bits == value.getFracBits() && outside_bits == value.getOutBits()) {
            // Create a new fixed_point_t with extended range in order to contain the entire value generated by the multiplication
            fixed_point_t *new_fp = new low_fixed_point_t(fractional_bits + value.getFracBits(), outside_bits + value.getOutBits());

            new_fp->setRaw(getRaw() * value.getRaw());

            // Come back to the previous representation, this may cause a loss of bits 
            new_fp->convert(fractional_bits, outside_bits);
            return *new_fp;
        } else {
            fixed_point_t& temp = value.clone();
            temp.convert(this->fractional_bits, this->outside_bits);

            return *this * temp;
        }
    }

    fixed_point_t& operator*=(const fixed_point_t& value) override {
        if(fractional_bits == value.getFracBits() && outside_bits == value.getOutBits()) {
            // Save the current raw because in the next operations it is modified
            raw_t curr_raw = getRaw();

            // Convert the current object into a fixed_point_t with extended range in order to contain 
            // the entire value generated by the multiplication
            convert(fractional_bits + value.getFracBits(), outside_bits + value.getOutBits());

            setRaw(curr_raw * value.getRaw());

            // Come back to the previous representation, this may cause a loss of bits 
            convert(value.getFracBits(), value.getOutBits());

            return *this;
        } else {
            fixed_point_t& temp = value.clone();
            temp.convert(this->fractional_bits, this->outside_bits);

            return *this *= temp;
        }
    }

    // Division

    fixed_point_t& operator/(const fixed_point_t& value) const override {
        if(fractional_bits == value.getFracBits() && outside_bits == value.getOutBits()) {
            
            fixed_point_t *new_fp = new low_fixed_point_t(fractional_bits, outside_bits);

            // Normalize the dividend to obtain a correct fixed_point
            raw_t intermediate = getRaw();
            intermediate <<= value.getFracBits() + value.getOutBits();

            intermediate /= value.getRaw();

            new_fp->setRaw(intermediate);

            return *new_fp;
        } else {
            fixed_point_t& temp = value.clone();
            temp.convert(this->fractional_bits, this->outside_bits);

            return *this / temp;
        }
    }

    fixed_point_t& operator/=(const fixed_point_t& value) override {
        if(fractional_bits == value.getFracBits() && outside_bits == value.getOutBits()) {

            raw_t intermediate = getRaw();

            intermediate <<= value.getFracBits() + value.getOutBits();

            intermediate /= value.getRaw();

            setRaw(intermediate);

            return *this;
        } else {
            fixed_point_t& temp = value.clone();
            temp.convert(this->fractional_bits, this->outside_bits);

            return *this /= temp;
        }
    }

    // -------------------------------------------------
    // Conversion
    // -------------------------------------------------

    void convert(unsigned int new_frac_bits, unsigned int new_out_bits) override {
        if(new_frac_bits > this->fractional_bits) {
            unsigned int sha = new_frac_bits - this->fractional_bits;
            setRaw(getRaw() << sha);
        } else {
            unsigned int sha = this->fractional_bits - new_frac_bits;
            setRaw(getRaw() >> sha);
        }

        if(new_out_bits > this->outside_bits) {
            unsigned int sha = new_out_bits - this->outside_bits;
            setRaw(getRaw() << sha);
        } else {
            unsigned int sha = this->outside_bits - new_out_bits;
            setRaw(getRaw() >> sha);
        }

        this->fractional_bits = new_frac_bits;
        this->outside_bits = new_out_bits;
    }
    
    // -------------------------------------------------
    // Print
    // -------------------------------------------------

    friend std::ostream& operator<<(std::ostream& stream, const low_fixed_point_t& fp) {
        auto old_precision = stream.precision();
        auto old_flags = stream.flags();

        stream << std::fixed << std::setprecision(((fp.fractional_bits + fp.outside_bits) * 3 + 9) / 10)
           << fp.getValueF() << std::setprecision(old_precision);

        stream.flags(old_flags);
        return stream;
    }
};

#endif