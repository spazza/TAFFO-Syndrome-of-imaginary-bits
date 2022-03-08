#ifndef GROUP_TEST
#define BOOST_TEST_MODULE Product
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
 * Test to verify the correctness of the product operation with all the possible representations.
 * Test with same types
 *  - INT_BITS >= 0, FRAC_BITS >= 0 - Integer values
 *  - INT_BITS >= 0, FRAC_BITS >= 0 - Floating point values
 *  - INT_BITS >= 0, FRAC_BITS <  0 - Integer values
 *  - INT_BITS <  0, FRAC_BITS >= 0 - Floating point values
 * Test with different types
 *  - INT_BITS >= 0, FRAC_BITS >= 0 and INT_BITS >= 0, FRAC_BITS >= 0 - Integer values
 *  - INT_BITS >= 0, FRAC_BITS >= 0 and INT_BITS >= 0, FRAC_BITS >= 0 - Floating point values
 *  - INT_BITS >= 0, FRAC_BITS <  0 and INT_BITS >= 0, FRAC_BITS <  0 - Integer values
 *  - INT_BITS <  0, FRAC_BITS >= 0 and INT_BITS <  0, FRAC_BITS >= 0 - Floating point values
 *  - INT_BITS >= 0, FRAC_BITS >= 0 and INT_BITS >= 0, FRAC_BITS <  0 - Integer values
 *  - INT_BITS >= 0, FRAC_BITS >= 0 and INT_BITS <  0, FRAC_BITS >= 0 - Floating point values
 */

BOOST_AUTO_TEST_SUITE(Product_test)

// Product with INT_BITS >= 0 and FRAC_BITS >= 0 - Integer values

const int32_t int_test_array_1[] = { // Corner case
                                     0, 0, std::numeric_limits<int16_t>::min(), 
                                     // Random values
                                     292, 379, 432, 807, 185, 457, 211, 386, 633, 1003, 
                                     // Random negative values
                                     -271, -79, -856, -331, -400, -775, -785, -251, -76, -791};

const int32_t int_test_array_2[] = { // Corner case
                                     0, std::numeric_limits<int16_t>::max(), 0,
                                     // Random values
                                     550, 886, 125, 956, 739, 887, 234, 386, 196, 393,
                                     // Random negative values
                                     -605, -309, -947, -391, -673, -507, -325, -985, -682, -750};

BOOST_DATA_TEST_CASE(Product_integer_same_type, bdata::make(int_test_array_1) ^ bdata::make(int_test_array_2), v1, v2) {
    extended_fixed_point_t<16,0> num1(v1);
    extended_fixed_point_t<16,0> num2(v2);
    extended_fixed_point_t<16,0> res1;

    extended_fixed_point_t<16,8> num3(v1);
    extended_fixed_point_t<16,8> num4(v2);
    extended_fixed_point_t<16,8> res2;

    extended_fixed_point_t<32,16> num5(v1);
    extended_fixed_point_t<32,16> num6(v2);
    extended_fixed_point_t<32,16> res3;

    res1 = num1 * num2;
    res2 = num3 * num4;
    res3 = num5 * num6;

    BOOST_TEST(res1 == v1 * v2);
    BOOST_TEST(res2 == v1 * v2);
    BOOST_TEST(res3 == v1 * v2);
    BOOST_TEST(num1 * num2 == v1 * v2);
    BOOST_TEST(num3 * num4 == v1 * v2);
    BOOST_TEST(num5 * num6 == v1 * v2);
    
    num1 *= num2;
    num3 *= num4;
    num5 *= num6;

    BOOST_TEST(num1 == v1 * v2);
    BOOST_TEST(num3 == v1 * v2);
    BOOST_TEST(num5 == v1 * v2);
}

// Product with INT_BITS >= 0 and FRAC_BITS >= 0 - Floating point values
   
const float float_test_array_1[] = { // Corner case
                                     0.0,
                                     // Random values
                                     941.38965, 569.4541, 200.26953, 792.88086, 260.83789, 511.37305, 253.94238, 976.95703, 138.08594, 981.42578,
                                     // Random negative values
                                     -532.04883, -384.37402, -300.85352, -454.04492, -893.36719, -378.08496, -426.15723, -365.25098, -837.59473, -765.40723};

const float float_test_array_2[] = { // Corner case
                                     0.0,
                                     // Random values
                                     939.69727, 51.454102, 309.43652, 842.66113, 923.36914, 479.94824, 313.87988, 67.871094, 1015.1016, 30.388672,
                                     // Random negative values
                                     -436.6709, -18.581055, -673.85547, -355.00781, -263.13379, -588.08789, -506.33789, -195.72559, -831.2832, -840.10938};

