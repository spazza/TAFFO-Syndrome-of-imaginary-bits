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
                                     29641.436951, 55892.721527, 47866.858734, 38982.110138, 11995.195908, 65018.022354, 47592.883682, 11232.018158, 733.179504, 17111.686813,
                                     // Random negative values
                                     -29641.436951, -55892.721527, -47866.858734, -38982.110138, -11995.195908, -65018.022354, -47592.883682, -11232.018158, -733.179504, -17111.686813};

const float float_test_array_2[] = { // Corner case
                                     0.0,
                                     // Random values
                                     37758.218964, 11420.790100, 26159.802307, 12541.457916, 1756.990570, 23383.192383, 38275.851257, 59305.757507, 15270.562973, 14160.928177,
                                     // Random negative values
                                     -37758.218964, -11420.790100, -26159.802307, -12541.457916, -1756.990570, -23383.192383, -38275.851257, -59305.757507, -15270.562973, -14160.928177};

BOOST_DATA_TEST_CASE(Sum_float_same_type, bdata::make(float_test_array_1) ^ bdata::make(float_test_array_2), v1, v2) {
    const float TOLERANCE = 1e-9;
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

    BOOST_TEST(std::abs(res1.getValueF() - (v1 + v2)) < TOLERANCE);
    BOOST_TEST(std::abs(res2.getValueF() - (v1 + v2)) < TOLERANCE);
    BOOST_TEST(std::abs(res3.getValueF() - (v1 + v2)) < TOLERANCE);
    BOOST_TEST(std::abs((num1 + num2).getValueF() - (v1 + v2)) < TOLERANCE);
    BOOST_TEST(std::abs((num3 + num4).getValueF() - (v1 + v2)) < TOLERANCE);
    BOOST_TEST(std::abs((num5 + num6).getValueF() - (v1 + v2)) < TOLERANCE);
    
    num1 += num2;
    num3 += num4;
    num5 += num6;

    BOOST_TEST(std::abs(num1.getValueF() - (v1 + v2)) < TOLERANCE);
    BOOST_TEST(std::abs(num3.getValueF() - (v1 + v2)) < TOLERANCE);
    BOOST_TEST(std::abs(num5.getValueF() - (v1 + v2)) < TOLERANCE);
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

// Sum with INT_BITS < 0 and FRAC_BITS >= 0 - Floating point values

const float low_float_test_array_1[] = { // Corner case
                                         0.0,
                                         // Random values
                                         0.00233263, 0.000424266, 0.00323349, 0.000540853, 0.00162107, 0.00346237, 0.00191909, 0.00154817, 0.000719845, 0.00317454,
                                         // Random negative values
                                         -0.00233263, -0.000424266, -0.00323349, -0.000540853, -0.00162107, -0.00346237, -0.00191909, -0.00154817, -0.000719845, -0.00317454};

const float low_float_test_array_2[] = { // Corner case
                                         0.0,
                                         // Random values
                                         0.00338411, 0.00251168, 0.00122833, 0.00138295, 0.00355881, 0.00308478, 0.000267446, 0.000317514, 0.00158608, 0.0010035,
                                         // Random negative values
                                         -0.00338411, -0.00251168, -0.00122833, -0.00138295, -0.00355881, -0.00308478, -0.000267446, -0.000317514, -0.00158608, -0.0010035};
                                         
BOOST_DATA_TEST_CASE(Sum_low_float_same_type, bdata::make(low_float_test_array_1) ^ bdata::make(low_float_test_array_2), v1, v2) {
    const float TOLERANCE = 1e-9;
    extended_fixed_point_t<-2, 42> num1(v1);
    extended_fixed_point_t<-2, 42> num2(v2);
    extended_fixed_point_t<-2, 42> res1;

    extended_fixed_point_t<-8, 42> num3(v1);
    extended_fixed_point_t<-8, 42> num4(v2);
    extended_fixed_point_t<-8, 42> res2;

    res1 = num1 + num2;
    res2 = num3 + num4;

    BOOST_TEST(std::abs(res1.getValueF() - (v1 + v2)) < TOLERANCE);
    BOOST_TEST(std::abs(res2.getValueF() - (v1 + v2)) < TOLERANCE);
    BOOST_TEST(std::abs((num1 + num2).getValueF() - (v1 + v2)) < TOLERANCE);
    BOOST_TEST(std::abs((num3 + num4).getValueF() - (v1 + v2)) < TOLERANCE);

    num1 += num2;
    num3 += num4;

    BOOST_TEST(std::abs(num1.getValueF() - (v1 + v2)) < TOLERANCE);
    BOOST_TEST(std::abs(num3.getValueF() - (v1 + v2)) < TOLERANCE);
}

// Sum between a number with INT_BITS >= 0, FRAC_BITS >= 0 and another with INT_BITS >= 0, FRAC_BITS >= 0 - Integer values

const int32_t different_type_int_test_array_1[] = { // Positive values
                                                    0, 6539, 23720, 29951, 7343, 3527, 8895, 6144, 24789, 25170,
                                                    // Negative values
                                                    -38285, -42917, -7030, -17179, -22917, -9292, -19520, -9180, -53449, -61040};

const int32_t different_type_int_test_array_2[] = { // Positive values
                                                    2982, 17416, 29704, 22711, 13156, 1758, 17781, 162, 26711, 26674,
                                                    // Negative values
                                                    -24900, -17752, -8720, -51583, -6988, -15943, -39551, -60935, -21091, -4761};

BOOST_DATA_TEST_CASE(Sum_integer_different_type, bdata::make(different_type_int_test_array_1) ^ bdata::make(different_type_int_test_array_2), v1, v2) {
    extended_fixed_point_t<16, 4> num1(v1);
    extended_fixed_point_t<16, 8> num2(v2);
    extended_fixed_point_t<16, 8> res1;

    extended_fixed_point_t<32, 0> num3(v1);
    extended_fixed_point_t<24, 8> num4(v2);
    extended_fixed_point_t<24, 4> res2;

    res1 = num1 + num2;
    res2 = num3 + num4;

    BOOST_TEST(res1 == v1 + v2);
    BOOST_TEST(res2 == v1 + v2);

    num1 += num2;
    num3 += num4;

    BOOST_TEST(num1 == v1 + v2);
    BOOST_TEST(num3 == v1 + v2);    
}

// Sum between a number with INT_BITS >= 0, FRAC_BITS >= 0 and another with INT_BITS >= 0, FRAC_BITS >= 0 - Floating point values

const float different_type_float_test_array_1[] = { // Positive values
                                                    28943.57671, 13293.91522, 51151.68497, 29353.87749, 27458.00121, 26806.39406, 24718.05527, 63898.77626, 30849.8351, 34748.95351,
                                                    // Negative values
                                                    -17731.14621, -23049.435, -23840.02747, -30928.57574, -32726.18082, -17640.66788, -9524.529449, -22460.90421, -24020.01379, -9128.785645};

const float different_type_float_test_array_2[] = { // Positive values
                                                    34033.8228, 58812.00446, 24647.93681, 54423.72485, 43091.83455, 1541.748749, 18559.66418, 31639.91714, 9788.343292, 18997.3071,
                                                    // Negative values
                                                    -11773.49783, -15566.66531, -18145.41245, -32373.79138, -6860.494568, -20314.31824, -30073.85803, -1935.976898, -5002.843353, -16633.82974};

BOOST_DATA_TEST_CASE(Sum_float_different_type, bdata::make(different_type_float_test_array_1) ^ bdata::make(different_type_float_test_array_2), v1, v2) {
    const float TOLERANCE = 1e-9;
    extended_fixed_point_t<16, 32> num1(v1);
    extended_fixed_point_t<16, 24> num2(v2);
    extended_fixed_point_t<16, 24> res1;

    extended_fixed_point_t<24, 32> num3(v1);
    extended_fixed_point_t<24, 16> num4(v2);
    extended_fixed_point_t<24, 16> res2;

    res1 = num1 + num2;
    res2 = num3 + num4;

    BOOST_TEST(std::abs(res1.getValueF() - (v1 + v2)) < TOLERANCE);
    BOOST_TEST(std::abs(res2.getValueF() - (v1 + v2)) < TOLERANCE);
    BOOST_TEST(std::abs((num1 + num2).getValueF() - (v1 + v2)) < TOLERANCE);
    BOOST_TEST(std::abs((num3 + num4).getValueF() - (v1 + v2)) < TOLERANCE);

    num1 += num2;
    num3 += num4;

    BOOST_TEST(num1.getValueF() - (v1 + v2) < TOLERANCE);
    BOOST_TEST(num3.getValueF() - (v1 + v2) < TOLERANCE);
}

// Sum between a number with INT_BITS >= 0, FRAC_BITS <  0 and another with INT_BITS >= 0, FRAC_BITS <  0 - Integer values

const int32_t different_type_high_integer_test_array_1[] = { // Positive values
                                                             8704, 16128, 3072, 9472, 3840, 2816, 13312, 13056, 3840, 16384,
                                                             // Negative values
                                                             -13312, -11520, -30976, -15360, -12800, -2816, -9216, -6912, -9728, -27648};

const int32_t different_type_high_integer_test_array_2[] = { // Positive values
                                                             9216, 1280, 3840, 18432, 2048, 6912, 10752, 17920, 11520, 6912,
                                                             // Negative values
                                                             -1536, -5120, -512, -3328, -12288, -7936, -6400, -9728, -2048, -3328};

BOOST_DATA_TEST_CASE(Sum_high_integer_different_type, bdata::make(different_type_high_integer_test_array_1) ^ bdata::make(different_type_high_integer_test_array_2), v1, v2) {
    extended_fixed_point_t<16, -4> num1(v1);
    extended_fixed_point_t<16, -8> num2(v2);
    extended_fixed_point_t<16, -8> res1;

    extended_fixed_point_t<32, 0> num3(v1);
    extended_fixed_point_t<24, -8> num4(v2);
    extended_fixed_point_t<24, -4> res2;

    res1 = num1 + num2;
    res2 = num3 + num4;

    BOOST_TEST(res1 == v1 + v2);
    BOOST_TEST(res2 == v1 + v2);

    num1 += num2;
    num3 += num4;

    BOOST_TEST(num1 == v1 + v2);
    BOOST_TEST(num3 == v1 + v2);   
}

// Sum between a number with INT_BITS < 0, FRAC_BITS >= 0 and another with INT_BITS < 0, FRAC_BITS >= 0 - Floating point values

const float different_type_low_float_test_array_1[] = { // Positive values
                                                        0.0009196598548, 0.002191785257, 0.001527325716, 0.003268658649, 0.002390918089, 0.0003982954659, 0.002827232005, 0.0005114038941, 0.001708508935, 0.001964675961,
                                                        // Negative values
                                                        -0.001164001646, -9.913463145e-05, -0.003453463782, -0.0001479478087, -0.002259602305, -0.003225600347, -0.0006870091893, -0.003518653568, -0.002796453657, -0.002394162118};

const float different_type_low_float_test_array_2[] = { // Positive values
                                                        0.001780493418, 6.480142474e-06, 0.001148348441, 0.002013686346, 0.0002156898845, 0.001779259415, 0.001369557111, 0.001719373511, 0.0007606700528, 0.001010248205,
                                                        // Negative values
                                                        -0.0008983036969, -0.001716916449, -0.003097339766, -0.0001312817913, -0.0004533648025, -0.00185032608, -0.0005824391264, -0.001216536155, -0.002187125152, -0.003449395765};

BOOST_DATA_TEST_CASE(Sum_low_float_different_type, bdata::make(different_type_low_float_test_array_1) ^ bdata::make(different_type_low_float_test_array_2), v1, v2) {
    const float TOLERANCE = 1e-9;
    extended_fixed_point_t<-4, 48> num1(v1);
    extended_fixed_point_t<-8, 48> num2(v2);
    extended_fixed_point_t<-8, 48> res1;

    extended_fixed_point_t<-8, 48> num3(v1);
    extended_fixed_point_t<-4, 48> num4(v2);
    extended_fixed_point_t<-6, 48> res2;

    res1 = num1 + num2;
    res2 = num3 + num4;

    BOOST_TEST(std::abs(res1.getValueF() - (v1 + v2)) < TOLERANCE);
    BOOST_TEST(std::abs(res2.getValueF() - (v1 + v2)) < TOLERANCE);
    BOOST_TEST(std::abs((num1 + num2).getValueF() - (v1 + v2)) < TOLERANCE);
    BOOST_TEST(std::abs((num3 + num4).getValueF() - (v1 + v2)) < TOLERANCE);

    num1 += num2;
    num3 += num4;

    BOOST_TEST(std::abs(num1.getValueF() - (v1 + v2)) < TOLERANCE);
    BOOST_TEST(std::abs(num3.getValueF() - (v1 + v2)) < TOLERANCE);
}

// Sum between a number with INT_BITS >= 0, FRAC_BITS >= 0 and another with INT_BITS >= 0, FRAC_BITS < 0 - Integer values
// Using previous values as input for the test

BOOST_DATA_TEST_CASE(Sum_high_integer_and_normal_different_type, bdata::make(different_type_high_integer_test_array_1) ^ bdata::make(different_type_high_integer_test_array_2), v1, v2) {
    extended_fixed_point_t<20, 4> num1(v1);
    extended_fixed_point_t<20, -8> num2(v2);
    extended_fixed_point_t<20, -8> res1;

    extended_fixed_point_t<32, -8> num3(v1);
    extended_fixed_point_t<24, 8> num4(v2);
    extended_fixed_point_t<24, 4> res2;

    res1 = num1 + num2;
    res2 = num3 + num4;

    BOOST_TEST(res1 == v1 + v2);
    BOOST_TEST(res2 == v1 + v2);

    num1 += num2;
    num3 += num4;

    BOOST_TEST(num1 == v1 + v2);
    BOOST_TEST(num3 == v1 + v2);   
}

// Sum between a number with INT_BITS >= 0, FRAC_BITS >= 0 and another with INT_BITS < 0, FRAC_BITS >= 0 - Floating point values
// Using previous values as input for the test
/*
BOOST_DATA_TEST_CASE(Sum_low_float_and_normal_different_type, bdata::make(different_type_low_float_test_array_1) ^ bdata::make(different_type_low_float_test_array_2), v1, v2) {
    const float TOLERANCE = 1e-9;
    extended_fixed_point_t<-4, 48> num1(v1);
    extended_fixed_point_t<2, 48> num2(v2);
    extended_fixed_point_t<2, 48> res1;

    extended_fixed_point_t<2, 48> num3(v1);
    extended_fixed_point_t<-2, 48> num4(v2);
    extended_fixed_point_t<-2, 48> res2;

    res1 = num1 + num2;
    res2 = num3 + num4;

    BOOST_TEST(std::abs(res1.getValueF() - (v1 + v2)) < TOLERANCE);
    BOOST_TEST(std::abs(res2.getValueF() - (v1 + v2)) < TOLERANCE);
    
    BOOST_TEST(std::abs((num1 + num2).getValueF() - (v1 + v2)) < TOLERANCE);
    BOOST_TEST(std::abs((num3 + num4).getValueF() - (v1 + v2)) < TOLERANCE);

    num1 += num2;
    num3 += num4;

    BOOST_TEST(std::abs(num1.getValueF() - (v1 + v2)) < TOLERANCE);
    BOOST_TEST(std::abs(num3.getValueF() - (v1 + v2)) < TOLERANCE);
}*/

BOOST_AUTO_TEST_SUITE_END()