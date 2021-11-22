#ifndef GROUP_TEST
#define BOOST_TEST_MODULE Raw_value_constructor_initialization
#include <boost/test/included/unit_test.hpp>
#endif

#include <boost/test/unit_test.hpp>
#include <boost/test/data/test_case.hpp>

#include <typeinfo>
#include <limits>

#include "extended_fixed_point.hpp"

using namespace boost;
namespace bdata = boost::unit_test::data;

/**
 * Test to verify the correct value assignment using the costructors.
 */

BOOST_AUTO_TEST_SUITE(Raw_value_initialization)

// Integer values

const int32_t integer_values[] = {0, 1, -1, 100, -100, std::numeric_limits<int32_t>::max(), std::numeric_limits<int32_t>::min()};

BOOST_DATA_TEST_CASE(Raw_value_integer_assignment, bdata::make(integer_values), value) {
    extended_fixed_point_t<31,0> efp1(value);
    extended_fixed_point_t<31,31> efp2(value);

    BOOST_TEST(efp1.getRaw() == value);
    BOOST_TEST(efp1.getValue() == value);

    BOOST_TEST(efp2.getRaw() == static_cast<int64_t>(value) << 31);
    BOOST_TEST(efp2.getValue() == value);
}

// High integer values (numbers with comma shifted on right)

const int32_t integer_values_high[] = { /* Extreme values*/ 
                                        0, 2147483392, -256,
                                        /* Random values */
                                        1508100352, 702999040, 1391671552, 102770176, 409824256, 1733782528, 1594623488, 141345536
                                      };

BOOST_DATA_TEST_CASE(Raw_value_integer_assignment_neg_frac, bdata::make(integer_values_high), value) {
    extended_fixed_point_t<31, 0> efp1(value);
    extended_fixed_point_t<31, -4> efp2(value);
    extended_fixed_point_t<31, -8> efp3(value);

    BOOST_TEST(efp1.getRaw() == value);
    BOOST_TEST(efp1.getValue() == value);

    BOOST_TEST(efp2.getRaw() == value >> abs(-4));
    BOOST_TEST(efp2.getValue() == value);

    BOOST_TEST(efp3.getRaw() == value >> abs(-8));
    BOOST_TEST(efp3.getValue() == value);
}

// Fractional values

const float float_values[] = {0.0, 0.1, -0.1, 100.001, -100.001, 100000.000001, -100000.000001};

BOOST_DATA_TEST_CASE(Raw_value_float_assignment, bdata::make(float_values), value) {
    extended_fixed_point_t<31, 31> efp(value);
    int64_t raw_booster = ((int64_t)1) << 31;

    BOOST_TEST(efp.getRaw() == (int64_t) (value * raw_booster));
    BOOST_TEST(efp.getValueF() == value);
}

// Low fractional values (numbers with comma shifted on left)

const float low_float_values[] = {0.0, 0.0001, -0.0001, 0.0000001, -0.0000001};

BOOST_DATA_TEST_CASE(Raw_value_float_assignment_neg_int, bdata::make(low_float_values), value) {
    extended_fixed_point_t<-2, 31> efp1(value);
    extended_fixed_point_t<-4, 31> efp2(value);
    extended_fixed_point_t<-8, 31> efp3(value);
    int32_t raw_booster = ((int32_t)1) << 31;

    BOOST_TEST(efp1.getRaw() == ((int32_t) (value * raw_booster)) << abs(-2));
    BOOST_TEST(abs(efp1.getValueF() - value) < 1e-18);

    BOOST_TEST(efp2.getRaw() == ((int32_t) (value * raw_booster)) << abs(-4));
    BOOST_TEST(abs(efp2.getValueF() - value) < 1e-18);

    BOOST_TEST(efp3.getRaw() == ((int32_t) (value * raw_booster)) << abs(-8));
    BOOST_TEST(abs(efp3.getValueF() - value) < 1e-18);
}

BOOST_AUTO_TEST_SUITE_END()