BOOST_DATA_TEST_CASE(Product_float_same_type, bdata::make(float_test_array_1) ^ bdata::make(float_test_array_2), v1, v2) {
    const float TOLERANCE = 1e-9;
    extended_fixed_point_t<16,32> num1(v1);
    extended_fixed_point_t<16,32> num2(v2);
    extended_fixed_point_t<16,32> res1;

    extended_fixed_point_t<16,32> num3(v1);
    extended_fixed_point_t<16,32> num4(v2);
    extended_fixed_point_t<16,32> res2;

    extended_fixed_point_t<32,32> num5(v1);
    extended_fixed_point_t<32,32> num6(v2);
    extended_fixed_point_t<32,32> res3;

    res1 = num1 * num2;
    res2 = num3 * num4;
    res3 = num5 * num6;

    BOOST_TEST(std::abs(res1.getValueF() - (v1 * v2)) < TOLERANCE);
    BOOST_TEST(std::abs(res2.getValueF() - (v1 * v2)) < TOLERANCE);
    BOOST_TEST(std::abs(res3.getValueF() - (v1 * v2)) < TOLERANCE);
    BOOST_TEST(std::abs((num1 * num2).getValueF() - (v1 * v2)) < TOLERANCE);
    BOOST_TEST(std::abs((num3 * num4).getValueF() - (v1 * v2)) < TOLERANCE);
    BOOST_TEST(std::abs((num5 * num6).getValueF() - (v1 * v2)) < TOLERANCE);
    
    num1 *= num2;
    num3 *= num4;
    num5 *= num6;

    BOOST_TEST(std::abs(num1.getValueF() - (v1 * v2)) < TOLERANCE);
    BOOST_TEST(std::abs(num3.getValueF() - (v1 * v2)) < TOLERANCE);
    BOOST_TEST(std::abs(num5.getValueF() - (v1 * v2)) < TOLERANCE);
}

// Product with INT_BITS >= 0 and FRAC_BITS <  0 - Integer values

const int32_t high_int_test_array_1[] = { // Corner case
                                          0, 261888,
                                          // Random values
                                          896, 336, 976, 432, 128, 768, 672, 496, 768, 176,
                                          // Random negative values
                                          -576, -976, -672, -176, -128, -992, -960, -256, -240, -768};

const int32_t high_int_test_array_2[] = { // Corner case
                                          261888, 0,
                                          // Random values
                                          880, 32, 784, 96, 32, 704, 640, 496, 736, 512,
                                          // Random negative values
                                          -560, -336, -432, -704, -592, -944, -960, -16, -384, -928};

BOOST_DATA_TEST_CASE(Product_high_integer_same_type, bdata::make(high_int_test_array_1) ^ bdata::make(high_int_test_array_2), v1, v2) {
    extended_fixed_point_t<32,-2> num1(v1);
    extended_fixed_point_t<32,-2> num2(v2);
    extended_fixed_point_t<32,-2> res1;

    extended_fixed_point_t<32,-4> num3(v1);
    extended_fixed_point_t<32,-4> num4(v2);
    extended_fixed_point_t<32,-4> res2;

    res1 = num1 * num2;
    res2 = num3 * num4;

    BOOST_TEST(res1 == v1 * v2);
    BOOST_TEST(res2 == v1 * v2);
    BOOST_TEST(num1 * num2 == v1 * v2);
    BOOST_TEST(num3 * num4 == v1 * v2);

    num1 *= num2;
    num3 *= num4;

    BOOST_TEST(num1 == v1 * v2);
    BOOST_TEST(num3 == v1 * v2);
}

// Product with INT_BITS < 0 and FRAC_BITS >= 0 - Floating point values
/*
const float low_float_test_array_1[] = { // Corner case
                                         0.0,
                                         // Random values
                                         0.0018081665, 0.0006980896, 0.00030136108, 0.0035057068, 0.0018920898, 0.0020866394, 0.00030517578, 0.0028762817, 7.2479248e-05, 0.003528595,
                                         // Random negative values
                                         -0.0022163391, -0.0027542114, -0.0011940002, -0.0034980774, -0.0015716553, -0.0028038025, -0.0013999939, -0.00059890747, -0.0021095276, -0.0022773743};

const float low_float_test_array_2[] = { // Corner case
                                         0.0,
                                         // Random values
                                         0.0030288696, 0.0016975403, 0.0014381409, 0.0012168884, 0.0019607544, 0.0028762817, 0.0036468506, 0.0010452271, 0.00042724609, 0.0016822815,
                                         // Random negative values
                                         -0.0019264221, -0.0015487671, -0.0015563965, -0.00078201294, -0.00059509277, -0.0035896301, -0.0019760132, -0.0018959045, -0.0020179749, -0.0038909912};
                                         
BOOST_DATA_TEST_CASE(Product_low_float_same_type, bdata::make(low_float_test_array_1) ^ bdata::make(low_float_test_array_2), v1, v2) {
    const float TOLERANCE = 1e-9;
    extended_fixed_point_t<-2, 34> num1(v1);
    extended_fixed_point_t<-2, 34> num2(v2);
    extended_fixed_point_t<-2, 34> res1;

    extended_fixed_point_t<-8, 34> num3(v1);
    extended_fixed_point_t<-8, 34> num4(v2);
    extended_fixed_point_t<-8, 34> res2;

    res1 = num1 * num2;
    res2 = num3 * num4;

    BOOST_TEST(std::abs(res1.getValueF() - (v1 * v2)) < TOLERANCE);
    BOOST_TEST(std::abs(res2.getValueF() - (v1 * v2)) < TOLERANCE);
    BOOST_TEST(std::abs((num1 * num2).getValueF() - (v1 * v2)) < TOLERANCE);
    BOOST_TEST(std::abs((num3 * num4).getValueF() - (v1 * v2)) < TOLERANCE);

    num1 *= num2;
    num3 *= num4;

    BOOST_TEST(std::abs(num1.getValueF() - (v1 * v2)) < TOLERANCE);
    BOOST_TEST(std::abs(num3.getValueF() - (v1 * v2)) < TOLERANCE);
}
*/
BOOST_AUTO_TEST_SUITE_END()