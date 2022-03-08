#ifndef GROUP_TEST
#define BOOST_TEST_MODULE Conversion
#include <boost/test/included/unit_test.hpp>
#endif

#include <boost/test/unit_test.hpp>
#include <boost/test/data/test_case.hpp>
#include <boost/mpl/list.hpp>
#include <boost/mpl/at.hpp>
#include <boost/mpl/int.hpp>

#include "extended_fixed_point.hpp"


using namespace boost::mpl;
namespace bdata = boost::unit_test::data;

/**
 * Test to verify the correct conversion among the various types of extended_fixed_point_t. 
 * Both integer and floating point values are tested.
 * In particular:
 * - From INT_BITS >= 0 , FRAC_BITS >= 0 to INT_BITS >= 0 , FRAC_BITS >= 0
 * - From INT_BITS >= 0 , FRAC_BITS <  0 to INT_BITS >= 0 , FRAC_BITS <  0
 * - From INT_BITS <  0 , FRAC_BITS >= 0 to INT_BITS <  0 , FRAC_BITS >= 0
 * 
 * - From INT_BITS >= 0 , FRAC_BITS >= 0 to INT_BITS >= 0 , FRAC_BITS <  0
 * - From INT_BITS >= 0 , FRAC_BITS >= 0 to INT_BITS <  0 , FRAC_BITS >= 0
 * - From INT_PART >= 0 , FRAC_PART <  0 to INT_PART >= 0 , FRAC_PART >= 0
 * - From INT_PART <  0 , FRAC_PART >= 0 to INT_PART >= 0 , FRAC_PART >= 0
 */

// Tolerance for floating point conversion
const double TOLERANCE = 1e-9;

BOOST_AUTO_TEST_SUITE(Conversion_test)

// From INT_PART >= 0, FRAC_PART >= 0 to INT_PART >= 0, FRAC_PART >= 0
// Test:
// 1) Reduced number of integer bits
// 2) Reduced number of fractional bits
// 3) Increased number of integer bits
// 4) Increased number of fractional bits
// 5) Reducing both
// 6) Increasing both

const float test_float_PPPP[] = {// Corner case   
                                0.0,
                                // Random values 
                                3.734375, 11.71875, 2.894531, 0.804688, 1.679688, 7.207031, 15.9375, 13.769531, 9.800781, 0.539062,
                                // Random negative values 
                                -3.27734, -6.41406, -13.2109, -4.70312, -10.3281, -6.58203, -6.25, -9.69922, -9.69531, -15.8438};

BOOST_DATA_TEST_CASE(Conversion_test_PPPP, bdata::make(test_float_PPPP), test_value) {
    extended_fixed_point_t<8,32> curr_efp(test_value);

    extended_fixed_point_t<4,32> new_efp_first = curr_efp.template convert<4,32>();
    extended_fixed_point_t<8,24> new_efp_second = curr_efp.template convert<8,24>();
    extended_fixed_point_t<12,32> new_efp_third = curr_efp.template convert<12,32>();
    extended_fixed_point_t<8,48> new_efp_fourth = curr_efp.template convert<8,48>();
    extended_fixed_point_t<4,24> new_efp_fifth = curr_efp.template convert<4,24>();
    extended_fixed_point_t<16,48> new_efp_sixth = curr_efp.template convert<16,48>();

    BOOST_TEST(std::abs(test_value - new_efp_first.getValueF()) < TOLERANCE);
    BOOST_TEST(std::abs(test_value - new_efp_second.getValueF()) < TOLERANCE);
    BOOST_TEST(std::abs(test_value - new_efp_third.getValueF()) < TOLERANCE);
    BOOST_TEST(std::abs(test_value - new_efp_fourth.getValueF()) < TOLERANCE);
    BOOST_TEST(std::abs(test_value - new_efp_fifth.getValueF()) < TOLERANCE);
    BOOST_TEST(std::abs(test_value - new_efp_sixth.getValueF()) < TOLERANCE);
}

// From INT_PART >= 0, FRAC_PART < 0 to INT_PART >= 0, FRAC_BITS < 0
// Test:
// 1) Reduced number of integer bits
// 2) Reduced number of fractional bits (less bits out of the range)
// 3) Increased number of integer bits
// 4) Increased number of fractional bits (more bits out of the range)
// 5) Reduced number ot integer bits and increased number of fractional bits  
// 6) Increasing number of interger bits and reduced number of fractional bits

// Only integer values considered, floating point cannot be represented

