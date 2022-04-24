#ifndef FIXED_POINT_HPP
#define FIXED_POINT_HPP
#define PURE 0 //for pure virtual methods

#include <limits>
#include <cmath>
#include <ostream>
#include <iomanip>

#ifdef _IS64bit
typedef __int128 raw_t;
#else
typedef int64_t raw_t;
#endif

struct fixed_point_t {

    // -------------------------------------------------
    // Internal attributes
    // -------------------------------------------------

public:

    /**
     * @brief It represents the low limit of the range that composes the raw value.
     */
    static const int low_lim = 0;

    /**
     * @brief It represents the high limit of the range that composes the raw value.
     */
    static const int high_lim = std::numeric_limits<raw_t>::digits;

protected:
    
    /**
     * @brief Integer bits that make up the fixed-point.
     */
    unsigned int integer_bits;

    /**
     * @brief Fractional bits that make up the fixed-point.
     */
    unsigned int fractional_bits;

    /**
     * @brief Bits that are considered out of the range of the raw value.
     */
    unsigned int outside_bits;

private:

    /**
     * @brief Fixed point variable that represents the number.
     */
    raw_t raw;

protected:

    // -------------------------------------------------
    // Constructors
    // -------------------------------------------------

    /**
     * @brief Construct a new fixed_point_t object initializing its range values and the bits out of the range.
     * @param integer_bits integer bits that make up the fixed-point.
     * @param fractional_bits fractional bits that make up the fixed-point.
     * @param outside_bits bits that are considered out of the range.
     */
    fixed_point_t(const int integer_bits, const int fractional_bits, const int outside_bits) : integer_bits(integer_bits), fractional_bits(fractional_bits), outside_bits(outside_bits) {}

public:

    // -------------------------------------------------
    // Cloning
    // -------------------------------------------------

    virtual fixed_point_t& clone() const = PURE;

    // -------------------------------------------------
    // Getter
    // -------------------------------------------------
    
    /**
     * @brief Get the value of the raw object.
     * @return auto value of the raw object.
     */
    raw_t getRaw() const { return raw; }

    /**
     * @brief Get the integer bits that make up the fixed_point_t object.
     * @return unsigned int integer bits of the fixed_point_t.
     */
    unsigned int getIntBits() const { return integer_bits; }

    /**
     * @brief Get the fractional bits that make up the fixed_point_t object.
     * @return unsigned int fractional bits of the fixed_point_t.
     */
    unsigned int getFracBits() const { return fractional_bits; }

    /**
     * @brief Get the outside bits that make up the fixed_point_t object.
     * @return unsigned int outside bits of the fixed_point_t.
     */
    unsigned int getOutBits() const { return outside_bits; }

    // -------------------------------------------------
    // Setter
    // -------------------------------------------------

    /**
     * @brief Set the value of the raw object.
     * @param value transformed value to be assigned at the raw
     */
    void setRaw(raw_t value) { this->raw = value; }

public:

    // -------------------------------------------------
    // Accessors
    // -------------------------------------------------

    /**
     * @brief Get the floating point value of the fixed_point.
     * @return float value of the fixed_point.
     */
    virtual float getValueF() const = PURE;

    /**
     * @brief Get the double precision floating point value of the fixed_point.
     * @return float value of the fixed_point.
     */
    virtual double getValueFD() const = PURE;

    /**
     * @brief Get the long double precision floating point value of the fixed_point.
     * @return float value of the fixed_point.
     */
    virtual long double getValueFLD() const = PURE;

    /**
     * @brief Get the integer value of the fixed_point.
     * @return raw_t integer value of the fixed_point.
     */
    virtual raw_t getValue() const = PURE;

    // -------------------------------------------------
    // Assignment operators
    // -------------------------------------------------

    virtual fixed_point_t& operator=(const fixed_point_t& value) = PURE;

    // -------------------------------------------------
    // Logic operators
    // -------------------------------------------------

    virtual bool operator<(const fixed_point_t& value) const = PURE;

    virtual bool operator>(const fixed_point_t& value) const = PURE;

    virtual bool operator==(const fixed_point_t& value) const = PURE;

    virtual bool operator!=(const fixed_point_t& value) const = PURE;

    virtual bool operator<=(const fixed_point_t& value) const = PURE;

    virtual bool operator>=(const fixed_point_t& value) const = PURE;

    // -------------------------------------------------
    // Arithmetic operators
    // -------------------------------------------------

    // Sum

    virtual fixed_point_t& operator+(const fixed_point_t& value) const = PURE;

    virtual fixed_point_t& operator+=(const fixed_point_t& value) = PURE;

    // Difference

    virtual fixed_point_t& operator-(const fixed_point_t& value) const = PURE;

    virtual fixed_point_t& operator-=(const fixed_point_t& value) = PURE;

    // Product

    virtual fixed_point_t& operator*(const fixed_point_t& value) const = PURE;

    virtual fixed_point_t& operator*=(const fixed_point_t& value) = PURE;

    // Division

    virtual fixed_point_t& operator/(const fixed_point_t& value) const = PURE;

    virtual fixed_point_t& operator/=(const fixed_point_t& value) = PURE;

    // -------------------------------------------------
    // Conversion
    // -------------------------------------------------

    virtual void convert(unsigned int new_first, unsigned int new_second) = PURE;

    // -------------------------------------------------
    // Print
    // -------------------------------------------------

    friend std::ostream& operator<<(std::ostream& stream, const fixed_point_t& fp);
};

#endif