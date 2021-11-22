#ifndef GROUP_TEST
#define BOOST_TEST_MODULE Sum
#include <boost/test/included/unit_test.hpp>
#endif

#include <boost/test/unit_test.hpp>
#include <boost/test/data/test_case.hpp>
#include <boost/mpl/list.hpp>
#include <boost/mpl/at.hpp>
#include <boost/mpl/int.hpp>

#include <limits>

#include "extended_fixed_point.hpp"

using namespace boost::mpl;
namespace bdata = boost::unit_test::data;

/**
 * Test to verify the correctness of the sum operation with all the possible representations.
 * Test with same types
 * Test with different types
 */

BOOST_AUTO_TEST_SUITE(Sum_test)

// Sum with INT_BITS >= 0 and FRAC_BITS >= 0 - Integer values

const int32_t int_test_array_1[] = { // Corner case
                                     0, 0, std::numeric_limits<int16_t>::min(), 
                                     // Random values
                                     60358, 2945, 62807, 29439, 7296, 21775, 65234, 38555, 6604, 54081,
                                     // Random negative values
                                     -45709, -53501, -40104, -40522, -63042, -65202, -10786, -58019, -13791, -49198};

const int32_t int_test_array_2[] = { // Corner case
                                     0, std::numeric_limits<int16_t>::max(), 0,
                                     // Random values
                                     552, 13528, 56175, 22604, 6023, 20886, 60537, 35870, 18076, 58879,
                                     // Random negative values
                                     -16359, -34118, -22997, -21481, -60146, -17239, -3059, -31715, -5660, -27597};

BOOST_DATA_TEST_CASE(Sum_integer_same_type, bdata::make(int_test_array_1) ^ bdata::make(int_test_array_2), v1, v2) {
    extended_fixed_point_t<16,0> num1(v1);
    extended_fixed_point_t<16,0> num2(v2);
    extended_fixed_point_t<16,0> res1;

    extended_fixed_point_t<16,8> num3(v1);
    extended_fixed_point_t<16,8> num4(v2);
    extended_fixed_point_t<16,8> res2;

    extended_fixed_point_t<32,16> num5(v1);
    extended_fixed_point_t<32,16> num6(v2);
    extended_fixed_point_t<32,16> res3;

    res1 = num1 + num2;
    res2 = num3 + num4;
    res3 = num5 + num6;

    BOOST_TEST(res1 == v1 + v2);
    BOOST_TEST(res2 == v1 + v2);
    BOOST_TEST(res3 == v1 + v2);
    BOOST_TEST(num1 + num2 == v1 + v2);
    BOOST_TEST(num3 + num4 == v1 + v2);
    BOOST_TEST(num5 + num6 == v1 + v2);
    
    num1 += num2;
    num3 += num4;
    num5 += num6;

    BOOST_TEST(num1 == v1 + v2);
    BOOST_TEST(num3 == v1 + v2);
    BOOST_TEST(num5 == v1 + v2);
}

// Sum with INT_BITS >= 0 and FRAC_BITS >= 0 - Floating point values

const float float_test_array_1[] = { // Corner case
                                     0.0,
                                     // Random values
                                     29641.436951, 55892.721527, 47866.858734, 38982.110138, 11995.195908, 65018.022354, 47592.883682, 11232.018158, 733.179504, 17111.686813};

const float float_test_array_2[] = { // Corner case
                                     0.0,
                                     // Random values
                                     37758.218964, 11420.790100, 26159.802307, 12541.457916, 1756.990570, 23383.192383, 38275.851257, 59305.757507, 15270.562973, 14160.928177};

BOOST_DATA_TEST_CASE(Sum_float_same_type, bdata::make(float_test_array_1) ^ bdata::make(float_test_array_2), v1, v2) {
    float TOLERANCE = 1e-9; //FIX HERE!!!
    extended_fixed_point_t<16,32> num1(v1);
    extended_fixed_point_t<16,32> num2(v2);
    extended_fixed_point_t<16,32> res1;

    extended_fixed_point_t<16,32> num3(v1);
    extended_fixed_point_t<16,32> num4(v2);
    extended_fixed_point_t<16,32> res2;

    extended_fixed_point_t<32,64> num5(v1);
    extended_fixed_point_t<32,64> num6(v2);
    extended_fixed_point_t<32,64> res3;

    res1 = num1 + num2;
    res2 = num3 + num4;
    res3 = num5 + num6;

    BOOST_TEST(res1 - (v1 + v2) < TOLERANCE);
    BOOST_TEST(res2 - (v1 + v2) < TOLERANCE);
    BOOST_TEST(res3 - (v1 + v2) < TOLERANCE);
    BOOST_TEST((num1 + num2) - (v1 + v2) < TOLERANCE);
    BOOST_TEST((num3 + num4) - (v1 + v2) < TOLERANCE);
    BOOST_TEST((num5 + num6) - (v1 + v2) < TOLERANCE);
    
    num1 += num2;
    num3 += num4;
    num5 += num6;

    BOOST_TEST(num1 - (v1 + v2) < TOLERANCE);
    BOOST_TEST(num3 - (v1 + v2) < TOLERANCE);
    BOOST_TEST(num5 - (v1 + v2) < TOLERANCE);
}

// Sum with INT_BITS >= 0 and FRAC_BITS <  0 - Integer values

const int32_t high_int_test_array_1[] = { // Corner case
                                          0, 261888,
                                          // Random values
                                          9728, 199168, 109056, 152320, 208896, 64256, 228096, 245504, 101632, 52480,
                                          // Random negative values
                                          -155392, -257536, -29952, -228608, -137472, -258816, -255744, -148992, -88832, -142592};

const int32_t high_int_test_array_2[] = { // Corner case
                                          261888, 0,
                                          // Random values
                                          8448, 11520, 2560, 9984, 3840, 14848, 768, 14336, 4352, 13568,
                                          // Random negative values
                                          -2304, -4352, -1024, -768, -512, -4096, -7424, -1792, -2816, -7936};

BOOST_DATA_TEST_CASE(Sum_high_integer_same_type, bdata::make(high_int_test_array_1) ^ bdata::make(high_int_test_array_2), v1, v2) {
    extended_fixed_point_t<16,-2> num1(v1);
    extended_fixed_point_t<16,-2> num2(v2);
    extended_fixed_point_t<16,-2> res1;

    extended_fixed_point_t<16,-8> num3(v1);
    extended_fixed_point_t<16,-8> num4(v2);
    extended_fixed_point_t<16,-8> res2;

    res1 = num1 + num2;
    res2 = num3 + num4;

    BOOST_TEST(res1 == v1 + v2);
    BOOST_TEST(res2 == v1 + v2);
    BOOST_TEST(num1 + num2 == v1 + v2);
    BOOST_TEST(num3 + num4 == v1 + v2);

    num1 += num2;
    num3 += num4;

    BOOST_TEST(num1 == v1 + v2);
    BOOST_TEST(num3 == v1 + v2);
}

// Sum with INT_BITS >= 0 and FRAC_BITS <  0 - Floating point values



BOOST_AUTO_TEST_SUITE_END()