const int32_t test_int_PNPN[] = {// Corner case (11111111000000, 00000001000000)
                                 16320, 64,
                                 // Random values
                                 2112, 12096, 9152, 5440, 15296, 1088, 10624, 13184, 14400, 9536, 
                                 // Random negative values
                                 -7104, -7424, -12992, -7552, -15872, -14528, -14272, -2112, -15680, -5504};

BOOST_DATA_TEST_CASE(Conversion_test_PNPN, bdata::make(test_int_PNPN), test_value) {
    extended_fixed_point_t<12,-4> curr_efp(test_value);

    extended_fixed_point_t<10,-4> new_efp_first = curr_efp.template convert<10,-4>();
    extended_fixed_point_t<12,-2> new_efp_second = curr_efp.template convert<12,-2>();
    extended_fixed_point_t<16,-4> new_efp_third = curr_efp.template convert<16,-4>();
    extended_fixed_point_t<12,-6> new_efp_fourth = curr_efp.template convert<12,-6>();
    extended_fixed_point_t<10,-2> new_efp_fifth = curr_efp.template convert<10,-2>();
    extended_fixed_point_t<16,-6> new_efp_sixth = curr_efp.template convert<16,-6>();

    BOOST_TEST(test_value == new_efp_first.getValue()); 
    BOOST_TEST(test_value == new_efp_second.getValue()); 
    BOOST_TEST(test_value == new_efp_third.getValue()); 
    BOOST_TEST(test_value == new_efp_fourth.getValue()); 
    BOOST_TEST(test_value == new_efp_fifth.getValue()); 
    BOOST_TEST(test_value == new_efp_sixth.getValue()); 
}


// From INT_PART < 0, FRAC_PART >= 0 to INT_PART < 0, FRAC_PART >= 0
// Test:
// 1) Reduced number of integer bits (less bits out of the range)
// 2) Reduced number of fractional bits 
// 3) Increased number of integer bits (more bits out of the range)
// 4) Increased number of fractional bits
// 5) Increased number of integer bits and reduced number of fractional bits
// 6) Reduced number of integer bits and increased number of fractional bits

// Only floating point values considered, integer cannot be represented

const float test_float_NPNP[] = {// Random values  
                                0.0078125, 0.0117188, 0.0273438, 0.00195312, 0.00195312, 0.0214844, 0.0195312, 0.0253906, 0.00390625, 0.0195312,
                                // Random negative values 
                                -0.0078125, -0.0117188, -0.0273438, -0.00195312, -0.00195312, -0.0214844, -0.0195312, -0.0253906, -0.00390625, -0.0195312};

BOOST_DATA_TEST_CASE(Conversion_test_NPNP, bdata::make(test_float_NPNP), test_value) {
    extended_fixed_point_t<-4,54> curr_efp(test_value);

    extended_fixed_point_t<-2,54> new_efp_first = curr_efp.template convert<-2,54>();
    extended_fixed_point_t<-4,58> new_efp_second = curr_efp.template convert<-4,58>();
    extended_fixed_point_t<-6,54> new_efp_third = curr_efp.template convert<-6,54>();
    extended_fixed_point_t<-4,52> new_efp_fourth = curr_efp.template convert<-4,52>();
    extended_fixed_point_t<-6,52> new_efp_fifth = curr_efp.template convert<-6,52>();
    extended_fixed_point_t<-2,58> new_efp_sixth = curr_efp.template convert<-2,58>(); 

    BOOST_TEST(std::abs(test_value - new_efp_first.getValueF()) < TOLERANCE);
    BOOST_TEST(std::abs(test_value - new_efp_second.getValueF()) < TOLERANCE);
    BOOST_TEST(std::abs(test_value - new_efp_third.getValueF()) < TOLERANCE);
    BOOST_TEST(std::abs(test_value - new_efp_fourth.getValueF()) < TOLERANCE);
    BOOST_TEST(std::abs(test_value - new_efp_fifth.getValueF()) < TOLERANCE);
    BOOST_TEST(std::abs(test_value - new_efp_sixth.getValueF()) < TOLERANCE);
}

// From INT_PART >= 0, FRAC_PART >= 0 to INT_PART >= 0, FRAC_PART < 0
// Test:
// 1) Same number of integer bits
// 2) Increased number of integer bits
// 3) Reduced number of integer bits

// Only integer values considered, floating point cannot be represented

const int32_t test_int_PPPN[] = {// Corner case (11111111110000) (00000000010000)
                                 16368, 16,
                                 // Random values
                                 6064, 4672, 5536, 2960, 10512, 14864, 9984, 512, 1456, 11472, 
                                 // Random negative values 
                                 -208, -14272, -14928, -2368, -3120, -9072, -12368, -5264, -7104, -3776};

BOOST_DATA_TEST_CASE(Conversion_test_PPPN, bdata::make(test_int_PPPN), test_value) {
    extended_fixed_point_t<20,4> curr_efp(test_value);

    extended_fixed_point_t<20,-4> new_efp_first = curr_efp.template convert<20,-4>();
    extended_fixed_point_t<24,-4> new_efp_second = curr_efp.template convert<24,-4>();
    extended_fixed_point_t<16,-4> new_efp_third = curr_efp.template convert<16,-4>();

    BOOST_TEST(test_value == new_efp_first.getValue()); 
    BOOST_TEST(test_value == new_efp_second.getValue()); 
    BOOST_TEST(test_value == new_efp_third.getValue()); 
}

// From INT_PART >= 0, FRAC_PART >= 0 to INT_PART < 0, FRAC_PART >= 0
// Test:
// 1) Same number of fractional bits
// 2) Increased number of fractional bits
// 3) Reduced number of fractional bits

// Only floating point values considered, integer cannot be represented

const float test_float_PPNP[] = {// Random values  
                                 0.027759, 0.015993, 0.006777, 0.000627, 0.006584, 0.000767, 0.003325, 0.013619, 0.004326, 0.007141, 
                                 // Random negative values 
                                 -0.018909, -0.014751, -0.017151, -0.029552, -0.012933, -0.010327, -0.01746, -0.005895, -0.013037, -0.023421};

BOOST_DATA_TEST_CASE(Conversion_test_float_PPNP, bdata::make(test_float_PPNP), test_value) {
    extended_fixed_point_t<5,54> curr_efp(test_value);

    extended_fixed_point_t<-4,54> new_efp_first = curr_efp.template convert<-4,54>();
    extended_fixed_point_t<-4,58> new_efp_second = curr_efp.template convert<-4,58>();
    extended_fixed_point_t<-4,50> new_efp_third = curr_efp.template convert<-4,50>();

    BOOST_TEST(std::abs(test_value - new_efp_first.getValueF()) < TOLERANCE);
    BOOST_TEST(std::abs(test_value - new_efp_second.getValueF()) < TOLERANCE);
    BOOST_TEST(std::abs(test_value - new_efp_third.getValueF()) < TOLERANCE);
}
/*
// From INT_PART >= 0, FRAC_PART < 0 to INT_PART >= 0, FRAC_PART >= 0 - Integer values

typedef list<
    // Test maintaining the overall number of bits 
    list<integral_c<int16_t, 8>, integral_c<int16_t, -2>, integral_c<int16_t, 10>, integral_c<int16_t, 0>, integral_c<int32_t, 508>>,
    list<integral_c<int16_t, 16>, integral_c<int16_t, -4>, integral_c<int16_t, 20>, integral_c<int16_t, 0>, integral_c<int32_t, 524272>>,
    list<integral_c<int16_t, 32>, integral_c<int16_t, -12>, integral_c<int16_t, 44>, integral_c<int16_t, 0>, integral_c<int64_t, 4398046507008>>,
    // Test reducing the overall number of bits
    list<integral_c<int16_t, 8>, integral_c<int16_t, -2>, integral_c<int16_t, 6>, integral_c<int16_t, 0>, integral_c<int32_t, 60>>,
    list<integral_c<int16_t, 16>, integral_c<int16_t, -4>, integral_c<int16_t, 14>, integral_c<int16_t, 0>, integral_c<int32_t, 8176>>,
    list<integral_c<int16_t, 32>, integral_c<int16_t, -12>, integral_c<int16_t, 36>, integral_c<int16_t, 0>, integral_c<int32_t, 1073737728>>,
    // Test increasing the overall number of bits 
    list<integral_c<int16_t, 8>, integral_c<int16_t, -2>, integral_c<int16_t, 14>, integral_c<int16_t, 0>, integral_c<int32_t, 508>>,
    list<integral_c<int16_t, 16>, integral_c<int16_t, -4>, integral_c<int16_t, 24>, integral_c<int16_t, 0>, integral_c<int32_t, 524272>>,
    list<integral_c<int16_t, 32>, integral_c<int16_t, -6>, integral_c<int16_t, 46>, integral_c<int16_t, 0>, integral_c<int64_t, 4398046507008>>,
    // Test maintaining the overall number of bits with negative numbers
    list<integral_c<int16_t, 8>, integral_c<int16_t, -2>, integral_c<int16_t, 10>, integral_c<int16_t, 0>, integral_c<int32_t, -508>>,
    list<integral_c<int16_t, 16>, integral_c<int16_t, -4>, integral_c<int16_t, 20>, integral_c<int16_t, 0>, integral_c<int32_t, -524272>>,
    list<integral_c<int16_t, 32>, integral_c<int16_t, -12>, integral_c<int16_t, 44>, integral_c<int16_t, 0>, integral_c<int64_t, -4398046507008>>,
    // Test reducing the overall number of bits with negative numbers
    list<integral_c<int16_t, 8>, integral_c<int16_t, -2>, integral_c<int16_t, 6>, integral_c<int16_t, 0>, integral_c<int32_t, -60>>,
    list<integral_c<int16_t, 16>, integral_c<int16_t, -4>, integral_c<int16_t, 14>, integral_c<int16_t, 0>, integral_c<int32_t, -8176>>,
    list<integral_c<int16_t, 32>, integral_c<int16_t, -12>, integral_c<int16_t, 36>, integral_c<int16_t, 0>, integral_c<int32_t, -1073737728>>,
    // Test increasing the overall number of bits with negative numbers
    list<integral_c<int16_t, 8>, integral_c<int16_t, -2>, integral_c<int16_t, 14>, integral_c<int16_t, 0>, integral_c<int32_t, -508>>,
    list<integral_c<int16_t, 16>, integral_c<int16_t, -4>, integral_c<int16_t, 24>, integral_c<int16_t, 0>, integral_c<int32_t, -524272>>,
    list<integral_c<int16_t, 32>, integral_c<int16_t, -6>, integral_c<int16_t, 46>, integral_c<int16_t, 0>, integral_c<int64_t, -4398046507008>>
    > test_template_parameters_PNPP_conversion;

    BOOST_AUTO_TEST_CASE_TEMPLATE(Conversion_test_int_PNPP, T, test_template_parameters_PNPP_conversion) {
    typedef typename at<T, int_<0>>::type INT_BITS;
    typedef typename at<T, int_<1>>::type FRAC_BITS;
    typedef typename at<T, int_<2>>::type INT_BITS_NEW;
    typedef typename at<T, int_<3>>::type FRAC_BITS_NEW;
    typedef typename at<T, int_<4>>::type EFP_VALUE;

    extended_fixed_point_t<INT_BITS::value, FRAC_BITS::value> curr_efp(EFP_VALUE::value);
    extended_fixed_point_t<INT_BITS_NEW::value, FRAC_BITS_NEW::value> new_efp = curr_efp.template convert<INT_BITS_NEW::value, FRAC_BITS_NEW::value>();

    BOOST_TEST(curr_efp.getValue() == new_efp.getValue()); 
}

// From INT_PART >= 0, FRAC_PART < 0 to INT_PART >= 0, FRAC_PART >= 0 - Floating point values
// Not tested because floating point values are erased

// From INT_PART < 0, FRAC_PART >= 0 to INT_PART >= 0, FRAC_PART >= 0 - Integer values
// Not tested because integer values are erased

// From INT_PART < 0, FRAC_PART >= 0 to INT_PART >= 0, FRAC_PART >= 0 - Floating point values

const float test_float_NPPP_parameters[] = {// Corner case  
                                            0.0,
                                            // Random values  
                                            0.0078125, 0.0117188, 0.0273438, 0.00195312, 0.00195312, 0.0214844, 0.0195312, 0.0253906, 0.00390625, 0.0195312,
                                            // Random negative values 
                                            -0.0078125, -0.0117188, -0.0273438, -0.00195312, -0.00195312,- 0.0214844, -0.0195312, -0.0253906, -0.00390625, -0.0195312
                                            };

BOOST_DATA_TEST_CASE(Conversion_test_float_NPPP, bdata::make(test_float_NPPP_parameters), test_value) {
    const double TOLERANCE = 1e-9;
    extended_fixed_point_t<-2, 66> curr_efp(test_value);
    extended_fixed_point_t<2, 66> new_efp_first = curr_efp.template convert<2, 66>();

    BOOST_TEST(std::abs(test_value - new_efp_first.getValueFD()) < TOLERANCE);

    extended_fixed_point_t<4, 66> new_efp_second = curr_efp.template convert<4, 66>();

    BOOST_TEST(std::abs(test_value - new_efp_second.getValueFD()) < TOLERANCE);
}
*/
BOOST_AUTO_TEST_SUITE_END()